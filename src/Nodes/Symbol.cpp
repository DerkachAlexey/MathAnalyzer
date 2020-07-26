#include "Symbol.h"
#include "SymbolVisitor.h"
#include "Constant.h"
#include "ArgumentSymbol.h"
#include "Expression.h"
#include "StringConstant.h"
#include "FunctionSymbol.h"
#include "VisualiserVis.h"

bool operator == (std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right) {

	if (!(typeid(*left) == typeid(*right)))
	{
		return false;
	}

	// Primitives
	else if (auto left_constant = std::dynamic_pointer_cast<Constant>(left)) {
		if (auto right_constant = std::dynamic_pointer_cast<Constant>(right)) {
			return left_constant->getValue() == right_constant->getValue();
		}
		return false;
	}
	else if (auto left_argument = std::dynamic_pointer_cast<ArgumentSymbol>(left)) {
		if (auto right_argument = std::dynamic_pointer_cast<ArgumentSymbol>(right)) {
			return left_argument->getValue() == right_argument->getValue();
		}
		return false;
	}
	else if (auto left_const_str = std::dynamic_pointer_cast<StringConstant>(left)) {
		if (auto right_const_str = std::dynamic_pointer_cast<StringConstant>(right)) {

			return (left_const_str->getValue() == right_const_str->getValue());

		}
	}

	// Composites
	else if (auto left_expression = std::dynamic_pointer_cast<Expression>(left)) {
		if (auto right_expression = std::dynamic_pointer_cast<Expression>(right)) {
			return (left_expression->getLeft() == right_expression->getLeft()) &&
				(left_expression->getRight() == right_expression->getRight());
		}
	}
	else if (auto left_func = std::dynamic_pointer_cast<FunctionSymbol>(left)) {
		if (auto right_func = std::dynamic_pointer_cast<FunctionSymbol>(right)) {

			return ((left_func->getFunctionType() == right_func->getFunctionType()) && 
				(left_func->getExpression() == right_func->getExpression()));

		}
	}
	
	return false;
}

std::ostream & operator<<(std::ostream& os, Symbol & s)
{
	VisualiserVis vis;
	s.Accept(&vis);
	os << vis.getResult();
	return os;
}