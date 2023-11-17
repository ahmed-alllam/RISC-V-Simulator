#include "instructions.h"
#include "registers.h"
#include "memory.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void memory_init(ifstream &memfile)
{
    string line;
    while (getline(memfile, line))
    {
        uint32_t addr = stoi(line.substr(0, line.find(' ')));
        uint32_t val = stoi(line.substr(line.find(' ') + 1, line.length() - 1));

        if (addr > ((1 << 11) - 1) || addr < 0)
        {
            cout << "Invalid address: " << addr << endl;
            exit(1);
        }

        // loop over the bytes
        for (int i = 0; i < 4; i++)
        {
            memory[addr + i] = (val >> (i * 8)) & 0xFF;
        }
    }
}

void memory_print()
{
    for (auto it = memory.begin(); it != memory.end();)
    {
        cout << it->first << ": ";
        vector<string> bytes;

        for (int i = 0; i < 4; i++)
        {
            if (it != memory.end())
            {
                bytes.push_back(bitset<8>(it->second).to_string());
                ++it;
            }
            else
            {
                bytes.push_back("        ");
            }
        }

        for (auto rit = bytes.rbegin(); rit != bytes.rend(); ++rit)
        {
            cout << *rit << " ";
        }

        cout << endl;
    }
}