swap(int&, int&):
        addi    sp,sp,-48
        sw      s0,44(sp)
        addi    s0,sp,48
        sw      a0,-36(s0)
        sw      a1,-40(s0)
        lw      a5,-36(s0)
        lw      a5,0(a5)
        sw      a5,-20(s0)
        lw      a5,-40(s0)
        lw      a4,0(a5)
        lw      a5,-36(s0)
        sw      a4,0(a5)
        lw      a5,-40(s0)
        lw      a4,-20(s0)
        sw      a4,0(a5)
        nop
        lw      s0,44(sp)
        addi    sp,sp,48
        jr      ra
bubbleSort(int*, int):
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        sw      a0,-36(s0)
        sw      a1,-40(s0)
        sw      zero,-20(s0)
        j       .L3
.L7:
        sw      zero,-24(s0)
        j       .L4
.L6:
        lw      a5,-24(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a5,a4,a5
        lw      a4,0(a5)
        lw      a5,-24(s0)
        addi    a5,a5,1
        slli    a5,a5,2
        lw      a3,-36(s0)
        add     a5,a3,a5
        lw      a5,0(a5)
        ble     a4,a5,.L5
        lw      a5,-24(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a3,a4,a5
        lw      a5,-24(s0)
        addi    a5,a5,1
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a5,a4,a5
        mv      a1,a5
        mv      a0,a3
        call    swap(int&, int&)
.L5:
        lw      a5,-24(s0)
        addi    a5,a5,1
        sw      a5,-24(s0)
.L4:
        lw      a4,-40(s0)
        lw      a5,-20(s0)
        sub     a5,a4,a5
        addi    a5,a5,-1
        lw      a4,-24(s0)
        blt     a4,a5,.L6
        lw      a5,-20(s0)
        addi    a5,a5,1
        sw      a5,-20(s0)
.L3:
        lw      a5,-40(s0)
        addi    a5,a5,-1
        lw      a4,-20(s0)
        blt     a4,a5,.L7
        nop
        nop
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
.LC0:
        .word   64
        .word   34
        .word   25
        .word   12
        .word   22
        .word   11
        .word   90
main:
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        lui     a5,%hi(.LC0)
        addi    a5,a5,%lo(.LC0)
        lw      a6,0(a5)
        lw      a0,4(a5)
        lw      a1,8(a5)
        lw      a2,12(a5)
        lw      a3,16(a5)
        lw      a4,20(a5)
        lw      a5,24(a5)
        sw      a6,-48(s0)
        sw      a0,-44(s0)
        sw      a1,-40(s0)
        sw      a2,-36(s0)
        sw      a3,-32(s0)
        sw      a4,-28(s0)
        sw      a5,-24(s0)
        li      a5,7
        sw      a5,-20(s0)
        addi    a5,s0,-48
        lw      a1,-20(s0)
        mv      a0,a5
        call    bubbleSort(int*, int)
        li      a5,0
        mv      a0,a5
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
