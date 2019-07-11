#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP
#include "Parse.hpp"
#include <vector>
#include <queue>
#include "Argument.hpp"
#include <string>
using namespace std;

class Connector : public Parse {
	protected:
		vector<Argument*> connectvect;
		queue <Argument*> chain;
		int flag;
		bool isParen;
	public:
		Connector();
		Connector(string);
		void parse();
		int size();
		Argument* at(int);
		bool isTrue();
		void changetoParen();
		void pushToChain();
		void chainPop();
		Argument* chainFront();
		bool chainEmpty();
		void changeFlag(int);
		int returnFlag();

};
#endif