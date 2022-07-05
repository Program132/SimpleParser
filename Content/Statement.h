#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>

#include "Type.h"

namespace SimpleParser {

    enum class StatementKind: int {
        VARIABLE_DECLARATION,
        FUNCTION_CALL,
        LITTERAL
    };

    static const char* sStatementKindStrings[] = {
        "VARIABLE_DECLARATION",
        "FUNCTION_CALL",
        "LITTERAL"
    };

    class Statement {
    public:
        std::string StatementName;
        Type StatementType{Type("void", VOID)};
        std::vector<Statement> StatementParameters;

        StatementKind kind{StatementKind::FUNCTION_CALL};

        void DebugPrint();
    };
}