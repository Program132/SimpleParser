#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <map>

#include "TokenBuilding.h"

namespace SimpleParser{

	enum BuiltinTypes {
		VOID,
		INT8,
		UINT8,
		INT32,
		UINT32,
		DOUBLE,
		STRUCT
	};


	class Type {
	public:
		Type(const std::string& name = "", enum BuiltinTypes type = VOID) : mName(name), mType(type) {}

		std::string mName;
		enum BuiltinTypes mType;
		std::vector<Type> mField; // Que pour les structs !
	};


	class Parser
	{
	public:
		Parser();

		void parse(std::vector<Token>& tokens);

	private:
		bool expectFunctionDef();

		std::optional<Type> expectType();
		std::optional<Token> expectIdentifier(std::string const& name = std::string());
		std::optional<Token> expectOperator(std::string const& name = std::string());

		std::vector<Token>::iterator _currentToken;
		std::vector<Token>::iterator _endToken;
		std::map<std::string, Type> mTypes;
	};
}