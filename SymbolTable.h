#pragma once

#include "stdafx.h"

class SymbolTable
{
public:
	SymbolTable();
	void addEntry(string symbol, BINCODE address);
	bool contains(string symbol);
	BINCODE getAddress(string symbol);
private:
	map<string, BINCODE> table;
};

