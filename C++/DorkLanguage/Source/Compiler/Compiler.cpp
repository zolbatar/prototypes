#include <chrono>
#include <stdexcept>
#include "Compiler.h"

Compiler::Compiler(std::istream* file)
{
	auto t1 = std::chrono::steady_clock::now();
	try
	{
		// Call Antlr4 and parse
		antlr4::ANTLRInputStream input(*file);
		DorkLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		DorkParser parser(&tokens);
		parser.removeErrorListeners();
		DorkErrorListener errorListener;
		parser.addErrorListener(&errorListener);
		parser.setBuildParseTree(true);
		parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);
		DorkParser::ProgContext* tree = parser.prog();

		// Set mode to be IMMEDIATE
		mode = CompileMode::Immediate;
		imm_method = new Method(BytecodeType::Unknown);

		// Parse and compile
		visitProg(tree);

		// Run!
		imm_method->Run();
	}
	catch (DorkException& ex)
	{
		ex.OutputToStdout();
		return;
	}
	catch (std::exception& ex)
	{
		std::cout << "Exception: " << ex.what() << std::endl;
		return;
	}
	auto t2 = std::chrono::steady_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	std::stringstream ss2;
	ss2 << "Compilation time was " << std::to_string(time_span.count()) << "ms\n";
}