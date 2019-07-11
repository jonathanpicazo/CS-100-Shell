# CS 100 Programming Project

# Introduction
##### Essentially we have been creating a shell which we will/have been making improvements through over the course of the quarter. In order to do this, we will need classes via use of composite patterns and polymorphism. As we have done in this assignment, we should have numerous classes that encompass a shell’s ability to run individual commands such as ls, rm, or multiple commands on one line such as ls -a; git branch, ls -a && git branch, etc. We have been able to differentiate between these commands, run multiple commands at once, and more and actually execute them and create functionality. We have used abstractions to limit the client to use limited commands to prevent them from infiltrating the shell. Each class has function names that mirror that of other classes(such as our parse function),  as well as their own unique functions. In testing our classes, we have made sure that they accept a wide range of commands not only for the client to use to organize whatever it is that they are working on, but to allow the creation of and removal of files, and more.

##### In Assignment 3, we are expanding on our shell by adding a new command (Test command), as well as the ability for the user to user parenthesis to choose precendece of order of command execution. We talk about how we do this in the CLASSES section

##### In Assignment 4, we expand our shell one last time to implement the use of file IO redirection. This allows users to write to a file, display what exists already in a file in the main terminal and more. We talk more about this in the CLASSES section.
# Diagram

### ![Github Logo](https://github.com/cs100/assignment-cs-100-jonathan-rhea/blob/master/images/UMLdiagaram.jpeg)


# Classes
##### A shell will need to be created which, for now, is capable of printing command prompts, can read in a line of commands and arguments which may or may not include connectors, and finally execute this commands and arguments. In this case, this particular program uses the Shell class as the basis for completing these tasks. First, Shell runs, and prompts the user for some input(of which will not run if "exit" is entered.) It is possible that users may enter one command/argument or multiple commands separated by connecters(; or && or || etc). So the CommandTable class will use the CommandTable class's execute function to, in the end, actually execute client commands. Before the program can actually execute though, the string that is entered by the user, will need to be passed into the Connector class to check for things like semicolons, pounds, or ampersands. If they are not found, we only have one command/argument which will be passed to the Arguments class to keep track of the number of commands/arguments and what they are - and only then will those commands/arguments actually be executed. If multiple commands/arguments(ex: ls -a, git branch) are found(separated by connectors),  the Connector class will find the separate commands/arguments, then pass them one at a time to the Arguments class(for our example, we would pass in ls -a first, then git branch), to subsequently be parsed into their individual components. So now the program know what to execute, and in what order. To summarize, the bottom line is, before any commands/arguments can be executed(actually do what the client is asking), in the CommandTable class, the program needs to first recognize how many commands/arguments there are, separate them accordingly, and THEN they can execute each command/argument IN ORDER using execvp(), fork(), etc.
##### This is how we went about doing Assignment Two!

##### In Assignment Three, however, a new class called Parenthesis was needed to account for if the client enters parenthesis. In the Parenthesis class, we essentially check for if parenthesis exists, then also check for connectors inside of the parenthesis and execute accordingly. If no connectors exist, then we simply continue on with execution. So We needed to account for Parenthesis/ Nested Parenthesis/ Connectors and combinations of all of these.

##### In Assignment four, our final assignment, we needed to implement input redirection, output redirection, a combination of these (multiple redirections) on the same line, as well as piping. Piping in part allows for this multiple redirection to take place, alone with the use of commands such as tr a-z A-Z which will change everything in a specified file from lower-case to upper-case, and vice-versa. We did not add new CLASSES for this assigment - rather we added additional functions to existing classes. We did not quite parse in the way that we did previous assignments, which is in part why we did not create new classes. The UML Diagaram shows the new functions added.
##### They are pipe_command() and redirection_parse() which check to see whether the client has entered <, >, >> or | and executes accordingly.


# Prototype and Research
##### fork() = Creates a new process and returns child's id of type pid_t. We use fork in order to execute commands with different processes.

##### execvp() = Uses 2 parameters in order to execute a command. One parameter is just the command and the other is the the command with the argument

##### waitpid() = waits for child process to complete.

##### In our prototype, we executing the "ls -l" command, which lists all the files and hidden files in a long format. Our program forks a new child process, wait for the child process to execute, and then kills the child process so there are no zombie processes, which could be a resource-intensive when multiple forks are called, even when they are no longer needed. Here is the link to our proptotype function: [Github] (https://github.com/cs100/assignment-cs-100-jonathan-rhea/blob/master/main.cpp)



# Development and Testing Roadmap
##### A very important concept for us to master is to make sure our program can even distinguish between commands vs. connectors vs arguments. We need to make sure, hence, that our parse base class makes sense and has the proper virtual functions within it. We also need to make sure that when using variations of commands/arguments such as &&, ||, echo, ls -a; git branch, etc., in numerous different variations, actually works.

##### Now that we have a general idea of how we will go about doing this project(which we have laid out in this assignment), we know what classes we plan on using. We will split the work for the classes between us. Jonathan will work on the connectors and command classes. The command class issue was that it Initially was not running execute().  This issue has been resolved.[Github](https://github.com/cs100/assignment-cs-100-jonathan-rhea/issues/6#issue-411141393)

##### Rhea will work on the arguments and collaborate on the command class. Issue: The program was not recognizing or statements initially. This issue has been resolved. [Github](https://github.com/cs100/assignment-cs-100-jonathan-rhea/issues/7#issue-411141517)


##### Unit tests will be completed separately based on the way we seperated classed. Rhea will do unit tests for commands and arguments and jonathan will do them for the connectors and command list classes.

