#ifndef COMMANDTABLE_HPP
#define COMMANDTABLE_HPP
#include "Connector.hpp"
#include "Paranthesis.hpp"
#include <string>
#include <queue>
using namespace std;

/* CommandTable should be the container for  Connector, that then converts them to char*, ready to be  */
class CommandTable : public Parse {
	protected:
		Paranthesis* command;
		queue<Connector* > line;
		vector<char*> e;
	public:
		CommandTable(string input);
		void execute();
		void parse();
		void convert(vector<string>);
		void clear();
		bool test_execute(vector<char*>);
		bool pipe_command(vector<char*>, int);
		int redirection_parse(vector<string>);
};
#endif