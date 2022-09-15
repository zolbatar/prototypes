
// Generated from Dork.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "DorkParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by DorkParser.
 */
class  DorkVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by DorkParser.
   */
    virtual std::any visitProg(DorkParser::ProgContext *context) = 0;

    virtual std::any visitStatement(DorkParser::StatementContext *context) = 0;

    virtual std::any visitStatementAssign(DorkParser::StatementAssignContext *context) = 0;

    virtual std::any visitStatementMethodCall(DorkParser::StatementMethodCallContext *context) = 0;

    virtual std::any visitExpr(DorkParser::ExprContext *context) = 0;

    virtual std::any visitLiteral(DorkParser::LiteralContext *context) = 0;

    virtual std::any visitIntegerLiteral(DorkParser::IntegerLiteralContext *context) = 0;

    virtual std::any visitFloatLiteral(DorkParser::FloatLiteralContext *context) = 0;

    virtual std::any visitStringLiteral(DorkParser::StringLiteralContext *context) = 0;


};

