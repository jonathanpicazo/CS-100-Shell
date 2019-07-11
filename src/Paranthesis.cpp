#include "Paranthesis.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Paranthesis::Paranthesis() {
	paren.resize(0);
	fullstring = "";
}

Paranthesis::Paranthesis(string input) {
	this->fullstring = input;
}

void Paranthesis::parse() {
	bool openParen = false;
	bool fullParen = false;
	int quote = 0;
	int i;
	//early abandon
	size_t found = fullstring.find("(");
	if (found == string::npos) {
		goto jumplabel;
	}
	for (i = 0; i < fullstring.size(); ++i) {
		if (fullstring.at(i) == '\"') {
			++quote;
			if (quote == 2) {
				Connector* temp = new Connector(fullstring.substr(0,i + 1));
				//special parse that doesnt parse ";, |, &"
				temp->parse();
				temp->changetoParen();
				paren.push_back(temp);
				if (i == fullstring.size() - 1) {
					return;
				}
				fullstring = fullstring.substr(i + 1);
				i = 0;
				quote = 0;
				continue;
			}
		}
		else if (fullstring.at(i) == '(' && quote != 1) {
			openParen = true;
		}
		else if (fullstring.at(i) == ')' && openParen && quote != 1) {
			openParen = false;
			fullParen = true;
			if (i == fullstring.size() - 1) {
				goto jumplabel;
			}
		}
		else if (fullstring.at(i) == ';' && quote != 1) {
			if (fullParen) {
				Connector* temp = new Connector(fullstring.substr(0, i));
				temp->parse();
				temp->changetoParen();
				paren.push_back(temp);
				fullParen = false;
				fullstring = fullstring.substr(i + 1);
				i = 0;
				continue;
			}
			else if (openParen) {
				continue;
			}
			else {
				Connector* temp = new Connector(fullstring.substr(0, i));
				temp->parse();
				paren.push_back(temp);
				fullstring = fullstring.substr(i + 1);
				i = 0;
				continue;
			}
		}
		else if (fullstring.at(i) == '&' && fullstring.at(i + 1) =='&' && quote != 1) {
			if (fullParen) {
				Connector* temp = new Connector(fullstring.substr(0, i-1));
				temp->parse();
				temp->changetoParen();
				temp->changeFlag(1);
				paren.push_back(temp);
				fullParen = false;
				fullstring = fullstring.substr(i + 2);
				i = 0;
				continue;
			}
			else if (openParen) {
				continue;
			}
			else {
				Connector* temp = new Connector(fullstring.substr(0, i-1));
				temp->parse();
				temp->changeFlag(1);
				paren.push_back(temp);
				fullstring = fullstring.substr(i + 2);
				i = 0;
				continue;
			}
		}
		else if (fullstring.at(i) == '|' && fullstring.at(i + 1) =='|' && quote != 1) {
			if (fullParen) {
				Connector* temp = new Connector(fullstring.substr(0, i-1));
				temp->parse();
				temp->changetoParen();
				temp->changeFlag(2);
				paren.push_back(temp);
				fullParen = false;
				fullstring = fullstring.substr(i + 2);
				i = 0;
				continue;
			}
			else if (openParen) {
				continue;
			}
			else {
				Connector* temp = new Connector(fullstring.substr(0, i-1));
				temp->parse();
				temp->changeFlag(2);
				paren.push_back(temp);
				fullstring = fullstring.substr(i + 2);
				i = 0;
				continue;
			}
		}
		else if (fullstring.at(i) == '#' && quote != 1) {
			if (i == 0) {
				//ignore everything bruh
				return;
			}
			else {
				Connector* temp = new Connector(fullstring.substr(0, i));
				temp->parse();
				paren.push_back(temp);
				return;
			}
		}
	}
	jumplabel: 
	Connector* temp = new Connector(fullstring);
	temp->parse();
	paren.push_back(temp);
}

Connector* Paranthesis::at(int i) {
	return this->paren.at(i);
}

int Paranthesis::size() {
	return this->paren.size();
}