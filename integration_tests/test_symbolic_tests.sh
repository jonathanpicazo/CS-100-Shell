#!/bin/sh

#[ -e src ]
[ -e src/main.cpp ]#
[ -e src ]
[ -e src/main.cpp ]
[ -d images ]
[ -f rshell ]
([ -d header ]) && echo yay
[ -f test ] && echo cool
([ -e src ] && echo dude)
([ -e src ] && (echo nice day))
[ -d images/testSomething ] && echo tested
[ -e src/Shell.cpp ] && echo ayyy
([ -e src/Shell.cpp ] && echo trying)


exit
exit
exit

