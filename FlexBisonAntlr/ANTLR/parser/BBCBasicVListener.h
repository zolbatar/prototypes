
// Generated from BBCBasicV.g by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "BBCBasicVParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by BBCBasicVParser.
 */
class  BBCBasicVListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(BBCBasicVParser::ProgContext *ctx) = 0;
  virtual void exitProg(BBCBasicVParser::ProgContext *ctx) = 0;

  virtual void enterLine(BBCBasicVParser::LineContext *ctx) = 0;
  virtual void exitLine(BBCBasicVParser::LineContext *ctx) = 0;

  virtual void enterLinenumber(BBCBasicVParser::LinenumberContext *ctx) = 0;
  virtual void exitLinenumber(BBCBasicVParser::LinenumberContext *ctx) = 0;

  virtual void enterAmperoper(BBCBasicVParser::AmperoperContext *ctx) = 0;
  virtual void exitAmperoper(BBCBasicVParser::AmperoperContext *ctx) = 0;

  virtual void enterAmprstmt(BBCBasicVParser::AmprstmtContext *ctx) = 0;
  virtual void exitAmprstmt(BBCBasicVParser::AmprstmtContext *ctx) = 0;

  virtual void enterStatement(BBCBasicVParser::StatementContext *ctx) = 0;
  virtual void exitStatement(BBCBasicVParser::StatementContext *ctx) = 0;

  virtual void enterVardecl(BBCBasicVParser::VardeclContext *ctx) = 0;
  virtual void exitVardecl(BBCBasicVParser::VardeclContext *ctx) = 0;

  virtual void enterRelop(BBCBasicVParser::RelopContext *ctx) = 0;
  virtual void exitRelop(BBCBasicVParser::RelopContext *ctx) = 0;

  virtual void enterNeq(BBCBasicVParser::NeqContext *ctx) = 0;
  virtual void exitNeq(BBCBasicVParser::NeqContext *ctx) = 0;

  virtual void enterIfstmt(BBCBasicVParser::IfstmtContext *ctx) = 0;
  virtual void exitIfstmt(BBCBasicVParser::IfstmtContext *ctx) = 0;

  virtual void enterEndstmt(BBCBasicVParser::EndstmtContext *ctx) = 0;
  virtual void exitEndstmt(BBCBasicVParser::EndstmtContext *ctx) = 0;

  virtual void enterReturnstmt(BBCBasicVParser::ReturnstmtContext *ctx) = 0;
  virtual void exitReturnstmt(BBCBasicVParser::ReturnstmtContext *ctx) = 0;

  virtual void enterNumber(BBCBasicVParser::NumberContext *ctx) = 0;
  virtual void exitNumber(BBCBasicVParser::NumberContext *ctx) = 0;

  virtual void enterFunc(BBCBasicVParser::FuncContext *ctx) = 0;
  virtual void exitFunc(BBCBasicVParser::FuncContext *ctx) = 0;

  virtual void enterVar(BBCBasicVParser::VarContext *ctx) = 0;
  virtual void exitVar(BBCBasicVParser::VarContext *ctx) = 0;

  virtual void enterVarname(BBCBasicVParser::VarnameContext *ctx) = 0;
  virtual void exitVarname(BBCBasicVParser::VarnameContext *ctx) = 0;

  virtual void enterVarsuffix(BBCBasicVParser::VarsuffixContext *ctx) = 0;
  virtual void exitVarsuffix(BBCBasicVParser::VarsuffixContext *ctx) = 0;

  virtual void enterVarlist(BBCBasicVParser::VarlistContext *ctx) = 0;
  virtual void exitVarlist(BBCBasicVParser::VarlistContext *ctx) = 0;

  virtual void enterExprlist(BBCBasicVParser::ExprlistContext *ctx) = 0;
  virtual void exitExprlist(BBCBasicVParser::ExprlistContext *ctx) = 0;

  virtual void enterExpression(BBCBasicVParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(BBCBasicVParser::ExpressionContext *ctx) = 0;

  virtual void enterSignExpression(BBCBasicVParser::SignExpressionContext *ctx) = 0;
  virtual void exitSignExpression(BBCBasicVParser::SignExpressionContext *ctx) = 0;

  virtual void enterExponentExpression(BBCBasicVParser::ExponentExpressionContext *ctx) = 0;
  virtual void exitExponentExpression(BBCBasicVParser::ExponentExpressionContext *ctx) = 0;

  virtual void enterMultiplyingExpression(BBCBasicVParser::MultiplyingExpressionContext *ctx) = 0;
  virtual void exitMultiplyingExpression(BBCBasicVParser::MultiplyingExpressionContext *ctx) = 0;

  virtual void enterAddingExpression(BBCBasicVParser::AddingExpressionContext *ctx) = 0;
  virtual void exitAddingExpression(BBCBasicVParser::AddingExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(BBCBasicVParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(BBCBasicVParser::RelationalExpressionContext *ctx) = 0;


};

