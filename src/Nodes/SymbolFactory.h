#pragma once 
#include "Symbol.h"
#include "Expression.h"
#include "FunctionSymbol.h" 
#include <string>

class SymbolFactory
{
public:

	enum class Symbol_t { arg_t, const_t, const_str_t };

public:
	static std::shared_ptr<Symbol> createSymbol(std::string const & str, Symbol_t type);
	static std::shared_ptr<Symbol> createSymbol(std::shared_ptr<Symbol> expr, FunctionSymbol::FunctionType type);
	static std::shared_ptr<Symbol> createSymbol(double value);

	static std::shared_ptr<Symbol> createExpression(std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right, char sign);
	static std::shared_ptr<Symbol> createExpression(std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right, Expression::ExpressionType sign);
};