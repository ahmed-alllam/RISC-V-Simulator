#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

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

    uint8_t get_name_in_binary() {
        int name_in_decimal = stoi(name.substr(1));
        return bitset<5>(name_in_decimal).to_ulong();
    }

    void print() {
        cout << name << ": " << value << endl;
    }
};

void registers_init();

void registers_print();

Register* get_register_by_name(string name);

Register* get_register_by_binary(uint8_t binary);

extern uint32_t pc;
extern vector<Register> registers;

#endif // REGISTERS_H