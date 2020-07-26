#include "Parser.h"
#include <string>
#include <cctype>
#include <stack>
#include <tuple>
#include <vector>
#include <algorithm>
#include "Constant.h"
#include "SymbolFactory.h"

enum class PriorityOfOperator
{
	hightest,
	hight,
	low,
	lowest
};

FunctionSymbol::FunctionType getFunctionTypeFromNode(Parser::compositeNode function) {

	static std::unordered_map<Parser::compositeNode, FunctionSymbol::FunctionType> function_type_correspondence
	{
		{ Parser::compositeNode::NaturalLogarithm, FunctionSymbol::FunctionType::NaturalLogarithm },
		{ Parser::compositeNode::Cos, FunctionSymbol::FunctionType::Cos },
		{ Parser::compositeNode::Sin, FunctionSymbol::FunctionType::Sin },

	};
	return function_type_correspondence[function];
}

Expression::ExpressionType getExpressionTypeFromNode(Parser::compositeNode expression) {

	static std::unordered_map<Parser::compositeNode, Expression::ExpressionType> expression_type_correspondence
	{
		{ Parser::compositeNode::Addition, Expression::ExpressionType::Addition },
		{ Parser::compositeNode::Difference, Expression::ExpressionType::Difference },
		{ Parser::compositeNode::Division, Expression::ExpressionType::Division },
		{ Parser::compositeNode::Product, Expression::ExpressionType::Product },
		{ Parser::compositeNode::Power, Expression::ExpressionType::Power }

	};
	return expression_type_correspondence[expression];
}
std::string getCharFromType(Parser::compositeNode type)
{
	static std::unordered_map<Parser::compositeNode, std::string> string_composite_type_correspondence
	{
		{ Parser::compositeNode::NaturalLogarithm, "ln" },
		{ Parser::compositeNode::Cos, "cos" },
		{ Parser::compositeNode::Sin, "sin" },
		{ Parser::compositeNode::Addition, "+" },
		{ Parser::compositeNode::Difference, "-" },
		{ Parser::compositeNode::Division, "/" },
		{ Parser::compositeNode::Product, "*" },
		{ Parser::compositeNode::Power, "^" }
	};
	return string_composite_type_correspondence[type];
}

PriorityOfOperator getPriorityOfComposite(Parser::compositeNode node)
{
	static std::unordered_map<Parser::compositeNode, PriorityOfOperator> priority_of_composite
	{
		{ Parser::compositeNode::NaturalLogarithm, PriorityOfOperator::lowest },
		{ Parser::compositeNode::Cos, PriorityOfOperator::lowest },
		{ Parser::compositeNode::Sin, PriorityOfOperator::lowest },
		{ Parser::compositeNode::Addition, PriorityOfOperator::hightest },
		{ Parser::compositeNode::Difference, PriorityOfOperator::hightest },
		{ Parser::compositeNode::Division, PriorityOfOperator::hight },
		{ Parser::compositeNode::Product, PriorityOfOperator::hight },
		{ Parser::compositeNode::Power, PriorityOfOperator::low }
	};
	return priority_of_composite[node];
}

bool stringIsDouble(std::string const & expr) {
	size_t dot_count = 0;
	for (std::string::const_iterator it = expr.begin(); it != expr.end(); ++it) {
		if (std::isdigit(*it) || (*it) == '.' && dot_count == 0) {
			dot_count = (*it) == '.' ? ++dot_count : dot_count;
		}
		else {
			return false;
		}
	}
	return true;
}




std::pair<Parser::compositeNode, size_t> Parser::getFirstOperator(std::string  & expr)
{
	static std::vector<compositeNode> composite_nodes{ compositeNode::Addition, compositeNode::Cos, compositeNode::Difference,
	compositeNode::Division,  compositeNode::NaturalLogarithm, compositeNode::Power,
	compositeNode::Product, compositeNode::Sin };

	// vector, which contains information of all operators : size of stack, priority of node, position of the composite node, type of node
	// this vectors allows as to recognize priority of each composite node

	std::vector<std::tuple<size_t, PriorityOfOperator, size_t, compositeNode>> composite_priority_char; 

	std::stack<char> bracket_stack;
	std::unordered_map<size_t, size_t> size_of_stack_position;
	size_t current_position = 0;
	for (auto &x : expr) {
		switch (x)
		{
		case '(':
			bracket_stack.push(x);
			break;
		case ')':
			if (!bracket_stack.empty())
			{
				bracket_stack.pop();
			}
			break;
		default:
			break;
		}
		size_of_stack_position.emplace(current_position, bracket_stack.size());
		++current_position;
	}

	for (compositeNode & x : composite_nodes) {
		size_t composite_position = expr.find(getCharFromType(x));

		while ( composite_position != std::string::npos )
		{
			composite_priority_char.push_back(
				{ size_of_stack_position[composite_position],
				getPriorityOfComposite(x),
				composite_position,
				x });

			composite_position = expr.find(getCharFromType(x), composite_position + 1);
		}
	}

	if (!composite_priority_char.empty())
	{
		std::sort(composite_priority_char.begin(), composite_priority_char.end());
		return std::pair<compositeNode, size_t>
		{
			std::get<3>(composite_priority_char.front()),
			std::get<2>(composite_priority_char.front()) 
		};
	}

	else {
		size_t left_bracket = expr.find('(');
		while( left_bracket != std::string::npos) {
			expr = expr.substr(left_bracket + 1);
			left_bracket = expr.find('(');
		}
		size_t right_bracket = expr.find(')');
		while( right_bracket != std::string::npos) {
			expr = expr.substr(0, right_bracket);
			right_bracket = expr.find(')');
		}
		return std::pair<compositeNode, size_t>(compositeNode::UnknownType, std::string::npos);
	}

}

std::shared_ptr<Symbol> Parser::createCompositeSymbol(std::pair<compositeNode, size_t> composite_information,
	std::string const & expr, std::vector<std::string> const & arguments)
{
	size_t pos_operator = composite_information.second;
	std::string skip_composite_substring = expr.substr(composite_information.second + getCharFromType(composite_information.first).length() - 1);

	std::vector<compositeNode> function_nodes{ compositeNode::Cos, compositeNode::Sin, compositeNode::NaturalLogarithm };

	std::vector<compositeNode> operator_nodes{ compositeNode::Addition, compositeNode::Product, compositeNode::Division,
											   compositeNode::Power, compositeNode::Difference};

	if (std::find(function_nodes.begin(), function_nodes.end(), composite_information.first) != function_nodes.end())
	{
		return SymbolFactory::createSymbol(startParsing(skip_composite_substring, arguments), getFunctionTypeFromNode(composite_information.first));
	}
	else if (std::find(operator_nodes.begin(), operator_nodes.end(), composite_information.first) != operator_nodes.end())
	{
		return SymbolFactory::createExpression(startParsing(expr.substr(0, pos_operator), arguments),
			startParsing(expr.substr(pos_operator + 1), arguments), getExpressionTypeFromNode(composite_information.first));
	}

	return std::shared_ptr<Symbol>();
}


void Parser::bracketsValidation(std::string const & expr)
{
	if (expr.find('(') == std::string::npos) {
		return;
	}
	std::stack<char> brackets_stack;
	for(auto & ch : expr)
	{
		switch (ch)
		{
		case '(':
			brackets_stack.push(ch);
			break;
		case ')':
			if (brackets_stack.empty()) {
				throw std::runtime_error("Incorrect pairs of brackets");
			}
			else
			{
				brackets_stack.pop();
			}
			break;
		default:
			break;
		}
	}

	if (!brackets_stack.empty()) {
		throw std::runtime_error("Incorrect amount of brackets");
	}
	
}

void Parser::unaryExpressionValidation(std::string const & expr)
{
	static std::vector<compositeNode> validattive_expressions
	{ compositeNode::Product, compositeNode::Division, compositeNode::Power };

	static std::vector<compositeNode> operations
	{ compositeNode::Product, compositeNode::Division, compositeNode::Power,
	  compositeNode::Addition, compositeNode::Difference};

	for (auto & exceptionable_operation : validattive_expressions) {
		if(expr.find(getCharFromType(exceptionable_operation)) == 0)
		{
			throw std::runtime_error("invalid syntax");
		}
	}
	for (auto & exceptionable_operation : validattive_expressions)
	{
		 
		size_t it = expr.find(getCharFromType(exceptionable_operation));

		while ( it != std::string::npos)
		{
			for (auto & operation : operations)
			{
				if (std::string(1, expr[it - 1]) == getCharFromType(operation))
				{
					throw std::runtime_error("invalid syntax");
				}
			}

			it = expr.find(getCharFromType(exceptionable_operation), it + 1);
		}
	}
}

std::string Parser::deleteSpaces(std::string const  & expr)
{
	std::string expr_copy = expr;
	expr_copy.erase(std::remove_if(expr_copy.begin(), expr_copy.end(), isspace), expr_copy.end());
	 return expr_copy;
}


std::shared_ptr<Symbol> Parser::startParsing(std::string & expr, std::vector<std::string> const & arguments) {

	std::pair<compositeNode, size_t> composite_information = getFirstOperator(expr);


	if (composite_information.first != compositeNode::UnknownType) {

		return createCompositeSymbol(composite_information, expr, arguments);
	}
	else {
		return createPrimitiveSymbol(expr, arguments);
	}

}

std::shared_ptr<Symbol> Parser::createPrimitiveSymbol(std::string & expr, std::vector<std::string> const & arguments)
{

	if (std::find(arguments.begin(), arguments.end(), expr) != arguments.end()) {
		return SymbolFactory::createSymbol(expr, SymbolFactory::Symbol_t::arg_t);
	}
	
	if (!stringIsDouble(expr))
	{
		return SymbolFactory::createSymbol(expr, SymbolFactory::Symbol_t::const_str_t);
	}
		
	
		bool expr_empty = expr.empty();


		return expr.empty() ? SymbolFactory::createSymbol(0) : SymbolFactory::createSymbol(expr, SymbolFactory::Symbol_t::const_t);
	
}



std::shared_ptr<Symbol>  Parser::Parse(std::string const & expr, std::vector<std::string> const & arguments)
{
	bracketsValidation(expr);
	unaryExpressionValidation(expr);
	auto expr_copy = deleteSpaces(expr);
	return startParsing(expr_copy, arguments);
}
