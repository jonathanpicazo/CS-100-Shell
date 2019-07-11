#include "Connector.hpp"
#include <string>
#include <iostream>
using namespace std;

Connector::Connector() {
	connectvect.resize(0);
	fullstring = "";
	isParen = false;
	flag = 0;
	/* for flag
	0 = normal;
	1 = and;
	2 = odd;
	*/
}

Connector::Connector(string pass) {
	this->fullstring = pass;
}

void Connector::parse() {
	int quote = 0;
	for (int i = 0; i < fullstring.size(); ++i) {
		if (fullstring.at(i) == '\"') {
			++quote;
			if (quote == 2) {
				Argument* temp = new Argument(fullstring.substr(0,i + 1));
				//special parse that doesnt parse ";, |, &"
				temp->quoteParse();
				connectvect.push_back(temp);
				if (i == fullstring.size() - 1) {
					return;
				}
				fullstring = fullstring.substr(i + 1);
				// cout << fullstring << endl;
				//reset quote
				i = 0;
				quote = 0;
				continue;
			}
		}
		else if (fullstring.at(i) == ';' && quote != 1) {
			Argument* temp = new Argument(fullstring.substr(0,i));
			temp->parse();
			connectvect.push_back(temp);
			fullstring = fullstring.substr(i + 1);
			i = 0;
			continue;
		}
		else if (fullstring.at(i) == '&' && fullstring.at(i + 1) =='&' && quote != 1) {
			Argument* temp = new Argument(fullstring.substr(0, i - 1));
			temp->parse();
			temp->changeFlag(1);
			connectvect.push_back(temp);
			fullstring = fullstring.substr(i + 2);
			i = 0;
			continue;
		}
		else if (fullstring.at(i) == '|' && fullstring.at(i + 1) =='|' && quote != 1) {
			Argument* temp = new Argument(fullstring.substr(0,i - 1));
			temp->parse();
			temp->changeFlag(2);
			connectvect.push_back(temp);
			fullstring = fullstring.substr(i + 2);
			i = 0;
			continue;
		}

		else if (fullstring.at(i) == '#') {
			if (i == 0) {
				return;
			}
			else if (quote != 1) {
				Argument* temp = new Argument(fullstring.substr(0,i));
				temp->parse();
				connectvect.push_back(temp);
				return;
			}
		}
	 }
	 Argument* temp = new Argument(fullstring);
	 temp->parse();
	 connectvect.push_back(temp);
}

int Connector::size() {
	return this->connectvect.size();
}

Argument* Connector::at(int i) {
	return this->connectvect.at(i);
}

void Connector::changeFlag(int a) {
	this->flag = a;
}

int Connector::returnFlag() {
	return this->flag;
}

void Connector::changetoParen() {
	this->isParen = true;
}

void Connector::pushToChain() {
	for (int i = 0; i < this->connectvect.size(); ++i) {
		this->chain.push(connectvect.at(i));
	}
}

void Connector::chainPop() {
	this->chain.pop();
}

Argument* Connector::chainFront() {
	return this->chain.front();
}

bool Connector::chainEmpty() {
	return this->chain.empty();
}

bool Connector::isTrue() {
	return isParen;
}