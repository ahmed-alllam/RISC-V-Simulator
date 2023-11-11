#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Instruction {
protected:
    string opcode;

public:
    Instruction(string op) : opcode(op) {}

    virtual void exec() = 0;
    virtual string get_machine_code() = 0;
};

class R_Instruction : public Instruction {
private:
    string funct3;
    string funct7;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;

    void exec_add();
    void exec_sub();
    void exec_sll();
    void exec_slt();
    void exec_sltu();
    void exec_xor();
    void exec_srl();
    void exec_sra();
    void exec_or();
    void exec_and();

public:
    R_Instruction(string op, string f3, string f7, uint32_t rd, uint32_t rs1, uint32_t rs2) : Instruction(op), funct3(f3), funct7(f7), rd(rd), rs1(rs1), rs2(rs2) {}

    void exec() override;
};

class I_Instruction : public Instruction {
private:
    string funct3;
    uint32_t rd;
    uint32_t rs1;
    int32_t imm;

    void exec_addi();
    void exec_slti();
    void exec_sltiu();
    void exec_xori();
    void exec_ori();
    void exec_andi();
    void exec_slli();
    void exec_srli();
    void exec_srai();
    void exec_lb();
    void exec_lh();
    void exec_lw();
    void exec_lbu();
    void exec_lhu();
    void exec_jalr();
    void exec_jal();

public:
    I_Instruction(string op, string f3, uint32_t rd, uint32_t rs1, int32_t imm) : Instruction(op), funct3(f3), rd(rd), rs1(rs1), imm(imm) {}

    void exec() override;
};

class S_Instruction : public Instruction {
private:
    string funct3;
    uint32_t rs1;
    uint32_t rs2;
    int32_t imm;

    void exec_sb();
    void exec_sh();
    void exec_sw();

public:
    S_Instruction(string op, string f3, uint32_t rs1, uint32_t rs2, int32_t imm) : Instruction(op), funct3(f3), rs1(rs1), rs2(rs2), imm(imm) {}

    void exec() override;
};

class B_Instruction : public Instruction {
private:
    string funct3;
    uint32_t rs1;
    uint32_t rs2;
    int32_t imm;

    void exec_beq();
    void exec_bne();
    void exec_blt();
    void exec_bge();
    void exec_bltu();
    void exec_bgeu();

public:
    B_Instruction(string op, string f3, uint32_t rs1, uint32_t rs2, int32_t imm) : Instruction(op), funct3(f3), rs1(rs1), rs2(rs2), imm(imm) {}

    void exec() override;
};

class U_Instruction : public Instruction {
private:
    uint32_t rd;
    int32_t imm;

    void exec_lui();
    void exec_auipc();

public:
    U_Instruction(string op, uint32_t rd, int32_t imm) : Instruction(op), rd(rd), imm(imm) {}

    void exec() override;
};


#endif // INSTRUCTIONS_H
