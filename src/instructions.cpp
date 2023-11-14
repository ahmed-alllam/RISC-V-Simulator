#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>

void R_Instruction::exec_add()
{
    registers[rd].set_value(registers[rs1].get_value() + registers[rs2].get_value());
}

void R_Instruction::exec_sub()
{
    registers[rd].set_value(registers[rs1].get_value() - registers[rs2].get_value());
}

void R_Instruction::exec_sll()
{
    registers[rd].set_value(registers[rs1].get_value() << (registers[rs2].get_value() & 0x1F));
}

void R_Instruction::exec_slt()
{
    registers[rd].set_value(static_cast<int32_t>(registers[rs1].get_value()) < static_cast<int32_t>(registers[rs2].get_value()));
}

void R_Instruction::exec_sltu()
{
    registers[rd].set_value(registers[rs1].get_value() < registers[rs2].get_value());
}

void R_Instruction::exec_xor()
{
    registers[rd].set_value(registers[rs1].get_value() ^ registers[rs2].get_value());
}

void R_Instruction::exec_srl()
{
    registers[rd].set_value(registers[rs1].get_value() >> (registers[rs2].get_value() & 0x1F));
}

void R_Instruction::exec_sra()
{
    registers[rd].set_value(static_cast<int32_t>(registers[rs1].get_value()) >> (registers[rs2].get_value() & 0x1F));
}

void R_Instruction::exec_or()
{
    registers[rd].set_value(registers[rs1].get_value() | registers[rs2].get_value());
}

void R_Instruction::exec_and()
{
    registers[rd].set_value(registers[rs1].get_value() & registers[rs2].get_value());
}

void R_Instruction::exec()
{
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
