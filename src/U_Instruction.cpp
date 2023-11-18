#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void U_Instruction::exec_lui()
{
    get_register_by_binary(rd)->set_value(imm << 12);
}

void U_Instruction::exec_auipc()
{
    get_register_by_binary(rd)->set_value(pc + (imm << 12));
}

void U_Instruction::exec()
{
    pc += 4;

    if (rd == 0)
    {
        return;
    }

    if (opcode == "0110111")
    {
        exec_lui();
    }
    else if (opcode == "0010111")
    {
        exec_auipc();
    }
}

string U_Instruction::get_machine_code() {
    string imm_str = bitset<20>(imm).to_string();
    string rd_str = bitset<5>(rd).to_string();

    return imm_str + rd_str + opcode;
}

bool U_Instruction::is_u_instruction(string op)
{
    return op == "lui" || op == "auipc";
}

U_Instruction* U_Instruction::parse_u_instruction(string line)
{
    string original_line = line.substr(0, line.find('#')); // remove comments

    string op = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    string rd_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rd = stoi(rd_str.substr(1));

    int32_t imm = stoi(line);

    if (op == "lui")
    {
        op = "0110111";
    }
    else // "auipc"
    {
        op = "0010111";
    }

    return new U_Instruction(op, original_line, rd, imm);
}