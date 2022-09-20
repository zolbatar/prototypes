#include <iostream>
#include "Grammar/DorkParser.h"
#include "../Exception/DorkException.h"

class DorkErrorListener : public antlr4::BaseErrorListener
{
	void syntaxError(antlr4::Recognizer* recognizer,
		antlr4::Token* offendingSymbol,
		size_t line,
		size_t charPositionInLine,
		const std::string& msg,
		std::exception_ptr e) override
	{
		throw DorkException(ExceptionType::PARSER, line, charPositionInLine, msg);
	}
};
