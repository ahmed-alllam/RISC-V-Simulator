#include <iostream>
#include <string>
#include <vector>

#include "memory.h"
#include "registers.h"
#include "instructions.h"

using namespace std;

uint32_t pc = 0x0;
vector<Register> registers;

int main() {
    cout << "Hello and Welcome to our RISC-V Simulator!" << endl;

    cout << "Please enter the path of the .asm file you would like to run: ";
    string filename;
    cin >> filename;

    ifstream asmfile;
    asmfile.open(filename);

    cout << "Please enter the path of the memory file, or enter 'none' if you do not have one: ";
    string memfilePath;
    cin >> memfilePath;

    if (memfilePath != "none") {
        ifstream memfile;
        memfile.open(memfilePath);
        memory_init(memfile);
    }

    cout << "Please enter the starting address of the program: ";
    uint32_t startAddr;
    cin >> startAddr;

    pc = startAddr;

    registers_init();


    // ToDo: while loop to execute instructions one by one
}