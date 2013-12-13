#include <xc.h>

#define C0_CONFIG       $16
#define C0_ENTRYLO0     $2
#define C0_ENTRYLO1     $3
#define C0_PAGEMASK     $5
#define C0_WIRED        $6
#define C0_INDEX        $0
#define C0_ENTRYHI      $10

#define CFG1_MMUSSHIFT  25

.set noreorder
.text
.global tlb_init
.ent tlb_init
tlb_init:
    /* Determine if we have a TLB */
    /* Read C0 Config0 */
    mfc0 v1, C0_CONFIG
    /* check MT field */
    ext v1, v1, 7, 3
    li a3, 0x1
    bne v1, a3, done_init_tlb

    /* read C0 Config1 */
    mfc0 v0, C0_CONFIG, 1

start_init_tlb:
    /* Extract MMU Size */
    ext v1, v0, CFG1_MMUSSHIFT, 6

    mtc0 zero, C0_ENTRYLO0
    mtc0 zero, C0_ENTRYLO1
    mtc0 zero, C0_PAGEMASK
    mtc0 zero, C0_WIRED

    li a0, 0x80000000

next_tlb_entry_pair:
    mtc0 v1, C0_INDEX
    mtc0 a0, C0_ENTRYHI

    ehb
    tlbwi

    add a0, (2<<13)
    bne v1, zero, next_tlb_entry_pair
    add v1, -1

waaa_tlb_entries:
    /* Set lowest two TLB entries as fixed (entry 0 and entry 1) */
    li t0, 2
    mtc0 t0, C0_WIRED

    /* Create one 64MB page table entry for EBI consisting of two 32MB physical pages */
    /* 64MB page mask for Entry 0 */
    li t0, 0x07FFE000
    mtc0 t0, C0_PAGEMASK
    /* EBI physical base address <31:12>, caceable (write back), dirty, global set */
    /* First 32MB page in Entrylo0 */
    li t0, 0x00800017
    mtc0 t0, C0_ENTRYLO0
    /* Second 32MB page in EntryLo1 */
    li t0, 0x00880017
    mtc0 t0, C0_ENTRYLO1
    /* TLB entry 0 */
    mtc0 zero, C0_INDEX
    /* EBI virtual base address (ASID 0) */
    li t0, 0xC0000000
    mtc0 t0, C0_ENTRYHI
    ehb
    tlbwi

    /* Create one 64MB page table entry for SQI consisting of two 32MB physical pages */
    /* 64MB page mask for Entry 1 */
    li t0, 0x07FFE000
    mtc0 t0, C0_PAGEMASK
    /* SQI physical base address <31:12>, caceable (write back), dirty, global set */
    /* First 32MB page in Entrylo0 */
    li t0, 0x00C00017
    mtc0 t0, C0_ENTRYLO0
    /* Second 32MB page in EntryLo1 */
    li t0, 0x00C80017
    mtc0 t0, C0_ENTRYLO1
    /* TLB entry 1 */
    li t0, 1
    mtc0 t0, C0_INDEX
    /* SQI virtual base address (ASID 0) */
    li t0, 0xD0000000
    mtc0 t0, C0_ENTRYHI
    ehb
    tlbwi

done_init_tlb:
    jr ra
    nop
.end tlb_init

