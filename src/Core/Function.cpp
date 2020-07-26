
#include "FunctionSymbol.h"
#include "Computer.h"
#include "Function.h"
#include "StringConstant.h"


std::shared_ptr<Symbol> Function::getExpression() const
{
	return _full_expression;
}

std::vector<std::string> Function::getArguments() const
{
	return _arguments;
}

std::vector<std::string> Function::getStrings() const
{
	return _const_strings;
}

Function::Function(std::shared_ptr<Symbol> s):
	_full_expression(s)
{
	fill_arguments_strings(s);
}

Function::Function(std::string const & expression)
{
	_full_expression = Parser::Parse(expression);
	fill_arguments_strings(_full_expression);
}

Function::Function(std::string const & expression, std::vector<std::string> const & arguments):
	_arguments(arguments)
{
	_full_expression = Parser::Parse(expression, arguments);
	fill_arguments_strings(_full_expression);
}

ComputeResult Function::operator()(std::vector< double > const & arguments)
{

	//if (arguments.size() != _arguments.size()) {
	//	throw std::runtime_error("invalid amount of arguments");
	//}

	std::vector<std::pair<const std::string, double>>  arg_correspondence;

	for (size_t i = 0; i < arguments.size(); ++i) {
		arg_correspondence.push_back(std::make_pair(_arguments[i], arguments[i]));
	}

	context = ComputeContext(arg_correspondence);

	return Computer::Compute(_full_expression, context);
}

void Function::fill_arguments_strings(std::shared_ptr<Symbol> s)
{
	if (auto argument_symbol = std::dynamic_pointer_cast<ArgumentSymbol>(s))
	{
		if (std::find(_arguments.begin(), _arguments.end(), argument_symbol->getValue()) == _arguments.end())
		{
			_arguments.push_back(argument_symbol->getValue());
		}
	}
	else if (auto string_symbol = std::dynamic_pointer_cast<StringConstant>(s))
	{
		_const_strings.push_back(string_symbol->getValue());
	}
	else if (auto expression = std::dynamic_pointer_cast<Expression>(s))
	{
		fill_arguments_strings(expression->getLeft());
		fill_arguments_strings(expression->getRight());
	}
	else if (auto func_symb = std::dynamic_pointer_cast<FunctionSymbol>(s))
	{
		fill_arguments_strings(func_symb->getExpression());
	}

	return;
}


