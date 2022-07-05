#include "Statement.h"

namespace SimpleParser{
    void Statement::DebugPrint() {
        std::cout <<  sStatementKindStrings[int(kind)] << " ";
        std::cout << StatementType.mName << " " << StatementName << " (\n";
        for (Statement statement : StatementParameters) {
            statement.DebugPrint();
        }
        std::cout << ")" << std::endl;
    }
}