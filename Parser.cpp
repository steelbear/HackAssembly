#include "stdafx.h"

#include "Parser.h"

Parser::Parser(const char* filename) {
	errno_t err = fopen_s(&file, filename, "r");

	if (err != 0) {
		printf("Err\n");
	}
};

Parser::~Parser() {
	fclose(file);
}

void Parser::printLine() {
	cout << line << endl;
}

bool Parser::hasMoreCommands()
{
	return !feof(file);
}

void Parser::advance()
{
	do {
		getLine();
	} while (hasMoreCommands() && isNotCommand());
}


CMD_TYPE Parser::commandType()
{
	if (line[0] == '@') {
		return CMD_TYPE::A_COMMAND;
	}
	else if (line.front() == '(' && line.back() == ')') {
		return CMD_TYPE::L_COMMAND;
	}
	else {
		return CMD_TYPE::C_COMMAND;
	}
}


string Parser::symbol()
{
	if (commandType() == CMD_TYPE::A_COMMAND) {
		return line.substr(1);
	}
	else if (commandType() == CMD_TYPE::L_COMMAND) {
		return line.substr(1, line.length() - 2);
	}
	else {
		return string();
	}
}


string Parser::dest()
{
	size_t pos = line.find('=');
	if (pos != string::npos) {
		return line.substr(0, (int)pos);
	}
	else {
		return string();
	}
}


string Parser::comp()
{
	size_t posEq = line.find('=');
	size_t posCo = line.find(';');

	if (posEq != string::npos) {
		return line.substr(posEq + 1);
	}
	else if (posCo != string::npos) {
		return line.substr(0, posCo);
	}
	else {
		return string();
	}
}


string Parser::jump()
{
	size_t pos = line.find(';');

	if (pos != string::npos) {
		return line.substr(pos + 1);
	}
	else {
		return string();
	}
}

bool Parser::isNotCommand() {
	return line.empty() || line.length() == 0 || line.substr(0, 2) == "//";
}

void Parser::getLine() {
	char buf[CMD_MAX_LENGTH];

	if (fgets(buf, CMD_MAX_LENGTH, file) == nullptr) {
		line = string();
	}
	else {
		line = string(buf);
		ltrim(line);
		rCommentTrim(line);
		rtrim(line);
	}
}

void Parser::rewindFile() {
	rewind(file);
}

inline void ltrim(string& str) {
	str.erase(str.begin(), find_if(str.begin(), str.end(), [](char c) {
		return !std::isspace(c);
	}));
}

inline void rtrim(string& str) {
	str.erase(find_if(str.rbegin(), str.rend(), [](char c) {
		return !std::isspace(c);
	}).base(), str.end());
}

void rCommentTrim(string& str) {
	size_t pos = str.find("//");
	if (pos != string::npos) {
		str.erase(pos, str.length() - pos);
	}
}