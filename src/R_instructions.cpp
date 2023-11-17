#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void R_Instruction::exec_add()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() + get_register_by_binary(rs2)->get_value());
}

void R_Instruction::exec_sub()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() - get_register_by_binary(rs2)->get_value());
}

void R_Instruction::exec_sll()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() << (get_register_by_binary(rs2)->get_value() & 0x1F));
}

void R_Instruction::exec_slt()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() < get_register_by_binary(rs2)->get_value());
}

void R_Instruction::exec_sltu()
{
    get_register_by_binary(rd)->set_value(static_cast<uint32_t>(get_register_by_binary(rs1)->get_value()) < static_cast<uint32_t>(get_register_by_binary(rs2)->get_value()));
}

void R_Instruction::exec_xor()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() ^ get_register_by_binary(rs2)->get_value());
}

void R_Instruction::exec_srl()
{
    get_register_by_binary(rd)->set_value(static_cast<uint32_t>(get_register_by_binary(rs1)->get_value()) >> (get_register_by_binary(rs2)->get_value() & 0x1F));
}

void R_Instruction::exec_sra()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() >> (get_register_by_binary(rs2)->get_value() & 0x1F));
}

void R_Instruction::exec_or()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() | get_register_by_binary(rs2)->get_value());
}

void R_Instruction::exec_and()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() & get_register_by_binary(rs2)->get_value());
}

void R_Instruction::exec()
{
    pc += 4;

    if (rd == 0)
    {
        return;
    }

    if (funct3 == "000")
    {
        if (funct7 == "0000000")
        {
            exec_add();
        }
        else if (funct7 == "0100000")
        {
            exec_sub();
        }
    }
    else if (funct3 == "001")
    {
        exec_sll();
    }
    else if (funct3 == "010")
    {
        exec_slt();
    }
    else if (funct3 == "011")
    {
        exec_sltu();
    }
    else if (funct3 == "100")
    {
        exec_xor();
    }
    else if (funct3 == "101")
    {
        if (funct7 == "0000000")
        {
            exec_srl();
        }
        else if (funct7 == "0100000")
        {
            exec_sra();
        }
    }
    else if (funct3 == "110")
    {
        exec_or();
    }
    else if (funct3 == "111")
    {
        exec_and();
    }
}

string R_Instruction::get_machine_code() {
    return funct7 + to_string(rs2) + to_string(rs1) + funct3 + to_string(rd) + opcode;
}

bool R_Instruction::is_r_instruction(string op)
{
    return op == "add" || op == "sub" || op == "sll" || op == "slt" || op == "sltu" || op == "xor" || op == "srl" || op == "sra" || op == "or" || op == "and";
}

R_Instruction* R_Instruction::parse_r_instruction(string line)
{
    string original_line = line.substr(0, line.find('#')); // remove comments

    string opcode = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    string rd_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rd = get_register_by_name(rd_str)->get_name_in_binary();

    string rs1_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rs1 = get_register_by_name(rs1_str)->get_name_in_binary();

    string rs2_str = line.substr(0, line.find('\n')).substr(0, line.find('#')); // remove comments
    uint8_t rs2 = get_register_by_name(rs2_str)->get_name_in_binary();

    string funct3;
    string funct7 = "0000000";

    // ToDo: Maybe refactor this along with exec??

    if (opcode == "add")
    {
        funct3 = "000";
    }
    else if (opcode == "sub")
    {
        funct3 = "000";
        funct7 = "0100000";
    }
    else if (opcode == "sll")
    {
        funct3 = "001";
    }
    else if (opcode == "slt")
    {
        funct3 = "010";
    }
    else if (opcode == "sltu")
    {
        funct3 = "011";
    }
    else if (opcode == "xor")
    {
        funct3 = "100";
    }
    else if (opcode == "srl")
    {
        funct3 = "101";
    }
    else if (opcode == "sra") 
    {
        funct3 = "101";
        funct7 = "0100000";
    }
    else if (opcode == "or")
    {
        funct3 = "110";
    }
    else if (opcode == "and")
    {
        funct3 = "111";
    }

    return new R_Instruction("0110011", original_line, funct3, funct7, rd, rs1, rs2);
}