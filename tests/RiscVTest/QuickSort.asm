swap(int*, int*):
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
partition(int*, int, int):
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        sw      a0,-36(s0)
        sw      a1,-40(s0)
        sw      a2,-44(s0)
        lw      a5,-44(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a5,a4,a5
        lw      a5,0(a5)
        sw      a5,-28(s0)
        lw      a5,-40(s0)
        addi    a5,a5,-1
        sw      a5,-20(s0)
        lw      a5,-40(s0)
        sw      a5,-24(s0)
        j       .L3
.L5:
        lw      a5,-24(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a5,a4,a5
        lw      a5,0(a5)
        lw      a4,-28(s0)
        ble     a4,a5,.L4
        lw      a5,-20(s0)
        addi    a5,a5,1
        sw      a5,-20(s0)
        lw      a5,-20(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a3,a4,a5
        lw      a5,-24(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a5,a4,a5
        mv      a1,a5
        mv      a0,a3
        call    swap(int*, int*)
.L4:
        lw      a5,-24(s0)
        addi    a5,a5,1
        sw      a5,-24(s0)
.L3:
        lw      a4,-44(s0)
        lw      a5,-24(s0)
        bgt     a4,a5,.L5
        lw      a5,-20(s0)
        addi    a5,a5,1
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a3,a4,a5
        lw      a5,-44(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a5,a4,a5
        mv      a1,a5
        mv      a0,a3
        call    swap(int*, int*)
        lw      a5,-20(s0)
        addi    a5,a5,1
        mv      a0,a5
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
quickSort(int*, int, int):
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        sw      a0,-36(s0)
        sw      a1,-40(s0)
        sw      a2,-44(s0)
        lw      a4,-40(s0)
        lw      a5,-44(s0)
        bge     a4,a5,.L9
        lw      a2,-44(s0)
        lw      a1,-40(s0)
        lw      a0,-36(s0)
        call    partition(int*, int, int)
        sw      a0,-20(s0)
        lw      a5,-20(s0)
        addi    a5,a5,-1
        mv      a2,a5
        lw      a1,-40(s0)
        lw      a0,-36(s0)
        call    quickSort(int*, int, int)
        lw      a5,-20(s0)
        addi    a5,a5,1
        lw      a2,-44(s0)
        mv      a1,a5
        lw      a0,-36(s0)
        call    quickSort(int*, int, int)
.L9:
        nop
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
.LC0:
        .word   10
        .word   7
        .word   8
        .word   9
        .word   1
        .word   5
main:
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        lui     a5,%hi(.LC0)
        addi    a5,a5,%lo(.LC0)
        lw      a0,0(a5)
        lw      a1,4(a5)
        lw      a2,8(a5)
        lw      a3,12(a5)
        lw      a4,16(a5)
        lw      a5,20(a5)
        sw      a0,-44(s0)
        sw      a1,-40(s0)
        sw      a2,-36(s0)
        sw      a3,-32(s0)
        sw      a4,-28(s0)
        sw      a5,-24(s0)
        li      a5,6
        sw      a5,-20(s0)
        lw      a5,-20(s0)
        addi    a4,a5,-1
        addi    a5,s0,-44
        mv      a2,a4
        li      a1,0
        mv      a0,a5
        call    quickSort(int*, int, int)
        li      a5,0
        mv      a0,a5
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
