#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void B_Instruction::exec_beq()
{
    if (get_register_by_binary(rs1)->get_value() == get_register_by_binary(rs2)->get_value())
    {
        pc += imm * 4;
    } else {
        pc += 4;
    }
}

void B_Instruction::exec_bne()
{
    if (get_register_by_binary(rs1)->get_value() != get_register_by_binary(rs2)->get_value())
    {
        pc += imm * 4;
    } else {
        pc += 4;
    }
}

void B_Instruction::exec_blt()
{
    if (get_register_by_binary(rs1)->get_value() < get_register_by_binary(rs2)->get_value())
    {
        pc += imm * 4;
    } else {
        pc += 4;
    }
}

void B_Instruction::exec_bge()
{
    if (get_register_by_binary(rs1)->get_value() >= get_register_by_binary(rs2)->get_value())
    {
        pc += imm * 4;
    } else {
        pc += 4;
    }
}

void B_Instruction::exec_bltu()
{
    if (static_cast<uint32_t>(get_register_by_binary(rs1)->get_value()) < static_cast<uint32_t>(get_register_by_binary(rs2)->get_value()))
    {
        pc += imm * 4;
    } else {
        pc += 4;
    }
}

void B_Instruction::exec_bgeu()
{
    if (static_cast<uint32_t>(get_register_by_binary(rs1)->get_value()) >= static_cast<uint32_t>(get_register_by_binary(rs2)->get_value()))
    {
        pc += imm * 4;
    } else {
        pc += 4;
    }
}

void B_Instruction::exec()
{
    if (imm == -1)
    {
        label_to_imm();
    }

    if (funct3 == "000")
    {
        exec_beq();
    }
    else if (funct3 == "001")
    {
        exec_bne();
    }
    else if (funct3 == "100")
    {
        exec_blt();
    }
    else if (funct3 == "101")
    {
        exec_bge();
    }
    else if (funct3 == "110")
    {
        exec_bltu();
    }
    else if (funct3 == "111")
    {
        exec_bgeu();
    }
}

string B_Instruction::get_machine_code() {
    if (imm == -1)
    {
        label_to_imm();
    }

    string imm_1 = bitset<1>(imm >> 11).to_string();
    string imm_2 = bitset<6>((imm >> 4) & 0x3F).to_string();
    string imm_3 = bitset<4>((imm & 0xF) << 1).to_string();
    string imm_4 = bitset<1>((imm >> 10) & 0x1).to_string();

    string rs1_bin = bitset<5>(rs1).to_string();
    string rs2_bin = bitset<5>(rs2).to_string();

    return imm_1 + imm_2 + rs2_bin + rs1_bin + funct3 + imm_3 + imm_4 + opcode;
}

void B_Instruction::label_to_imm()
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

    imm = (labels[label] - (current_instruction_index * 4 + startAddr)) / 4;
}

bool B_Instruction::is_b_instruction(string op)
{
    return op == "beq" || op == "bne" || op == "blt" || op == "bge" || op == "bltu" || op == "bgeu";
}

B_Instruction* B_Instruction::parse_b_instruction(string line)
{
    string original_line = line.substr(0, line.find('#')); // remove comments

    string op = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    string rs1_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rs1 = get_register_by_name(rs1_str)->get_name_in_binary();

    string rs2_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rs2 = get_register_by_name(rs2_str)->get_name_in_binary();

    string label = line.substr(1, line.find('\n'));
    uint32_t imm = -1; // -1 by default, until we find the label

    string funct3;

    if (op == "beq")
    {
        funct3 = "000";
    }
    else if (op == "bne")
    {
        funct3 = "001";
    }
    else if (op == "blt")
    {
        funct3 = "100";
    }
    else if (op == "bge")
    {
        funct3 = "101";
    }
    else if (op == "bltu")
    {
        funct3 = "110";
    }
    else if (op == "bgeu")
    {
        funct3 = "111";
    }

    return new B_Instruction("1100011", original_line, funct3, rs1, rs2, imm, label);
}