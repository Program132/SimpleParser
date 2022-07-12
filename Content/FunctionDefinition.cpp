#include "FunctionDefinition.h"

namespace SimpleParser {
    void FunctionDefinition::DebugPrint() const
    {
        std::cout << FunctionName << "(\n";

        for (auto &param : FunctionParameters) // ParameterFunction
        {
            param.DebugPrint(1);
            std::cout << "\n";
        }

        std::cout << ") {\n" << std::endl;
        for (Statement statement : FunctionStatements)
        {
            statement.DebugPrint(0);
        }
        std::cout << "} \n" << std::endl;
    }

    void ParameterFunction::DebugPrint(size_t indent) const
    {
        std::cout << std::string(indent, '\t') << ParameterType.mName << " " << ParameterName;
    }
}