/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.
  
  Summary:
    Crypto Framework Libarary header for cryptographic functions.

  Description:
    This header file contains function prototypes and definitions of
    the data types and constants that make up the Cryptographic Framework
    Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
FileName:   sha.h
Copyright � 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
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




#ifndef CTAO_CRYPT_SHA_H
#define CTAO_CRYPT_SHA_H

#include <types.h>

#ifdef __cplusplus
    extern "C" {
#endif


/* in bytes */
enum {
#ifdef STM32F2_CRYPTO
    SHA_REG_SIZE     =  4,    /* STM32 register size, bytes */
#endif
    SHA              =  1,    /* hash type unique */
    SHA_BLOCK_SIZE   = 64,
    SHA_DIGEST_SIZE  = 20,
    SHA_PAD_SIZE     = 56
};


/* Sha digest */
typedef struct Sha {
    word32  buffLen;   /* in bytes          */
    word32  loLen;     /* length in bytes   */
    word32  hiLen;     /* length in bytes   */
    word32  digest[SHA_DIGEST_SIZE / sizeof(word32)];
    word32  buffer[SHA_BLOCK_SIZE  / sizeof(word32)];
} Sha;


CYASSL_API void InitSha(Sha*);
CYASSL_API void ShaUpdate(Sha*, const byte*, word32);
CYASSL_API void ShaFinal(Sha*, byte*);


#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* CTAO_CRYPT_SHA_H */

