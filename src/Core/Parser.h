#pragma once
#include "Symbol.h"
#include "FunctionSymbol.h"
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

class Parser
{

public:
	enum class compositeNode
	{
		Addition,
		Difference,
		Division,
		Product,
		Power,
		NaturalLogarithm,
		Cos,
		Sin,

		UnknownType
	};


	static std::shared_ptr<Symbol>  Parse(std::string const & expr, std::vector<std::string> const & arguments = {});

private:

	static void bracketsValidation(std::string const & expr);
	static void unaryExpressionValidation(std::string const & expr);
	static std::string deleteSpaces(std::string const & expr);
	static std::shared_ptr<Symbol> startParsing(std::string & expr, std::vector<std::string> const & arguments);
	static std::shared_ptr<Symbol> createPrimitiveSymbol(std::string & expr, std::vector<std::string> const & arguments);
	static std::pair<compositeNode, size_t> getFirstOperator(std::string  & expr);
	static std::shared_ptr<Symbol> createCompositeSymbol(std::pair<compositeNode, size_t>, std::string const &, std::vector<std::string> const &);

};
