CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include_directories(header)
ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "-Wno-write-strings")

ADD_EXECUTABLE(rshell
    src/Argument.cpp
    src/main.cpp
    src/Connector.cpp
    src/CommandTable.cpp
    src/Shell.cpp
    header/Argument.hpp
    header/Connector.hpp
    header/CommandTable.hpp
    header/Shell.hpp
    header/Parse.hpp
    header/Paranthesis.hpp
    src/Paranthesis.cpp
)

ADD_EXECUTABLE(test
    src/Argument.cpp
    unit_tests/unit_test.cpp
    src/Connector.cpp
    src/CommandTable.cpp
    src/Shell.cpp
    header/Argument.hpp
    header/Connector.hpp
    header/CommandTable.hpp
    header/Shell.hpp
    header/Parse.hpp
    header/Paranthesis.hpp
    src/Paranthesis.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)


