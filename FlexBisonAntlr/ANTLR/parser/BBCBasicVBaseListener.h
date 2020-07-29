
// Generated from BBCBasicV.g by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "BBCBasicVListener.h"


/**
 * This class provides an empty implementation of BBCBasicVListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  BBCBasicVBaseListener : public BBCBasicVListener {
public:

  virtual void enterProg(BBCBasicVParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(BBCBasicVParser::ProgContext * /*ctx*/) override { }

  virtual void enterLine(BBCBasicVParser::LineContext * /*ctx*/) override { }
  virtual void exitLine(BBCBasicVParser::LineContext * /*ctx*/) override { }

  virtual void enterLinenumber(BBCBasicVParser::LinenumberContext * /*ctx*/) override { }
  virtual void exitLinenumber(BBCBasicVParser::LinenumberContext * /*ctx*/) override { }

  virtual void enterAmperoper(BBCBasicVParser::AmperoperContext * /*ctx*/) override { }
  virtual void exitAmperoper(BBCBasicVParser::AmperoperContext * /*ctx*/) override { }

  virtual void enterAmprstmt(BBCBasicVParser::AmprstmtContext * /*ctx*/) override { }
  virtual void exitAmprstmt(BBCBasicVParser::AmprstmtContext * /*ctx*/) override { }

  virtual void enterStatement(BBCBasicVParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(BBCBasicVParser::StatementContext * /*ctx*/) override { }

  virtual void enterVardecl(BBCBasicVParser::VardeclContext * /*ctx*/) override { }
  virtual void exitVardecl(BBCBasicVParser::VardeclContext * /*ctx*/) override { }

  virtual void enterRelop(BBCBasicVParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(BBCBasicVParser::RelopContext * /*ctx*/) override { }

  virtual void enterNeq(BBCBasicVParser::NeqContext * /*ctx*/) override { }
  virtual void exitNeq(BBCBasicVParser::NeqContext * /*ctx*/) override { }

  virtual void enterIfstmt(BBCBasicVParser::IfstmtContext * /*ctx*/) override { }
  virtual void exitIfstmt(BBCBasicVParser::IfstmtContext * /*ctx*/) override { }

  virtual void enterEndstmt(BBCBasicVParser::EndstmtContext * /*ctx*/) override { }
  virtual void exitEndstmt(BBCBasicVParser::EndstmtContext * /*ctx*/) override { }

  virtual void enterReturnstmt(BBCBasicVParser::ReturnstmtContext * /*ctx*/) override { }
  virtual void exitReturnstmt(BBCBasicVParser::ReturnstmtContext * /*ctx*/) override { }

  virtual void enterNumber(BBCBasicVParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(BBCBasicVParser::NumberContext * /*ctx*/) override { }

  virtual void enterFunc(BBCBasicVParser::FuncContext * /*ctx*/) override { }
  virtual void exitFunc(BBCBasicVParser::FuncContext * /*ctx*/) override { }

  virtual void enterVar(BBCBasicVParser::VarContext * /*ctx*/) override { }
  virtual void exitVar(BBCBasicVParser::VarContext * /*ctx*/) override { }

  virtual void enterVarname(BBCBasicVParser::VarnameContext * /*ctx*/) override { }
  virtual void exitVarname(BBCBasicVParser::VarnameContext * /*ctx*/) override { }

  virtual void enterVarsuffix(BBCBasicVParser::VarsuffixContext * /*ctx*/) override { }
  virtual void exitVarsuffix(BBCBasicVParser::VarsuffixContext * /*ctx*/) override { }

  virtual void enterVarlist(BBCBasicVParser::VarlistContext * /*ctx*/) override { }
  virtual void exitVarlist(BBCBasicVParser::VarlistContext * /*ctx*/) override { }

  virtual void enterExprlist(BBCBasicVParser::ExprlistContext * /*ctx*/) override { }
  virtual void exitExprlist(BBCBasicVParser::ExprlistContext * /*ctx*/) override { }

  virtual void enterExpression(BBCBasicVParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(BBCBasicVParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterSignExpression(BBCBasicVParser::SignExpressionContext * /*ctx*/) override { }
  virtual void exitSignExpression(BBCBasicVParser::SignExpressionContext * /*ctx*/) override { }

  virtual void enterExponentExpression(BBCBasicVParser::ExponentExpressionContext * /*ctx*/) override { }
  virtual void exitExponentExpression(BBCBasicVParser::ExponentExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplyingExpression(BBCBasicVParser::MultiplyingExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplyingExpression(BBCBasicVParser::MultiplyingExpressionContext * /*ctx*/) override { }

  virtual void enterAddingExpression(BBCBasicVParser::AddingExpressionContext * /*ctx*/) override { }
  virtual void exitAddingExpression(BBCBasicVParser::AddingExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(BBCBasicVParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(BBCBasicVParser::RelationalExpressionContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

