#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace SimpleParser {
    enum BuiltinTypes {
        VOID,
        INT8,
        UINT8,
        INT32,
        UINT32,
        DOUBLE,
        STRUCT
    };


    class Type {
    public:
        Type(const std::string &name = "", enum BuiltinTypes type = VOID)
                : mName(name), mType(type) {}

        std::string mName;
        enum BuiltinTypes mType;
        std::vector<Type> mField; // Que pour les structs !
    };
}