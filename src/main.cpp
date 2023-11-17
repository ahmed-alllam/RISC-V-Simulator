#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "memory.h"
#include "registers.h"
#include "instructions.h"

using namespace std;

uint32_t pc = 0x0;
vector<Register> registers;
vector<Instruction*> instructions;
map<string, uint32_t> labels;

int main() {
    cout << "Hello and Welcome to our RISC-V Simulator!" << endl;

    registers_init();

    cout << "Please enter the path of the .asm file you would like to run: ";
    string filename;
    cin >> filename; // TODO: check if file exists

    ifstream asmfile;
    asmfile.open(filename);

    cout << "Please enter the path of the memory file, or enter 'none' if you do not have one: ";
    string memfilePath;
    cin >> memfilePath; // TODO: check if file exists

    if (memfilePath != "none") {
        ifstream memfile;
        memfile.open(memfilePath);
        memory_init(memfile);
    }

    cout << "Please enter the starting address of the program: ";
    uint32_t startAddr;
    cin >> startAddr; // TODO: check if address is valid

    pc = startAddr;

    instructions_init(asmfile);

    while ((pc - startAddr) / 4 < instructions.size()) {
        Instruction *instr = instructions[(pc - startAddr) / 4];

        cout << "Executing instruction: ";
        instr->print();

        instr->exec();

        cout << "Program Counter now at: " << pc << endl;
        cout << "Registers: " << endl;
        registers_print();
    }

    // Todo: Add option to print machine code of instructions

    cout << "Program finished :)" << endl;

    return 0;
}