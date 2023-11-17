#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void instructions_init(ifstream &asmfile)
{
    string line;
    while (getline(asmfile, line))
    {
        if (line[0] == '#')
        { // comment
            continue;
        }
        else if (line[0] == '.')
        { // directive. ToDo: implement directives
            continue;
        }
        else if (line.find(' ') == string::npos && line.find(':') != string::npos)
        { // label
            string label = line.substr(0, line.find(':'));
            labels[label] = instructions.size() * 4 + pc;
        }
        else
        {
            string opcode = line.substr(0, line.find(' '));

            if (R_Instruction::is_r_instruction(opcode))
            {
                instructions.push_back(R_Instruction::parse_r_instruction(line));
            }
            // else if (I_Instruction::is_i_instruction(opcode)) {
            //     instructions.push_back(I_Instruction::parse_i_instruction(line));
            // } else if (S_Instruction::is_s_instruction(opcode)) {
            //     instructions.push_back(S_Instruction::parse_s_instruction(line));
            // } else if (B_Instruction::is_b_instruction(opcode)) {
            //     instructions.push_back(B_Instruction::parse_b_instruction(line));
            // } else if (U_Instruction::is_u_instruction(opcode)) {
            //     instructions.push_back(U_Instruction::parse_u_instruction(line));
            // }
            else
            {
                cout << "Error: Invalid instruction" << endl;
                exit(1);
            }
        }
    }
}
