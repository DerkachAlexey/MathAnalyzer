#include "Computer.h"
#include "ComputeVisitor.h"

ComputeResult Computer::Compute(std::shared_ptr<Symbol>  target, ComputeContext & context)
{
	ComputeVisitor vis(context);
	target->Accept(&vis);
	return vis.getResult();
}

ComputeResult Computer::Compute(std::shared_ptr<Symbol>  target)
{
	ComputeContext context;
	return Compute(target, context);
}
