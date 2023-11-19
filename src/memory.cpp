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
        // move trailing whitespaces

        line = line.substr(0, line.find('#'));

        while (line[line.length() - 1] == ' ')
        {
            line = line.substr(0, line.length() - 1);
        }

        // remove leading whitespaces
        while (line[0] == ' ')
        {
            line = line.substr(1);
        }

        // if line is empty, skip
        if (line.empty())
        {
            continue;
        }

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
    if (memory.size() == 0)
    {
        return;
    }

    cout << "Memory: " << endl;
    cout << "Address (dec) (hex)     Bytes (dec) (hex) (binary)" << endl;

    for (auto it = memory.begin(); it != memory.end();)
    {
        cout << it->first << "  0x" << decimal_to_hex(it->first) << "\t\t\t";
        vector<string> bytes;

        for (int i = 0; i < 4; i++)
        {
            if (it != memory.end())
            {
                bytes.push_back(to_string(it->second) + "  0x" + decimal_to_hex(it->second) + "  0b" + decimal_to_binary(it->second, 8) + "\t");
                ++it;
            }
        }

        for (auto rit = bytes.rbegin(); rit != bytes.rend(); ++rit)
        {
            cout << *rit << " ";
        }

        cout << endl;
    }
}