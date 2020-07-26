#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../catch2.hpp"
#include "Parser.h"
#include "SymbolFactory.h"
#include "Constant.h"
#include "AdditionExpression.h"
#include "Function.h"

TEST_CASE("Function creating") {


		SECTION("Function with constant creating")
		{
			Function func("3", {});

			REQUIRE((((func.getExpression() == SymbolFactory::createSymbol(3.0)) &&
				(func.getArguments().empty() == true)) &&
				(func.getStrings().empty() == true)));
		}

		SECTION("Function with argument creating")
		{
			Function func("3", {"x"});

			REQUIRE((((func.getExpression() == SymbolFactory::createSymbol(3.0)) &&
				(func.getArguments().size() == 1)) &&
				(func.getStrings().empty() == true)));
		}

		SECTION("Function with string creating")
		{
			Function func("d", { "x" });

			REQUIRE((((func.getExpression() == SymbolFactory::createSymbol("d", SymbolFactory::Symbol_t::const_str_t)) &&
				(func.getArguments().size() == 1)) &&
				(func.getStrings()[0] == "d")));
		}
		
		SECTION("Function with string&argument creating")
		{
			Function func("d * x", { "x" });

			REQUIRE((((func.getExpression() == SymbolFactory::createExpression(SymbolFactory::createSymbol("d", SymbolFactory::Symbol_t::const_str_t), 
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), Expression::ExpressionType::Product)
				) &&
				(func.getArguments().size() == 1)) &&
				(func.getStrings()[0] == "d")));
		}
	
}

TEST_CASE("Function computing")
{
	SECTION("Trying to compute without arguments")
	{
		Function func("3*x", { "x" });

		REQUIRE_THROWS(func({}));
	}

	SECTION("Trying to compute with not enough amount of arguments")
	{
		Function func("3*x*y", { {"x"},{"y"} });

		REQUIRE_THROWS(func({1}));
	}

	SECTION("Check double result in function with constant")
	{
		Function func("3", {});

		REQUIRE(func({}).GetValue() == 3.0);
	}

	SECTION("Check result properties in function with constant & string")
	{
		Function func("3 + d", {});

		REQUIRE(((func({}).GetValue() == 3.0) &&
				(func.getStrings()[0] == "d")));
	}

	SECTION("Check result properties in '+' function with constant & argument")
	{
		Function func("3 + d", {"d"});

		REQUIRE(((func({1}).GetValue() == 4.0) &&
			(func.getArguments()[0] == "d")));
	}

	SECTION("Check result properties in '-' function with constant & argument")
	{
		Function func("3 - d", { "d" });

		REQUIRE(((func({ 1 }).GetValue() == 2.0) &&
			(func.getArguments()[0] == "d")));
	}

	SECTION("Check result properties in '*' function with constant & argument")
	{
		Function func("3 * d", { "d" });

		REQUIRE(((func({ 2 }).GetValue() == 6.0) &&
			(func.getArguments()[0] == "d")));
	}

	SECTION("Check result properties in '/' function with constant & argument")
	{
		Function func("3 / d", { "d" });

		REQUIRE(((func({ 2 }).GetValue() == 1.5) &&
			(func.getArguments()[0] == "d")));
	}

	SECTION("Check result properties in 'cos' function with constant & argument")
	{
		Function func("cos(d)", { "d" });

		REQUIRE(((func({ 0 }).GetValue() == 1.0) &&
			(func.getArguments()[0] == "d")));
	}

	SECTION("Check result properties in 'sin' function with constant & argument")
	{
		Function func("sin(d)", { "d" });

		REQUIRE(((func({ 0 }).GetValue() == 0.0) &&
			(func.getArguments()[0] == "d")));
	}

	SECTION("Check result properties in 'sin' function with constant & argument")
	{
		Function func("ln(d)", { "d" });

		REQUIRE(((func({ 1 }).GetValue() == 0.0) &&
			(func.getArguments()[0] == "d")));
	}

	// ln(negative number) = complex number ... Complex numbers will be added later

	SECTION("Compute large expression")
	{
		Function func("ln(x) * cos(y) + string / sin(x)  - 4 * 5*x/y^x", { {"x"},{"y"} });
		//for now - string [*,/,+,-] any_expression = string. Waiting for simplyfier
		REQUIRE(((func({ 1, 2 }).GetValue() == -10.0) &&
			(func.getStrings()[0] == "string")));
	}
	
}