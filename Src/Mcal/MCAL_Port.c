/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief
 *
 *      \details
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "MCAL_Port.h"


/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
uint32 portBase[6]={
	0x40058000UL,0x40059000UL,0x4005A000UL,0x4005B000UL,0x4005C000UL,0x4005D000UL};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void MCAL_Port_Init(const Port_ConfigType * ConfigPtr)
{
/*pin number is in config file*/
	for(uint8 i =0;i<48;i++){
		uint32 port;
		port = i  / 8;
		uint32 pin=i%8;
		/*enable the clock in the rcgcgpio register per port */
			volatile uint32 * rcgcgpio = (volatile uint32 *)0x400FE000UL;
			rcgcgpio = (volatile uint32 *)((1UL << port) | (uint32)rcgcgpio);
		/*set the direction of the pin in gpiodir register -- 1 out , 0 in*/
			volatile uint32 * gpiodir =(volatile uint32 *) (0x400UL | portBase[port]);
			if(ConfigPtr[i].Port_PinDirectionType){
				gpiodir = (volatile uint32 *)((uint32)gpiodir |(1 << pin)) ;
			}else{
				gpiodir =(volatile uint32 *)((uint32)gpiodir & !(1 << pin)) ;
			}

		/*gpioafsel each bit as gpio or alternate pin -- 0 gpio ,1 alt fn */
			volatile uint32 * gpioafsel = (volatile uint32 *) (0x420UL | portBase[port]);
			if(ConfigPtr[i].Port_PinModeType == GPIO_PORT_PIN_MODE_ALT){
				gpioafsel = (volatile uint32 *)((uint32)gpioafsel | (1 << pin));
			}else{
				gpioafsel = (volatile uint32 *)((uint32)gpioafsel & !(1 << pin));
			}

		/*set drive strength for each pin in gpior2r/r4r/r8r  -- r2r is default for all pins-- */
			volatile uint32 * gpior2r = (volatile uint32 *) (0x500UL| portBase[port]);
			volatile uint32 * gpior4r = (volatile uint32 *) (0x504UL| portBase[port]);
			volatile uint32 * gpior8r = (volatile uint32 *) (0x508UL| portBase[port]);

			if(ConfigPtr[i].Port_PinOutputCurrentType == PORT_PIN_OUTPUT_CURRENT_4){
				gpior2r = (uint32 *)((uint32 )gpior2r & !(1 << pin));
				gpior4r =(uint32 *)((uint32 ) gpior4r | (1 << pin));
			}else if(ConfigPtr[i].Port_PinOutputCurrentType == PORT_PIN_OUTPUT_CURRENT_8){
				gpior2r = (uint32 *)((uint32 )gpior2r & !(1 << pin));
				gpior8r =(uint32 *)((uint32 ) gpior8r | (1 << pin));
			}

		/*each pin as pull up down opendrain in gpiopur/pdr/odr --  0 disable , 1 enable*/
			volatile uint32 * gpioodr = (volatile uint32 *)(0x50CUL | portBase[port]);
			volatile uint32 * gpiopur = (volatile uint32 *)(0x510UL | portBase[port]);
			volatile uint32 * gpiopdr = (volatile uint32 *)(0x514UL | portBase[port]);

			if(ConfigPtr[i].Port_PinInternalAttachType == PORT_PIN_INTERNAL_ATTACH_PULL_UP){
				gpiopur =(uint32 *)((uint32 )gpiopur | (1 << pin));
				gpioodr =(uint32 *)((uint32 ) gpioodr & !(1 << pin));
				gpiopdr =(uint32 *)((uint32 ) gpiopdr & !(1 << pin));
			}else if(ConfigPtr[i].Port_PinInternalAttachType == PORT_PIN_INTERNAL_ATTACH_PULL_DOWN){
				gpiopur =(uint32 *)((uint32 )gpiopur & !(1 << pin));
				gpioodr =(uint32 *)((uint32 ) gpioodr & !(1 << pin));
				gpiopdr = (uint32 *)((uint32 ) gpiopdr | (1 << pin));
			}else if(ConfigPtr[i].Port_PinInternalAttachType == PORT_PIN_INTERNAL_ATTACH_OPEN_DRAIN){
				gpiopur =(uint32 *)((uint32 )gpiopur & !(1 << pin));
				gpioodr =(uint32 *)((uint32 )gpioodr |(1 << pin));
				gpiopdr =(uint32 *)((uint32 ) gpiopdr &!(1 << pin));
			}
		/*digital or analog in gpioden or gpioamsel -- 0 disable , 1 enable*/
			volatile uint32 * gpioden = (volatile uint32 * )(0x51CUL |  portBase[port]);
			if(ConfigPtr[i].Port_PinModeType == GPIO_PORT_PIN_MODE_GPIO){
				gpioden =(uint32 *)((uint32 ) gpioden | (1 << pin));
			}
		/*interrupts and jtag XXX */
	}


}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
