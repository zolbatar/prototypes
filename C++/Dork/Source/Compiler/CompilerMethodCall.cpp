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

	// Right type?
	if (method->GetType() != BytecodeType::Unary)
	{
		ParserException("Method '" + m + "' mismatch of parameters", context);
	}

	return Bytecode{ method->GetType(), method->GetFunc(), std::vector<void*>({ o }) };
}
