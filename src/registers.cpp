#include "registers.h"
#include "instructions.h"
#include "memory.h"

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
    cout << "Registers: " << endl;

    cout << "Name   Value (dec) (hex) (binary)" << endl;

    for (int i = 0; i < registers.size(); i++) {
        registers[i].print();
    }
}

void PC_print() {
    cout << "Program Counter at: " << pc << "   0x" << decimal_to_hex(pc) << "   0b" << decimal_to_binary(pc, 32) << endl;
}

Register* get_register_by_name(string name) {
    name.erase(name.find_last_not_of(' ') + 1);
    name.erase(0, name.find_first_not_of(' '));

    for (int i = 0; i < registers.size(); i++) {
        if (registers[i].get_name() == name || registers[i].get_ABI_name() == name) {
            return &registers[i];
        }
    }

    cout << "Error: Invalid register name" << endl;
    exit(1);
}

Register* get_register_by_binary(uint8_t binary) {
    for (int i = 0; i < registers.size(); i++) {
        if (registers[i].get_name_in_binary() == binary) {
            return &registers[i];
        }
    }

    cout << "Error: Invalid register binary" << endl;
    exit(1);
}