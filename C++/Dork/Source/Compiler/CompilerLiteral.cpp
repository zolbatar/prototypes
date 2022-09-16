#include "Compiler.h"

std::any Compiler::visitLiteral(DorkParser::LiteralContext* context)
{
	return visitChildren(context);
}

std::any Compiler::visitIntegerLiteral(DorkParser::IntegerLiteralContext* context)
{
	int64_t i = 0;
	if (context->INTEGERLITERAL() != nullptr)
	{
		auto v = context->INTEGERLITERAL()->getText();

		try
		{
			i = std::stoi(v, nullptr, 10);
		}
		catch (const std::invalid_argument&)
		{
			ParserException("Invalid number", context);
		}
		if (context->MINUS() != nullptr)
		{
			i = -i;
		}
	}
	else if (context->HEXNUMBER() != nullptr)
	{
		auto v = context->HEXNUMBER()->getText();
		v.erase(0, 1);
		try
		{
			i = std::stoi(v, nullptr, 16);
		}
		catch (const std::invalid_argument&)
		{
			ParserException("Invalid number", context);
		}
	}
	else if (context->BINARYNUMBER() != nullptr)
	{
		auto v = context->BINARYNUMBER()->getText();
		v.erase(0, 1);
		try
		{
			i = std::stoi(v, nullptr, 2);
		}
		catch (const std::invalid_argument&)
		{
			ParserException("Invalid number", context);
		}
	}
	return vm.Integer("", scope, i);
}

std::any Compiler::visitFloatLiteral(DorkParser::FloatLiteralContext* context)
{
	auto v = context->FLOATLITERAL()->getText();
	double f;
	try
	{
		f = std::stod(v);
	}
	catch (const std::invalid_argument&)
	{
		ParserException("Invalid number", context);
	}
	if (context->MINUS() != nullptr)
	{
		f = -f;
	}
	return vm.Float("", scope, f);
}

std::any Compiler::visitStringLiteral(DorkParser::StringLiteralContext* context)
{
	return visitChildren(context);
}
