#ifndef PARANTHESIS_HPP
#define PARANTHESIS_HPP
#include <string>
#include <vector>
#include "Connector.hpp"
using namespace std;

class Paranthesis : public Parse {
	protected:
		//fullstring from Parse
		vector<Connector* > paren;
	public:
		Paranthesis();
		Paranthesis(string);
		void parse();
		Connector* at(int);
		int size();
};
#endif