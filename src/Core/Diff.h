#pragma once
#include "Symbol.h"
#include "PowerExpression.h"
#include "Constant.h"
#include "ProductExpression.h"
#include "AdditionExpression.h"
#include "Function.h"
class Diff
{

public:
	static std::shared_ptr<Symbol>  diff(std::shared_ptr<Symbol> s, std::string const & argument);
	static Function diff(Function const &, std::string const & );
};

