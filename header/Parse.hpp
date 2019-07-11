#ifndef PARSE_HPP
#define PARSE_HPP
#include <string>
using namespace std;
class Parse {
	protected:
	string fullstring;
	public:
		Parse(){}
		Parse(string in){this->fullstring = in;}
		virtual void parse() = 0;
};
#endif