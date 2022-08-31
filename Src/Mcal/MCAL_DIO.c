/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  MCAL_DIO.c
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
#include "MCAL_DIO.h"


/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
uint32 pv_portBase[6]={
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
Dio_LevelType Dio_Read_Channel(Dio_ChannelType ChannelId)
{
	uint32 port;
	port= (  ChannelId / 8);
	uint32 pin = (ChannelId % 8 );
	uint32  gpiodata = 0x000UL | pv_portBase[port];
	uint32  mask = (1 << (pin + 2));
	uint32  value = *((volatile uint32 * )(gpiodata | mask));
	if(value){
		return DIO_LEVEL_HIGH;
	}
	return DIO_LEVEL_LOW;

}
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
void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level)
{
	uint32 port;
	port=ChannelId/8;
	uint32 pin=ChannelId%8;
	uint32  gpiodata = 0x000UL | pv_portBase[port];
	uint32  mask = (1 << (pin + 2));
	volatile uint32 *  value = (volatile uint32 * )(gpiodata |mask);
	*value = Level;

}
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
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId )
{
	uint32 port;
		port=PortId;
		uint32  gpiodata = 0x000UL | pv_portBase[port];
		uint32  mask = (0xFFUL <<  2);
		uint32  value = *((volatile uint32 *)(gpiodata |mask));
		return value;
}
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
void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)
{
	uint32 port;
		port=PortId;
		uint32  gpiodata = 0x000UL | pv_portBase[port];
		uint32  mask = (0xFFUL <<  2);
		volatile uint32 *  value = (volatile uint32 *)(gpiodata |mask);
		*value = Level;

}
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
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	uint32 port;
	port = ( ChannelId / 8);
	uint32 pin=ChannelId%8;
	uint32  gpiodata = 0x000UL | pv_portBase[port];
	uint32  mask = (1 << (pin + 2));
	uint32  value = *((volatile uint32 *)(gpiodata |mask));
	if(value){
		volatile uint32 * temp = (volatile uint32 * )((gpiodata | mask) & ! (1 << (pin + 2)));
		return DIO_LEVEL_HIGH;
	}
	volatile uint32 * temp = (volatile uint32 * )((gpiodata | mask) | (1 << (pin + 2)));
	return DIO_LEVEL_LOW;

}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
