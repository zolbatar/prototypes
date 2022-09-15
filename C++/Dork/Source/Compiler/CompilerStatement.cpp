#include "Compiler.h"

std::any Compiler::visitStatement(DorkParser::StatementContext* context)
{
	return visitChildren(context);
}
