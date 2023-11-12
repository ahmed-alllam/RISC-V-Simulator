#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

extern uint32_t pc;
extern vector<Register> registers;

class Register {
private:
    uint32_t value = 0;
    string name;
    string ABI_name;

public:
    Register(string n, string ABI_n) : name(n), ABI_name(ABI_n) {}

    void set_value(uint32_t val) {
        value = val;
    }

    uint32_t get_value() {
        return value;
    }

    string get_name() {
        return name;
    }

    string get_ABI_name() {
        return ABI_name;
    }

    void print() {
        cout << name << ": " << value << endl;
    }
};


void registers_init();

void registers_print();

#endif // REGISTERS_H