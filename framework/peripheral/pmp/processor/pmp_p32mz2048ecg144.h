/* Created by plibgen $Revision: 1.29 $ */

#ifndef _PMP_P32MZ2048ECG144_H
#define _PMP_P32MZ2048ECG144_H

/* Section 1 - Enumerate instances, define constants, VREGs */

#include <xc.h>
#include <stdbool.h>

#include "peripheral/peripheral_common_32bit.h"

/* Default definition used for all API dispatch functions */
#ifndef INLINE_API
    #define INLINE_API extern inline
#endif

/* Default definition used for all other functions */
#ifndef INLINE
    #define INLINE extern inline
#endif

typedef enum {

    PMP_ID_0 = 0,
    PMP_NUMBER_OF_MODULES

} PMP_MODULE_ID;

typedef enum {

    PMP_LEGACY_SLAVE = 0x00,
    PMP_ENHANCED_SLAVE = 0x01,
    PMP_MASTER_READ_WRITE_STROBES_INDEPENDENT = 0x2,
    PMP_MASTER_READ_WRITE_STROBES_MULTIPLEXED = 0x3

} PMP_OPERATION_MODE;

typedef enum {

    PMP_MUX_LINES_16_ADDRESS_16_DATA = 0x3,
    PMP_MUX_LINES_16_ADDRESS_8_DATA = 0x2,
    PMP_MUX_LINES_8_ADDRESS_8_DATA = 0x1,
    PMP_MUX_NONE = 0x0

} PMP_MUX_MODE;

typedef enum {

    PMP_BUFFERS_AUTO_INCREMENT = 0x3,
    PMP_ADDRESS_AUTO_DECREMENT = 0x2,
    PMP_ADDRESS_AUTO_INCREMENT = 0x1,
    PMP_ADDRESS_INCREMENT_DECREMENT_DISABLE = 0x0

} PMP_INCREMENT_MODE;

typedef enum {

    PMP_ADDRESS_LATCH_HIGH = 0x2,
    PMP_ADDRESS_LATCH_LOW = 0x1

} PMP_ADDRESS_LATCH;

typedef enum {

    PMP_DATA_WAIT_FOUR = 0x3,
    PMP_DATA_WAIT_THREE = 0x2,
    PMP_DATA_WAIT_TWO = 0x1,
    PMP_DATA_WAIT_ONE = 0x0

} PMP_DATA_WAIT_STATES;

typedef enum {

    PMP_STROBE_WAIT_1 = 0x0,
    PMP_STROBE_WAIT_2 = 0x1,
    PMP_STROBE_WAIT_3 = 0x2,
    PMP_STROBE_WAIT_4 = 0x3,
    PMP_STROBE_WAIT_5 = 0x4,
    PMP_STROBE_WAIT_6 = 0x5,
    PMP_STROBE_WAIT_7 = 0x6,
    PMP_STROBE_WAIT_8 = 0x7,
    PMP_STROBE_WAIT_9 = 0x8,
    PMP_STROBE_WAIT_10 = 0x9,
    PMP_STROBE_WAIT_11 = 0xa,
    PMP_STROBE_WAIT_12 = 0xb,
    PMP_STROBE_WAIT_13 = 0xc,
    PMP_STROBE_WAIT_14 = 0xd,
    PMP_STROBE_WAIT_15 = 0xe,
    PMP_STROBE_WAIT_16 = 0xf

} PMP_STROBE_WAIT_STATES;

typedef enum {

    PMP_DATA_HOLD_1 = 0x0,
    PMP_DATA_HOLD_2 = 0x1,
    PMP_DATA_HOLD_3 = 0x2,
    PMP_DATA_HOLD_4 = 0x3

} PMP_DATA_HOLD_STATES;

typedef enum {

    PMP_INTERRUPT_NONE = 0x0,
    PMP_INTERRUPT_EVERY_RW_CYCLE = 0x1,
    PMP_INTERRUPT_BUFFER_3_IS_ACCESSED = 0x2

} PMP_INTERRUPT_MODE;

typedef enum {

    PMP_DATA_SIZE_8_BITS = 0x0,
    PMP_DATA_SIZE_16_BITS = 0x1

} PMP_DATA_SIZE;

typedef enum {

    PMP_CHIP_SELECT_ONE = 0x0,
    PMP_CHIP_SELECT_TWO = 0x1

} PMP_CHIP_SELECT;

typedef enum {

    PMCS1_PMCS2_AS_ADDRESS_LINES = 0x0,
    PMCS1_AS_ADDRESS_LINE_PMCS2_AS_CHIP_SELECT = 0x1,
    PMCS1_AND_PMCS2_AS_CHIP_SELECT = 0x2

} PMP_CHIPSELECT_FUNCTION;

typedef enum {

    PMP_PMA0_PORT = 0x1,
    PMP_PMA1_PORT = 0x2,
    PMP_PMA2_PORT = 0x4,
    PMP_PMA3_PORT = 0x8,
    PMP_PMA4_PORT = 0x10,
    PMP_PMA5_PORT = 0x20,
    PMP_PMA6_PORT = 0x40,
    PMP_PMA7_PORT = 0x80,
    PMP_PMA8_PORT = 0x100,
    PMP_PMA9_PORT = 0x200,
    PMP_PMA10_PORT = 0x400,
    PMP_PMA11_PORT = 0x800,
    PMP_PMA12_PORT = 0x1000,
    PMP_PMA13_PORT = 0x2000,
    PMP_PMA14_PORT = 0x4000,
    PMP_PMA15_PORT = 0x8000,
    PMP_PMA2_TO_PMA13_PORTS = 0x3FFC

} PMP_ADDRESS_PORT;

typedef enum {

    PMP_INPUT_BUFFER_TTL = 0x1,
    PMP_INPUT_BUFFER_SCHMITT = 0x0

} PMP_INPUT_BUFFER_TYPE;

typedef enum {

    PMP_POLARITY_ACTIVE_HIGH = 0x1,
    PMP_POLARITY_ACTIVE_LOW = 0x0

} PMP_POLARITY_LEVEL;

typedef enum {

    PMP_ACK_MODE_NONE

} PMP_ACK_MODE;

typedef enum {

    PMP_ADDRESS_WAIT_HALF = 0xFC

} PMP_ADDRESS_LATCH_WAIT_STATES;

typedef enum {

    PMP_ADDRESS_HOLD_LATCH_WAIT_STATES_NONE

} PMP_ADDRESS_HOLD_LATCH_WAIT_STATES;

typedef enum {

    PMP_PMBE_PORT_NONE

} PMP_PMBE_PORT;

typedef enum {

    PMP_MASTER_MODE_NONE

} PMP_MASTER_MODE;

typedef enum {

    PMP_ALTERNATE_MASTER_WAIT_3_NOT_SUPPORTED = -1,
    PMP_ALTERNATE_MASTER_WAIT_4_NOT_SUPPORTED = -1,
    PMP_ALTERNATE_MASTER_WAIT_5_NOT_SUPPORTED = -1,
    PMP_ALTERNATE_MASTER_WAIT_6_NOT_SUPPORTED = -1,
    PMP_ALTERNATE_MASTER_WAIT_7_NOT_SUPPORTED = -1,
    PMP_ALTERNATE_MASTER_WAIT_8_NOT_SUPPORTED = -1

} PMP_ALTERNATE_MASTER_WAIT_STATES;

INLINE SFR_TYPE* _PMP_ENABLE_CONTROL_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_STOP_IN_IDLE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_MUX_MODE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INPUT_BUFFER_TYPE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_WRITE_ENABLE_STROBE_PORT_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_READ_WRITE_STROBE_PORT_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_CHIPSELECT_FUNCTION_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_ADDRESS_LATCH_POLARITY_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_CS1_POLARITY_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_CS2_POLARITY_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_WRITE_ENABLE_POLARITY_BASIC_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_READ_WRITE_POLARITY_BASIC_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMCON;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_BUSY_STATUS_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INT_MODE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INCREMENT_MODE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_DATA_TRANSFER_SIZE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_OP_MODE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_WAIT_STATES_SET_UP_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_WAIT_STATES_STROBE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_WAIT_STATES_HOLD_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMMODE;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_CS_ENABLE_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMADDR;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_ADDRESS_CONTROL_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMADDR;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_ADDRESS_PORT_CONTROL_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMAEN;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_ADDRESS_LATCH_STROBE_PORT_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMAEN;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INPUT_BUFFER_FULL_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_BUFFER_OVERFLOW_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INPUT_BUFFERX_STATUS_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INPUT_BUFFERX_STATUS_1_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INPUT_BUFFERX_STATUS_2_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_INPUT_BUFFERX_STATUS_3_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_OUTPUT_BUFFER_EMPTY_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_BUFFER_UNDERFLOW_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_OUTPUT_BUFFERX_STATUS_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_OUTPUT_BUFFERX_STATUS_1_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_OUTPUT_BUFFERX_STATUS_2_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_OUTPUT_BUFFERX_STATUS_3_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMSTAT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_OUT1_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMDOUT;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PMP_IN1_VREG(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return &PMDIN;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _PMP_ENABLE_CONTROL_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ON_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_STOP_IN_IDLE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_SIDL_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_MUX_MODE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ADRMUX_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFER_TYPE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PMPTTL_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WRITE_ENABLE_STROBE_PORT_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PTWREN_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_READ_WRITE_STROBE_PORT_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PTRDEN_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CHIPSELECT_FUNCTION_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CSF_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_LATCH_POLARITY_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ALP_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS1_POLARITY_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CS1P_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS2_POLARITY_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CS2P_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WRITE_ENABLE_POLARITY_BASIC_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_WRSP_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_READ_WRITE_POLARITY_BASIC_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_RDSP_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUSY_STATUS_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_BUSY_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INT_MODE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_IRQM_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INCREMENT_MODE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_INCM_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_DATA_TRANSFER_SIZE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_MODE16_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OP_MODE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_MODE_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_SET_UP_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITB_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_STROBE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITM_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_HOLD_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITE_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS_ENABLE_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMADDR_CS_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_CONTROL_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMADDR_ADDR_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_PORT_CONTROL_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMAEN_PTEN_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_LATCH_STROBE_PORT_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMAEN_PTEN_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFER_FULL_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IBF_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUFFER_OVERFLOW_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IBOV_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB0F_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_1_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB1F_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_2_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB2F_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_3_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB3F_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFER_EMPTY_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OBE_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUFFER_UNDERFLOW_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OBUF_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB0E_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_1_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB1E_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_2_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB2E_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_3_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB3E_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUT1_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMDOUT_DATAOUT_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_IN1_MASK(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMDIN_DATAIN_MASK;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ENABLE_CONTROL_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ON_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_STOP_IN_IDLE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_SIDL_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_MUX_MODE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ADRMUX_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFER_TYPE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PMPTTL_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WRITE_ENABLE_STROBE_PORT_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PTWREN_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_READ_WRITE_STROBE_PORT_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PTRDEN_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CHIPSELECT_FUNCTION_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CSF_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_LATCH_POLARITY_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ALP_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS1_POLARITY_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CS1P_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS2_POLARITY_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CS2P_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WRITE_ENABLE_POLARITY_BASIC_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_WRSP_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_READ_WRITE_POLARITY_BASIC_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_RDSP_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUSY_STATUS_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_BUSY_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INT_MODE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_IRQM_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INCREMENT_MODE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_INCM_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_DATA_TRANSFER_SIZE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_MODE16_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OP_MODE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_MODE_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_SET_UP_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITB_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_STROBE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITM_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_HOLD_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITE_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS_ENABLE_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMADDR_CS_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_CONTROL_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMADDR_ADDR_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_PORT_CONTROL_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMAEN_PTEN_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_LATCH_STROBE_PORT_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMAEN_PTEN_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFER_FULL_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IBF_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUFFER_OVERFLOW_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IBOV_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB0F_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_1_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB1F_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_2_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB2F_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_3_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB3F_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFER_EMPTY_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OBE_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUFFER_UNDERFLOW_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OBUF_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB0E_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_1_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB1E_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_2_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB2E_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_3_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB3E_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUT1_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMDOUT_DATAOUT_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_IN1_POS(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMDIN_DATAIN_POSITION;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ENABLE_CONTROL_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ON_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_STOP_IN_IDLE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_SIDL_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_MUX_MODE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ADRMUX_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFER_TYPE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PMPTTL_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WRITE_ENABLE_STROBE_PORT_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PTWREN_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_READ_WRITE_STROBE_PORT_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_PTRDEN_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CHIPSELECT_FUNCTION_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CSF_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_LATCH_POLARITY_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_ALP_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS1_POLARITY_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CS1P_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS2_POLARITY_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_CS2P_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WRITE_ENABLE_POLARITY_BASIC_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_WRSP_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_READ_WRITE_POLARITY_BASIC_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMCON_RDSP_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUSY_STATUS_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_BUSY_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INT_MODE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_IRQM_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INCREMENT_MODE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_INCM_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_DATA_TRANSFER_SIZE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_MODE16_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OP_MODE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_MODE_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_SET_UP_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITB_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_STROBE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITM_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_WAIT_STATES_HOLD_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMMODE_WAITE_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_CS_ENABLE_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMADDR_CS_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_CONTROL_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMADDR_ADDR_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_PORT_CONTROL_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMAEN_PTEN_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_ADDRESS_LATCH_STROBE_PORT_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMAEN_PTEN_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFER_FULL_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IBF_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUFFER_OVERFLOW_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IBOV_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB0F_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_1_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB1F_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_2_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB2F_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_INPUT_BUFFERX_STATUS_3_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_IB3F_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFER_EMPTY_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OBE_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_BUFFER_UNDERFLOW_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OBUF_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB0E_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_1_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB1E_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_2_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB2E_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUTPUT_BUFFERX_STATUS_3_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMSTAT_OB3E_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_OUT1_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMDOUT_DATAOUT_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PMP_IN1_LEN(PMP_MODULE_ID i)
{
    switch (i) {
        case PMP_ID_0 :
            return _PMDIN_DATAIN_LENGTH;
        case PMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/pmp_EnableControl_Default.h"
#include "../templates/pmp_StopInIdleControl_Default.h"
#include "../templates/pmp_MUXModeSelect_Default.h"
#include "../templates/pmp_BufferType_Default.h"
#include "../templates/pmp_WriteEnablePortControl_Default.h"
#include "../templates/pmp_ReadWriteStrobePortControl_Default.h"
#include "../templates/pmp_ChipSelectoperation_Default.h"
#include "../templates/pmp_AddressLatchPolarity_Default.h"
#include "../templates/pmp_ChipXPolarity_Default.h"
#include "../templates/pmp_WriteEnablePolarity_Basic.h"
#include "../templates/pmp_ReadWritePolarity_Basic.h"
#include "../templates/pmp_BusyStatus_Default.h"
#include "../templates/pmp_InterruptMode_Default.h"
#include "../templates/pmp_IncrementMode_Default.h"
#include "../templates/pmp_DataTransferSize_Default.h"
#include "../templates/pmp_OperationMode_Default.h"
#include "../templates/pmp_DataSetUpWaitStates_Default.h"
#include "../templates/pmp_DataStrobeWaitStates_Default.h"
#include "../templates/pmp_DataHoldWaitStates_Default.h"
#include "../templates/pmp_ChipSelectEnable_Basic.h"
#include "../templates/pmp_AddressControl_Default.h"
#include "../templates/pmp_AddressPortPinControl_Basic.h"
#include "../templates/pmp_AddressLatchStrobePortControl_Default.h"
#include "../templates/pmp_InputBufferFull_Default.h"
#include "../templates/pmp_BufferOverFlow_Default.h"
#include "../templates/pmp_InputBufferXStatus_Default.h"
#include "../templates/pmp_OutPutBufferEmpty_Default.h"
#include "../templates/pmp_BufferUnderFlow_Default.h"
#include "../templates/pmp_OutputBufferXStatus_Default.h"
#include "../templates/pmp_BufferRead_32bit.h"
#include "../templates/pmp_BufferWrite_32bit.h"
#include "../templates/pmp_MasterRXTX_Default.h"
#include "../templates/pmp_SlaveTX_Default.h"
#include "../templates/pmp_SlaveRX_Default.h"
#include "../templates/pmp_CSXActiveStatus_Default.h"
#include "../templates/pmp_ByteEnablePortControl_Unsupported.h"
#include "../templates/pmp_ByteEnablePolarity_Unsupported.h"
#include "../templates/pmp_ChipXByteEnablePolarity_Unsupported.h"
#include "../templates/pmp_ChipXWriteEnablePolarity_Unsupported.h"
#include "../templates/pmp_ChipXReadWritePolarity_Unsupported.h"
#include "../templates/pmp_SmartAddress_Unsupported.h"
#include "../templates/pmp_BusKeeper_Unsupported.h"
#include "../templates/pmp_TransactionError_Unsupported.h"
#include "../templates/pmp_TransactionTimeOut_Unsupported.h"
#include "../templates/pmp_AltMasterRequest_Unsupported.h"
#include "../templates/pmp_CurrentMaster_Unsupported.h"
#include "../templates/pmp_EnhancedMasterMode_Unsupported.h"
#include "../templates/pmp_ReservedAddrSpace_Unsupported.h"
#include "../templates/pmp_WaitStatesAddrLatchStrobe_Unsupported.h"
#include "../templates/pmp_WaitStatesAddrHoldStrobe_Unsupported.h"
#include "../templates/pmp_CSXPortControl_Unsupported.h"
#include "../templates/pmp_ChipXEnableStorbeSelect_Unsupported.h"
#include "../templates/pmp_ChipXACKPolarity_Unsupported.h"
#include "../templates/pmp_ChipXDataSize_Unsupported.h"
#include "../templates/pmp_ChipXBaseAddress_Unsupported.h"
#include "../templates/pmp_ChipXACKMode_Unsupported.h"
#include "../templates/pmp_ChipXAltMasterWaitStates_Unsupported.h"
#include "../templates/pmp_ChipXDataSetupWaitStates_Unsupported.h"
#include "../templates/pmp_ChipXStrobeWaitStates_Unsupported.h"
#include "../templates/pmp_ChipXDataHoldWaitStates_Unsupported.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool PLIB_PMP_ExistsEnableControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsEnableControl_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_Disable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_Disable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PMP_Enable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_Enable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_IsEnabled(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_IsEnabled_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsStopInIdleControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsStopInIdleControl_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_StopInIdleEnable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_StopInIdleEnable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PMP_StopInIdleDisable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_StopInIdleDisable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsMUXModeSelect(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsMUXModeSelect_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_MultiplexModeSelect(PMP_MODULE_ID index, PMP_MUX_MODE multiplexMode)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_MultiplexModeSelect_Default(index, multiplexMode);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API PMP_MUX_MODE PLIB_PMP_MultiplexModeGet(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_MultiplexModeGet_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (PMP_MUX_MODE)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsBufferType(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsBufferType_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_InputBufferTypeSelect(PMP_MODULE_ID index, PMP_INPUT_BUFFER_TYPE inputBuffer)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_InputBufferTypeSelect_Default(index, inputBuffer);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsWriteEnablePortControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsWriteEnablePortControl_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_WriteEnableStrobePortEnable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WriteEnableStrobePortEnable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PMP_WriteEnableStrobePortDisable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WriteEnableStrobePortDisable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsReadWriteStrobePortControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsReadWriteStrobePortControl_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_ReadWriteStrobePortEnable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ReadWriteStrobePortEnable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PMP_ReadWriteStrobePortDisable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ReadWriteStrobePortDisable_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsChipSelectoperation(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipSelectoperation_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_ChipSelectFunctionSelect(PMP_MODULE_ID index, PMP_CHIPSELECT_FUNCTION chipselfunct)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectFunctionSelect_Default(index, chipselfunct);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsAddressLatchPolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsAddressLatchPolarity_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_AddressLatchPolaritySelect(PMP_MODULE_ID index, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressLatchPolaritySelect_Default(index, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsChipXPolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXPolarity_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_ChipSelectXPolaritySelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXPolaritySelect_Default(index, chipSelect, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsWriteEnablePolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsWriteEnablePolarity_Basic(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_WriteEnableStrobePolaritySelect(PMP_MODULE_ID index, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WriteEnableStrobePolaritySelect_Basic(index, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsReadWritePolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsReadWritePolarity_Basic(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_ReadWriteStrobePolaritySelect(PMP_MODULE_ID index, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ReadWriteStrobePolaritySelect_Basic(index, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsBusyStatus(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsBusyStatus_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_PortIsBusy(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_PortIsBusy_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsInterruptMode(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsInterruptMode_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_InterruptModeSelect(PMP_MODULE_ID index, PMP_INTERRUPT_MODE interruptMode)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_InterruptModeSelect_Default(index, interruptMode);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API PMP_INTERRUPT_MODE PLIB_PMP_InterruptModeGet(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_InterruptModeGet_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (PMP_INTERRUPT_MODE)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsIncrementMode(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsIncrementMode_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_AddressIncrementModeSelect(PMP_MODULE_ID index, PMP_INCREMENT_MODE incrementMode)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressIncrementModeSelect_Default(index, incrementMode);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API PMP_INCREMENT_MODE PLIB_PMP_AddressIncrementModeGet(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_AddressIncrementModeGet_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (PMP_INCREMENT_MODE)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsDataTransferSize(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsDataTransferSize_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_DataSizeSelect(PMP_MODULE_ID index, PMP_DATA_SIZE size)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_DataSizeSelect_Default(index, size);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsOperationMode(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsOperationMode_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_OperationModeSelect(PMP_MODULE_ID index, PMP_OPERATION_MODE operationMode)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_OperationModeSelect_Default(index, operationMode);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API PMP_OPERATION_MODE PLIB_PMP_OperationModeGet(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_OperationModeGet_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (PMP_OPERATION_MODE)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsDataSetUpWaitStates(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsDataSetUpWaitStates_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_WaitStatesDataSetUpSelect(PMP_MODULE_ID index, PMP_DATA_WAIT_STATES dataWaitState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WaitStatesDataSetUpSelect_Default(index, dataWaitState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsDataStrobeWaitStates(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsDataStrobeWaitStates_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_WaitStatesStrobeSelect(PMP_MODULE_ID index, PMP_STROBE_WAIT_STATES strobeWaitState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WaitStatesStrobeSelect_Default(index, strobeWaitState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsDataHoldWaitStates(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsDataHoldWaitStates_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_WaitStatesDataHoldSelect(PMP_MODULE_ID index, PMP_DATA_HOLD_STATES dataHoldState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WaitStatesDataHoldSelect_Default(index, dataHoldState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsChipSelectEnable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipSelectEnable_Basic(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_ChipSelectXEnable(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXEnable_Basic(index, chipSelect);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PMP_ChipSelectXDisable(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXDisable_Basic(index, chipSelect);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsAddressControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsAddressControl_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_AddressSet(PMP_MODULE_ID index, uint32_t address)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressSet_Default(index, address);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_PMP_AddressGet(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_AddressGet_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API void PLIB_PMP_AddressLinesA0A1Set(PMP_MODULE_ID index, uint8_t address)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressLinesA0A1Set_Default(index, address);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_PMP_AddressLinesA0A1Get(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_AddressLinesA0A1Get_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsAddressPortPinControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsAddressPortPinControl_Basic(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_AddressPortEnable(PMP_MODULE_ID index, PMP_ADDRESS_PORT portfunctions)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressPortEnable_Basic(index, portfunctions);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PMP_AddressPortDisable(PMP_MODULE_ID index, PMP_ADDRESS_PORT portfunctions)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressPortDisable_Basic(index, portfunctions);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsAddressLatchStrobePortControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsAddressLatchStrobePortControl_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_AddressLatchStrobeEnable(PMP_MODULE_ID index, PMP_ADDRESS_LATCH latch)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressLatchStrobeEnable_Default(index, latch);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PMP_AddressLatchStrobeDisable(PMP_MODULE_ID index, PMP_ADDRESS_LATCH latch)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_AddressLatchStrobeDisable_Default(index, latch);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsInputBufferFull(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsInputBufferFull_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_InputBuffersAreFull(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_InputBuffersAreFull_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsBufferOverFlow(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsBufferOverFlow_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_InputOverflowHasOccurred(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_InputOverflowHasOccurred_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_InputOverflowClear(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_InputOverflowClear_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsInputBufferXStatus(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsInputBufferXStatus_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_InputBufferXIsFull(PMP_MODULE_ID index, uint8_t buffer)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_InputBufferXIsFull_Default(index, buffer);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_IsDataReceived(PMP_MODULE_ID index, uint8_t buffer)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_IsDataReceived_Default(index, buffer);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsOutPutBufferEmpty(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsOutPutBufferEmpty_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_OutputBuffersAreEmpty(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_OutputBuffersAreEmpty_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsBufferUnderFlow(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsBufferUnderFlow_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_OutputUnderflowHasOccurred(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_OutputUnderflowHasOccurred_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_OutputUnderflowClear(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_OutputUnderflowClear_Default(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsOutputBufferXStatus(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsOutputBufferXStatus_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_OutputBufferXIsEmpty(PMP_MODULE_ID index, uint8_t buffer)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_OutputBufferXIsEmpty_Default(index, buffer);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_IsDataTransmitted(PMP_MODULE_ID index, uint8_t buffer)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_IsDataTransmitted_Default(index, buffer);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsBufferRead(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsBufferRead_32bit(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_PMP_InputBufferXByteReceive(PMP_MODULE_ID index, uint8_t buffer)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_InputBufferXByteReceive_32bit(index, buffer);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsBufferWrite(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsBufferWrite_32bit(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_OutputBufferXByteSend(PMP_MODULE_ID index, uint8_t buffer, uint8_t data)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_OutputBufferXByteSend_32bit(index, buffer, data);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsMasterRXTX(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsMasterRXTX_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_MasterSend(PMP_MODULE_ID index, uint16_t data)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_MasterSend_Default(index, data);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint16_t PLIB_PMP_MasterReceive(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_MasterReceive_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsSlaveTX(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsSlaveTX_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PMP_SlaveSend(PMP_MODULE_ID index, uint16_t data)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_SlaveSend_Default(index, data);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PMP_ExistsSlaveRX(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsSlaveRX_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t PLIB_PMP_SlaveReceive(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_SlaveReceive_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool PLIB_PMP_ExistsCSXActiveStatus(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsCSXActiveStatus_Default(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PMP_ChipSelectXIsActive(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ChipSelectXIsActive_Default(index, chipSelect);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsByteEnablePortControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsByteEnablePortControl_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ByteEnablePortEnable(PMP_MODULE_ID index, PMP_PMBE_PORT pmbeInstance)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ByteEnablePortEnable_Unsupported(index, pmbeInstance);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ByteEnablePortDisable(PMP_MODULE_ID index, PMP_PMBE_PORT pmbeInstance)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ByteEnablePortDisable_Unsupported(index, pmbeInstance);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsByteEnablePolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsByteEnablePolarity_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ByteEnablePolaritySelect(PMP_MODULE_ID index, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ByteEnablePolaritySelect_Unsupported(index, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXByteEnablePolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXByteEnablePolarity_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXByteEnablePortPolaritySelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXByteEnablePortPolaritySelect_Unsupported(index, chipSelect, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXWriteEnablePolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXWriteEnablePolarity_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXWriteEnableStrobePolaritySelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXWriteEnableStrobePolaritySelect_Unsupported(index, chipSelect, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXReadWritePolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXReadWritePolarity_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXReadWriteStrobePolaritySelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXReadWriteStrobePolaritySelect_Unsupported(index, chipSelect, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsSmartAddress(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsSmartAddress_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_SmartAddressStrobeEnable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_SmartAddressStrobeEnable_Unsupported(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_SmartAddressStrobeDisable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_SmartAddressStrobeDisable_Unsupported(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsBusKeeper(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsBusKeeper_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_BusKeeperEnable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_BusKeeperEnable_Unsupported(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_BusKeeperDisable(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_BusKeeperDisable_Unsupported(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsTransactionError(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsTransactionError_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_TransactionErrorHasOccurred(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_TransactionErrorHasOccurred_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_TransactionErrorClear(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_TransactionErrorClear_Unsupported(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsTransactionTimeOut(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsTransactionTimeOut_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_TransactionHasTimedOut(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_TransactionHasTimedOut_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_TransactionTimeoutClear(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_TransactionTimeoutClear_Unsupported(index);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsAltMasterRequest(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsAltMasterRequest_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_AlternateMasterRequestStatus(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_AlternateMasterRequestStatus_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsCurrentMaster(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsCurrentMaster_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_AlternateMasterHasAccess(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_AlternateMasterHasAccess_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsEnhancedMasterMode(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsEnhancedMasterMode_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_EnhancedMasterModeSelect(PMP_MODULE_ID index, PMP_MASTER_MODE master)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_EnhancedMasterModeSelect_Unsupported(index, master);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsReservedAddrSpace(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsReservedAddrSpace_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ReservedAddressSpaceBitsSet(PMP_MODULE_ID index, uint8_t reservedAddress)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ReservedAddressSpaceBitsSet_Unsupported(index, reservedAddress);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsWaitStatesAddrLatchStrobe(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsWaitStatesAddrLatchStrobe_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_WaitStatesAddressLatchStrobeSelect(PMP_MODULE_ID index, PMP_ADDRESS_LATCH_WAIT_STATES waitState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WaitStatesAddressLatchStrobeSelect_Unsupported(index, waitState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsWaitStatesAddrHoldStrobe(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsWaitStatesAddrHoldStrobe_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_WaitStatesAddressHoldStrobeSelect(PMP_MODULE_ID index, PMP_ADDRESS_HOLD_LATCH_WAIT_STATES waitState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_WaitStatesAddressHoldStrobeSelect_Unsupported(index, waitState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsCSXPortControl(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsCSXPortControl_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXPortEnable(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXPortEnable_Unsupported(index, chipSelect);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXPortDisable(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXPortDisable_Unsupported(index, chipSelect);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXEnableStorbeSelect(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXEnableStorbeSelect_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXEnableStrobeSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXEnableStrobeSelect_Unsupported(index, chipSelect);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXEnableStrobeDeSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXEnableStrobeDeSelect_Unsupported(index, chipSelect);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXACKPolarity(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXACKPolarity_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipSelectXAckPolaritySelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_POLARITY_LEVEL polarity)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipSelectXAckPolaritySelect_Unsupported(index, chipSelect, polarity);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXDataSize(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXDataSize_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipXDataSizeSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_DATA_SIZE size)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipXDataSizeSelect_Unsupported(index, chipSelect, size);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXBaseAddress(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXBaseAddress_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipXBaseAddressSet(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, uint16_t baseAddress)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipXBaseAddressSet_Unsupported(index, chipSelect, baseAddress);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXACKMode(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXACKMode_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipXAckModeSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_ACK_MODE mode)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipXAckModeSelect_Unsupported(index, chipSelect, mode);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXAltMasterWaitStates(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXAltMasterWaitStates_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipXWaitStatesAlternateMasterSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipSelect, PMP_ALTERNATE_MASTER_WAIT_STATES waitStates)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipXWaitStatesAlternateMasterSelect_Unsupported(index, chipSelect, waitStates);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXDataSetupWaitStates(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXDataSetupWaitStates_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipXWaitStatesDataSetupSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipselect, PMP_DATA_WAIT_STATES dataWaitState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipXWaitStatesDataSetupSelect_Unsupported(index, chipselect, dataWaitState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXStrobeWaitStates(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXStrobeWaitStates_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipXWaitStatesStrobeSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipselect, PMP_STROBE_WAIT_STATES strobeWaitState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipXWaitStatesStrobeSelect_Unsupported(index, chipselect, strobeWaitState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PMP_ExistsChipXDataHoldWaitStates(PMP_MODULE_ID index)
{
    switch (index) {
        case PMP_ID_0 :
            return PMP_ExistsChipXDataHoldWaitStates_Unsupported(index);
        case PMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PMP_ChipXWaitStatesDataHoldSelect(PMP_MODULE_ID index, PMP_CHIP_SELECT chipselect, PMP_DATA_HOLD_STATES dataHoldState)
{
    switch (index) {
        case PMP_ID_0 :
            PMP_ChipXWaitStatesDataHoldSelect_Unsupported(index, chipselect, dataHoldState);
            break;
        case PMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
