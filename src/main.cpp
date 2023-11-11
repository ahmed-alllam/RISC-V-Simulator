#include <iostream>
#include <string>
#include <vector>

#include "memory.h"
#include "register.h"
#include "instruction.h"

using namespace std;

int main() {
    cout << "Hello and Welcome to our RISC-V Simulator!" << endl;

    cout << "Please enter the path of the .asm file you would like to run: ";
    string filename;
    cin >> filename;

    cout << "Please enter the path of the memory file, or enter 'none' if you do not have one: ";
    string memfilePath;
    cin >> memfilePath;

    if (memfilePath != "none") {
        ifstream memfile;
        memfile.open(memfilePath);
        memory_init(memfile);
    }

    cout << "Please enter the starting address of the program (in hex, in range 0x00000000 to 0xFFFFFFFF): ";
    string startAddr;
    cin >> startAddr;


    // ToDo: while loop to execute instructions one by one
}