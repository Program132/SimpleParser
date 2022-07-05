#include "FunctionDefinition.h"

namespace SimpleParser {
    void FunctionDefinition::DebugPrint() const
    {
        std::cout << FunctionName << "(\n";

        for (ParameterFunction param : FunctionParameters)
        {
            param.DebugPrint();
            std::cout << "\n";
        }

        std::cout << ") {\n" << std::endl;
        for (Statement statement : FunctionStatements)
        {
            statement.DebugPrint();
        }
        std::cout << "} \n" << std::endl;
    }

    void ParameterFunction::DebugPrint() const
    {
        std::cout << ParameterType.mName << " " << ParameterName;
    }
}