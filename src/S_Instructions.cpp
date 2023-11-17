#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void S_Instruction::exec_sb()
{
    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;
    uint32_t value = get_register_by_binary(rs2)->get_value();

    // check if address is valid
    if (address > ((1 << 11) - 1))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    memory[address] = value & 0xFF;
}

void S_Instruction::exec_sh()
{
    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;
    uint32_t value = get_register_by_binary(rs2)->get_value();

    // check if address is valid
    if (address > ((1 << 11) - 1))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    for (int i = 0; i < 2; i++)
    {
        memory[address + i] = (value >> (i * 8)) & 0xFF;
    }
}

void S_Instruction::exec_sw()
{
    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;
    uint32_t value = get_register_by_binary(rs2)->get_value();

    // check if address is valid
    if (address > ((1 << 11) - 1))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        memory[address + i] = (value >> (i * 8)) & 0xFF;
    }
}

void S_Instruction::exec()
{
    pc += 4;

    if (funct3 == "000")
        exec_sb();
    else if (funct3 == "001")
        exec_sh();
    else if (funct3 == "010")
        exec_sw();
}

string S_Instruction::get_machine_code() {
    string imm_upper = bitset<7>(imm >> 5).to_string(); // imm[11:5]
    string imm_lower = bitset<5>(imm).to_string();      // imm[4:0]

    string rs1_bin = bitset<5>(rs1).to_string();
    string rs2_bin = bitset<5>(rs2).to_string();

    return imm_upper + rs2_bin + rs1_bin + funct3 + imm_lower + opcode;
}

bool S_Instruction::is_s_instruction(string op)
{
    return op == "sb" || op == "sh" || op == "sw";
}

S_Instruction* S_Instruction::parse_s_instruction(string line)
{
    string original_line = line.substr(0, line.find('#')); // remove comments

    string op = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    string rs1_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rs1 = get_register_by_name(rs1_str)->get_name_in_binary();

    string imm_str = line.substr(0, line.find('('));
    line = line.substr(line.find('(') + 1);
    int32_t imm = stoi(imm_str);

    string rs2_str = line.substr(0, line.find(')'));
    uint8_t rs2 = get_register_by_name(rs2_str)->get_name_in_binary();

    string funct3;

    if (op == "sb")
    {
        funct3 = "000";
    }
    else if (op == "sh")
    {
        funct3 = "001";
    }
    else if (op == "sw")
    {
        funct3 = "010";
    }

    return new S_Instruction("0100011", original_line, funct3, rs1, rs2, imm);
}