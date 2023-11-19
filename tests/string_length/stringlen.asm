L1:
    lb x6, 0(x5)   # Load a byte from the string
    beq x6, x0, L2   # Check if it's null-terminator (0x00)
    addi x5, x5, 1   # Move to the next character in the string
    addi x10, x10, 1   # Increment the counter
    jal x1, L1   # Jump back to the beginning of the loop
L2:
    add x11, x0, x10   # Copy the length from x10 to x11
    ebreak
