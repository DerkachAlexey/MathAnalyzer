#include "SymbolFactory.h"
#include "ArgumentSymbol.h"
#include "AdditionExpression.h"
#include "DifferenceExpression.h"
#include "ProductExpression.h"
#include "DivideExpression.h"
#include "PowerExpression.h"
#include "Constant.h"
#include "StringConstant.h"
#include "FunctionSymbol.h" 
#include <cctype>


std::shared_ptr<Symbol> SymbolFactory::createSymbol(std::string const & expr, Symbol_t t)
{
	switch (t)
	{
	case Symbol_t::arg_t:
		return std::make_shared<ArgumentSymbol>(expr);
		break;
	case Symbol_t::const_t:
		return std::make_shared<Constant>(expr);
		break;
	case Symbol_t::const_str_t:
		return std::make_shared<StringConstant>(expr);
		break;
	default:
		break;
	}
}

std::shared_ptr<Symbol> SymbolFactory::createSymbol(std::shared_ptr<Symbol> expr, FunctionSymbol::FunctionType type)
{
	return 	std::make_shared<FunctionSymbol>(expr, type);
}

std::shared_ptr<Symbol> SymbolFactory::createSymbol(double value)
{
	return 	std::make_shared<Constant>(std::to_string(value));
}


std::shared_ptr<Symbol> SymbolFactory::createExpression(std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right, char sign)
{

	switch (sign)
	{
	case '+':
		return std::make_shared < AdditionExpression>(left, right);
	case '-':
		return std::make_shared < DifferenceExpression>(left, right);
	case '*':
		return std::make_shared < ProductExpression>(left, right);
	case '/':
		return std::make_shared < DivideExpression>(left, right);
	case '^':
		return std::make_shared <PowerSymbol>(left, right);
	default:
		break;
	}
}

std::shared_ptr<Symbol> SymbolFactory::createExpression(std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right, Expression::ExpressionType sign)
{
	switch (sign)
	{
	case Expression::ExpressionType::Addition:
		return std::make_shared < AdditionExpression>(left, right);
	case Expression::ExpressionType::Difference:
		return std::make_shared < DifferenceExpression>(left, right);
	case Expression::ExpressionType::Division:
		return std::make_shared < DivideExpression>(left, right);
	case Expression::ExpressionType::Product:
		return std::make_shared < ProductExpression>(left, right);
	case Expression::ExpressionType::Power:
		return std::make_shared <PowerSymbol>(left, right);
	default:
		break;
	}

}
