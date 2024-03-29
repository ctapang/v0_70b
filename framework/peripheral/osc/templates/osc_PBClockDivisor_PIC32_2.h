/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_PBClockDivisor_PIC32_2.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PBClockDivisor
    and its Variant : PIC32_2
    For following APIs :
        PLIB_OSC_ExistsPBClockDivisor
        PLIB_OSC_PBClockDivisorGet
        PLIB_OSC_PBClockDivisorSet

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/

//DOM-IGNORE-END

#ifndef _OSC_PBCLOCKDIVISOR_PIC32_2_H
#define _OSC_PBCLOCKDIVISOR_PIC32_2_H


// *****************************************************************************
/* Oscillator Peripheral Bus Clock Divisor Value Type

  Summary:
    Type of the oscillator PB Clock divisor value.

  Description:
    This macro defines the type of the oscillator PB Clock divisor value.

  Remarks:
    None
*/

#define OSC_PB_CLOCK_DIV_TYPE						SFR_TYPE

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_OSC_PB_DIVISOR_1_VREG(index)
    _OSC_OSC_PB_DIVISOR_2_VREG(index)
    _OSC_OSC_PB_DIVISOR_3_VREG(index)
    _OSC_OSC_PB_DIVISOR_4_VREG(index)
    _OSC_OSC_PB_DIVISOR_5_VREG(index)
    _OSC_OSC_PB_DIVISOR_7_VREG(index)
    _OSC_OSC_PB_DIVISOR_8_VREG(index)
    _OSC_OSC_REGISTER_LOCK_VREG(index)

  MASKs: 
    _OSC_OSC_PB_DIVISOR_1_MASK(index)
    _OSC_OSC_PB_DIVISOR_2_MASK(index)
    _OSC_OSC_PB_DIVISOR_3_MASK(index)
    _OSC_OSC_PB_DIVISOR_4_MASK(index)
    _OSC_OSC_PB_DIVISOR_5_MASK(index)
    _OSC_OSC_PB_DIVISOR_7_MASK(index)
    _OSC_OSC_PB_DIVISOR_8_MASK(index)
    _OSC_OSC_REGISTER_LOCK_MASK(index)

  POSs: 
    _OSC_OSC_PB_DIVISOR_1_POS(index)
    _OSC_OSC_PB_DIVISOR_2_POS(index)
    _OSC_OSC_PB_DIVISOR_3_POS(index)
    _OSC_OSC_PB_DIVISOR_4_POS(index)
    _OSC_OSC_PB_DIVISOR_5_POS(index)
    _OSC_OSC_PB_DIVISOR_7_POS(index)
    _OSC_OSC_PB_DIVISOR_8_POS(index)
    _OSC_OSC_REGISTER_LOCK_POS(index)

  LENs: 
    _OSC_OSC_PB_DIVISOR_1_LEN(index)
    _OSC_OSC_PB_DIVISOR_2_LEN(index)
    _OSC_OSC_PB_DIVISOR_3_LEN(index)
    _OSC_OSC_PB_DIVISOR_4_LEN(index)
    _OSC_OSC_PB_DIVISOR_5_LEN(index)
    _OSC_OSC_PB_DIVISOR_7_LEN(index)
    _OSC_OSC_PB_DIVISOR_8_LEN(index)
    _OSC_OSC_REGISTER_LOCK_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsPBClockDivisor_PIC32_2

  Summary:
    Implements PIC32_2 variant of PLIB_OSC_ExistsPBClockDivisor

  Description:
    This template implements the PIC32_2 variant of the PLIB_OSC_ExistsPBClockDivisor function.
*/

PLIB_TEMPLATE bool OSC_ExistsPBClockDivisor_PIC32_2( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_PBClockDivisorGet_PIC32_2

  Summary:
    Implements PIC32_2 variant of PLIB_OSC_PBClockDivisorGet 

  Description:
    This template implements the PIC32_2 variant of the PLIB_OSC_PBClockDivisorGet function.
*/

PLIB_TEMPLATE OSC_PB_CLOCK_DIV_TYPE OSC_PBClockDivisorGet_PIC32_2( OSC_MODULE_ID index , OSC_PERIPHERAL_BUS peripheralBusNumber )
{
    switch(peripheralBusNumber)
	{
	case OSC_PERIPHERAL_BUS_1:
		return ( _SFR_FIELD_READ( _OSC_OSC_PB_DIVISOR_1_VREG(index),
                           		  _OSC_OSC_PB_DIVISOR_1_MASK(index),
                           		  _OSC_OSC_PB_DIVISOR_1_POS(index) ) + 1);
	case OSC_PERIPHERAL_BUS_2:
		return ( _SFR_FIELD_READ(	_OSC_OSC_PB_DIVISOR_2_VREG(index),
                           		_OSC_OSC_PB_DIVISOR_2_MASK(index),
                           		_OSC_OSC_PB_DIVISOR_2_POS(index) ) + 1);
	case OSC_PERIPHERAL_BUS_3:
		return ( _SFR_FIELD_READ(	_OSC_OSC_PB_DIVISOR_3_VREG(index),
                           		_OSC_OSC_PB_DIVISOR_3_MASK(index),
                           		_OSC_OSC_PB_DIVISOR_3_POS(index) ) + 1);
	case OSC_PERIPHERAL_BUS_4:
		return ( _SFR_FIELD_READ(	_OSC_OSC_PB_DIVISOR_4_VREG(index),
                           		_OSC_OSC_PB_DIVISOR_4_MASK(index),
                           		_OSC_OSC_PB_DIVISOR_4_POS(index) ) + 1);
	case OSC_PERIPHERAL_BUS_5:
		return ( _SFR_FIELD_READ(	_OSC_OSC_PB_DIVISOR_5_VREG(index),
                           		_OSC_OSC_PB_DIVISOR_5_MASK(index),
                           		_OSC_OSC_PB_DIVISOR_5_POS(index) ) + 1);
	case OSC_PERIPHERAL_BUS_7:
		return ( _SFR_FIELD_READ(	_OSC_OSC_PB_DIVISOR_7_VREG(index),
                           		_OSC_OSC_PB_DIVISOR_7_MASK(index),
                           		_OSC_OSC_PB_DIVISOR_7_POS(index) ) + 1);
	case OSC_PERIPHERAL_BUS_8:
		return ( _SFR_FIELD_READ(	_OSC_OSC_PB_DIVISOR_8_VREG(index),
                           		_OSC_OSC_PB_DIVISOR_8_MASK(index),
                           		_OSC_OSC_PB_DIVISOR_8_POS(index) ) + 1);

	}
}


//******************************************************************************
/* Function :  OSC_PBClockDivisorSet_PIC32_2

  Summary:
    Implements PIC32_2 variant of PLIB_OSC_PBClockDivisorSet 

  Description:
    This template implements the PIC32_2 variant of the PLIB_OSC_PBClockDivisorSet function.
*/

PLIB_TEMPLATE void OSC_PBClockDivisorSet_PIC32_2( OSC_MODULE_ID index , OSC_PERIPHERAL_BUS peripheralBusNumber , OSC_PB_CLOCK_DIV_TYPE peripheralBusClkDiv )
{
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0xAA996655);
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0x556699AA);

	if ( peripheralBusClkDiv < 129)
	{
		switch(peripheralBusNumber)
		{
		case OSC_PERIPHERAL_BUS_1: 	
			_SFR_FIELD_WRITE(_OSC_OSC_PB_DIVISOR_1_VREG(index),
							 _OSC_OSC_PB_DIVISOR_1_MASK(index),
							 _OSC_OSC_PB_DIVISOR_1_POS(index) ,
							 (peripheralBusClkDiv - 1) );
			break;
			
		case OSC_PERIPHERAL_BUS_2: 	
			_SFR_FIELD_WRITE(_OSC_OSC_PB_DIVISOR_2_VREG(index),
							 _OSC_OSC_PB_DIVISOR_2_MASK(index),
							 _OSC_OSC_PB_DIVISOR_2_POS(index) ,
							 (peripheralBusClkDiv - 1) );
			break;
			
		case OSC_PERIPHERAL_BUS_3: 	
			_SFR_FIELD_WRITE(_OSC_OSC_PB_DIVISOR_3_VREG(index),
							 _OSC_OSC_PB_DIVISOR_3_MASK(index),
							 _OSC_OSC_PB_DIVISOR_3_POS(index) ,
							 (peripheralBusClkDiv - 1) );
			break;
			
		case OSC_PERIPHERAL_BUS_4: 	
			_SFR_FIELD_WRITE(_OSC_OSC_PB_DIVISOR_4_VREG(index),
							 _OSC_OSC_PB_DIVISOR_4_MASK(index),
							 _OSC_OSC_PB_DIVISOR_4_POS(index) ,
							 (peripheralBusClkDiv - 1) );
			break;
			
		case OSC_PERIPHERAL_BUS_5: 	
			_SFR_FIELD_WRITE(_OSC_OSC_PB_DIVISOR_5_VREG(index),
							 _OSC_OSC_PB_DIVISOR_5_MASK(index),
							 _OSC_OSC_PB_DIVISOR_5_POS(index) ,
							 (peripheralBusClkDiv - 1) );
			break;
			
		case OSC_PERIPHERAL_BUS_7: 	
			_SFR_FIELD_WRITE(_OSC_OSC_PB_DIVISOR_7_VREG(index),
							 _OSC_OSC_PB_DIVISOR_7_MASK(index),
							 _OSC_OSC_PB_DIVISOR_7_POS(index) ,
							 (peripheralBusClkDiv - 1) );
			break;
			
		case OSC_PERIPHERAL_BUS_8: 	
			_SFR_FIELD_WRITE(_OSC_OSC_PB_DIVISOR_8_VREG(index),
							 _OSC_OSC_PB_DIVISOR_8_MASK(index),
							 _OSC_OSC_PB_DIVISOR_8_POS(index) ,
							 (peripheralBusClkDiv - 1) );
			break;
		}
	}
	else
	{
		PLIB_ASSERT(false, "Given PB Divisor value is not supported for the selected device");
	}
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
}


#endif /*_OSC_PBCLOCKDIVISOR_PIC32_2_H*/

/******************************************************************************
 End of File
*/

