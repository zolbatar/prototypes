#include "Compiler.h"

std::any Compiler::visitExpr(DorkParser::ExprContext* context)
{
	auto o = std::any_cast<Object>(visitChildren(context));
	return o;
}
