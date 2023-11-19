#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <string>

using namespace std;

void I_Instruction::exec_addi()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() + imm);
}

void I_Instruction::exec_xori()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() ^ imm);
}

void I_Instruction::exec_ori()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() | imm);
}

void I_Instruction::exec_andi()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() & imm);
}

void I_Instruction::exec_slti()
{
    int32_t rs1_value = get_register_by_binary(rs1)->get_value();
    int32_t imm_value = imm;

    get_register_by_binary(rd)->set_value(rs1_value < imm_value ? 1 : 0);
}

void I_Instruction::exec_sltiu()
{
    uint32_t rs1_value = get_register_by_binary(rs1)->get_value();
    uint32_t imm_value = imm;

    get_register_by_binary(rd)->set_value(rs1_value < imm_value ? 1 : 0);
}

void I_Instruction::exec_slli()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() << imm);
}

void I_Instruction::exec_srli()
{
    get_register_by_binary(rd)->set_value(get_register_by_binary(rs1)->get_value() >> imm);
}

void I_Instruction::exec_srai()
{
    int32_t rs1_value = get_register_by_binary(rs1)->get_value();
    uint32_t imm_value = imm;

    get_register_by_binary(rd)->set_value(rs1_value >> (imm_value & 0x1F));
}

void I_Instruction::exec_lbu()
{
    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;

    if (address > ((1 << 11) - 1))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    uint8_t loadedByte = memory[address];

    get_register_by_binary(rd)->set_value(static_cast<uint32_t>(loadedByte));
}

void I_Instruction::exec_lb()
{

    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;

    if (address > ((1 << 11) - 1))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    int8_t loadedByte = memory[address];

    get_register_by_binary(rd)->set_value(static_cast<uint32_t>(loadedByte));
}

void I_Instruction::exec_lhu()
{

    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;

    if (address > ((1 << 11) - 2))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    uint16_t loadedHalfword = 0;

    for (int i = 0; i < 2; i++)
    {
        loadedHalfword |= static_cast<uint16_t>(memory[address + i]) << (i * 8);
    }

    get_register_by_binary(rd)->set_value(static_cast<uint32_t>(loadedHalfword));
}

void I_Instruction::exec_lh()
{

    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;

    if (address > ((1 << 11) - 2))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    int16_t loadedHalfword = 0;

    for (int i = 0; i < 2; i++)
    {
        loadedHalfword |= static_cast<int16_t>(memory[address + i]) << (i * 8);
    }

    get_register_by_binary(rd)->set_value(static_cast<uint32_t>(loadedHalfword));
}

void I_Instruction::exec_lw()
{
    uint32_t address = get_register_by_binary(rs1)->get_value() + imm;
    uint32_t loadedValue = 0;

    if (address > ((1 << 11) - 4))
    {
        cout << "Invalid address: " << address << endl;
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        loadedValue |= static_cast<uint32_t>(memory[address + i]) << (i * 8);
    }

    get_register_by_binary(rd)->set_value(loadedValue);
}


void I_Instruction::exec_jalr()
{
    uint32_t target_address = get_register_by_binary(rs1)->get_value() + imm;

    get_register_by_binary(rd)->set_value(pc + 4);

    pc = target_address;
}

void I_Instruction::exec()
{
    if (opcode != "1100111")
        pc += 4;

    if (rd == 0)
    {
        return;
    }

    if (opcode == "0010011")
    {
        if (funct3 == "001")
        {
            exec_slli();
        }
        else if (funct3 == "101")
        {
            if (imm >> 5 == 0)
            {
                exec_srli();
            }
            else
            {
                exec_srai();
            }
        }
        else if (funct3 == "000")
        {
            exec_addi();
        }
        else if (funct3 == "010")
        {
            exec_slti();
        }
        else if (funct3 == "011")
        {
            exec_sltiu();
        }
        else if (funct3 == "100")
        {
            exec_xori();
        }
        else if (funct3 == "110")
        {
            exec_ori();
        }
        else if (funct3 == "111")
        {
            exec_andi();
        }
    }
    else if (opcode == "0000011")
    {
        if (funct3 == "000")
        {
            exec_lb();
        }
        else if (funct3 == "001")
        {
            exec_lh();
        }
        else if (funct3 == "010")
        {
            exec_lw();
        }
        else if (funct3 == "100")
        {
            exec_lbu();
        }
        else if (funct3 == "101")
        {
            exec_lhu();
        }
    }
    else if (opcode == "1100111")
    {
        exec_jalr();
    }
}

string I_Instruction::get_machine_code()
{
    string rs1_bin = bitset<5>(rs1).to_string();
    string rd_bin = bitset<5>(rd).to_string();
    string imm_bin = bitset<12>(imm).to_string();

    return imm_bin + rs1_bin + funct3 + rd_bin + opcode;
}

bool I_Instruction::is_i_instruction(string op)
{
    return op == "lb" || op == "lh" || op == "lw" || op == "lbu" || op == "lhu" || op == "addi" || op == "slti" || op == "sltiu" || op == "xori" || op == "ori" || op == "andi" || op == "slli" || op == "srli" || op == "srai" || op == "jalr";
}

I_Instruction *I_Instruction::parse_i_instruction(string line)
{
    string original_line = line.substr(0, line.find('#'));

    string opcode = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    string rd_str = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    uint8_t rd = get_register_by_name(rd_str)->get_name_in_binary();

    string rs1_str;
    uint8_t rs1;
    int32_t imm;

    if (opcode == "jalr")
    {
        // try to parse rs1, imm. use if statement to check if the line has (
        if (original_line.find('(') != string::npos)
        {
            imm = stoi(line.substr(0, line.find('(')));
            line = line.substr(line.find('(') + 1);
            rs1_str = line.substr(0, line.find(')'));
        }
        else
        {
            rs1_str = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1);
            imm = stoi(line);
        }
    }
    else if (opcode == "lb" || opcode == "lh" || opcode == "lw" || opcode == "lbu" || opcode == "lhu")
    {
        imm = stoi(line.substr(0, line.find('(')));
        line = line.substr(line.find('(') + 1);
        rs1_str = line.substr(0, line.find(')'));
    }
    else
    {
        rs1_str = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        imm = stoi(line);
    }

    rs1 = get_register_by_name(rs1_str)->get_name_in_binary();

    if (opcode == "addi" || opcode == "slti" || opcode == "sltiu" || opcode == "xori" || opcode == "ori" || opcode == "andi" || opcode == "slli" || opcode == "srli" || opcode == "srai")
    {
        opcode = "0010011";
    }
    else if (opcode == "lb" || opcode == "lh" || opcode == "lw" || opcode == "lbu" || opcode == "lhu")
    {
        opcode = "0000011";
    }
    else if (opcode == "jalr")
    {
        opcode = "1100111";
    }

    string funct3;

    if (opcode == "0010011")
    {
        if (original_line.find("slli") != string::npos)
        {
            funct3 = "001";
        }
        else if (original_line.find("srli") != string::npos)
        {
            funct3 = "101";
        }
        else if (original_line.find("srai") != string::npos)
        {
            funct3 = "101";
        }
        else if (original_line.find("addi") != string::npos)
        {
            funct3 = "000";
        }
        else if (original_line.find("slti") != string::npos)
        {
            funct3 = "010";
        }
        else if (original_line.find("sltiu") != string::npos)
        {
            funct3 = "011";
        }
        else if (original_line.find("xori") != string::npos)
        {
            funct3 = "100";
        }
        else if (original_line.find("ori") != string::npos)
        {
            funct3 = "110";
        }
        else if (original_line.find("andi") != string::npos)
        {
            funct3 = "111";
        }
    }
    else if (opcode == "0000011")
    {
        if (original_line.find("lb") != string::npos)
        {
            funct3 = "000";
        }
        else if (original_line.find("lh") != string::npos)
        {
            funct3 = "001";
        }
        else if (original_line.find("lw") != string::npos)
        {
            funct3 = "010";
        }
        else if (original_line.find("lbu") != string::npos)
        {
            funct3 = "100";
        }
        else if (original_line.find("lhu") != string::npos)
        {
            funct3 = "101";
        }
    }
    else if (opcode == "1100111")
    {
        funct3 = "000";
    }

    return new I_Instruction(opcode, original_line, funct3, rd, rs1, imm);
}
