
// Generated from Dork.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "DorkVisitor.h"


/**
 * This class provides an empty implementation of DorkVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  DorkBaseVisitor : public DorkVisitor {
public:

  virtual std::any visitProg(DorkParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(DorkParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementAssign(DorkParser::StatementAssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementUnary(DorkParser::StatementUnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(DorkParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(DorkParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntegerLiteral(DorkParser::IntegerLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatLiteral(DorkParser::FloatLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteral(DorkParser::StringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

