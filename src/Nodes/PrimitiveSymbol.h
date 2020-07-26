#pragma once
#include "Symbol.h"
#include <string>

class PrimitiveSymbol :
	public Symbol
{
public:
	virtual std::string getValue() const = 0;
	~PrimitiveSymbol() = 0
	{}
};

