#include "Compiler.h"

std::any Compiler::visitExpr(DorkParser::ExprContext* context)
{
	auto o = std::any_cast<Class>(visitChildren(context));
	return o;
}
