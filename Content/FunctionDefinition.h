#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <optional>

#include "Type.h"
#include "Statement.h"

namespace SimpleParser {

    class ParameterFunction {
    public:
        std::string ParameterName;
        Type ParameterType;

        void DebugPrint(size_t indent) const;
    };

    class FunctionDefinition {
    public:
        std::string FunctionName;
        std::vector<ParameterFunction> FunctionParameters;
        std::vector<Statement> FunctionStatements;

        void DebugPrint() const;
    };
}