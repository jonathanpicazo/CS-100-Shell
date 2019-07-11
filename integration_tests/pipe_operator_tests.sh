#!/bin/sh

cat < integration_tests/input.txt
echo wow | tr A-Z a-z
cat < names.txt | tr A-Z a-z
echo oh < CMakeLists.txt | tr A-Z a-z
echo "should not work" && cat < integration_tests
cat < inegration_tests/input.txt | tr A-Z a-z
cat < names.txt | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > out.txt
cat < names.txt | tee names.txt

cat < names.txt | tr A-Z a-z && echo wow


cat < names.txt | tr A-Z a-z && echo wow && ls -a

exit
