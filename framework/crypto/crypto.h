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
FileName:   crypto.h
Copyright © 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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




/* Defines Microchip CRYPTO API layer */


#ifndef MC_CRYPTO_API_H
#define MC_CRYPTO_API_H


#ifdef __cplusplus
    extern "C" {
#endif

/* MD5 */
typedef struct CRYPT_MD5_CTX {
    int holder[24];   /* big enough to hold internal, but check on init */
} CRYPT_MD5_CTX;

//******************************************************************************
/* Function:
    int CRYPT_MD5_Initialize(CRYPT_MD5_CTX* md5)

  Summary:
    Initializes the internal structures necessary for MD5 hash calculations.

  Description:
    This function initializes the internal structures necessary for MD5 hash calculations.

  Precondition:
	None.
	
  Parameters:
    md5             - Pointer to CRYPT_MD5_CTX strucure which holds the hash values.

  Returns:
    - BAD_FUNC_ARG	- An invalid pointer was passed to the function.
	- 0 			- Otherwise.

  Example:
    <code>
	CRYPT_MD5_CTX md5;
	uint8_t buffer[1024];
	uint8_t md5sum[MD5_DIGEST_SIZE];
	
    CRYPT_MD5_Initialize(&md5);
	CRYPT_MD5_DataAdd(&md5, buffer, sizeof(buffer));
	CRYPT_MD5_Finalize(&md5, md5sum);
    </code>

  Remarks:
	All MD5 hashes have to start at a particular value before adding new data
	to it. This function sets the necessary values for the structure.
*/

int CRYPT_MD5_Initialize(CRYPT_MD5_CTX* md5);

/********************************************************************************************
  Function:
       int CRYPT_MD5_DataAdd(CRYPT_MD5_CTX* md5, const unsigned char* input, unsigned int sz)
    
  Summary:
    Updates the hash with the data provided.
  Description:
    This function updates the hash with the data provided.
  Conditions:
    The MD5 context must be initialized prior to the first call of this
    \function. The context must not be modified by code outside of this
    \function.
  Input:
    md5 -     Pointer to CRYPT_MD5_CTX strucure which holds the hash values.
    \input -  Pointer to the data to use to update the hash.
    sz -      Size of the data (in bytes) of the data to use to update the
              hash.
  Return:
      * BAD_FUNC_ARG &#45; An invalid pointer was passed to the function,
        either in md5 or input.
      * 0 &#45; Otherwise.
  Example:
    <code>
    CRYPT_MD5_CTX md5;
    uint8_t buffer[1024];
    uint8_t md5sum[MD5_DIGEST_SIZE];
    
    CRYPT_MD5_Initialize(&amp;md5);
    CRYPT_MD5_DataAdd(&amp;md5, buffer, sizeof(buffer));
    CRYPT_MD5_Finalize(&amp;md5, md5sum);
    </code>
  Remarks:
    In order to preserve the validity of the MD5 hash, nothing must modify
    the context holding variable between calls to CRYPT_MD5_DataAdd.                         
  ********************************************************************************************/

int CRYPT_MD5_DataAdd(CRYPT_MD5_CTX*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_MD5_Finalize(CRYPT_MD5_CTX* md5, unsigned char* digest)

  Summary:
    Finalizes the hash and puts the result into digest.

  Description:
    This function finalizes the hash and puts the result into digest.

  Precondition:
	The MD5 context must be initialized prior to calling this function.
	\The context must not be modified by code outside of this function.
	
  Parameters:
    md5             - Pointer to CRYPT_MD5_CTX strucure which holds the hash values.
	digest			- Pointer to byte array to store hash result.

  Returns:
    - BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in md5 or digest.
	- 0 			- Otherwise.

  Example:
    <code>
	CRYPT_MD5_CTX md5;
	uint8_t buffer[1024];
	uint8_t md5sum[MD5_DIGEST_SIZE];
	
    CRYPT_MD5_Initialize(&md5);
	CRYPT_MD5_DataAdd(&md5, buffer, sizeof(buffer));
	CRYPT_MD5_Finalize(&md5, md5sum);
    </code>

  Remarks:
	In order to preserve the validity of the MD5 hash, nothing must modify the
	\context holding variable between calls to CRYPT_MD5_DataAdd and CRYPT_MD5_Finalize.
*/

int CRYPT_MD5_Finalize(CRYPT_MD5_CTX*, unsigned char*);

enum {
    CRYPT_MD5_DIGEST_SIZE = 16 
};


/* SHA */
typedef struct CRYPT_SHA_CTX {
    int holder[24];   /* big enough to hold internal, but check on init */
} CRYPT_SHA_CTX;

//******************************************************************************
/* Function:
    int CRYPT_SHA_Initialize(CRYPT_SHA_CTX* sha)

  Summary:
    Initializes the internal structures necessary for SHA hash calculations.

  Description:
    This function initializes the internal structures necessary for SHA hash calculations.

  Precondition:
	None.
	
  Parameters:
    sha             - Pointer to CRYPT_SHA_CTX strucure which holds the hash values.

  Returns:
    - BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	- 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA_CTX sha;
	uint8_t shaSum[SHA_DIGEST_SIZE];
	
    CRYPT_SHA_Initialize(&sha);
	CRYPT_SHA_DataAdd(&sha, buffer, sizeof(buffer));
	CRYPT_SHA_Finalize(&sha, shaSum);
    </code>

  Remarks:
	All SHA hashes have to start at a particular value before adding new data
	to it. This function sets the necessary values for the structure.
*/

int CRYPT_SHA_Initialize(CRYPT_SHA_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_SHA_DataAdd(CRYPT_SHA_CTX* sha, const unsigned char* input, unsigned int sz)

  Summary:
    Updates the hash with the data provided. 

  Description:
    This function updates the hash with the data provided.

  Precondition:
	The SHA context must be initialized prior to the first call of this function.
	The context must not be modified by code outside of this function.
	
  Parameters:
    sha             - Pointer to CRYPT_SHA_CTX strucure which holds the hash values.
    \input			- Pointer to the data to use to update the hash.
    sz				- Size of the data (in bytes) of the data to use to update the hash.

  Returns:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in sha or input.
	* 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA_CTX sha;
	uint8_t buffer[1024];
	uint8_t shaSum[SHA_DIGEST_SIZE];
	
    CRYPT_SHA_Initialize(&sha);
	CRYPT_SHA_DataAdd(&sha, buffer, sizeof(buffer));
	CRYPT_SHA_Finalize(&sha, shaSum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA hash, nothing must modify the
	\context holding variable between calls to CRYPT_SHA_DataAdd.
*/

int CRYPT_SHA_DataAdd(CRYPT_SHA_CTX*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_SHA_Finalize(CRYPT_SHA_CTX* sha, unsigned char* digest)

  Summary:
    Finalizes the hash and puts the result into digest.

  Description:
    This function finalizes the hash and puts the result into digest.

  Precondition:
	The SHA context must be initialized prior to calling this function.
	The context must not be modified by code outside of this function.
	
  Parameters:
    sha             - Pointer to CRYPT_SHA_CTX strucure which holds the hash values.
	digest			- Pointer to byte array to store hash result.

  Returns:
    BAD_FUNC_ARG - An invalid pointer was passed to the function, either in sha or digest.
	0 - Otherwise.

  Example:
    <code>
	CRYPT_SHA_CTX sha;
	uint8_t buffer[1024];
	uint8_t shaSum[SHA_DIGEST_SIZE];
	
    CRYPT_SHA_Initialize(&sha);
	CRYPT_SHA_DataAdd(&sha, buffer, sizeof(buffer));
	CRYPT_SHA_Finalize(&sha, shaSum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA hash, nothing must modify the
	context holding variable between calls to CRYPT_SHA_DataAdd and CRYPT_SHA_Finalize.
*/

int CRYPT_SHA_Finalize(CRYPT_SHA_CTX*, unsigned char*);

enum {
    CRYPT_SHA_DIGEST_SIZE = 20
};


/* SHA-256 */
typedef struct CRYPT_SHA256_CTX {
    int holder[28];   /* big enough to hold internal, but check on init */
} CRYPT_SHA256_CTX;

//******************************************************************************
/* Function:
    int CRYPT_SHA256_Initialize(CRYPT_SHA256_CTX* sha256)

  Summary:
    Initializes the internal structures necessary for SHA256 hash calculations.

  Description:
    This function initializes the internal structures necessary for SHA256 hash calculations.

  Precondition:
	None.
	
  Parameters:
    sha256			- Pointer to context which saves state between calls.

  Returns:
    *BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0 				- Otherwise.

  Example:
    <code>
	CRYPT_SHA256_CTX sha;
	uint8_t shaSum[SHA256_DIGEST_SIZE];
	
    CRYPT_SHA256_Initialize(&sha);
	CRYPT_SHA256_DataAdd(&sha, buffer, sizeof(buffer));
	CRYPT_SHA256_Finalize(&sha, shaSum);
    </code>

  Remarks:
	All SHA hashes have to start at a particular value before adding new data
	to it. This function sets the necessary values for the structure.
*/

int CRYPT_SHA256_Initialize(CRYPT_SHA256_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_SHA256_DataAdd(CRYPT_SHA256_CTX* sha256, const unsigned char* input, unsigned int sz)

  Summary:
    Updates the hash with the data provided. 

  Description:
    This function updates the hash with the data provided.

  Precondition:
	The SHA256 context must be initialized prior to the first call of this function.
	\The context must not be modified by code outside of this function.
	
  Parameters:
    sha256          - Pointer to CRYPT_SHA256_CTX strucure which holds the hash values.
    \input			- Pointer to the data to use to update the hash.
    sz				- Size of the data (in bytes) of the data to use to update the hash.

  Returns:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in sha256 or input.
	* 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA256_CTX sha256;
	uint8_t buffer[1024];
	uint8_t shaSum[SHA256_DIGEST_SIZE];
	
    CRYPT_SHA256_Initialize(&sha256);
	CRYPT_SHA256_DataAdd(&sha256, buffer, sizeof(buffer));
	CRYPT_SHA256_Finalize(&sha256, shaSum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA256 hash, nothing must modify the
	\context holding variable between calls to CRYPT_SHA256_DataAdd.
*/

int CRYPT_SHA256_DataAdd(CRYPT_SHA256_CTX*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_SHA256_Finalize(CRYPT_SHA256_CTX* sha256, unsigned char* digest)

  Summary:
    Finalizes the hash and puts the result into digest.

  Description:
    This function finalizes the hash and puts the result into digest.

  Precondition:
	The SHA256 context must be initialized prior to calling this function.
	\The context must not be modified by code outside of this function.
	
  Parameters:
    sha256          - Pointer to CRYPT_SHA256_CTX strucure which holds the hash values.
	digest			- Pointer to byte array to store hash result.

  Returns:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in sha or digest.
	* 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA256_CTX sha256;
	uint8_t buffer[1024];
	uint8_t shaSum[SHA256_DIGEST_SIZE];
	
    CRYPT_SHA256_Initialize(&sha256);
	CRYPT_SHA256_DataAdd(&sha256, buffer, sizeof(buffer));
	CRYPT_SHA256_Finalize(&sha256, shaSum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA256 hash, nothing must modify the
	context holding variable between calls to CRYPT_SHA256_DataAdd and CRYPT_SHA256_Finalize.
*/

int CRYPT_SHA256_Finalize(CRYPT_SHA256_CTX*, unsigned char*);

enum {
    CRYPT_SHA256_DIGEST_SIZE = 32 
};


/* SHA-384 */
typedef struct CRYPT_SHA384_CTX {
    long long holder[32];   /* big enough to hold internal, but check on init */
} CRYPT_SHA384_CTX;

//******************************************************************************
/* Function:
    int CRYPT_SHA384_Initialize(CRYPT_SHA384_CTX* sha384)

  Summary:
    Initializes the internal structures necessary for SHA384 hash calculations.

  Description:
    This function initializes the internal structures necessary for SHA384 hash calculations.

  Precondition:
	None.
	
  Parameters:
    sha384          - Pointer to CRYPT_SHA384_CTX strucure which holds the hash values.

  Returns:
    - BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	- 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA384_CTX sha384;
	uint8_t shaSum[SHA384_DIGEST_SIZE];
	
    CRYPT_SHA384_Initialize(&sha384);
	CRYPT_SHA384_DataAdd(&sha384, buffer, sizeof(buffer));
	CRYPT_SHA384_Finalize(&sha384, shaSum);
    </code>

  Remarks:
	All SHA384 hashes have to start at a particular value before adding new data
	to it. This function sets the necessary values for the structure.
*/

int CRYPT_SHA384_Initialize(CRYPT_SHA384_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_SHA384_DataAdd(CRYPT_SHA384_CTX* sha384, const unsigned char* input, unsigned int sz)

  Summary:
    Updates the hash with the data provided. 

  Description:
    This function updates the hash with the data provided.

  Precondition:
	The SHA384 context must be initialized prior to the first call of this function.
	\The context must not be modified by code outside of this function.
	
  Parameters:
    sha384          - Pointer to CRYPT_SHA384_CTX strucure which holds the hash values.
    \input			- Pointer to the data to use to update the hash.
    sz				- Size of the data (in bytes) of the data to use to update the hash.

  Returns:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in sha384 or input.
	* 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA384_CTX sha384;
	uint8_t buffer[1024];
	uint8_t shaSum[SHA384_DIGEST_SIZE];
	
    CRYPT_SHA384_Initialize(&sha384);
	CRYPT_SHA384_DataAdd(&sha384, buffer, sizeof(buffer));
	CRYPT_SHA384_Finalize(&sha384, shaSum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA384 hash, nothing must modify the
	\context holding variable between calls to CRYPT_SHA384_DataAdd.
*/

int CRYPT_SHA384_DataAdd(CRYPT_SHA384_CTX*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_SHA384_Finalize(CRYPT_SHA384_CTX* sha384, unsigned char* digest)

  Summary:
    Finalizes the hash and puts the result into digest.

  Description:
    This function finalizes the hash and puts the result into digest.

  Precondition:
	The SHA384 context must be initialized prior to calling this function.
	\The context must not be modified by code outside of this function.
	
  Parameters:
    sha384          - Pointer to CRYPT_SHA384_CTX strucure which holds the hash values.
	digest			- Pointer to byte array to store hash result.

  Returns:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in sha384 or digest.
	* 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA384_CTX sha384;
	uint8_t buffer[1024];
	uint8_t shaSum[SHA384_DIGEST_SIZE];
	
    CRYPT_SHA384_Initialize(&sha384);
	CRYPT_SHA384_DataAdd(&sha384, buffer, sizeof(buffer));
	CRYPT_SHA384_Finalize(&sha384, shaSum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA384 hash, nothing must modify the
	context holding variable between calls to CRYPT_SHA384_DataAdd and CRYPT_SHA384_Finalize.
*/

int CRYPT_SHA384_Finalize(CRYPT_SHA384_CTX*, unsigned char*);

enum {
    CRYPT_SHA384_DIGEST_SIZE = 48
};


/* SHA-512 */
typedef struct CRYPT_SHA512_CTX {
    long long holder[36];   /* big enough to hold internal, but check on init */
} CRYPT_SHA512_CTX;

//******************************************************************************
/* Function:
    int CRYPT_SHA512_Initialize(CRYPT_SHA512_CTX* sha512)

  Summary:
    Initializes the internal structures necessary for SHA512 hash calculations.

  Description:
    This function initializes the internal structures necessary for SHA512 hash calculations.

  Precondition:
	None.
	
  Parameters:
    sha512          - Pointer to CRYPT_SHA512_CTX strucure which holds the hash values.

  Returns:
    - BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	- 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA512_CTX sha512;
	uint8_t sha512Sum[SHA512_DIGEST_SIZE];
	
    CRYPT_SHA512_Initialize(&sha512);
	CRYPT_SHA512_DataAdd(&sha512, buffer, sizeof(buffer));
	CRYPT_SHA512_Finalize(&sha512, sha512Sum);
    </code>

  Remarks:
	All SHA512 hashes have to start at a particular value before adding new data
	to it. This function sets the necessary values for the structure.
*/

int CRYPT_SHA512_Initialize(CRYPT_SHA512_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_SHA512_DataAdd(CRYPT_SHA512_CTX* sha512, const unsigned char* input, unsigned int sz)

  Summary:
    Updates the hash with the data provided. 

  Description:
    This function updates the hash with the data provided.

  Precondition:
	The SHA512 context must be initialized prior to the first call of this function.
	\The context must not be modified by code outside of this function.
	
  Parameters:
    sha512          - Pointer to CRYPT_SHA512_CTX strucure which holds the hash values.
    \input			- Pointer to the data to use to update the hash.
    sz				- Size of the data (in bytes) of the data to use to update the hash.

  Returns:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in sha512 or input.
	* 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA512_CTX sha512;
	uint8_t buffer[1024];
	uint8_t sha512Sum[SHA512_DIGEST_SIZE];
	
    CRYPT_SHA512_Initialize(&sha512);
	CRYPT_SHA512_DataAdd(&sha512, buffer, sizeof(buffer));
	CRYPT_SHA512_Finalize(&sha512, sha512Sum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA512 hash, nothing must modify the
	\context holding variable between calls to CRYPT_SHA512_DataAdd.
*/

int CRYPT_SHA512_DataAdd(CRYPT_SHA512_CTX*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_SHA512_Finalize(CRYPT_SHA512_CTX* sha512, unsigned char* digest)

  Summary:
    Finalizes the hash and puts the result into digest.

  Description:
    This function finalizes the hash and puts the result into digest.

  Precondition:
	The SHA512 context must be initialized prior to calling this function.
	\The context must not be modified by code outside of this function.
	
  Parameters:
    sha512          - Pointer to CRYPT_SHA512_CTX strucure which holds the hash values.
	digest			- Pointer to byte array to store hash result.

  Returns:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function, either in sha512 or digest.
	* 0 			- Otherwise.

  Example:
    <code>
	CRYPT_SHA512_CTX sha512;
	uint8_t buffer[1024];
	uint8_t sha512Sum[SHA512_DIGEST_SIZE];
	
    CRYPT_SHA512_Initialize(&sha512);
	CRYPT_SHA512_DataAdd(&sha512, buffer, sizeof(buffer));
	CRYPT_SHA512_Finalize(&sha512, sha512Sum);
    </code>

  Remarks:
	In order to preserve the validity of the SHA512 hash, nothing must modify the
	context holding variable between calls to CRYPT_SHA512_DataAdd and CRYPT_SHA512_Finalize.
*/

int CRYPT_SHA512_Finalize(CRYPT_SHA512_CTX*, unsigned char*);

enum {
    CRYPT_SHA512_DIGEST_SIZE = 64 
};


/* HMAC */
typedef struct CRYPT_HMAC_CTX {
    long long holder[67];   /* big enough to hold internal, but check on init */
} CRYPT_HMAC_CTX;

/******************************************************************************************************
  Function:
    int CRYPT_HMAC_SetKey(CRYPT_HMAC_CTX* hmac, int type, const unsigned char* key, unsigned int sz)
    
  Summary:
	Initialize the HMAC context and set the key for the hash.
	
  Description:
	This function initializes the HMAC context and set the key for the hash.
  
  Preconditions:
	None.
	
  Input:
    hmac -  Pointer to context which saves state between calls.
    type -  Type of SHA operation to use with HMAC. Must be one of the
            following\:
            * CRYPT_HMAC_SHA
            * CRYPT_HMAC_SHA256
            * CRYPT_HMAC_SHA384
            * CRYPT_HMAC_SHA512
    key -   Secret key used for the hash.
	sz	-	Size of the input data in bytes.
  Return:
    * BAD_FUNC_ARG 	- An invalid pointer was passed to the function. 
	* 0				- Otherwise.
  Example:
    <code>
    CRYPT_HMAC_CTX mcHmac;
    byte           mcDigest[CRYPT_SHA512_DIGEST_SIZE];
    
    CRYPT_HMAC_SetKey(&amp;mcHmac, CRYPT_HMAC_SHA, key, 4);
    
    CRYPT_HMAC_DataAdd(&amp;mcHmac, ourData, OUR_DATA_SIZE);
    
    CRYPT_HMAC_Finalize(&amp;mcHmac, mcDigest);
    </code>
  Remarks:
    \ \                                                                                                
  ******************************************************************************************************/

int CRYPT_HMAC_SetKey(CRYPT_HMAC_CTX*, int, const unsigned char*, unsigned int);

/*********************************************************************************
  Function:
       int CRYPT_HMAC_DataAdd(CRYPT_HMAC_CTX*, const unsigned char*, unsigned int)
    
  Summary:
	Add data to the HMAC calculation. 
  Description:
	This function adds data to the HMAC so that multiple blocks of data can be processed.
  Conditions:
    The CRYPT_HMAC_CTX context must be initialized using the
    CRYPT_HMAC_SetKey function prior to any call to this function.
  Input:
    hmac -    Pointer to context which saves state between calls.
    \input -  Pointer to the data to use to update the hash.
    sz -      Size of the input data in bytes.
  Return:
    \*BAD_FUNC_ARG - An invalid pointer was passed to the function. *0 -
    Otherwise.
  Example:
    <code>
    CRYPT_HMAC_CTX mcHmac;
    byte           mcDigest[CRYPT_SHA512_DIGEST_SIZE];
    
    CRYPT_HMAC_SetKey(&amp;mcHmac, CRYPT_HMAC_SHA, key, 4);
    
    CRYPT_HMAC_DataAdd(&amp;mcHmac, ourData, OUR_DATA_SIZE);
    
    CRYPT_HMAC_Finalize(&amp;mcHmac, mcDigest);
    </code>
  Remarks:
    \ \                                                                           
  *********************************************************************************/

int CRYPT_HMAC_DataAdd(CRYPT_HMAC_CTX*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_HMAC_Finalize(CRYPT_HMAC_CTX* hmac, unsigned char* digest)

  Summary:
	Complete the HMAC calculation and get the results.
	
  Description:
	This function completes the HMAC calculations. The results are placed in \
	the location pointed to by digest.

  Precondition:
    The CRYPT_HMAC_CTX context must be initialized using the
    CRYPT_HMAC_SetKey function prior to any call to this function.
	
  Parameters:
    hmac		- Pointer to context which saves state between calls.
    digest		- Pointer to place to put the final HMAC digest results.

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    CRYPT_HMAC_CTX mcHmac;
    byte           mcDigest[CRYPT_SHA512_DIGEST_SIZE];

    CRYPT_HMAC_SetKey(&mcHmac, CRYPT_HMAC_SHA, key, 4);

    CRYPT_HMAC_DataAdd(&mcHmac, ourData, OUR_DATA_SIZE);

    CRYPT_HMAC_Finalize(&mcHmac, mcDigest);
    </code>

  Remarks:
	The area pointed to by digest must be large enough to hold the results.
*/

int CRYPT_HMAC_Finalize(CRYPT_HMAC_CTX*, unsigned char*);

/* HMAC types */
enum {
    CRYPT_HMAC_SHA    = 1, 
    CRYPT_HMAC_SHA256 = 2, 
    CRYPT_HMAC_SHA384 = 5, 
    CRYPT_HMAC_SHA512 = 4 
};


/* Huffman */

//******************************************************************************
/* Function:
    int CRYPT_HUFFMAN_Compress(unsigned char* out, unsigned int outSz, const unsigned char* in,
                               unsigned int inSz, unsigned int flags)

  Summary:
	Compress a block of data.

  Description:
	This function compresses a block of data using Huffman encoding.

  Precondition:
	None.
	
  Parameters:
    out		- Pointer to location to store the compressed data.
    outSz	- Maximum size of the output data in bytes.
    in		- Point to location of source data.
    inSz	- Size of the input data in bytes.
    flags	- Flags to control how compress operates

  Returns:
	* negative	- error code
	* positive	- bytes stored in out buffer

  Example:
    <code>
	const unsigned char text[] = "...";
	unsigned int inSz = sizeof(text);
	unsigned int outSz;
	unsigned char cBuffer[1024];
	
	int ret;
	
	ret = CRYPT_HUFFMAN_COMPRESS(cBuffer, sizeof(cBuffer), text, inSz, 0);
    </code>

  Remarks:
	Output buffer must be large enough to hold the contents of the operation.
*/

int CRYPT_HUFFMAN_Compress(unsigned char*, unsigned int, const unsigned char*,
                           unsigned int, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_HUFFMAN_DeCompress(unsigned char* out, unsigned int outSz, const unsigned char* in, unsigned int inSz)

  Summary:
	Decompress a block of data.

  Description:
	This function decompresses a block of data using Huffman encoding.

  Precondition:
	None.
	
  Parameters:
    out		- Pointer to destination buffer
    outSz	- Size of destination buffer
    in		- Pointer to source buffer to decompres
    inSz	- Size of source buffer to decompress

  Returns:
	* negative 	- Error code
	* positive	- Bytes stored in out buffer

  Example:
    <code>
    unsigned char cBuffer[1024];
    unsigned char dBuffer[1024];

	int ret
	
	ret = CRYPT_HUFFMAN_DeCompress(dBuffer, sizeof(dBuffer), cBuffer, msglen);
    </code>

  Remarks:
	Output buffer must be large enough to hold the contents of the operation.
*/

int CRYPT_HUFFMAN_DeCompress(unsigned char*, unsigned int, const unsigned char*,
                             unsigned int);

/* flag to use static huffman */
enum {
    CRYPT_HUFFMAN_COMPRESS_STATIC = 1 
};


/* RNG */
typedef struct CRYPT_RNG_CTX {
    int holder[66];   /* big enough to hold internal, but check on init */
} CRYPT_RNG_CTX;

//******************************************************************************
/* Function:
    int CRYPT_RNG_Initialize(CRYPT_RNG_CTX* rng)

  Summary:
	Initialize random number generator.

  Description:
	This function initializes the context that stores information relative to
	random number generation.

  Precondition:
	None.
	
  Parameters:
    rng		- Pointer to random number generator context.

  Returns:
	* negative 	- An error occurred setting up the random number generator.
	* 0			- Otherwise.

  Example:
    <code>
	#define RANDOM_BYTE_SZ 32

	int           ret;
	CRYPT_RNG_CTX mcRng;
	byte          out[RANDOM_BYTE_SZ];
	
	ret = CRYPT_RNG_Initialize(&mcRng);
	
	ret = CRYPT_RNG_Get(&mcRng, &out[0]);

    ret = CRYPT_RNG_BlockGenerate(&mcRng, out, RANDOM_BYTE_SZ);
    </code>

  Remarks:
*/

int CRYPT_RNG_Initialize(CRYPT_RNG_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_RNG_Get(CRYPT_RNG_CTX* rng, unsigned char* b)

  Summary:
	Get one random number.

  Description:
	This function gets one random number from the random number generator.

  Precondition:
	RNG context was initialized using the CRYPT_RNG_Initialize function.
	
  Parameters:
    rng		- Pointer to context which saves state between calls.
    b		- Pointer to 8-bit location to store the result.

  Returns:
	* BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	* <0			- An error occurred.
	* 0 or positive	- Success.

  Example:
    <code>
	#define RANDOM_BYTE_SZ 32

	int           ret;
	CRYPT_RNG_CTX mcRng;
	byte          out[RANDOM_BYTE_SZ];
	
	ret = CRYPT_RNG_Initialize(&mcRng);
	
	ret = CRYPT_RNG_Get(&mcRng, &out[0]);

    ret = CRYPT_RNG_BlockGenerate(&mcRng, out, RANDOM_BYTE_SZ);
    </code>

  Remarks:
*/

int CRYPT_RNG_Get(CRYPT_RNG_CTX*, unsigned char*);

//******************************************************************************
/* Function:
    int CRYPT_RNG_BlockGenerate(CRYPT_RNG_CTX* rng, unsigned char* b, unsigned int sz)

  Summary:
	Create several random numbers.

  Description:
	This function generates several random numbers and places them in the space allocated.

  Precondition:
	RNG context was initialized using the CRYPT_RNG_Initialize function.
	
  Parameters:
    rng		- Pointer to context which saves state between calls.
    b		- Pointer to buffer to store the random numbers.
    sz		- Number of 8-bit random numbers to generate.

  Returns:
	* BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	* 0				- Otherwise.

  Example:
    <code>
	#define RANDOM_BYTE_SZ 32

	int           ret;
	CRYPT_RNG_CTX mcRng;
	byte          out[RANDOM_BYTE_SZ];
	
	ret = CRYPT_RNG_Initialize(&mcRng);
	
	ret = CRYPT_RNG_Get(&mcRng, &out[0]);

    ret = CRYPT_RNG_BlockGenerate(&mcRng, out, RANDOM_BYTE_SZ);
    </code>

  Remarks:
*/

int CRYPT_RNG_BlockGenerate(CRYPT_RNG_CTX*, unsigned char*, unsigned int);


/* TDES */
typedef struct CRYPT_TDES_CTX {
    int holder[100];   /* big enough to hold internal, but check on init */
} CRYPT_TDES_CTX;

//******************************************************************************
/* Function:
    int CRYPT_TDES_KeySet(CRYPT_TDES_CTX* tdes, const unsigned char* key, const unsigned char* iv, int dir)

  Summary:
	Initialization of Triple DES context.

  Description:
	This function sets the key and initialization vector (IV) for a set of Triple-DES operations.

  Precondition:
	None.
	
  Parameters:
    tdes	- Pointer to context which saves state between calls.
    key		- Pointer to buffer holding the key. Must be 24 bytes in size.
    iv		- Pointer to buffer holding the initialization vector. Must be 8 bytes in size.
    dir		- Indicates whether encryption or decryption will be done. Can be set to\:
		* CRYPT_TDES_ENCRYPTION	- For Encryption operations
		* CRYPT_TDES_DECRYPTION	- Fro Decryption operations

  Returns:
	* BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	* 0				- Otherwise.

  Example:
    <code>
    CRYPT_TDES_CTX mcDes3;
    int            ret;
    byte           out1[TDES_SIZE];
    byte           out2[TDES_SIZE];

    strncpy((char*)key, "1234567890abcdefghijklmn", 24);
    strncpy((char*)iv,  "12345678", 8);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_ENCRYPTION);

    ret = CRYPT_TDES_CBC_Encrypt(&mcDes3, out1, ourData, TDES_SIZE);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_DECRYPTION);
	
    ret = CRYPT_TDES_CBC_Decrypt(&mcDes3, out2, out1, TDES_TEST_SIZE);
    </code>

  Remarks:
	The input data must be a multiple of 8 bytes, and must be padded at the end with zeros to meet the length.
*/

int CRYPT_TDES_KeySet(CRYPT_TDES_CTX*, const unsigned char*,
                      const unsigned char*, int);

//******************************************************************************
/* Function:
    int CRYPT_TDES_IvSet(CRYPT_TDES_CTX* tdes, const unsigned char* iv)

  Summary:
	Set the Initialization Vector (IV) for a Triple DES operation.

  Description:
	This function changes the IV of a TDES context, but leaves the Key alone.

  Precondition:
	None.
	
  Parameters:
    tdes	- Pointer to context which saves state between calls.
    iv		- Pointer to buffer holding the initialization vector. Must be 8 bytes in size.

  Returns:
	* BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	* 0				- Otherwise.

  Example:
    <code>
    CRYPT_TDES_CTX mcDes3;
    int            ret;
    byte           out1[TDES_SIZE];
    byte           out2[TDES_SIZE];

    strncpy((char*)key, "1234567890abcdefghijklmn", 24);
    strncpy((char*)iv,  "12345678", 8);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_ENCRYPTION);

	ret = CRYPT_TDES_IvSet(&mcDes3, iv);

    ret = CRYPT_TDES_CBC_Encrypt(&mcDes3, out1, ourData, TDES_SIZE);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_DECRYPTION);
	
    ret = CRYPT_TDES_CBC_Decrypt(&mcDes3, out2, out1, TDES_TEST_SIZE);
    </code>

  Remarks:
	The IV must be 8 bytes long.
*/

int CRYPT_TDES_IvSet(CRYPT_TDES_CTX*, const unsigned char*);

//******************************************************************************
/* Function:
    int CRYPT_TDES_CBC_Encrypt(CRYPT_TDES_CTX* tdes, unsigned char* out, const unsigned char* in, unsigned int inSz)

  Summary:
	Encrypt a data block using Triple DES.

  Description:
	This function encrypts a block of data using a Triple DES algorithm.

  Precondition:
	The context tdes must be set earlier using CRYPT_TDES_KeySet. The input block must be a multiple of 8 bytes long.
	
  Parameters:
    tdes	- Pointer to context which saves state between calls.
    out		- Pointer to output buffer to store the results.
    in		- Pointer to input buffer for the source of the data.
    inSz	- Size of the input data buffer.

  Returns:
	* BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	* 0				- Otherwise.

  Example:
    <code>
    CRYPT_TDES_CTX mcDes3;
    int            ret;
    byte           out1[TDES_SIZE];
    byte           out2[TDES_SIZE];

    strncpy((char*)key, "1234567890abcdefghijklmn", 24);
    strncpy((char*)iv,  "12345678", 8);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_ENCRYPTION);

    ret = CRYPT_TDES_CBC_Encrypt(&mcDes3, out1, ourData, TDES_SIZE);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_DECRYPTION);
	
    ret = CRYPT_TDES_CBC_Decrypt(&mcDes3, out2, out1, TDES_TEST_SIZE);
    </code>

  Remarks:
	The input data must be padded at the end with zeros to make the length a multiple of 8.
*/

int CRYPT_TDES_CBC_Encrypt(CRYPT_TDES_CTX*, unsigned char*,
                           const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_TDES_CBC_Decrypt(CRYPT_TDES_CTX* tdes, unsigned char* out, const unsigned char* in, unsigned int inSz)

  Summary:
	Decrypt a data block using Triple DES.

  Description:
	This function decrypts a block of data using a Triple DES algorithm.

  Precondition:
	The context tdes must be set earlier using CRYPT_TDES_KeySet. The input block must be a multiple of 8 bytes long.
	
  Parameters:
    tdes	- Pointer to context which saves state between calls.
    out		- Pointer to output buffer to store the results.
    in		- Pointer to input buffer for the source of the data.
    inSz	- Size of the input data buffer.

  Returns:
	* BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	* 0				- Otherwise.

  Example:
    <code>
    CRYPT_TDES_CTX mcDes3;
    int            ret;
    byte           out1[TDES_SIZE];
    byte           out2[TDES_SIZE];

    strncpy((char*)key, "1234567890abcdefghijklmn", 24);
    strncpy((char*)iv,  "12345678", 8);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_ENCRYPTION);

    ret = CRYPT_TDES_CBC_Encrypt(&mcDes3, out1, ourData, TDES_SIZE);

    ret = CRYPT_TDES_KeySet(&mcDes3, key, iv, CRYPT_TDES_DECRYPTION);
	
    ret = CRYPT_TDES_CBC_Decrypt(&mcDes3, out2, out1, TDES_TEST_SIZE);
    </code>

  Remarks:
	Input data must have a length a multiple of 8 bytes. Output data will be
	zero-padded at the end if the original data was not a multiple of 8 bytes long.
*/

int CRYPT_TDES_CBC_Decrypt(CRYPT_TDES_CTX*, unsigned char*,
                           const unsigned char*, unsigned int);

/* key direction flags for setup */
enum {
    CRYPT_TDES_ENCRYPTION = 0,
    CRYPT_TDES_DECRYPTION = 1 
};


/* AES */
typedef struct CRYPT_AES_CTX {
    int holder[69];   /* big enough to hold internal, but check on init */
} CRYPT_AES_CTX;

//******************************************************************************
/* Function:
    int CRYPT_AES_KeySet(CRYPT_AES_CTX*, const unsigned char*, unsigned int,
                      const unsigned char*, int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    aes		- Pointer to context which saves state between calls.
    key		-
    keyLen		-
    iv		-
    dir		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_AES_KeySet(CRYPT_AES_CTX*, const unsigned char*, unsigned int,
                      const unsigned char*, int);

//******************************************************************************
/* Function:
    int CRYPT_AES_IvSet(CRYPT_AES_CTX*, const unsigned char*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_AES_IvSet(CRYPT_AES_CTX*, const unsigned char*);

//******************************************************************************
/* Function:
    int CRYPT_AES_CBC_Encrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*, unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_AES_CBC_Encrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_AES_CBC_Decrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*, unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_AES_CBC_Decrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*, unsigned int);


//******************************************************************************
/* Function:
    int CRYPT_AES_CTR_Encrypt(CRYPT_AES_CTX*, unsigned char*,
                          const unsigned char*, unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
	ctr (counter), use Encrypt both ways with ENCRYPT key setup
*/

int CRYPT_AES_CTR_Encrypt(CRYPT_AES_CTX*, unsigned char*,
                          const unsigned char*, unsigned int);


//******************************************************************************
/* Function:
    int CRYPT_AES_DIRECT_Encrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*)

  Summary:
	Direct encryption of one block of data.

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_AES_DIRECT_Encrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*);

//******************************************************************************
/* Function:
    int CRYPT_AES_DIRECT_Decrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*)

  Summary:
	Direct encryption of one block of data.

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_AES_DIRECT_Decrypt(CRYPT_AES_CTX*, unsigned char*,
                           const unsigned char*);

/* key direction flags for setup, ctr always uses ENCRYPT flag */
enum {
    CRYPT_AES_ENCRYPTION = 0,
    CRYPT_AES_DECRYPTION = 1,
    CRYPT_AES_BLOCK_SIZE = 16
};



/* RSA */
typedef struct CRYPT_RSA_CTX {
    void* holder;
} CRYPT_RSA_CTX;


//******************************************************************************
/* Function:
    int CRYPT_RSA_Initialize(CRYPT_RSA_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_RSA_Initialize(CRYPT_RSA_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_RSA_Free(CRYPT_RSA_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_RSA_Free(CRYPT_RSA_CTX*);


//******************************************************************************
/* Function:
    int CRYPT_RSA_PublicKeyDecode(CRYPT_RSA_CTX*, const unsigned char*,
                              unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_RSA_PublicKeyDecode(CRYPT_RSA_CTX*, const unsigned char*,
                              unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_RSA_PrivateKeyDecode(CRYPT_RSA_CTX*, const unsigned char*,
                               unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_RSA_PrivateKeyDecode(CRYPT_RSA_CTX*, const unsigned char*,
                               unsigned int);


//******************************************************************************
/* Function:
    int CRYPT_RSA_PublicEncrypt(CRYPT_RSA_CTX*, unsigned char*,
                            unsigned int, const unsigned char*, unsigned int,
                            CRYPT_RNG_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_RSA_PublicEncrypt(CRYPT_RSA_CTX*, unsigned char*,
                            unsigned int, const unsigned char*, unsigned int,
                            CRYPT_RNG_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_RSA_PrivateDecrypt(CRYPT_RSA_CTX*, unsigned char*,
                             unsigned int, const unsigned char*, unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_RSA_PrivateDecrypt(CRYPT_RSA_CTX*, unsigned char*,
                             unsigned int, const unsigned char*, unsigned int);


//******************************************************************************
/* Function:
    int CRYPT_RSA_EncryptSizeGet(CRYPT_RSA_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_RSA_EncryptSizeGet(CRYPT_RSA_CTX*);                             



/* ECC */
typedef struct CRYPT_ECC_CTX {
    void* holder;
} CRYPT_ECC_CTX;


//******************************************************************************
/* Function:
    int CRYPT_ECC_Initialize(CRYPT_ECC_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_Initialize(CRYPT_ECC_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_ECC_Free(CRYPT_ECC_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_Free(CRYPT_ECC_CTX*);


//******************************************************************************
/* Function:
    int CRYPT_ECC_PublicExport(CRYPT_ECC_CTX*, unsigned char*, unsigned int,
                           unsigned int*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_PublicExport(CRYPT_ECC_CTX*, unsigned char*, unsigned int,
                           unsigned int*);

//******************************************************************************
/* Function:
    int CRYPT_ECC_PublicImport(CRYPT_ECC_CTX*, const unsigned char*, unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_PublicImport(CRYPT_ECC_CTX*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_ECC_PrivateImport(CRYPT_ECC_CTX*, const unsigned char*, unsigned int,
                            const unsigned char*, unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_PrivateImport(CRYPT_ECC_CTX*, const unsigned char*, unsigned int,
                            const unsigned char*, unsigned int);


//******************************************************************************
/* Function:
    int CRYPT_ECC_DHE_KeyMake(CRYPT_ECC_CTX*, CRYPT_RNG_CTX*, int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/
int CRYPT_ECC_DHE_KeyMake(CRYPT_ECC_CTX*, CRYPT_RNG_CTX*, int);

//******************************************************************************
/* Function:
    int CRYPT_ECC_DHE_SharedSecretMake(CRYPT_ECC_CTX*, CRYPT_ECC_CTX*,
                                   unsigned char*, unsigned int, unsigned int*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_DHE_SharedSecretMake(CRYPT_ECC_CTX*, CRYPT_ECC_CTX*,
                                   unsigned char*, unsigned int, unsigned int*);


//******************************************************************************
/* Function:
    int CRYPT_ECC_DSA_HashSign(CRYPT_ECC_CTX*, CRYPT_RNG_CTX*, unsigned char*,
        unsigned int, unsigned int*, const unsigned char*, unsigned int)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_DSA_HashSign(CRYPT_ECC_CTX*, CRYPT_RNG_CTX*, unsigned char*,
        unsigned int, unsigned int*, const unsigned char*, unsigned int);

//******************************************************************************
/* Function:
    int CRYPT_ECC_DSA_HashVerify(CRYPT_ECC_CTX*, const unsigned char*,
                     unsigned int, unsigned char*, unsigned int, int*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_DSA_HashVerify(CRYPT_ECC_CTX*, const unsigned char*,
                     unsigned int, unsigned char*, unsigned int, int*);


//******************************************************************************
/* Function:
    int CRYPT_ECC_KeySizeGet(CRYPT_ECC_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_KeySizeGet(CRYPT_ECC_CTX*);

//******************************************************************************
/* Function:
    int CRYPT_ECC_SignatureSizeGet(CRYPT_ECC_CTX*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
*/

int CRYPT_ECC_SignatureSizeGet(CRYPT_ECC_CTX*);



//******************************************************************************
/* Function:
    int CRYPT_ERROR_StringGet(int, char*)

  Summary:

  Description:

  Precondition:
	
  Parameters:
    Param1		- Pointer to context which saves state between calls.
    Param2		-
    Param3		-
    Param4		-
    Param5		-

  Returns:
	*BAD_FUNC_ARG 	- An invalid pointer was passed to the function.
	*0				- Otherwise.

  Example:
    <code>
    </code>

  Remarks:
	String needs to be >= 80 chars.
*/

int CRYPT_ERROR_StringGet(int, char*);


#ifdef __cplusplus
    }  /* extern "C" */ 
#endif


#endif /* MC_CRYPTO_API_H */

