#include "Compiler.h"

std::any Compiler::visitProg(DorkParser::ProgContext* context)
{
	return visitChildren(context);
}
