#pragma once
#include "Symbol.h"
class Simplifier
{
public :
	static std::shared_ptr<Symbol>  Simplify(std::shared_ptr<Symbol>  s);
};

