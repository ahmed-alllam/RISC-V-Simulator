#include "utils.h"

#include <string>
#include <bitset>
#include <sstream>

using namespace std;

string decimal_to_binary(int decimal, int num_bits)
{
    return bitset<32>(decimal).to_string().substr(32 - num_bits, num_bits);
}

string decimal_to_hex(int decimal)
{
    stringstream ss;
    ss << hex << decimal;
    return ss.str();
}