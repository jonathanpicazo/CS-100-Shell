#!/bin/sh 

#test -e src 
test -e src/#
test -e src
test -e src/main.cpp
test -d images
test -f rshell
test -f test

(test -e src) && (echo wow || echo dude)


(test -f rshell && echo wow)

(test -e src && (echo wow))
(test -e src && (echo wow && echo dude))
(test -f header) || echo nope

exit;
exit;
