#include "stdafx.h"

#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"


int main(int argc, const char* argv[]) {
	string filename("Add.asm");

	Parser parser = Parser(filename.c_str());
	SymbolTable symTable = SymbolTable();

	ofstream ofs(filename.replace(filename.length() - 3, 3, "hack").c_str(), ofstream::out);

	int lineno = 0;
	int newVariable = 16;

	parser.advance();
	while (parser.hasMoreCommands()) {
		switch (parser.commandType()) {
		case CMD_TYPE::A_COMMAND:
		case CMD_TYPE::C_COMMAND:
			lineno++;
			break;
		case CMD_TYPE::L_COMMAND:
			if (!symTable.contains(parser.symbol())) {
				symTable.addEntry(parser.symbol(), (BINCODE)lineno);
			}
			else {
				cerr << "ERR : " << parser.symbol() << "is already defined" << endl;
			}
			break;
		}

		parser.advance();
	}

	parser.rewindFile();
	lineno = 0;

	parser.advance();
	while (parser.hasMoreCommands()) {
		switch (parser.commandType()) {
		case CMD_TYPE::A_COMMAND:
			try {
				BINCODE addr = stoi(parser.symbol());
				// ofs << bitset<16>(addr) << endl;
				cout << bitset<16>(addr) << endl;
			}
			catch (const invalid_argument& err) {
				if (symTable.contains(parser.symbol())) {
					// ofs << bitset<16>(symTable.getAddress(parser.symbol())) << endl;
					cout << bitset<16>(symTable.getAddress(parser.symbol())) << endl;
				}
				else {
					symTable.addEntry(parser.symbol(), newVariable);
					// ofs << bitset<16>(symTable.getAddress(parser.symbol())) << endl;
					cout << bitset<16>(symTable.getAddress(parser.symbol())) << endl;
					newVariable++;
				}
			}
			catch (const exception& err) {
				cerr << "ERR : invalid address - " << parser.symbol() << endl;
			}
			lineno++;
			break;
		case CMD_TYPE::L_COMMAND:
			break;
		case CMD_TYPE::C_COMMAND:
			BINCODE code = (7 << 13)
				+ Code::comp(parser.comp())
				+ Code::dest(parser.dest())
				+ Code::jump(parser.jump());
			// ofs << bitset<16>(code) << endl;
			cout << bitset<16>(code) << endl;
			lineno++;
			break;
		}

		parser.advance();
	}

	// ofs.close();

	return 0;
}