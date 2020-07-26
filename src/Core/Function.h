#pragma once

#include <vector>
#include <map>
#include <stack>
#include "Symbol.h"
#include "ArgumentSymbol.h"
#include "Expression.h"
#include "ComputeUtils.h"
#include "Parser.h"

class Function {

private:

	std::vector<std::string> _arguments;
	std::vector<std::string> _const_strings;
	std::shared_ptr<Symbol> _full_expression;
	ComputeContext context;
	void fill_arguments_strings(std::shared_ptr<Symbol> s);

public:
	std::shared_ptr<Symbol> getExpression() const;
	std::vector<std::string> getArguments() const;
	std::vector<std::string> getStrings() const;
	Function(std::shared_ptr<Symbol> s);
	Function(std::string const & expression);
	Function(std::string const & expression, std::vector<std::string> const & arguments);
	ComputeResult operator () (std::vector< double > const & arguments);
};