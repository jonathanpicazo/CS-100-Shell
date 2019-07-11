#include <string>
#include "Shell.hpp"
#include <iostream>
using namespace std;
Shell::Shell() {
	table = NULL;
}


void Shell::run() {
	string str;
	while (true) {
		cout << "$ ";
		getline(cin, str);
		if (str == "exit") {
			exit(0);
		}
		else if (str == "") {
			continue;
		}
		this->table = new CommandTable(str);
		this->table->execute();
	}
}
