#!/bin/sh 

echo abc >> out.txt
echo xyz > out.txt
ls -a && echo trydis > out.txt
echo key >> integration_tests/intfile.txt
echo "what" && echo trueee && echo done >> integration_tests/outfile.txt
echo is >> out.txt || echo over >> out.txt
ls -a >> CMakeLists.txt

exit
