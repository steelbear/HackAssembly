#pragma once

#include "stdafx.h"

class Code
{
public:
    static BINCODE dest(string symbol);
    static BINCODE comp(string symbol);
    static BINCODE jump(string symbol);
private:
    static const map<string, BINCODE> destTable;
    static const map<string, BINCODE> compTable;
    static const map<string, BINCODE> jumpTable;
};

