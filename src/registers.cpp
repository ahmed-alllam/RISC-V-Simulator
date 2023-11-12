#include "registers.h"

void registers_init() {
    // source: https://en.wikichip.org/wiki/risc-v/registers

    registers.push_back(Register("x0", "zero"));
    registers.push_back(Register("x1", "ra"));
    registers.push_back(Register("x2", "sp"));
    registers.push_back(Register("x3", "gp"));
    registers.push_back(Register("x4", "tp"));
    registers.push_back(Register("x5", "t0"));
    registers.push_back(Register("x6", "t1"));
    registers.push_back(Register("x7", "t2"));
    registers.push_back(Register("x8", "s0"));
    registers.push_back(Register("x9", "s1"));
    registers.push_back(Register("x10", "a0"));
    registers.push_back(Register("x11", "a1"));
    registers.push_back(Register("x12", "a2"));
    registers.push_back(Register("x13", "a3"));
    registers.push_back(Register("x14", "a4"));
    registers.push_back(Register("x15", "a5"));
    registers.push_back(Register("x16", "a6"));
    registers.push_back(Register("x17", "a7"));
    registers.push_back(Register("x18", "s2"));
    registers.push_back(Register("x19", "s3"));
    registers.push_back(Register("x20", "s4"));
    registers.push_back(Register("x21", "s5"));
    registers.push_back(Register("x22", "s6"));
    registers.push_back(Register("x23", "s7"));
    registers.push_back(Register("x24", "s8"));
    registers.push_back(Register("x25", "s9"));
    registers.push_back(Register("x26", "s10"));
    registers.push_back(Register("x27", "s11"));
    registers.push_back(Register("x28", "t3"));
    registers.push_back(Register("x29", "t4"));
    registers.push_back(Register("x30", "t5"));
    registers.push_back(Register("x31", "t6"));
}

void registers_print() {
    for (int i = 0; i < registers.size(); i++) {
        registers[i].print();
    }
}
