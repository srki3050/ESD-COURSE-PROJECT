/*
 * port.c
 *
 *  Created on: Apr 15, 2022
 *      Author: unnia
 */

#include <inc/port.h>

void portRemap(void) {
    PMAP->KEYID = 0x2D52;           /* unlock PMAP */

    P2MAP->PMAP_REGISTER1 = 23;     /* remap P2.1 to 23 (TPM0.4) */
    P2->DIR |= 2;
    P2->SEL0 |= 2;
    P2->SEL1 &= ~2;

    PMAP->CTL = 1;                  /* lock PMAP */
    PMAP->KEYID = 0;
}
