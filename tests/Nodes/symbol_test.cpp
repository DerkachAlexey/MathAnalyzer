#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../catch2.hpp"
#include "Parser.h"
#include "SymbolFactory.h"
#include "Constant.h"
#include "AdditionExpression.h"

TEST_CASE("Symbol operator ==") {
	SECTION("check contain") {
		std::shared_ptr<Symbol> symb_1 = SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createSymbol("4", SymbolFactory::Symbol_t::const_t), '+');
		std::shared_ptr<Symbol> symb_2 = SymbolFactory::createExpression(
			SymbolFactory::createSymbol("2", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createSymbol("4", SymbolFactory::Symbol_t::const_t), '+');

		REQUIRE(symb_1 != symb_2);
	}

	SECTION("inequal types of expressions") {
		std::shared_ptr<Symbol> symb_1 = SymbolFactory::createExpression(
			SymbolFactory::createExpression(SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t), '+'),
			SymbolFactory::createSymbol("4", SymbolFactory::Symbol_t::const_t), '+');
		std::shared_ptr<Symbol> symb_2 = SymbolFactory::createExpression(
			SymbolFactory::createExpression(SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t), '*'),
			SymbolFactory::createSymbol("4", SymbolFactory::Symbol_t::const_t), '+');

		REQUIRE(symb_1 != symb_2);
	}

	SECTION("equal types of expressions") {
		std::shared_ptr<Symbol> symb_1 = SymbolFactory::createExpression(
			SymbolFactory::createExpression(SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t), '*'),
			SymbolFactory::createSymbol("4", SymbolFactory::Symbol_t::const_t), '+');
		std::shared_ptr<Symbol> symb_2 = SymbolFactory::createExpression(
			SymbolFactory::createExpression(SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t), '*'),
			SymbolFactory::createSymbol("4", SymbolFactory::Symbol_t::const_t), '+');

		REQUIRE(symb_1 == symb_2);
	}
}

