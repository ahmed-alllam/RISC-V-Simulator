#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Instruction {
protected:
    string opcode;
    string asm_line;

public:
    Instruction(string op, string line) : opcode(op), asm_line(line) {}

    void print() {
        cout << asm_line << endl;
    }

    virtual void exec() = 0;
    virtual string get_machine_code() = 0;
};

class R_Instruction : public Instruction {
private:
    string funct3;
    string funct7;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;

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
    R_Instruction(string op, string line, string f3, string f7, uint8_t rd, uint8_t rs1, uint8_t rs2) : Instruction(op, line), funct3(f3), funct7(f7), rd(rd), rs1(rs1), rs2(rs2) {}

    void exec() override;
    string get_machine_code() override;

    static bool is_r_instruction(string op);
    static R_Instruction* parse_r_instruction(string line);
};

// class I_Instruction : public Instruction {
// private:
//     string funct3;
//     uint8_t rd;
//     uint8_t rs1;
//     int32_t imm;

//     void exec_addi();
//     void exec_slti();
//     void exec_sltiu();
//     void exec_xori();
//     void exec_ori();
//     void exec_andi();
//     void exec_slli();
//     void exec_srli();
//     void exec_srai();
//     void exec_lb();
//     void exec_lh();
//     void exec_lw();
//     void exec_lbu();
//     void exec_lhu();
//     void exec_jalr();
//     void exec_jal();

// public:
//     I_Instruction(string op, string line, string f3, uint8_t rd, uint8_t rs1, int32_t imm) : Instruction(op, line), funct3(f3), rd(rd), rs1(rs1), imm(imm) {}

//     void exec() override;

//     static bool is_i_instruction(string op);
//     static I_Instruction* parse_i_instruction(string line);
// };

class S_Instruction : public Instruction {
private:
    string funct3;
    uint8_t rs1;
    uint8_t rs2;
    int32_t imm;

    void exec_sb();
    void exec_sh();
    void exec_sw();

public:
    S_Instruction(string op, string line, string f3, uint8_t rs1, uint8_t rs2, int32_t imm) : Instruction(op, line), funct3(f3), rs1(rs1), rs2(rs2), imm(imm) {}

    void exec() override;
    string get_machine_code() override;

    static bool is_s_instruction(string op);
    static S_Instruction* parse_s_instruction(string line);
};

class B_Instruction : public Instruction {
private:
    string funct3;
    uint8_t rs1;
    uint8_t rs2;
    int32_t imm;
    string label;

    void exec_beq();
    void exec_bne();
    void exec_blt();
    void exec_bge();
    void exec_bltu();
    void exec_bgeu();

public:
    B_Instruction(string op, string line, string f3, uint8_t rs1, uint8_t rs2, int32_t imm, string label) : Instruction(op, line), funct3(f3), rs1(rs1), rs2(rs2), imm(imm), label(label) {}

    void exec() override;
    string get_machine_code() override;

    void label_to_imm();

    static bool is_b_instruction(string op);
    static B_Instruction* parse_b_instruction(string line);
};

// class U_Instruction : public Instruction {
// private:
//     uint8_t rd;
//     int32_t imm;

//     void exec_lui();
//     void exec_auipc();

// public:
//     U_Instruction(string op, string line, uint8_t rd, int32_t imm) : Instruction(op, line), rd(rd), imm(imm) {}

//     void exec() override;

//     static bool is_u_instruction(string op);
//     static U_Instruction* parse_u_instruction(string line);
// };

void instructions_init(ifstream &asmfile);

extern vector<Instruction*> instructions;
extern map<string, uint32_t> labels;

#endif // INSTRUCTIONS_H
