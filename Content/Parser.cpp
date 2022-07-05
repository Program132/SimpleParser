#include "Parser.h"

namespace SimpleParser {
	Parser::Parser() {
		mTypes["void"] = Type("void", VOID);
		mTypes["int"] = Type("signed int", INT32);
		mTypes["unsigned"] = Type("unsignd int", INT32);
        mTypes["char"] = Type("signed char", INT8);
		mTypes["uint8_t"] = Type("uint8_t", INT8);
        mTypes["double"] = Type("double", DOUBLE);
	}

    void Parser::debugPrint() const
    {
        for (auto funcPair : Functions)
        {
            funcPair.second.DebugPrint();
        }
    }


	bool Parser::expectFunctionDef() {
        std::vector<Token>::iterator parseStart = _currentToken;
		std::optional<Type> possibleType = expectType();
		if (possibleType.has_value()) // Un type à été trouvé
		{
			std::optional<Token> possibleName = expectIdentifier();

			if (possibleName.has_value()) { // On a un nom
				std::optional<Token> possibleOperator = expectOperator("(");

				if (possibleOperator.has_value()) { // On a une fonction

                    FunctionDefinition func;
                    func.FunctionName = possibleName->mText;

                    while (!expectOperator(")").has_value())
                    {
                        std::optional<Type> possibleTypeParameter = expectType();
                        if (!possibleTypeParameter.has_value())
                        {
                            throw std::runtime_error("Un type est attendu avant le nom de l'argument.");
                        }

                        ParameterFunction param;
                        param.ParameterType = possibleTypeParameter->mName;
                        std::optional<Token> possibleVariableNameParameter = expectIdentifier();
                        if (possibleVariableNameParameter.has_value())
                        {
                            param.ParameterName = possibleVariableNameParameter->mText;
                        }

                        func.FunctionParameters.push_back(param);

                        if (expectOperator(")").has_value())
                        {
                            break;
                        }
                        if (!expectOperator(",").has_value() && !expectOperator(")").has_value())
                        {
                            throw std::runtime_error("Un ',' est attendu pour separer les parametres. Une ')' est attendu pour indiquer la fin de la liste des arguments.");
                        }
                    }

                    std::optional<std::vector<Statement>> statements = parseFunctionBody();
                    if (!statements.has_value())
                    {
                        Parser::_currentToken = parseStart;
                        return false;
                    }
                    func.FunctionStatements.insert(func.FunctionStatements.begin(), statements->begin(), statements->end());

                    Functions[func.FunctionName] = func;

                    return true;
				} else {
                    Parser::_currentToken = parseStart;
				}
			} else {
                Parser::_currentToken = parseStart;
			}
		}
		return false;
	}

	void Parser::parse(std::vector<Token>& tokens)
	{
		Parser::_endToken = tokens.end();
		Parser::_currentToken = tokens.begin();

		while (Parser::_currentToken != Parser::_endToken)
		{
			if (Parser::expectFunctionDef())
			{

			}
			else {
				std::cerr <<  "Identifier inconnu : " << Parser::_currentToken->mText << std::endl;
				++Parser::_currentToken;
			}
		}
	}

	std::optional<Token> Parser::expectIdentifier(std::string const& name)
	{
		if (Parser::_currentToken == Parser::_endToken) { return std::nullopt; }

		if (Parser::_currentToken->mType != IDENTIFIER) { return std::nullopt; }

		if (!name.empty() && Parser::_currentToken->mText != name) { return std::nullopt; }

		Token returnToken = *Parser::_currentToken;
		++Parser::_currentToken;
		return returnToken;
	}

	std::optional<Token> Parser::expectOperator(std::string const& name)
	{
		if (Parser::_currentToken == Parser::_endToken) { return std::nullopt; }
		if (Parser::_currentToken->mType != OPERATOR) { return std::nullopt; }
		if (!name.empty() && Parser::_currentToken->mText != name) { return std::nullopt; }

		Token returnToken = *Parser::_currentToken;
		++Parser::_currentToken;
		return returnToken;
	}

    std::optional<Type> Parser::expectType() {
        std::optional<Token> possibleType = expectIdentifier();
        if (!possibleType) { return std::nullopt; }

        std::map<std::string, Type>::iterator foundType = mTypes.find(possibleType->mText);
        if (foundType == mTypes.end()) {
            --Parser::_currentToken;
            return std::nullopt;
        }

        return foundType->second;
    }

    std::optional<std::vector<Statement>> Parser::parseFunctionBody()
    {
        if (!expectOperator("{").has_value()) {
            return std::nullopt;
        }

        std::vector<Statement> statements;

        while (!expectOperator("}").has_value())
        {
            std::optional<Statement> statement = expectOneValue();
            if (statement.has_value()) {
                statements.push_back(statement.value());
            }
        }

        return statements;
    }

    std::optional<Statement> Parser::expectOneValue()
    {
        std::optional<Statement> res;
        if (Parser::_currentToken != Parser::_endToken && Parser::_currentToken->mType == DOUBLE_LITERAL)
        {
            Statement doubleLitteralStatement;
            doubleLitteralStatement.kind = StatementKind::LITTERAL;
            doubleLitteralStatement.StatementName = _currentToken->mText;
            doubleLitteralStatement.StatementType = Type("double", DOUBLE);
            res = doubleLitteralStatement;
            ++Parser::_currentToken;
        }
        else if (Parser::_currentToken != Parser::_endToken && Parser::_currentToken->mType == INTERGER_LITERAL)
        {
            Statement integerLitteralStatement;
            integerLitteralStatement.kind = StatementKind::LITTERAL;
            integerLitteralStatement.StatementName = _currentToken->mText;
            integerLitteralStatement.StatementType = Type("signed integer", INT32);
            res = integerLitteralStatement;
            ++Parser::_currentToken;
        }
        else if (Parser::_currentToken != Parser::_endToken && Parser::_currentToken->mType == STRING_LITTERAL)
        {
            Statement stringLitteralStatement;
            stringLitteralStatement.kind = StatementKind::LITTERAL;
            stringLitteralStatement.StatementName = Parser::_currentToken->mText;
            stringLitteralStatement.StatementType = Type("string", UINT8);
            res = stringLitteralStatement;
            ++Parser::_currentToken;
        }
        else {
            res = expectVariableDeclaration();
        }

        if (!res.has_value())
        {
            res = expectFunctionCall();
        }

        return res;
    }

    std::optional<Statement> Parser::expectVariableDeclaration()
    {
        std::vector<Token>::iterator startToken = _currentToken;
        std::optional<Type> possibleType = expectType();
        if (!possibleType.has_value())
        {
            Parser::_currentToken = startToken;
            return std::nullopt;
        }

        std::optional<Token> possibleVariableName = expectIdentifier();
        if (!possibleVariableName.has_value()) {
            Parser::_currentToken = startToken;
            return std::nullopt;
        }

        Statement statement;
        statement.kind = StatementKind::VARIABLE_DECLARATION;
        statement.StatementName = possibleVariableName->mText;
        statement.StatementType = possibleType.value();

        if (expectOperator("=").has_value())
        {
            std::optional<Statement> initialValue = expectOneValue();
            if (!initialValue.has_value())
            {
                throw std::runtime_error("Une valeur est attendu a droite du '='.");
            }

            statement.StatementParameters.push_back(initialValue.value());
        }

        if (!expectOperator(";").has_value())
        {
            throw std::runtime_error("Un ';' est attendu a la fin de la declaration de la variable.");
        }

        return statement;
    }

    std::optional<Statement> Parser::expectFunctionCall() {
        std::vector<Token>::iterator startToken = Parser::_currentToken;

        std::optional<Token> possibleFunctionName = expectIdentifier();
        if (!possibleFunctionName.has_value())
        {
            Parser::_currentToken = startToken;
            return std::nullopt;
        }

        if (!expectOperator("(").has_value())
        {
            Parser::_currentToken = startToken;
            return std::nullopt;
        }

        Statement functionCall;
        functionCall.kind = StatementKind::FUNCTION_CALL;
        functionCall.StatementName = possibleFunctionName->mText;

        while (!expectOperator(")").has_value()) {
            std::optional<Statement> parameter = expectOneValue();
            if (!parameter.has_value())
            {
                throw std::runtime_error("Expression attendue en parametre.");
            }

            functionCall.StatementParameters.push_back(parameter.value());
            if (expectOperator(")").has_value())
            {
                break;
            }
            if (!expectOperator(",").has_value())
            {
                throw std::runtime_error(std::string("Une ',' est attendu pour separer les parametres, trouve dans : ") + Parser::_currentToken->mText + "'.");
            }
        }

        if (!expectOperator(";").has_value())
        {
            throw std::runtime_error("Un ';' est attendu a la fin de l'appellation de la fonction.");
        }

        return functionCall;
    }
}