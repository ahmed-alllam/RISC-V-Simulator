#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

extern map<uint32_t, uint8_t> memory; 

void memory_init(ifstream &memfile);

void memory_print();

#endif // MEMORY_H