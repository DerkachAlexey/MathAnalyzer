#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../catch2.hpp"
#include "Parser.h"
#include "SymbolFactory.h"
#include "Constant.h"
#include "AdditionExpression.h"
#include "Diff.h"

TEST_CASE("Differntial simple rules", "[Diff]") {

	SECTION("Diff constant") {
		std::shared_ptr<Symbol> parsing = Parser::Parse("3", { "x" });
		REQUIRE(Diff::diff(parsing, "x") == SymbolFactory::createSymbol("0", SymbolFactory::Symbol_t::const_t));

	}

	SECTION("Diff argument") {
		std::shared_ptr<Symbol> parsing = Parser::Parse("x", { "x" });
		REQUIRE(Diff::diff(parsing, "x") == SymbolFactory::createSymbol("1", SymbolFactory::Symbol_t::const_t));
	}
	SECTION("Diff another arg") {
		std::shared_ptr<Symbol> parsing = Parser::Parse("x + y", { "x", "y" });
		auto diffs = Diff::diff(parsing, "x");
		std::cout << *diffs;
		REQUIRE(Diff::diff(parsing, "x") == SymbolFactory::createSymbol("1", SymbolFactory::Symbol_t::const_t));
	} //WAITING FOR SIMPLYFIER...
	SECTION("Diff pow") {
		std::shared_ptr<Symbol> parsing = Parser::Parse("x^3", { "x" });
		std::shared_ptr<Symbol> symb = Diff::diff(parsing, "x");
		REQUIRE(symb == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createExpression(SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("2", SymbolFactory::Symbol_t::const_t), '^'), '*'));

	} //WAITING FOR SIMPLYFIER...

	SECTION("Diff cos") {
		std::shared_ptr<Symbol> parsing = Parser::Parse("cos(x)", { "x" });
		std::shared_ptr<Symbol> symb = Diff::diff(parsing, "x");
		REQUIRE(Diff::diff(parsing,"x") == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createExpression(SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("2", SymbolFactory::Symbol_t::const_t), '^'), '*'));

	}

}



