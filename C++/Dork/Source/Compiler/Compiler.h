#pragma once

#include <vector>
#include <map>
#include <istream>
#include "Grammar/DorkVisitor.h"
#include "Grammar/DorkLexer.h"
#include "Grammar/DorkParser.h"
#include "CompilerErrorListener.h"
#include "../VM/VM.h"

class Compiler : DorkVisitor
{
 public:
	Compiler(std::istream* file);

 private:
	void ParserException(std::string msg, antlr4::ParserRuleContext* context)
	{
		throw DorkException(ExceptionType::PARSER, context->start->getLine(), context->start->getCharPositionInLine(), msg);
	}

	Scope scope = Scope::Global;

 protected:
	std::any visitProg(DorkParser::ProgContext* context);
	std::any visitStatement(DorkParser::StatementContext* context);
	std::any visitStatementAssign(DorkParser::StatementAssignContext* context);
	std::any visitStatementMethodCallUnary(DorkParser::StatementMethodCallUnaryContext* context);
	std::any visitExpr(DorkParser::ExprContext* context);
	std::any visitLiteral(DorkParser::LiteralContext* context);
	std::any visitIntegerLiteral(DorkParser::IntegerLiteralContext* context);
	std::any visitFloatLiteral(DorkParser::FloatLiteralContext* context);
	std::any visitStringLiteral(DorkParser::StringLiteralContext* context);
};
