#include "CommandTable.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <cstdio> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>  
#include <iostream>
using namespace std;



CommandTable::CommandTable(string in) {
    e.resize(0);
    fullstring = in;
}

int CommandTable::redirection_parse(vector<string> aug) {
  for (int i = 0; i < aug.size(); ++i) {
    if (aug.at(i) == "<") {
      return 0;
      //redirect stdin
      //file_desc = 
    }
    else if (aug.at(i) == ">") {
      // cout << "yeah boii" << endl;
      //redirecto stdout
      return 1;
      //file_desc = 
    }
    else if (aug.at(i) == ">>") {
      //redirect stdout but appends instead of override
      //file_desc = 
      return 2;
    }
  }
  return -1;
}

void CommandTable::execute() {
    int failure = 0;
    this->parse();
    jumplabel:
	while(!line.empty()) {
        this->clear();
        while (!line.front()->chainEmpty()) {
            this->clear();
            this->convert(line.front()->chainFront()->retVect());
            int* childStatus = NULL;
            pid_t childId = fork();
            pid_t tempfork = childId;
            if (childId == 0) {
                if (line.front()->chainFront()->at(0) == "test" || line.front()->chainFront()->at(0) == "[") {
                    if (this->test_execute(e)) {
                        goto end;
                    }
                    else {
                        ++failure;
                        goto fail;
                    }
                }
                else if (this->redirection_parse(line.front()->chainFront()->retVect()) != -1) {
                    int a = this->redirection_parse(line.front()->chainFront()->retVect());
                    if (!pipe_command(e, a)) {
                      cout << "ye boi it worked" << endl;
                      goto fail;
                    }

                }
                else if (execvp(e.at(0), e.data()) == -1) {
                    fail:
                    if (line.front()->chainFront()->returnFlag() == 2) {
                        line.front()->chainPop();
                        this->clear();
                        goto jumplabel;
                    }
                    else if (line.front()->isTrue()) {
                        if (line.front()->returnFlag() == 2) {
                            line.pop();
                            this->clear();
                            goto jumplabel;
                        }
                        if (line.front()->returnFlag() == 1) {
                            line.pop();
                            line.pop();
                            this->clear();
                            goto jumplabel;
                        }
                    }
                    else if (line.front()->chainFront()->returnFlag() == 1) {
                        line.front()->chainPop();
                        line.front()->chainPop();
                        this->clear();
                        goto jumplabel;
                    }
                    else {
                        if (failure > 0) {
                            return;
                        }
                        perror("command not found");
                        return;
                    }
                }
                waitpid(0, childStatus, 0);
                kill (childId, 2);
            }
            else if (childId > 0) {
                // wait(NULL);
                // while(1);
                //parent and child have same id
                if (wait(childStatus) == -1) {
                    perror("Unsuccesful wait");
                }
            }
            else {
                perror("Unsuccesful fork");
            }
            end:
            // kill (childId, 2);
            // this->clear();
            if (line.front()->chainFront()->returnFlag() == 2) {
                line.front()->chainPop();
            }
            line.front()->chainPop();
        }
        if (line.front()->isTrue()) {
            if (line.front()->returnFlag() == 2) {
                line.pop();
            }
        }
        line.pop();
    }
    return;
}

void CommandTable::parse() {
    this->command = new Paranthesis(fullstring);
    command->parse();
    // cout << "here" << endl;
    if (fullstring == "exit") {
        exit(0);
    }
    for (int i = 0; i < command->size(); ++i) {
        command->at(i)->pushToChain();
        line.push(command->at(i));
        // command->at(i)->pushToChain();
    }
}

void CommandTable::convert(vector<string> tempy) {
    for(int i = 0; i < tempy.size(); ++i) {
        if (tempy.at(0) == "exit") {
            exit(1);
        }
        e.push_back(const_cast<char*>(tempy.at(i).c_str()));
    }
    e.push_back(NULL);
}

void CommandTable::clear() {
    e.resize(0);
}

bool CommandTable::pipe_command(vector<char*> streamy, int flag) {
  if (flag == 0) {
    int save = dup(0);
    const char* back = streamy.at(streamy.size() - 2);
    streamy.pop_back();
    streamy.pop_back();
    streamy.pop_back();
    int infile = open(back, O_RDONLY);
    streamy.push_back(NULL);
    dup2(infile, 0);
    if (execvp(streamy.at(0), streamy.data()) == -1) {
      return false;
    }
    close(infile);
    dup2(save, 0);
  }
  else if (flag == 1) {
    int save = dup(1);
    const char* back = streamy.at(streamy.size() - 2);
    // will pop the output file and the redirection symbol and initial NULL
    streamy.pop_back();
    streamy.pop_back();
    streamy.pop_back();
    int outfile = open(back, O_CREAT | O_WRONLY);
    streamy.push_back(NULL);
    dup2(outfile, 1);
    if (execvp(streamy.at(0), streamy.data()) == -1) {
      return false;
    }
    close(outfile);
    // //return to standard
    dup2(save, 1);
    //   return false;
    // }
    // else {
    //   return true;
    // }
  }
  else if (flag == 2) {
    int save = dup(1);
    const char* back = streamy.at(streamy.size() - 2);
    streamy.pop_back();
    streamy.pop_back();
    streamy.pop_back();
    int outfile = open(back, O_CREAT | O_WRONLY | O_APPEND);
    streamy.push_back(NULL);
    dup2(outfile, 1);
    if (execvp(streamy.at(0), streamy.data()) == -1) {
      return false;
    }
    close(outfile);
    dup2(save, 1);
  }
  return true;
}


bool CommandTable::test_execute(vector<char*> s) {
  char *tmp = s.at(0);
  string madeString = tmp;
    
    if (s.size() == 1) {
        return false;
    }
    
    //char *tmp = s.at(0);
   // string tmpString = tmp;
   //this checks if the first thing is test or bracket THEN only do you check for flags/implement accordinly
     if(madeString == "[" || madeString == "test"){ 
     char* thepath;
     char* f;
     string flagtype;
        if ((s.size() == 4 && madeString == "test") || (s.size() == 5 && madeString == "[")) {
        f = s.at(1);
        thepath = s.at(2);
        flagtype = f;
      }
        else {
        thepath = s.at(1);
        flagtype = "-e";
       } 
       string path = thepath;
     if (flagtype == "-e") {
       
       struct stat a;
        //cout << path;
        bool exists = (stat(path.c_str(), &a)==0);
        if (exists) { 
            cout << "(True)" << endl;
            return true;
        }
        else {
            cout << "(False)" << endl; 
            return false;
        }
    } 
    else if (flagtype == "-f") {
        struct stat a;
        int result = stat(path.c_str(), &a);
        if(result !=-1) { 
         int exists = S_ISREG(a.st_mode);
         if(exists == 1){
        
            cout << "(True)" << endl;
            return true;
        }
       
        else {
            cout << "(False)" << endl;
            return false;
        }
       }
  else {
 cout << "(False)" << endl;
return false;
}
}

     else   {
        struct stat a;
        int result = stat(path.c_str(), &a);
        if(result !=-1) {
         int exists = S_ISDIR(a.st_mode);
         if(exists == 1){

            cout << "(True)" << endl;
            return true;
        }

        else {
            cout << "(False)" << endl;
            return false;
        }
       }
  else {
 cout << "(False)" << endl;
return false;
}
}

}
}

