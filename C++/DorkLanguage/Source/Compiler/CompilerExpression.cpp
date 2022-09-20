#include "Compiler.h"

std::any Compiler::visitExpr(DorkParser::ExprContext* context)
{
	// Literals
	if (context->literal() != NULL)
	{
		std::any_cast<Instance*>(visitChildren(context));
	}

	// Unary
	if (context->IDENTIFIER() != NULL)
	{
		auto o = std::any_cast<Instance*>(visitChildren(context));;
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

		AddCode(Bytecode{ method->GetType(), method->GetFunc(), std::vector<void*>({ o }) });
	}

	// Binary
	if (context->BINARY() != NULL)
	{
		assert(0);
	}

	return NULL;
}
