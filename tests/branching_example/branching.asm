add t0, zero, zero
add t1, zero, zero
bltu t0, t1, L1

L1:
add t0, zero, zero
add t1, zero, zero
beq t1, t0, L2

L2:
beq t0, t1, L1

L3:
add s0, zero, zero