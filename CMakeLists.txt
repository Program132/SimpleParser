cmake_minimum_required(VERSION 3.22)
project(SimpleParser)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(Content)

add_executable(SimpleParser
        Content/Parser.cpp
        Content/Parser.h
        Content/TokenBuilding.cpp
        Content/TokenBuilding.h
        main.cpp Content/FunctionDefinition.cpp Content/FunctionDefinition.h Content/Type.cpp Content/Type.h Content/Statement.cpp Content/Statement.h)
