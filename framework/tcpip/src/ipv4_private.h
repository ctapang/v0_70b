/*******************************************************************************
  IPv4 private API for Microchip TCP/IP Stack

  Summary:
    
  Description:
*******************************************************************************/

/*******************************************************************************
FileName:  ipv4_private.h 
Copyright � 2012 released Microchip Technology Inc.  All rights
reserved.

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

#ifndef _IPV4_PRIVATE_H_
#define _IPV4_PRIVATE_H_



#define ETHERTYPE_IPV4      	(0x0800u)
#define ETHERTYPE_IPV6          (0x86DDu)

// values in network order
#define ETHERTYPE_IPV4_NET     	(0x0008u)
#define ETHERTYPE_IPV6_NET      (0xDD86u)




// IPv4 packet filter registration

typedef struct  _TAG_IPV4_FILTER_LIST_NODE
{
	struct _TAG_IPV4_FILTER_LIST_NODE*  next;       // next node in list
                                                    // makes it valid SGL_LIST_NODE node
    IPV4_FILTER_FUNC                    handler;    // handler to be called for the filter
    const void*                         hParam;     // handler parameter
}IPV4_FILTER_LIST_NODE;



#endif // _IPV4_PRIVATE_H_



