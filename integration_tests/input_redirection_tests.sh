#!/bin/sh

# names.txt
echo hello && ls >> names.txt
cat < images/hello.md
cat < names.txt
cat < CMakeLists.txt
echo how && ls -a && cat < CMakeLists.txt
cat < images/txt && echo no
ls >> CMakeLists.txt
echo hello && ls >> names.txt || echo done
ls -a && cat < names.txt



exit
