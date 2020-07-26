#pragma once
#include "Symbol.h"
#include <unordered_map>
class Expression : public Symbol
{
public:
	enum class ExpressionType
	{
		Addition,
		Difference,
		Division,
		Product,
		Power
	};


protected:

	std::shared_ptr<Symbol>  left;
	std::shared_ptr<Symbol>  right;
	ExpressionType type;

public:

	Expression(std::shared_ptr<Symbol>  _left, std::shared_ptr<Symbol>  _right, ExpressionType _t);
	std::shared_ptr<Symbol>  getLeft();
	std::shared_ptr<Symbol>  getRight();

	ExpressionType getType();

	virtual ~Expression() = 0
	{

	}
};

