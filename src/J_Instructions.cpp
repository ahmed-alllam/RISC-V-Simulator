
#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void J_Instruction::exec_jal()
{
    if (rd != 0)
    {
        get_register_by_binary(rd)->set_value(pc + 4);
    }

    pc += imm * 4;
}

void J_Instruction::exec()
{
    if (imm == -1)
    {
        label_to_imm();
    }

    exec_jal();
}

void J_Instruction::label_to_imm()
{
    if (labels.find(label) == labels.end())
    {
        cout << "Label " << label << " not found" << endl;
        exit(1);
    }

    int current_instruction_index;

    for (int i = 0; i < instructions.size(); i++)
    {
        if (instructions[i] == this)
        {
            current_instruction_index = i;
            break;
        }
    }

    imm = (static_cast<int32_t>(labels[label]) - (static_cast<int32_t>(current_instruction_index) * 4 + static_cast<int32_t>(startAddr))) / 4;
}

string J_Instruction::get_machine_code() {
    if (imm == -1)
    {
        label_to_imm();
    }

    string imm_1 = bitset<1>(imm >> 20).to_string();
    string imm_2 = bitset<10>(imm >> 1).to_string();
    string imm_3 = bitset<1>(imm >> 11).to_string();
    string imm_4 = bitset<8>(imm >> 12).to_string();
    string rd_str = bitset<5>(rd).to_string();

    return imm_1 + imm_2 + imm_3 + imm_4 + rd_str + opcode;
}

bool J_Instruction::is_j_instruction(string op)
{
    return op == "jal";
}

J_Instruction* J_Instruction::parse_j_instruction(string line)
{
    string original_line = line.substr(0, line.find('#')); // remove comments

    string op = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    string rd_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rd = get_register_by_name(rd_str)->get_name_in_binary();

    string label = line.substr(1, line.find('\n'));
    uint32_t imm = -1; // -1 by default, until we find the label

    return new J_Instruction("1101111", original_line, rd, imm, label);
}