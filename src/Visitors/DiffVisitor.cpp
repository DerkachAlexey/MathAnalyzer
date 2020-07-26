#include "DiffVisitor.h"
#include <stdexcept>
#include "PowerExpression.h"
#include "Constant.h"
#include "ProductExpression.h"
#include "AdditionExpression.h"
#include "DifferenceExpression.h"
#include "DivideExpression.h"
#include "FunctionSymbol.h"
#include "ArgumentSymbol.h"
#include "Computer.h"
#include "SymbolFactory.h"



DiffVisitor::DiffVisitor(std::string const & argument):
	argument(argument)
{

}

void DiffVisitor::Visit(std::shared_ptr<PowerSymbol> s)
{
	

	if (auto powConstant = std::dynamic_pointer_cast<Constant>(s->getRight()))
	{
		if (std::stod(powConstant->getValue()) - 1 == 0)
		{
			result = SymbolFactory::createSymbol("1", SymbolFactory::Symbol_t::const_t);
			return;
		}
		else
		{
			DiffVisitor leftVis(argument);
			s->getLeft()->Accept(&leftVis);

			result = SymbolFactory::createExpression(
				SymbolFactory::createExpression(
					SymbolFactory::createSymbol((std::stod(powConstant->getValue()))),

					SymbolFactory::createExpression(
						s->getLeft()->Clone(),
						SymbolFactory::createSymbol((std::stod(powConstant->getValue()) - 1)),
						expr_t::Power
					)
					,
					expr_t::Product
				),
				leftVis.getResult(),
				expr_t::Product
			);
			return;
		}
	}

	DiffVisitor leftVis(argument);
	s->getLeft()->Accept(&leftVis);
	DiffVisitor rightVis(argument);
	s->getRight()->Accept(&rightVis);

	result = SymbolFactory::createExpression( 
			SymbolFactory::createExpression( s->getRight()->Clone(), 
						SymbolFactory::createExpression(
							leftVis.getResult(), 
								SymbolFactory::createExpression(
									s->getLeft()->Clone(),
										SymbolFactory::createExpression(
											s->getRight()->Clone(),
											SymbolFactory::createSymbol("1", SymbolFactory::Symbol_t::const_t),
										expr_t::Difference)
									,
								expr_t::Power),
						expr_t::Product),
					expr_t::Product), 
				SymbolFactory::createExpression( 
					SymbolFactory::createExpression(
						s->Clone(),
						SymbolFactory::createSymbol(s->getLeft()->Clone(), FunctionSymbol::FunctionType::NaturalLogarithm),
					expr_t::Product), 
					rightVis.getResult(), 
				expr_t::Product),
			expr_t::Addition);
}

void DiffVisitor::Visit(std::shared_ptr < Constant> )
{
	result = SymbolFactory::createSymbol(0);
}

void DiffVisitor::Visit(std::shared_ptr < ProductExpression > s)
{
	DiffVisitor rightDiff = DiffVisitor(argument);
	s->getRight()->Accept(&rightDiff);
	DiffVisitor leftDiff = DiffVisitor(argument);
	s->getLeft()->Accept(&leftDiff);
	result = std::make_shared < AdditionExpression>(
		std::make_shared < ProductExpression>(rightDiff.getResult(), s->getLeft()),
		std::make_shared < ProductExpression>(leftDiff.getResult(), s->getRight())
		);
}

void DiffVisitor::Visit(std::shared_ptr < AdditionExpression > s)
{
	DiffVisitor rightDiff = DiffVisitor(argument);
	s->getRight()->Accept(&rightDiff);
	DiffVisitor leftDiff = DiffVisitor(argument);
	s->getLeft()->Accept(&leftDiff);
	result = std::make_shared < AdditionExpression>(leftDiff.getResult(), rightDiff.getResult());
}

void DiffVisitor::Visit(std::shared_ptr < DifferenceExpression> s)
{
	DiffVisitor rightDiff = DiffVisitor(argument);
	s->getRight()->Accept(&rightDiff);
	DiffVisitor leftDiff = DiffVisitor(argument);
	s->getLeft()->Accept(&leftDiff);
	result = std::make_shared < DifferenceExpression>(leftDiff.getResult(), rightDiff.getResult());
}

void DiffVisitor::Visit(std::shared_ptr < DivideExpression > s)
{
	DiffVisitor rightDiff = DiffVisitor(argument);
	s->getRight()->Accept(&rightDiff);
	DiffVisitor leftDiff = DiffVisitor(argument);
	s->getLeft()->Accept(&leftDiff);
	std::shared_ptr<DifferenceExpression> numerator =
		std::make_shared < DifferenceExpression>(
			std::make_shared <ProductExpression>(leftDiff.getResult()->Clone(), s->getRight()->Clone()),
			std::make_shared <ProductExpression>(s->getLeft()->Clone(), rightDiff.getResult()->Clone())
		);
	std::shared_ptr<ProductExpression> divider = std::make_shared < ProductExpression>(s->getRight()->Clone(), s->getRight()->Clone()
	);

	result = std::make_shared < DivideExpression>(numerator, divider);
}



void DiffVisitor::Visit(std::shared_ptr<ArgumentSymbol> s)
{
	
	result = s->getValue() == argument ? SymbolFactory::createSymbol("1", SymbolFactory::Symbol_t::const_t):
										SymbolFactory::createSymbol("0", SymbolFactory::Symbol_t::const_t);
	
}

void DiffVisitor::Visit(std::shared_ptr<FunctionSymbol> s)
{
switch (s->getFunctionType())
	{
	case FunctionSymbol::FunctionType::NaturalLogarithm:
		diffNaturalLog(s);
		break;
	case FunctionSymbol::FunctionType::Cos:
		diffCos(s);
		break;
	case FunctionSymbol::FunctionType::Sin:
		diffSin(s);
		break;
	default:
		break;
	}
}

void DiffVisitor::Visit(std::shared_ptr<StringConstant> s)
{
	result = SymbolFactory::createSymbol(1);
}
	
void DiffVisitor::diffNaturalLog(std::shared_ptr<FunctionSymbol> s)
{

	DiffVisitor log_expression(argument);
	s->getExpression()->Accept(&log_expression);
	result = SymbolFactory::createExpression(SymbolFactory::createExpression(SymbolFactory::createSymbol("1", SymbolFactory::Symbol_t::const_t),
		s->getExpression()->Clone(), expr_t::Division),
		log_expression.getResult(),
		expr_t::Product);

}

void DiffVisitor::diffCos(std::shared_ptr<FunctionSymbol> s)
{
	DiffVisitor cos_expr(argument);
	s->getExpression()->Accept(&cos_expr);

	result = SymbolFactory::createExpression(
		cos_expr.getResult(),
		SymbolFactory::createExpression(
			SymbolFactory::createSymbol("0", SymbolFactory::Symbol_t::const_t),
			SymbolFactory::createSymbol(s->getExpression()->Clone(), FunctionSymbol::FunctionType::Sin),
			expr_t::Difference
		),
		expr_t::Product);
}

void DiffVisitor::diffSin(std::shared_ptr<FunctionSymbol> s)
{
	DiffVisitor sin_expr(argument);
	s->getExpression()->Accept(&sin_expr);

	result = SymbolFactory::createExpression(
		sin_expr.getResult(),
			SymbolFactory::createSymbol(s->getExpression()->Clone(), FunctionSymbol::FunctionType::Cos),
		 expr_t::Product);
}

