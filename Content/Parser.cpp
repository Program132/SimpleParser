#include "Parser.h"

namespace SimpleParser {
	Parser::Parser() {
		mTypes["void"] = Type("void", VOID);
		mTypes["int"] = Type("signed int", INT32);
		mTypes["unsigned"] = Type("unsignd int", INT32);
		mTypes["char"] = Type("signed char", INT8);
		mTypes["uint8_t"] = Type("uint8_t", INT8);
	}


	
	bool Parser::expectFunctionDef() {
		std::optional<Type> possibleType = expectType();
		if (possibleType.has_value()) // Un type à été trouvé
		{
			std::optional<Token> possibleName = expectIdentifier();

			if (possibleName.has_value()) { // On a un nom
				std::optional<Token> possibleOperator = expectOperator("(");

				if (possibleOperator.has_value()) { // On a une fonction

					std::cout << "Fonction trouve : " << possibleName->mText << std::endl;;
					return true;
				} else {
					--Parser::_currentToken;
					--Parser::_currentToken;
				}
			} else {
				--Parser::_currentToken;
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
}