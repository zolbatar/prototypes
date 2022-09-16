#include "Compiler.h"

std::any Compiler::visitStatementMethodCallUnary(DorkParser::StatementMethodCallUnaryContext* context)
{
	auto o = std::any_cast<Instance*>(visit(context->expr()));
	auto m = context->IDENTIFIER()->getText();
	auto method = o->GetClass()->GetMethod(m);

	// Not subclassed?
	if (method->NotImplemented())
	{
		ParserException("Method '" + m + "' not implemented", context);
	}

	return NULL;
}
