#include "Compiler.h"

std::any Compiler::visitStatement(DorkParser::StatementContext* context)
{
	auto s = std::any_cast<Bytecode>(visitChildren(context));
	switch (mode)
	{
		case CompileMode::Immediate:
			imm_method->AddCode(std::move(s));
			break;
		default:
			assert(0);
	}
	return NULL;
}
