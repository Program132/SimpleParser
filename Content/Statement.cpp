#include "Statement.h"

namespace SimpleParser{
    void Statement::DebugPrint(size_t indent) {
        std::cout << std::string(indent, '\t') << sStatementKindStrings[int(kind)] << " ";
        std::cout << StatementType.mName << " " << StatementName << " (\n";
        for (Statement statement : StatementParameters) {
            statement.DebugPrint(0);
        }
        std::cout << std::string(indent, '\t') << ")" << std::endl;
    }
}