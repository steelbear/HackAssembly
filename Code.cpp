#include "stdafx.h"

#include "Code.h"

const map<string, BINCODE> Code::destTable = {
    {"", 0},
    {"M", 1},
    {"D", 2},
    {"MD", 3},
    {"A", 4},
    {"AM", 5},
    {"AD", 6},
    {"AMD", 7}
};

const map<string, BINCODE> Code::compTable = {
    {"0", 42},
    {"1", 63},
    {"-1", 58},
    {"D", 12},
    {"A", 48},
    {"!D", 13},
    {"!A", 49},
    {"-D", 15},
    {"-A", 51},
    {"D+1", 31},
    {"A+1", 55},
    {"D-1", 14},
    {"A-1", 50},
    {"D+A", 2},
    {"D-A", 19},
    {"A-D", 7},
    {"D&A", 0},
    {"D|A", 21},
};

const map<string, BINCODE> Code::jumpTable = {
    {"", 0},
    {"JGT", 1},
    {"JEQ", 2},
    {"JGE", 3},
    {"JLT", 4},
    {"JNE", 5},
    {"JLE", 6},
    {"JMP", 7}
};

BINCODE Code::dest(string symbol)
{
    if (destTable.find(symbol) != destTable.end()) {
        return destTable.at(symbol) << 3;
    }
    else {
        cerr << "ERR : Invalid dest - " << symbol << endl;
        return -1;
    }
}


BINCODE Code::comp(string symbol)
{
    BINCODE code = 0;
    size_t indexM = symbol.find_first_of('M');
    if (indexM != string::npos) {
        symbol[indexM] = 'A';
        code += 1 << 6;
    }
    if (compTable.find(symbol) != compTable.end()) {
        code += compTable.at(symbol);
    }
    else {
        cerr << "ERR : Invalid comp - " << symbol << endl;
        return -1;
    }

    return code << 6;
}


BINCODE Code::jump(string symbol)
{
    if (jumpTable.find(symbol) != jumpTable.end()) {
        return jumpTable.at(symbol);
    }
    else {
        cerr << "ERR : Invalid jump - " << symbol << endl;
        return -1;
    }
}
