#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void memory_init(ifstream &memfile)
{
    while (!memfile.eof())
    {
        string line;
        getline(memfile, line);

        uint32_t addr = stoi(line.substr(0, line.find(' ')));
        uint32_t val = stoi(line.substr(line.find(' ') + 1, line.length() - 1));

        memory[addr] = val;
    }
}

void memory_print()
{
    for (auto it = memory.begin(); it != memory.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
}