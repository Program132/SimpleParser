#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

namespace SimpleParser {


	enum TokenType {
		WHITESPACE,
		IDENTIFIER,
		INTERGER_LITERAL,
		DOUBLE_LITERAL,
		STRING_LITTERAL,
		OPERATOR,
		STRING_ESCAPE_SEQUENCE,
		ONE_LINE_SEQUENCE,
		POTENTIAL_DOUBLE,
		POTENTIAL_COMMENT,
		COMMENT
	};

	static const char* sTokenTypeStrins[] = {
		"WHITESPACE",
		"IDENTIFIER",
		"INTERGER_LITERAL",
		"DOUBLE_LITERAL",
		"STRING_LITTERAL",
		"OPERATOR",
		"STRING_ESCAPE_SEQUENCE",
		"ONE_LINE_SEQUENCE",
		"POTENTIAL_DOUBLE",
		"POTENTIAL_COMMENT",
		"COMMENT"
	};

	class Token
	{
	public:
		enum TokenType mType{WHITESPACE};
		std::string mText;
		size_t mLineNumber{ 0 };

		void DebugPrint() const;
	};

	class TokenBuilding 
	{
	public:
		std::vector<Token> parse(const std::string& inProgram);
		void endToken(Token& token, std::vector<Token>& tokens);
	};

}