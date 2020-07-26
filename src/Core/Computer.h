#pragma once 
#include "ComputeUtils.h"
#include "Symbol.h"

class Computer
{
public:
	static ComputeResult Compute(std::shared_ptr<Symbol>  target, ComputeContext & context);
	static ComputeResult Compute(std::shared_ptr<Symbol>  target);
};