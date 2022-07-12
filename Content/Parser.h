#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <map>

#include "TokenBuilding.h"
#include "Type.h"
#include "FunctionDefinition.h"
#include "Statement.h"

namespace SimpleParser{

    class Parser
    {
    public:
        Parser();

        void parse(std::vector<Token>& tokens);

        void debugPrint() const;

    private:
        bool expectFunctionDef();
        std::optional<std::vector<Statement>> parseFunctionBody();

        std::optional<Statement> expectOneValue();
        std::optional<Statement> expectVariableDeclaration();
        std::optional<Statement> expectFunctionCall();
        std::optional<Statement> expectStatement();
        std::optional<Statement> expectExpression();
        size_t operatorPrecedence(const std::string &operatorName);

        std::optional<Type> expectType();
        std::optional<Token> expectIdentifier(std::string const& name = std::string());
        std::optional<Token> expectOperator(std::string const& name = std::string());

        std::vector<Token>::iterator _currentToken;
        std::vector<Token>::iterator _endToken;
        std::map<std::string, Type> mTypes;
        std::map<std::string, FunctionDefinition> Functions;

        Statement *findRightmostStatement(Statement *lhs, size_t rhsPrecedence);
    };
}