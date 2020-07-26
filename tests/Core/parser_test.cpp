#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../catch2.hpp"
#include "Parser.h"
#include "SymbolFactory.h"
#include "Constant.h"
#include "AdditionExpression.h"
#include "Computer.h"

TEST_CASE("Parser validation", "[Parse]") {

	SECTION("throw on incorrect amount") {
		REQUIRE_THROWS(Parser::Parse("()(", { "x" }));
	}

	SECTION("throw on incorrect pairs") {
		REQUIRE_THROWS(Parser::Parse("())(", { "x" }));
	}

}

TEST_CASE("Parser composite functions testing", "[Parse]") {

	SECTION("Check cos simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("cos(x)", { "x" });
		REQUIRE(single_operator == SymbolFactory::createSymbol(
			SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
			FunctionSymbol::FunctionType::Cos));
	}

	SECTION("Check sin in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("sin(x)", { "x" });
		REQUIRE(single_operator == SymbolFactory::createSymbol(
			SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
			FunctionSymbol::FunctionType::Sin));
	}

	SECTION("Check ln in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("ln(x)", { "x" });
		REQUIRE(single_operator == SymbolFactory::createSymbol(
			SymbolFactory::createSymbol("x",SymbolFactory::Symbol_t::arg_t),
			FunctionSymbol::FunctionType::NaturalLogarithm));
	}

	SECTION("Check cos & product in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("cos(x) * 6", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol(
			SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
			FunctionSymbol::FunctionType::Cos),
			SymbolFactory::createSymbol("6", SymbolFactory::Symbol_t::const_t),
			Expression::ExpressionType::Product));
	}

	SECTION("Check ln & divide in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("ln(x) / lr", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol(
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				FunctionSymbol::FunctionType::NaturalLogarithm),
			SymbolFactory::createSymbol("lr", SymbolFactory::Symbol_t::const_str_t),
			Expression::ExpressionType::Division));
	}

	SECTION("Check sin & XOR in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("sin(x) ^ lrafffres", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol(
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				FunctionSymbol::FunctionType::Sin),
			SymbolFactory::createSymbol("lrafffres", SymbolFactory::Symbol_t::const_str_t),
			Expression::ExpressionType::Power));
	}

	SECTION("Check composites with brackets") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("(sin(x + y) ^ lrafffres) * ln(5+6*x)", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol(SymbolFactory::createExpression(SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), SymbolFactory::createSymbol("y", SymbolFactory::Symbol_t::const_str_t), Expression::ExpressionType::Addition),
					FunctionSymbol::FunctionType::Sin), SymbolFactory::createSymbol("lrafffres", SymbolFactory::Symbol_t::const_str_t), Expression::ExpressionType::Power),
			SymbolFactory::createSymbol(
				SymbolFactory::createExpression(SymbolFactory::createSymbol("5",SymbolFactory::Symbol_t::const_t), 
					SymbolFactory::createExpression(SymbolFactory::createSymbol("6", SymbolFactory::Symbol_t::const_t),SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), Expression::ExpressionType::Product),
					Expression::ExpressionType::Addition),
				FunctionSymbol::FunctionType::NaturalLogarithm),
			Expression::ExpressionType::Product));
	}

}

TEST_CASE("Parser operators testing", "[Parse]") {

	SECTION("Check plus operator in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("3+x", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '+'));
	}

	SECTION("Check minus operator in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("3-x", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t)
			, SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '-'));
	}

	SECTION("Check product operator in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("3*x", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t)
			, SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '*'));
	}

	SECTION("Check divide operator in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("3/x", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t)
			, SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '/'));
	}

	SECTION("Check XOR operator in simple expression") {
		std::shared_ptr<Symbol> single_operator = Parser::Parse("3^x", { "x" });
		REQUIRE(single_operator == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t)
			, SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '^'));
	}

}

TEST_CASE("Parser priority testing", "[Parse]") {

	// +,- the hightest priority
	// ^ - low priority
	// *,/ - hight priority
	// func nodes - the lowest priority

	// position of operator - the lowest priority

	SECTION("Check plus & product priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3*x+lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '*'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '+'));
	}

	SECTION("Check plus & divide priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3/x+lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '/'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '+'));
	}

	SECTION("Check plus & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3^x+lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '^'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '+'));
	}

	SECTION("Check minus & product priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3*x-lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '*'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '-'));
	}

	SECTION("Check minus & divide priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3/x-lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '/'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '-'));
	}

	SECTION("Check minus & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3^x-lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '^'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '-'));
	}

	SECTION("Check product & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3*x^lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '^'),
			 '*'));
	}

	SECTION("Check divide & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3/x^lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t),
				SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '^'),
			'/'));
	}

	SECTION("Check all priorities") {
		std::shared_ptr<Symbol> priority = Parser::Parse("3/4^5+7*lor-x", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createExpression(SymbolFactory::createSymbol("4", SymbolFactory::Symbol_t::const_t)
					, SymbolFactory::createSymbol("5", SymbolFactory::Symbol_t::const_t),'^'),
				 '/'),
			SymbolFactory::createExpression(
				SymbolFactory::createExpression(SymbolFactory::createSymbol("7", SymbolFactory::Symbol_t::const_t),
					SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t),'*'),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '-'),
			'+'));
	}
}

TEST_CASE("Parser priority testing with brackets", "[Parse]") {
	
	// amount of brackets - the highest priority (less brackets - higher priority)

	// +,- the hightest priority
	// ^ - low priority
	// *,/ - hight priority
	// func nodes - the lowest priority

	// position of operator - the lowest priority

	SECTION("Check plus & product priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3+x)*lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '+'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '*'));
	}

	SECTION("Check plus & divide priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3+x)/lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '+'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '/'));
	}

	SECTION("Check plus & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3+x)^lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '+'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '^'));
	}

	SECTION("Check minus & product priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3-x)*lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '-'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '*'));
	}

	SECTION("Check minus & divide priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3-x)/lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '-'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '/'));
	}

	SECTION("Check minus & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3-x)^lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '-'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '^'));
	}

	SECTION("Check divide & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3^x)/lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '^'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '/'));
	}

	SECTION("Check product & XOR priority") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3^x)*lor", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol("3", SymbolFactory::Symbol_t::const_t),
				SymbolFactory::createSymbol("x", SymbolFactory::Symbol_t::arg_t), '^'),
			SymbolFactory::createSymbol("lor", SymbolFactory::Symbol_t::const_str_t), '*'));
	}

	SECTION("Check all priorities") {
		std::shared_ptr<Symbol> priority = Parser::Parse("(3/((4^lor)+7))*((8-x)^9)", { "x" });
		REQUIRE(priority == SymbolFactory::createExpression(
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol(
					"3", SymbolFactory::Symbol_t::const_t
				),
				SymbolFactory::createExpression(
					SymbolFactory::createExpression(
						SymbolFactory::createSymbol(
							"4", SymbolFactory::Symbol_t::const_t
						),
						SymbolFactory::createSymbol(
							"lor", SymbolFactory::Symbol_t::const_str_t
						),
						'^'
					),
					SymbolFactory::createSymbol(
						"7", SymbolFactory::Symbol_t::const_t
					),
					'+'
				),
				'/'
			),
			SymbolFactory::createExpression(
				SymbolFactory::createExpression(
					SymbolFactory::createSymbol(
						"8", SymbolFactory::Symbol_t::const_t
					),
					SymbolFactory::createSymbol(
						"x", SymbolFactory::Symbol_t::arg_t
					),
					'-'
					),
				SymbolFactory::createSymbol(
					"9", SymbolFactory::Symbol_t::const_t
				),
				'^'
			),
			'*'
		));
			
	}

}

TEST_CASE("unary operation")
{

	SECTION("first operator - *")
	{
		REQUIRE_THROWS(Parser::Parse("*+3"));
	}

	SECTION("first operator - /")
	{
		REQUIRE_THROWS(Parser::Parse("/+3"));
	}

	SECTION("first operator - ^")
	{
		REQUIRE_THROWS(Parser::Parse("^+3"));
	}

	SECTION("the pair of operators *^")
	{
		REQUIRE_THROWS(Parser::Parse("4+^*3"));
		REQUIRE_THROWS(Parser::Parse("4+*^3"));
	}

	SECTION("the pair of operators /*")
	{
		REQUIRE_THROWS(Parser::Parse("4+/*3"));
		REQUIRE_THROWS(Parser::Parse("4+*/3"));
	}

	SECTION("the pair of operators /^")
	{
		REQUIRE_THROWS(Parser::Parse("4+/^3"));
		REQUIRE_THROWS(Parser::Parse("4+^/3"));
	}


	SECTION("unary minus") {
		auto symb = Parser::Parse("-3");
		REQUIRE(SymbolFactory::createExpression(
			SymbolFactory::createSymbol(0),
			SymbolFactory::createSymbol(3),
				Expression::ExpressionType::Difference));
	}

	SECTION("unary plus") {
		auto symb = Parser::Parse("+3");
		REQUIRE(SymbolFactory::createExpression(
			SymbolFactory::createSymbol(0),
			SymbolFactory::createSymbol(3),
			Expression::ExpressionType::Addition));
	}

	SECTION("const + + const")
	{
		auto symb = Parser::Parse("3++3");
		REQUIRE(SymbolFactory::createExpression(SymbolFactory::createSymbol(3),
			SymbolFactory::createExpression(
			SymbolFactory::createSymbol(0),
			SymbolFactory::createSymbol(3),
			Expression::ExpressionType::Addition),
			Expression::ExpressionType::Addition));
	}

	SECTION("const + - const")
	{
		auto symb = Parser::Parse("3+-3");
		REQUIRE(SymbolFactory::createExpression(SymbolFactory::createSymbol(3),
			SymbolFactory::createExpression(
				SymbolFactory::createSymbol(0),
				SymbolFactory::createSymbol(3),
				Expression::ExpressionType::Difference),
			Expression::ExpressionType::Addition));
	}
}

TEST_CASE("Parsing validation") {

	SECTION("Parsing double")
	{
		auto expr = Parser::Parse("3.14");
		REQUIRE(Computer::Compute(expr).GetValue() - Computer::Compute(SymbolFactory::createSymbol(3.14)).GetValue() < 0.00001);
	}

	SECTION("Parsing double with 2 dots")
	{
		auto expr = Parser::Parse("3.14.");
		REQUIRE(expr == SymbolFactory::createSymbol("3.14.", SymbolFactory::Symbol_t::const_str_t));
	}
}

