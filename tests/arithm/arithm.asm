    addi x1, x0, 10
    addi x2, x0, 5

    add x3, x1, x2
    sub x4, x1, x2 

    and x7, x1, x2 
    or x8, x1, x2 
    xor x9, x1, x2
    sll x13, x1, x2
    srl x14, x1, x2 
    sra x15, x1, x2

    sw x3, 0(zero)
    sw x4, 4(zero)
    sw x5, 8(zero) 
    sw x6, 12(zero)
    sw x7, 16(zero) 
    sw x8, 20(zero)
    sw x9, 24(zero)
    sw x13, 28(zero) 
    sw x14, 32(zero)
    sw x15, 36(zero)

    ecall