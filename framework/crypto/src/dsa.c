/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.
  
  Summary:
    Crypto Framework Libarary source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic 
	Framework Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
FileName:   dsa.c
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



#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#ifndef NO_DSA

#include <dsa.h>
#include <sha.h>
#include <random.h>
#include <error.h>


enum {
    DSA_HALF_SIZE = 20,   /* r and s size  */
    DSA_SIG_SIZE  = 40    /* signature size */
};


#ifndef min

    static INLINE word32 min(word32 a, word32 b)
    {
        return a > b ? b : a;
    }

#endif /* min */


void InitDsaKey(DsaKey* key)
{
    key->type = -1;  /* haven't decided yet */

/* TomsFastMath doesn't use memory allocation */
#ifndef USE_FAST_MATH
    key->p.dp = 0;   /* public  alloc parts */
    key->q.dp = 0;    
    key->g.dp = 0;    
    key->y.dp = 0;    

    key->x.dp = 0;   /* private alloc parts */
#endif
}


void FreeDsaKey(DsaKey* key)
{
    (void)key;
/* TomsFastMath doesn't use memory allocation */
#ifndef USE_FAST_MATH
    if (key->type == DSA_PRIVATE)
        mp_clear(&key->x);
    mp_clear(&key->y);
    mp_clear(&key->g);
    mp_clear(&key->q);
    mp_clear(&key->p);
#endif
}


int DsaSign(const byte* digest, byte* out, DsaKey* key, RNG* rng)
{
    mp_int k, kInv, r, s, H;
    int    ret = 0, sz;
    byte   buffer[DSA_HALF_SIZE];

    if (mp_init_multi(&k, &kInv, &r, &s, &H, 0) != MP_OKAY)
        return MP_INIT_E;

    sz = min(sizeof(buffer), mp_unsigned_bin_size(&key->q)); 

    /* generate k */
    RNG_GenerateBlock(rng, buffer, sz);
    buffer[0] |= 0x0C;

    if (mp_read_unsigned_bin(&k, buffer, sz) != MP_OKAY)
        ret = MP_READ_E;

    if (mp_cmp_d(&k, 1) != MP_GT)
        ret = MP_CMP_E;

    /* inverse k mod q */
    if (ret == 0 && mp_invmod(&k, &key->q, &kInv) != MP_OKAY)
        ret = MP_INVMOD_E;

    /* generate r, r = (g exp k mod p) mod q */
    if (ret == 0 && mp_exptmod(&key->g, &k, &key->p, &r) != MP_OKAY)
        ret = MP_EXPTMOD_E;

    if (ret == 0 && mp_mod(&r, &key->q, &r) != MP_OKAY)
        ret = MP_MOD_E;

    /* generate H from sha digest */
    if (ret == 0 && mp_read_unsigned_bin(&H, digest,SHA_DIGEST_SIZE) != MP_OKAY)
        ret = MP_READ_E;

    /* generate s, s = (kInv * (H + x*r)) % q */
    if (ret == 0 && mp_mul(&key->x, &r, &s) != MP_OKAY)
        ret = MP_MUL_E;

    if (ret == 0 && mp_add(&s, &H, &s) != MP_OKAY)
        ret = MP_ADD_E;

    if (ret == 0 && mp_mulmod(&s, &kInv, &key->q, &s) != MP_OKAY)
        ret = MP_MULMOD_E;

    /* write out */
    if (ret == 0)  {
        int rSz = mp_unsigned_bin_size(&r);
        int sSz = mp_unsigned_bin_size(&s);

        if (rSz == DSA_HALF_SIZE - 1) {
            out[0] = 0;
            out++;
        }

        if (mp_to_unsigned_bin(&r, out) != MP_OKAY)
            ret = MP_TO_E;
        else {
            if (sSz == DSA_HALF_SIZE - 1) {
                out[rSz] = 0;
                out++;
            }    
            ret = mp_to_unsigned_bin(&s, out + rSz);
        }
    }

    mp_clear(&H);
    mp_clear(&s);
    mp_clear(&r);
    mp_clear(&kInv);
    mp_clear(&k);

    return ret;
}


int DsaVerify(const byte* digest, const byte* sig, DsaKey* key, int* answer)
{
    mp_int w, u1, u2, v, r, s;
    int    ret = 0;

    if (mp_init_multi(&w, &u1, &u2, &v, &r, &s) != MP_OKAY)
        return MP_INIT_E;

    /* set r and s from signature */
    if (mp_read_unsigned_bin(&r, sig, DSA_HALF_SIZE) != MP_OKAY ||
        mp_read_unsigned_bin(&s, sig + DSA_HALF_SIZE, DSA_HALF_SIZE) != MP_OKAY)
        ret = MP_READ_E;

    /* sanity checks */


    /* put H into u1 from sha digest */
    if (ret == 0 && mp_read_unsigned_bin(&u1,digest,SHA_DIGEST_SIZE) != MP_OKAY)
        ret = MP_READ_E;

    /* w = s invmod q */
    if (ret == 0 && mp_invmod(&s, &key->q, &w) != MP_OKAY)
        ret = MP_INVMOD_E;

    /* u1 = (H * w) % q */
    if (ret == 0 && mp_mulmod(&u1, &w, &key->q, &u1) != MP_OKAY)
        ret = MP_MULMOD_E;

    /* u2 = (r * w) % q */
    if (ret == 0 && mp_mulmod(&r, &w, &key->q, &u2) != MP_OKAY)
        ret = MP_MULMOD_E;

    /* verify v = ((g^u1 * y^u2) mod p) mod q */
    if (ret == 0 && mp_exptmod(&key->g, &u1, &key->p, &u1) != MP_OKAY)
        ret = MP_EXPTMOD_E;

    if (ret == 0 && mp_exptmod(&key->y, &u2, &key->p, &u2) != MP_OKAY)
        ret = MP_EXPTMOD_E;

    if (ret == 0 && mp_mulmod(&u1, &u2, &key->p, &v) != MP_OKAY)
        ret = MP_MULMOD_E;

    if (ret == 0 && mp_mod(&v, &key->q, &v) != MP_OKAY)
        ret = MP_MULMOD_E;

    /* do they match */
    if (ret == 0 && mp_cmp(&r, &v) == MP_EQ)
        *answer = 1;
    else
        *answer = 0;

    mp_clear(&s);
    mp_clear(&r);
    mp_clear(&u1);
    mp_clear(&u2);
    mp_clear(&w);
    mp_clear(&v);

    return ret;
}


#endif /* NO_DSA */

