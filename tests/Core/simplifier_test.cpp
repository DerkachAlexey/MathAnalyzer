#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../catch2.hpp"
#include "Simplifier.h"
#include "Parser.h"
#include "SymbolFactory.h"
#include "Constant.h"
#include "AdditionExpression.h"

TEST_CASE("Simple expression testing", "[Simplify]") {

	SECTION("Simply expression") {
		auto add_expr = Parser::Parse("3+3");
		auto dif_expr = Parser::Parse("8-2");
		auto div_expr = Parser::Parse("12/2");
		auto prod_expr = Parser::Parse("3*2");

		auto res = SymbolFactory::createSymbol("6", SymbolFactory::Symbol_t::const_t);

		add_expr = Simplifier::Simplify(add_expr);
		dif_expr = Simplifier::Simplify(dif_expr);
		div_expr = Simplifier::Simplify(div_expr);
		prod_expr = Simplifier::Simplify(prod_expr);

		REQUIRE(add_expr == res);
		REQUIRE(dif_expr == res);
		REQUIRE(div_expr == res);
		REQUIRE(prod_expr == res);
	}

	SECTION("Brackets expression")
	{
		auto add_expr = Parser::Parse("4+(2*2)");
		auto dif_expr = Parser::Parse("12-(2*2)");
		auto div_expr = Parser::Parse("32/(2*2)");
		auto prod_expr = Parser::Parse("2*(2*2)");

		auto res = SymbolFactory::createSymbol("8", SymbolFactory::Symbol_t::const_t);

		add_expr = Simplifier::Simplify(add_expr);
		dif_expr = Simplifier::Simplify(dif_expr);
		div_expr = Simplifier::Simplify(div_expr);
		prod_expr = Simplifier::Simplify(prod_expr);

		REQUIRE(add_expr == res);
		REQUIRE(dif_expr == res);
		REQUIRE(div_expr == res);
		REQUIRE(prod_expr == res);
	}

	SECTION("Composite brackets expression")
	{
		auto add_expr = Parser::Parse("(5+5)+(2*5)");
		auto dif_expr = Parser::Parse("(10*3)-(2*5)");
		auto div_expr = Parser::Parse("(40+40)/(2*2)");
		auto prod_expr = Parser::Parse("(2+3)*(2*2)");

		auto res = SymbolFactory::createSymbol("20", SymbolFactory::Symbol_t::const_t);

		add_expr = Simplifier::Simplify(add_expr);
		dif_expr = Simplifier::Simplify(dif_expr);
		div_expr = Simplifier::Simplify(div_expr);
		prod_expr = Simplifier::Simplify(prod_expr);

		REQUIRE(add_expr == res);
		REQUIRE(dif_expr == res);
		REQUIRE(div_expr == res);
		REQUIRE(prod_expr == res);
	}


}

TEST_CASE("Expresstion with arguments testing", "[Simplify]") {

	SECTION("Simplify constant") {
		//3x+2*3 = 3x + 6
		auto expr = Parser::Parse("3x+2*3", {"x"});
		auto res = Parser::Parse("3x+6", {"x"});
		
		expr = Simplifier::Simplify(expr);

		REQUIRE(expr == res);
	}

	SECTION("Simplify arguments") {
		//3x - 2x = x
		auto expr = Parser::Parse("5*x-2*x", { "x" });
		auto res = Parser::Parse("3*x", { "x" });

		expr = Simplifier::Simplify(expr);

		REQUIRE(expr == res);
	}

	SECTION("Simplify Constant with brackets") {
		//(3x + 2) * 3 = 9x + 6
		auto expr = Parser::Parse("(3*x + 2) * 3", { "x" });
		auto res = Parser::Parse("9*x + 6", { "x" });

		expr = Simplifier::Simplify(expr);

		REQUIRE(expr == res);
	}

	SECTION("Simplify arguments with brackets") {
		//(3x^2 + x) / x = 3x + 1
		auto expr = Parser::Parse("(3*x^2 + x) / x", { "x" });
		auto res = Parser::Parse("3*x + 1", { "x" });

		expr = Simplifier::Simplify(expr);

		REQUIRE(expr == res);
	}

}

