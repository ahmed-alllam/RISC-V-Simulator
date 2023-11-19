myStrcpy(char*, char const*):
        addi    sp,sp,-32
        sw      s0,28(sp)
        addi    s0,sp,32
        sw      a0,-20(s0)
        sw      a1,-24(s0)
        j       .L2
.L3:
        lw      a5,-24(s0)
        addi    a4,a5,1
        sw      a4,-24(s0)
        lbu     a4,0(a5)
        lw      a5,-20(s0)
        addi    a3,a5,1
        sw      a3,-20(s0)
        sb      a4,0(a5)
.L2:
        lw      a5,-24(s0)
        lbu     a5,0(a5)
        bne     a5,zero,.L3
        lw      a5,-20(s0)
        sb      zero,0(a5)
        nop
        lw      s0,28(sp)
        addi    sp,sp,32
        jr      ra
main:
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        li      a5,1819041792
        addi    a5,a5,1352
        sw      a5,-28(s0)
        li      a5,1867980800
        addi    a5,a5,111
        sw      a5,-24(s0)
        li      a5,6582272
        addi    a5,a5,-910
        sw      a5,-20(s0)
        addi    a4,s0,-28
        addi    a5,s0,-48
        mv      a1,a4
        mv      a0,a5
        call    myStrcpy(char*, char const*)
        li      a5,0
        mv      a0,a5
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
