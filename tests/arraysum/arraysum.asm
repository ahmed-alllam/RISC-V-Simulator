lw x10, 0(x0) 
lw x11, 4(x0) 
lw x12, 8(x0)
lw x13, 12(x0)

loop:
    bge x11, x13, end
    slli x5, x11, 2  
    add x5, x10, x5 
    lw x6, 0(x5)   
    add x12, x12, x6
    addi x11, x11, 1
    jal x1, loop   
end:
    ebreak
