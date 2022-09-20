#include "Compiler.h"

std::any Compiler::visitStatementAssign(DorkParser::StatementAssignContext* context)
{
	return visitChildren(context);
}
