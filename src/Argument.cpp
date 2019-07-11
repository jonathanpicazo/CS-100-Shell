#include "Argument.hpp"
#include <boost/tokenizer.hpp>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
using namespace boost;

Argument::Argument() {
	parsed.resize(0);
	fullstring = "";
	flag = 0;
}

Argument::Argument(string in) {
	this->fullstring = in;
}

void Argument::parse() {
	char_separator<char> sep(" ;|&()\"");
	tokenizer<char_separator<char>> t(fullstring, sep);
	tokenizer<char_separator<char>>::iterator iter;
	//push parsed string into vector
	for (iter = t.begin(); iter != t.end(); ++iter) {
		parsed.push_back(*iter);
	}
	// for (int i = 0; i < parsed.size(); ++i) {
	// 	this->arg.push_back(const_cast<char*>(parsed.at(i).c_str()));

	// }
	// //null-terminating
	// this->arg.push_back(NULL);
}

void Argument::quoteParse() {
	char_separator<char> sep("\" ");
	tokenizer<char_separator<char>> t(fullstring, sep);
	tokenizer<char_separator<char>>::iterator iter;
	for (iter = t.begin(); iter != t.end(); ++iter) {
		parsed.push_back(*iter);
	}
}

string Argument::at(int i) {
	return parsed.at(i);
}

vector<string> Argument::retVect() {
	return this->parsed;
}

string Argument::retString() {
	return this->fullstring;
}

void Argument::changeFlag(int a) {
	this->flag = a;
}

int Argument::returnFlag() {
	return this->flag;
}
