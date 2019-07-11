#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP
#include "Parse.hpp"
#include <vector>
#include <string>
using namespace std;

class Argument : public Parse {
	protected:
		vector<string> parsed;
		int flag;
		// flag = 0 : normal
		// flag = 1 : and
		// flag = 2 : or
	public:
		Argument();
		Argument(string);
		void parse();
		void quoteParse();
		string at(int);
		vector<string> retVect();
		string retString();
		void changeFlag(int);
		int returnFlag();
};
#endif