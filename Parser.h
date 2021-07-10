#pragma once

#include "stdafx.h"

#define CMD_MAX_LENGTH 100

typedef enum class CMD_TYPE { A_COMMAND, C_COMMAND, L_COMMAND } CMD_TYPE;

class Parser
{
public:
	Parser(const char* filename);
	~Parser();

	void printLine();

	bool hasMoreCommands();
	void advance();
	CMD_TYPE commandType();
	string symbol();
	string dest();
	string comp();
	string jump();

	void rewindFile();


private:
	FILE* file;
	string line;

	bool isNotCommand();
	void getLine();
};

void ltrim(string& str);
void rtrim(string& str);
void rCommentTrim(string& str);