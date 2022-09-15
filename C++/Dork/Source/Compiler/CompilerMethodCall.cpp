#include "Compiler.h"

std::any Compiler::visitStatementMethodCall(DorkParser::StatementMethodCallContext* context)
{
	return visitChildren(context);
}
