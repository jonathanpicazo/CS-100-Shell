#ifndef SHELL_HPP
#define SHELL_HPP
#include "CommandTable.hpp"
using namespace std;

class Shell {
	protected:
		CommandTable* table;
		friend class CommandTable;
	public:
		Shell();
		void run();
};
#endif