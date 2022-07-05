#include "TokenBuilding.h"

namespace SimpleParser
{
	std::vector<Token> TokenBuilding::parse(const std::string& inProgram)
	{
		std::vector<Token> tokens;
		Token currentToken;

		currentToken.mLineNumber = 1;

		for (char _character : inProgram)
		{
			if (currentToken.mType == STRING_ESCAPE_SEQUENCE)
			{
				switch (_character)
				{
				case 'n': 
					currentToken.mText.append(1, '\n');
					break;
				case 'r':
					currentToken.mText.append(1, '\r');
					break;
				case 't':
					currentToken.mText.append(1, '\t');
					break;
				case '\\':
					currentToken.mText.append(1, '\\');
					break;
				default:
					throw std::runtime_error(std::string("unknown escape sequence: \\") + std::string(1, _character) +
						" in string on line " + std::to_string(currentToken.mLineNumber) + ".");
					break;
				}

				currentToken.mType = STRING_LITTERAL;
				continue;
			}
			else if (currentToken.mType == POTENTIAL_COMMENT && _character != '/') {
				currentToken.mType = OPERATOR;
				endToken(currentToken, tokens);
				continue;
			}



			switch (_character)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (currentToken.mType == WHITESPACE) {
					currentToken.mType = INTERGER_LITERAL;
					currentToken.mText.append(1, _character);
				} else if (currentToken.mType == POTENTIAL_DOUBLE) {
					currentToken.mType = DOUBLE_LITERAL;
					currentToken.mText.append(1, _character);
				}
				else {
					currentToken.mText.append(1, _character);
				}
				break;


			case '.':
				if (currentToken.mType == WHITESPACE) {
					currentToken.mType = POTENTIAL_DOUBLE;
					currentToken.mText.append(1, _character);
				}
				else if (currentToken.mType == INTERGER_LITERAL) {
					currentToken.mType = DOUBLE_LITERAL;
					currentToken.mText.append(1, _character);
				}
				else if (currentToken.mType == STRING_LITTERAL) {
					currentToken.mText.append(1, _character);
				}
				else {
					endToken(currentToken, tokens);
					currentToken.mType = OPERATOR;
					currentToken.mText.append(1, _character);
					endToken(currentToken, tokens);
				}
				break;



			case '{':
			case '}':
			case '(':
			case ')':
			case '=':
			case '-':
			case ';':
			case ',':
				if (currentToken.mType != STRING_LITTERAL) {
					endToken(currentToken, tokens);
					currentToken.mType = OPERATOR;
					currentToken.mText.append(1, _character);
					endToken(currentToken, tokens);
				}
				else {
					currentToken.mText.append(1, _character);
				}
				break;



			case ' ':
			case '\t':
				if (currentToken.mType == STRING_LITTERAL || currentToken.mType == COMMENT)
				{	
					currentToken.mText.append(1, _character);
				}
				else {
					endToken(currentToken, tokens);
				}
				break;

			case '\n':
			case '\r':
				endToken(currentToken, tokens);
				++currentToken.mLineNumber;
				break;



			case '"':
				if (currentToken.mType != STRING_LITTERAL) {
					endToken(currentToken, tokens);
					currentToken.mType = STRING_LITTERAL;
				}
				else if (currentToken.mType == STRING_LITTERAL) {
					endToken(currentToken, tokens);
				}
				break;

			case '\\':
				if (currentToken.mType == STRING_LITTERAL) {
					currentToken.mType = STRING_ESCAPE_SEQUENCE;
				}
				else {
					endToken(currentToken, tokens);
					currentToken.mType = OPERATOR;
					currentToken.mText.append(1, _character);
					endToken(currentToken, tokens);
				}
				break;


			case '/':
				if (currentToken.mType == STRING_LITTERAL)
				{
					currentToken.mText.append(1, _character);
				} else if (currentToken.mType == POTENTIAL_COMMENT)
				{
					currentToken.mType = COMMENT;
					currentToken.mText.erase();
				}
				else {
					endToken(currentToken, tokens);
					currentToken.mType = POTENTIAL_COMMENT;
					currentToken.mText.append(1, _character);
				}
				break;


			default:
				if (currentToken.mType == WHITESPACE || currentToken.mType == INTERGER_LITERAL
					|| currentToken.mType == DOUBLE_LITERAL)
				{
					endToken(currentToken, tokens);
					currentToken.mType = IDENTIFIER;
					currentToken.mText.append(1, _character);
				}
				else {
					currentToken.mText.append(1, _character);
				}
				break;
			}
		}

		endToken(currentToken, tokens);

		return tokens;
	}

	void TokenBuilding::endToken(Token &token, std::vector<Token> &tokens)
	{
		if (token.mType == COMMENT)
		{
			std::cout << "Ignoring comment : " << token.mText;
		} else if (token.mType != WHITESPACE)
		{
			tokens.push_back(token);
		}
		if (token.mType == POTENTIAL_DOUBLE)
		{
			if (token.mText.compare(".") == 0) {
				token.mType = OPERATOR;
			}
			else {
				token.mType = DOUBLE_LITERAL;
			}
		}
		
		token.mType = WHITESPACE;
		token.mText.erase();
	}

	void Token::DebugPrint() const 
	{
		std::cout << "Token(" << sTokenTypeStrins[mType] << ", \"" << mText << "\", " << mLineNumber << ")." << std::endl;
	}
}