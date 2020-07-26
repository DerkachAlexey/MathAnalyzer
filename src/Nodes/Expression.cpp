#include "Expression.h"

Expression::Expression(std::shared_ptr<Symbol>  _left, std::shared_ptr<Symbol>  _right, ExpressionType _t)
	: left(_left), right(_right), type(_t)
{
}

std::shared_ptr<Symbol>  Expression::getLeft()
{
	return left;
}

std::shared_ptr<Symbol>  Expression::getRight()
{
	return right;
}

Expression::ExpressionType Expression::getType()
{
	return type;
}
