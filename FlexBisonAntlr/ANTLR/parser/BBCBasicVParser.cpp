
// Generated from BBCBasicV.g by ANTLR 4.7.2


#include "BBCBasicVListener.h"

#include "BBCBasicVParser.h"


using namespace antlrcpp;
using namespace antlr4;

BBCBasicVParser::BBCBasicVParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

BBCBasicVParser::~BBCBasicVParser() {
  delete _interpreter;
}

std::string BBCBasicVParser::getGrammarFileName() const {
  return "BBCBasicV.g";
}

const std::vector<std::string>& BBCBasicVParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& BBCBasicVParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

BBCBasicVParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::ProgContext::EOF() {
  return getToken(BBCBasicVParser::EOF, 0);
}

std::vector<BBCBasicVParser::LineContext *> BBCBasicVParser::ProgContext::line() {
  return getRuleContexts<BBCBasicVParser::LineContext>();
}

BBCBasicVParser::LineContext* BBCBasicVParser::ProgContext::line(size_t i) {
  return getRuleContext<BBCBasicVParser::LineContext>(i);
}


size_t BBCBasicVParser::ProgContext::getRuleIndex() const {
  return BBCBasicVParser::RuleProg;
}

void BBCBasicVParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void BBCBasicVParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}

BBCBasicVParser::ProgContext* BBCBasicVParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, BBCBasicVParser::RuleProg);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(51); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(50);
      line();
      setState(53); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == BBCBasicVParser::NUMBER);
    setState(55);
    match(BBCBasicVParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LineContext ------------------------------------------------------------------

BBCBasicVParser::LineContext::LineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BBCBasicVParser::LinenumberContext* BBCBasicVParser::LineContext::linenumber() {
  return getRuleContext<BBCBasicVParser::LinenumberContext>(0);
}

tree::TerminalNode* BBCBasicVParser::LineContext::COMMENT() {
  return getToken(BBCBasicVParser::COMMENT, 0);
}

tree::TerminalNode* BBCBasicVParser::LineContext::REM() {
  return getToken(BBCBasicVParser::REM, 0);
}

std::vector<BBCBasicVParser::AmprstmtContext *> BBCBasicVParser::LineContext::amprstmt() {
  return getRuleContexts<BBCBasicVParser::AmprstmtContext>();
}

BBCBasicVParser::AmprstmtContext* BBCBasicVParser::LineContext::amprstmt(size_t i) {
  return getRuleContext<BBCBasicVParser::AmprstmtContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::LineContext::COLON() {
  return getTokens(BBCBasicVParser::COLON);
}

tree::TerminalNode* BBCBasicVParser::LineContext::COLON(size_t i) {
  return getToken(BBCBasicVParser::COLON, i);
}


size_t BBCBasicVParser::LineContext::getRuleIndex() const {
  return BBCBasicVParser::RuleLine;
}

void BBCBasicVParser::LineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLine(this);
}

void BBCBasicVParser::LineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLine(this);
}

BBCBasicVParser::LineContext* BBCBasicVParser::line() {
  LineContext *_localctx = _tracker.createInstance<LineContext>(_ctx, getState());
  enterRule(_localctx, 2, BBCBasicVParser::RuleLine);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    linenumber();
    setState(69);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(58);
      amprstmt();
      setState(65);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BBCBasicVParser::COLON) {
        setState(59);
        match(BBCBasicVParser::COLON);
        setState(61);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << BBCBasicVParser::AMPERSAND)
          | (1ULL << BBCBasicVParser::IF)
          | (1ULL << BBCBasicVParser::REM)
          | (1ULL << BBCBasicVParser::END)
          | (1ULL << BBCBasicVParser::RETURN)
          | (1ULL << BBCBasicVParser::COMMENT))) != 0)) {
          setState(60);
          amprstmt();
        }
        setState(67);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      setState(68);
      _la = _input->LA(1);
      if (!(_la == BBCBasicVParser::REM

      || _la == BBCBasicVParser::COMMENT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LinenumberContext ------------------------------------------------------------------

BBCBasicVParser::LinenumberContext::LinenumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::LinenumberContext::NUMBER() {
  return getToken(BBCBasicVParser::NUMBER, 0);
}


size_t BBCBasicVParser::LinenumberContext::getRuleIndex() const {
  return BBCBasicVParser::RuleLinenumber;
}

void BBCBasicVParser::LinenumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLinenumber(this);
}

void BBCBasicVParser::LinenumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLinenumber(this);
}

BBCBasicVParser::LinenumberContext* BBCBasicVParser::linenumber() {
  LinenumberContext *_localctx = _tracker.createInstance<LinenumberContext>(_ctx, getState());
  enterRule(_localctx, 4, BBCBasicVParser::RuleLinenumber);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(BBCBasicVParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AmperoperContext ------------------------------------------------------------------

BBCBasicVParser::AmperoperContext::AmperoperContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::AmperoperContext::AMPERSAND() {
  return getToken(BBCBasicVParser::AMPERSAND, 0);
}


size_t BBCBasicVParser::AmperoperContext::getRuleIndex() const {
  return BBCBasicVParser::RuleAmperoper;
}

void BBCBasicVParser::AmperoperContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAmperoper(this);
}

void BBCBasicVParser::AmperoperContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAmperoper(this);
}

BBCBasicVParser::AmperoperContext* BBCBasicVParser::amperoper() {
  AmperoperContext *_localctx = _tracker.createInstance<AmperoperContext>(_ctx, getState());
  enterRule(_localctx, 6, BBCBasicVParser::RuleAmperoper);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    match(BBCBasicVParser::AMPERSAND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AmprstmtContext ------------------------------------------------------------------

BBCBasicVParser::AmprstmtContext::AmprstmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BBCBasicVParser::StatementContext* BBCBasicVParser::AmprstmtContext::statement() {
  return getRuleContext<BBCBasicVParser::StatementContext>(0);
}

BBCBasicVParser::AmperoperContext* BBCBasicVParser::AmprstmtContext::amperoper() {
  return getRuleContext<BBCBasicVParser::AmperoperContext>(0);
}

tree::TerminalNode* BBCBasicVParser::AmprstmtContext::COMMENT() {
  return getToken(BBCBasicVParser::COMMENT, 0);
}

tree::TerminalNode* BBCBasicVParser::AmprstmtContext::REM() {
  return getToken(BBCBasicVParser::REM, 0);
}


size_t BBCBasicVParser::AmprstmtContext::getRuleIndex() const {
  return BBCBasicVParser::RuleAmprstmt;
}

void BBCBasicVParser::AmprstmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAmprstmt(this);
}

void BBCBasicVParser::AmprstmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAmprstmt(this);
}

BBCBasicVParser::AmprstmtContext* BBCBasicVParser::amprstmt() {
  AmprstmtContext *_localctx = _tracker.createInstance<AmprstmtContext>(_ctx, getState());
  enterRule(_localctx, 8, BBCBasicVParser::RuleAmprstmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(80);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BBCBasicVParser::AMPERSAND:
      case BBCBasicVParser::IF:
      case BBCBasicVParser::END:
      case BBCBasicVParser::RETURN: {
        enterOuterAlt(_localctx, 1);
        setState(76);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == BBCBasicVParser::AMPERSAND) {
          setState(75);
          amperoper();
        }
        setState(78);
        statement();
        break;
      }

      case BBCBasicVParser::REM:
      case BBCBasicVParser::COMMENT: {
        enterOuterAlt(_localctx, 2);
        setState(79);
        _la = _input->LA(1);
        if (!(_la == BBCBasicVParser::REM

        || _la == BBCBasicVParser::COMMENT)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

BBCBasicVParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BBCBasicVParser::EndstmtContext* BBCBasicVParser::StatementContext::endstmt() {
  return getRuleContext<BBCBasicVParser::EndstmtContext>(0);
}

BBCBasicVParser::IfstmtContext* BBCBasicVParser::StatementContext::ifstmt() {
  return getRuleContext<BBCBasicVParser::IfstmtContext>(0);
}

BBCBasicVParser::ReturnstmtContext* BBCBasicVParser::StatementContext::returnstmt() {
  return getRuleContext<BBCBasicVParser::ReturnstmtContext>(0);
}


size_t BBCBasicVParser::StatementContext::getRuleIndex() const {
  return BBCBasicVParser::RuleStatement;
}

void BBCBasicVParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void BBCBasicVParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

BBCBasicVParser::StatementContext* BBCBasicVParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 10, BBCBasicVParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BBCBasicVParser::END: {
        enterOuterAlt(_localctx, 1);
        setState(82);
        endstmt();
        break;
      }

      case BBCBasicVParser::IF: {
        enterOuterAlt(_localctx, 2);
        setState(83);
        ifstmt();
        break;
      }

      case BBCBasicVParser::RETURN: {
        enterOuterAlt(_localctx, 3);
        setState(84);
        returnstmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardeclContext ------------------------------------------------------------------

BBCBasicVParser::VardeclContext::VardeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BBCBasicVParser::VarContext* BBCBasicVParser::VardeclContext::var() {
  return getRuleContext<BBCBasicVParser::VarContext>(0);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::VardeclContext::LPAREN() {
  return getTokens(BBCBasicVParser::LPAREN);
}

tree::TerminalNode* BBCBasicVParser::VardeclContext::LPAREN(size_t i) {
  return getToken(BBCBasicVParser::LPAREN, i);
}

std::vector<BBCBasicVParser::ExprlistContext *> BBCBasicVParser::VardeclContext::exprlist() {
  return getRuleContexts<BBCBasicVParser::ExprlistContext>();
}

BBCBasicVParser::ExprlistContext* BBCBasicVParser::VardeclContext::exprlist(size_t i) {
  return getRuleContext<BBCBasicVParser::ExprlistContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::VardeclContext::RPAREN() {
  return getTokens(BBCBasicVParser::RPAREN);
}

tree::TerminalNode* BBCBasicVParser::VardeclContext::RPAREN(size_t i) {
  return getToken(BBCBasicVParser::RPAREN, i);
}


size_t BBCBasicVParser::VardeclContext::getRuleIndex() const {
  return BBCBasicVParser::RuleVardecl;
}

void BBCBasicVParser::VardeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardecl(this);
}

void BBCBasicVParser::VardeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardecl(this);
}

BBCBasicVParser::VardeclContext* BBCBasicVParser::vardecl() {
  VardeclContext *_localctx = _tracker.createInstance<VardeclContext>(_ctx, getState());
  enterRule(_localctx, 12, BBCBasicVParser::RuleVardecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    var();
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BBCBasicVParser::LPAREN) {
      setState(88);
      match(BBCBasicVParser::LPAREN);
      setState(89);
      exprlist();
      setState(90);
      match(BBCBasicVParser::RPAREN);
      setState(96);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

BBCBasicVParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::RelopContext::GTE() {
  return getToken(BBCBasicVParser::GTE, 0);
}

tree::TerminalNode* BBCBasicVParser::RelopContext::GT() {
  return getToken(BBCBasicVParser::GT, 0);
}

tree::TerminalNode* BBCBasicVParser::RelopContext::EQ() {
  return getToken(BBCBasicVParser::EQ, 0);
}

tree::TerminalNode* BBCBasicVParser::RelopContext::LTE() {
  return getToken(BBCBasicVParser::LTE, 0);
}

tree::TerminalNode* BBCBasicVParser::RelopContext::LT() {
  return getToken(BBCBasicVParser::LT, 0);
}

BBCBasicVParser::NeqContext* BBCBasicVParser::RelopContext::neq() {
  return getRuleContext<BBCBasicVParser::NeqContext>(0);
}


size_t BBCBasicVParser::RelopContext::getRuleIndex() const {
  return BBCBasicVParser::RuleRelop;
}

void BBCBasicVParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void BBCBasicVParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

BBCBasicVParser::RelopContext* BBCBasicVParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 14, BBCBasicVParser::RuleRelop);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(111);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(97);
      match(BBCBasicVParser::GTE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(98);
      match(BBCBasicVParser::GT);
      setState(99);
      match(BBCBasicVParser::EQ);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(100);
      match(BBCBasicVParser::EQ);
      setState(101);
      match(BBCBasicVParser::GT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(102);
      match(BBCBasicVParser::LTE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(103);
      match(BBCBasicVParser::LT);
      setState(104);
      match(BBCBasicVParser::EQ);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(105);
      match(BBCBasicVParser::EQ);
      setState(106);
      match(BBCBasicVParser::LT);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(107);
      neq();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(108);
      match(BBCBasicVParser::EQ);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(109);
      match(BBCBasicVParser::GT);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(110);
      match(BBCBasicVParser::LT);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NeqContext ------------------------------------------------------------------

BBCBasicVParser::NeqContext::NeqContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::NeqContext::LT() {
  return getToken(BBCBasicVParser::LT, 0);
}

tree::TerminalNode* BBCBasicVParser::NeqContext::GT() {
  return getToken(BBCBasicVParser::GT, 0);
}


size_t BBCBasicVParser::NeqContext::getRuleIndex() const {
  return BBCBasicVParser::RuleNeq;
}

void BBCBasicVParser::NeqContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNeq(this);
}

void BBCBasicVParser::NeqContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNeq(this);
}

BBCBasicVParser::NeqContext* BBCBasicVParser::neq() {
  NeqContext *_localctx = _tracker.createInstance<NeqContext>(_ctx, getState());
  enterRule(_localctx, 16, BBCBasicVParser::RuleNeq);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    match(BBCBasicVParser::LT);
    setState(114);
    match(BBCBasicVParser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfstmtContext ------------------------------------------------------------------

BBCBasicVParser::IfstmtContext::IfstmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::IfstmtContext::IF() {
  return getToken(BBCBasicVParser::IF, 0);
}

BBCBasicVParser::ExpressionContext* BBCBasicVParser::IfstmtContext::expression() {
  return getRuleContext<BBCBasicVParser::ExpressionContext>(0);
}

BBCBasicVParser::StatementContext* BBCBasicVParser::IfstmtContext::statement() {
  return getRuleContext<BBCBasicVParser::StatementContext>(0);
}

BBCBasicVParser::LinenumberContext* BBCBasicVParser::IfstmtContext::linenumber() {
  return getRuleContext<BBCBasicVParser::LinenumberContext>(0);
}

tree::TerminalNode* BBCBasicVParser::IfstmtContext::THEN() {
  return getToken(BBCBasicVParser::THEN, 0);
}


size_t BBCBasicVParser::IfstmtContext::getRuleIndex() const {
  return BBCBasicVParser::RuleIfstmt;
}

void BBCBasicVParser::IfstmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfstmt(this);
}

void BBCBasicVParser::IfstmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfstmt(this);
}

BBCBasicVParser::IfstmtContext* BBCBasicVParser::ifstmt() {
  IfstmtContext *_localctx = _tracker.createInstance<IfstmtContext>(_ctx, getState());
  enterRule(_localctx, 18, BBCBasicVParser::RuleIfstmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(BBCBasicVParser::IF);
    setState(117);
    expression();
    setState(119);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BBCBasicVParser::THEN) {
      setState(118);
      match(BBCBasicVParser::THEN);
    }
    setState(123);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BBCBasicVParser::IF:
      case BBCBasicVParser::END:
      case BBCBasicVParser::RETURN: {
        setState(121);
        statement();
        break;
      }

      case BBCBasicVParser::NUMBER: {
        setState(122);
        linenumber();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EndstmtContext ------------------------------------------------------------------

BBCBasicVParser::EndstmtContext::EndstmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::EndstmtContext::END() {
  return getToken(BBCBasicVParser::END, 0);
}


size_t BBCBasicVParser::EndstmtContext::getRuleIndex() const {
  return BBCBasicVParser::RuleEndstmt;
}

void BBCBasicVParser::EndstmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEndstmt(this);
}

void BBCBasicVParser::EndstmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEndstmt(this);
}

BBCBasicVParser::EndstmtContext* BBCBasicVParser::endstmt() {
  EndstmtContext *_localctx = _tracker.createInstance<EndstmtContext>(_ctx, getState());
  enterRule(_localctx, 20, BBCBasicVParser::RuleEndstmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(BBCBasicVParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnstmtContext ------------------------------------------------------------------

BBCBasicVParser::ReturnstmtContext::ReturnstmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::ReturnstmtContext::RETURN() {
  return getToken(BBCBasicVParser::RETURN, 0);
}


size_t BBCBasicVParser::ReturnstmtContext::getRuleIndex() const {
  return BBCBasicVParser::RuleReturnstmt;
}

void BBCBasicVParser::ReturnstmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnstmt(this);
}

void BBCBasicVParser::ReturnstmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnstmt(this);
}

BBCBasicVParser::ReturnstmtContext* BBCBasicVParser::returnstmt() {
  ReturnstmtContext *_localctx = _tracker.createInstance<ReturnstmtContext>(_ctx, getState());
  enterRule(_localctx, 22, BBCBasicVParser::RuleReturnstmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    match(BBCBasicVParser::RETURN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

BBCBasicVParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::NumberContext::NUMBER() {
  return getToken(BBCBasicVParser::NUMBER, 0);
}

tree::TerminalNode* BBCBasicVParser::NumberContext::FLOAT() {
  return getToken(BBCBasicVParser::FLOAT, 0);
}

tree::TerminalNode* BBCBasicVParser::NumberContext::PLUS() {
  return getToken(BBCBasicVParser::PLUS, 0);
}

tree::TerminalNode* BBCBasicVParser::NumberContext::MINUS() {
  return getToken(BBCBasicVParser::MINUS, 0);
}


size_t BBCBasicVParser::NumberContext::getRuleIndex() const {
  return BBCBasicVParser::RuleNumber;
}

void BBCBasicVParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void BBCBasicVParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

BBCBasicVParser::NumberContext* BBCBasicVParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 24, BBCBasicVParser::RuleNumber);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BBCBasicVParser::PLUS

    || _la == BBCBasicVParser::MINUS) {
      setState(129);
      _la = _input->LA(1);
      if (!(_la == BBCBasicVParser::PLUS

      || _la == BBCBasicVParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(132);
    _la = _input->LA(1);
    if (!(_la == BBCBasicVParser::NUMBER

    || _la == BBCBasicVParser::FLOAT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncContext ------------------------------------------------------------------

BBCBasicVParser::FuncContext::FuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::FuncContext::STRINGLITERAL() {
  return getToken(BBCBasicVParser::STRINGLITERAL, 0);
}

BBCBasicVParser::NumberContext* BBCBasicVParser::FuncContext::number() {
  return getRuleContext<BBCBasicVParser::NumberContext>(0);
}

tree::TerminalNode* BBCBasicVParser::FuncContext::LPAREN() {
  return getToken(BBCBasicVParser::LPAREN, 0);
}

BBCBasicVParser::ExpressionContext* BBCBasicVParser::FuncContext::expression() {
  return getRuleContext<BBCBasicVParser::ExpressionContext>(0);
}

tree::TerminalNode* BBCBasicVParser::FuncContext::RPAREN() {
  return getToken(BBCBasicVParser::RPAREN, 0);
}


size_t BBCBasicVParser::FuncContext::getRuleIndex() const {
  return BBCBasicVParser::RuleFunc;
}

void BBCBasicVParser::FuncContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc(this);
}

void BBCBasicVParser::FuncContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc(this);
}

BBCBasicVParser::FuncContext* BBCBasicVParser::func() {
  FuncContext *_localctx = _tracker.createInstance<FuncContext>(_ctx, getState());
  enterRule(_localctx, 26, BBCBasicVParser::RuleFunc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(140);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BBCBasicVParser::STRINGLITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(134);
        match(BBCBasicVParser::STRINGLITERAL);
        break;
      }

      case BBCBasicVParser::PLUS:
      case BBCBasicVParser::MINUS:
      case BBCBasicVParser::NUMBER:
      case BBCBasicVParser::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(135);
        number();
        break;
      }

      case BBCBasicVParser::LPAREN: {
        enterOuterAlt(_localctx, 3);
        setState(136);
        match(BBCBasicVParser::LPAREN);
        setState(137);
        expression();
        setState(138);
        match(BBCBasicVParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarContext ------------------------------------------------------------------

BBCBasicVParser::VarContext::VarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BBCBasicVParser::VarnameContext* BBCBasicVParser::VarContext::varname() {
  return getRuleContext<BBCBasicVParser::VarnameContext>(0);
}

BBCBasicVParser::VarsuffixContext* BBCBasicVParser::VarContext::varsuffix() {
  return getRuleContext<BBCBasicVParser::VarsuffixContext>(0);
}


size_t BBCBasicVParser::VarContext::getRuleIndex() const {
  return BBCBasicVParser::RuleVar;
}

void BBCBasicVParser::VarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar(this);
}

void BBCBasicVParser::VarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar(this);
}

BBCBasicVParser::VarContext* BBCBasicVParser::var() {
  VarContext *_localctx = _tracker.createInstance<VarContext>(_ctx, getState());
  enterRule(_localctx, 28, BBCBasicVParser::RuleVar);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    varname();
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BBCBasicVParser::DOLLAR

    || _la == BBCBasicVParser::PERCENT) {
      setState(143);
      varsuffix();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarnameContext ------------------------------------------------------------------

BBCBasicVParser::VarnameContext::VarnameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> BBCBasicVParser::VarnameContext::LETTERS() {
  return getTokens(BBCBasicVParser::LETTERS);
}

tree::TerminalNode* BBCBasicVParser::VarnameContext::LETTERS(size_t i) {
  return getToken(BBCBasicVParser::LETTERS, i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::VarnameContext::NUMBER() {
  return getTokens(BBCBasicVParser::NUMBER);
}

tree::TerminalNode* BBCBasicVParser::VarnameContext::NUMBER(size_t i) {
  return getToken(BBCBasicVParser::NUMBER, i);
}


size_t BBCBasicVParser::VarnameContext::getRuleIndex() const {
  return BBCBasicVParser::RuleVarname;
}

void BBCBasicVParser::VarnameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarname(this);
}

void BBCBasicVParser::VarnameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarname(this);
}

BBCBasicVParser::VarnameContext* BBCBasicVParser::varname() {
  VarnameContext *_localctx = _tracker.createInstance<VarnameContext>(_ctx, getState());
  enterRule(_localctx, 30, BBCBasicVParser::RuleVarname);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(BBCBasicVParser::LETTERS);
    setState(150);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BBCBasicVParser::LETTERS

    || _la == BBCBasicVParser::NUMBER) {
      setState(147);
      _la = _input->LA(1);
      if (!(_la == BBCBasicVParser::LETTERS

      || _la == BBCBasicVParser::NUMBER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(152);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarsuffixContext ------------------------------------------------------------------

BBCBasicVParser::VarsuffixContext::VarsuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BBCBasicVParser::VarsuffixContext::DOLLAR() {
  return getToken(BBCBasicVParser::DOLLAR, 0);
}

tree::TerminalNode* BBCBasicVParser::VarsuffixContext::PERCENT() {
  return getToken(BBCBasicVParser::PERCENT, 0);
}


size_t BBCBasicVParser::VarsuffixContext::getRuleIndex() const {
  return BBCBasicVParser::RuleVarsuffix;
}

void BBCBasicVParser::VarsuffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarsuffix(this);
}

void BBCBasicVParser::VarsuffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarsuffix(this);
}

BBCBasicVParser::VarsuffixContext* BBCBasicVParser::varsuffix() {
  VarsuffixContext *_localctx = _tracker.createInstance<VarsuffixContext>(_ctx, getState());
  enterRule(_localctx, 32, BBCBasicVParser::RuleVarsuffix);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    _la = _input->LA(1);
    if (!(_la == BBCBasicVParser::DOLLAR

    || _la == BBCBasicVParser::PERCENT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarlistContext ------------------------------------------------------------------

BBCBasicVParser::VarlistContext::VarlistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BBCBasicVParser::VardeclContext *> BBCBasicVParser::VarlistContext::vardecl() {
  return getRuleContexts<BBCBasicVParser::VardeclContext>();
}

BBCBasicVParser::VardeclContext* BBCBasicVParser::VarlistContext::vardecl(size_t i) {
  return getRuleContext<BBCBasicVParser::VardeclContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::VarlistContext::COMMA() {
  return getTokens(BBCBasicVParser::COMMA);
}

tree::TerminalNode* BBCBasicVParser::VarlistContext::COMMA(size_t i) {
  return getToken(BBCBasicVParser::COMMA, i);
}


size_t BBCBasicVParser::VarlistContext::getRuleIndex() const {
  return BBCBasicVParser::RuleVarlist;
}

void BBCBasicVParser::VarlistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarlist(this);
}

void BBCBasicVParser::VarlistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarlist(this);
}

BBCBasicVParser::VarlistContext* BBCBasicVParser::varlist() {
  VarlistContext *_localctx = _tracker.createInstance<VarlistContext>(_ctx, getState());
  enterRule(_localctx, 34, BBCBasicVParser::RuleVarlist);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    vardecl();
    setState(160);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BBCBasicVParser::COMMA) {
      setState(156);
      match(BBCBasicVParser::COMMA);
      setState(157);
      vardecl();
      setState(162);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprlistContext ------------------------------------------------------------------

BBCBasicVParser::ExprlistContext::ExprlistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BBCBasicVParser::ExpressionContext *> BBCBasicVParser::ExprlistContext::expression() {
  return getRuleContexts<BBCBasicVParser::ExpressionContext>();
}

BBCBasicVParser::ExpressionContext* BBCBasicVParser::ExprlistContext::expression(size_t i) {
  return getRuleContext<BBCBasicVParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::ExprlistContext::COMMA() {
  return getTokens(BBCBasicVParser::COMMA);
}

tree::TerminalNode* BBCBasicVParser::ExprlistContext::COMMA(size_t i) {
  return getToken(BBCBasicVParser::COMMA, i);
}


size_t BBCBasicVParser::ExprlistContext::getRuleIndex() const {
  return BBCBasicVParser::RuleExprlist;
}

void BBCBasicVParser::ExprlistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprlist(this);
}

void BBCBasicVParser::ExprlistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprlist(this);
}

BBCBasicVParser::ExprlistContext* BBCBasicVParser::exprlist() {
  ExprlistContext *_localctx = _tracker.createInstance<ExprlistContext>(_ctx, getState());
  enterRule(_localctx, 36, BBCBasicVParser::RuleExprlist);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(163);
    expression();
    setState(168);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BBCBasicVParser::COMMA) {
      setState(164);
      match(BBCBasicVParser::COMMA);
      setState(165);
      expression();
      setState(170);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

BBCBasicVParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BBCBasicVParser::FuncContext* BBCBasicVParser::ExpressionContext::func() {
  return getRuleContext<BBCBasicVParser::FuncContext>(0);
}

std::vector<BBCBasicVParser::RelationalExpressionContext *> BBCBasicVParser::ExpressionContext::relationalExpression() {
  return getRuleContexts<BBCBasicVParser::RelationalExpressionContext>();
}

BBCBasicVParser::RelationalExpressionContext* BBCBasicVParser::ExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<BBCBasicVParser::RelationalExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::ExpressionContext::AND() {
  return getTokens(BBCBasicVParser::AND);
}

tree::TerminalNode* BBCBasicVParser::ExpressionContext::AND(size_t i) {
  return getToken(BBCBasicVParser::AND, i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::ExpressionContext::OR() {
  return getTokens(BBCBasicVParser::OR);
}

tree::TerminalNode* BBCBasicVParser::ExpressionContext::OR(size_t i) {
  return getToken(BBCBasicVParser::OR, i);
}


size_t BBCBasicVParser::ExpressionContext::getRuleIndex() const {
  return BBCBasicVParser::RuleExpression;
}

void BBCBasicVParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void BBCBasicVParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

BBCBasicVParser::ExpressionContext* BBCBasicVParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, BBCBasicVParser::RuleExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(171);
      func();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(172);
      relationalExpression();
      setState(177);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BBCBasicVParser::AND

      || _la == BBCBasicVParser::OR) {
        setState(173);
        _la = _input->LA(1);
        if (!(_la == BBCBasicVParser::AND

        || _la == BBCBasicVParser::OR)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(174);
        relationalExpression();
        setState(179);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignExpressionContext ------------------------------------------------------------------

BBCBasicVParser::SignExpressionContext::SignExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BBCBasicVParser::FuncContext* BBCBasicVParser::SignExpressionContext::func() {
  return getRuleContext<BBCBasicVParser::FuncContext>(0);
}

tree::TerminalNode* BBCBasicVParser::SignExpressionContext::NOT() {
  return getToken(BBCBasicVParser::NOT, 0);
}

tree::TerminalNode* BBCBasicVParser::SignExpressionContext::PLUS() {
  return getToken(BBCBasicVParser::PLUS, 0);
}

tree::TerminalNode* BBCBasicVParser::SignExpressionContext::MINUS() {
  return getToken(BBCBasicVParser::MINUS, 0);
}


size_t BBCBasicVParser::SignExpressionContext::getRuleIndex() const {
  return BBCBasicVParser::RuleSignExpression;
}

void BBCBasicVParser::SignExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignExpression(this);
}

void BBCBasicVParser::SignExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignExpression(this);
}

BBCBasicVParser::SignExpressionContext* BBCBasicVParser::signExpression() {
  SignExpressionContext *_localctx = _tracker.createInstance<SignExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, BBCBasicVParser::RuleSignExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BBCBasicVParser::NOT) {
      setState(182);
      match(BBCBasicVParser::NOT);
    }
    setState(186);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(185);
      _la = _input->LA(1);
      if (!(_la == BBCBasicVParser::PLUS

      || _la == BBCBasicVParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    }
    setState(188);
    func();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExponentExpressionContext ------------------------------------------------------------------

BBCBasicVParser::ExponentExpressionContext::ExponentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BBCBasicVParser::SignExpressionContext *> BBCBasicVParser::ExponentExpressionContext::signExpression() {
  return getRuleContexts<BBCBasicVParser::SignExpressionContext>();
}

BBCBasicVParser::SignExpressionContext* BBCBasicVParser::ExponentExpressionContext::signExpression(size_t i) {
  return getRuleContext<BBCBasicVParser::SignExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::ExponentExpressionContext::EXPONENT() {
  return getTokens(BBCBasicVParser::EXPONENT);
}

tree::TerminalNode* BBCBasicVParser::ExponentExpressionContext::EXPONENT(size_t i) {
  return getToken(BBCBasicVParser::EXPONENT, i);
}


size_t BBCBasicVParser::ExponentExpressionContext::getRuleIndex() const {
  return BBCBasicVParser::RuleExponentExpression;
}

void BBCBasicVParser::ExponentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExponentExpression(this);
}

void BBCBasicVParser::ExponentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExponentExpression(this);
}

BBCBasicVParser::ExponentExpressionContext* BBCBasicVParser::exponentExpression() {
  ExponentExpressionContext *_localctx = _tracker.createInstance<ExponentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, BBCBasicVParser::RuleExponentExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    signExpression();
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BBCBasicVParser::EXPONENT) {
      setState(191);
      match(BBCBasicVParser::EXPONENT);
      setState(192);
      signExpression();
      setState(197);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplyingExpressionContext ------------------------------------------------------------------

BBCBasicVParser::MultiplyingExpressionContext::MultiplyingExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BBCBasicVParser::ExponentExpressionContext *> BBCBasicVParser::MultiplyingExpressionContext::exponentExpression() {
  return getRuleContexts<BBCBasicVParser::ExponentExpressionContext>();
}

BBCBasicVParser::ExponentExpressionContext* BBCBasicVParser::MultiplyingExpressionContext::exponentExpression(size_t i) {
  return getRuleContext<BBCBasicVParser::ExponentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::MultiplyingExpressionContext::TIMES() {
  return getTokens(BBCBasicVParser::TIMES);
}

tree::TerminalNode* BBCBasicVParser::MultiplyingExpressionContext::TIMES(size_t i) {
  return getToken(BBCBasicVParser::TIMES, i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::MultiplyingExpressionContext::DIV() {
  return getTokens(BBCBasicVParser::DIV);
}

tree::TerminalNode* BBCBasicVParser::MultiplyingExpressionContext::DIV(size_t i) {
  return getToken(BBCBasicVParser::DIV, i);
}


size_t BBCBasicVParser::MultiplyingExpressionContext::getRuleIndex() const {
  return BBCBasicVParser::RuleMultiplyingExpression;
}

void BBCBasicVParser::MultiplyingExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplyingExpression(this);
}

void BBCBasicVParser::MultiplyingExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplyingExpression(this);
}

BBCBasicVParser::MultiplyingExpressionContext* BBCBasicVParser::multiplyingExpression() {
  MultiplyingExpressionContext *_localctx = _tracker.createInstance<MultiplyingExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, BBCBasicVParser::RuleMultiplyingExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(198);
    exponentExpression();
    setState(203);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BBCBasicVParser::TIMES

    || _la == BBCBasicVParser::DIV) {
      setState(199);
      _la = _input->LA(1);
      if (!(_la == BBCBasicVParser::TIMES

      || _la == BBCBasicVParser::DIV)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(200);
      exponentExpression();
      setState(205);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddingExpressionContext ------------------------------------------------------------------

BBCBasicVParser::AddingExpressionContext::AddingExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BBCBasicVParser::MultiplyingExpressionContext *> BBCBasicVParser::AddingExpressionContext::multiplyingExpression() {
  return getRuleContexts<BBCBasicVParser::MultiplyingExpressionContext>();
}

BBCBasicVParser::MultiplyingExpressionContext* BBCBasicVParser::AddingExpressionContext::multiplyingExpression(size_t i) {
  return getRuleContext<BBCBasicVParser::MultiplyingExpressionContext>(i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::AddingExpressionContext::PLUS() {
  return getTokens(BBCBasicVParser::PLUS);
}

tree::TerminalNode* BBCBasicVParser::AddingExpressionContext::PLUS(size_t i) {
  return getToken(BBCBasicVParser::PLUS, i);
}

std::vector<tree::TerminalNode *> BBCBasicVParser::AddingExpressionContext::MINUS() {
  return getTokens(BBCBasicVParser::MINUS);
}

tree::TerminalNode* BBCBasicVParser::AddingExpressionContext::MINUS(size_t i) {
  return getToken(BBCBasicVParser::MINUS, i);
}


size_t BBCBasicVParser::AddingExpressionContext::getRuleIndex() const {
  return BBCBasicVParser::RuleAddingExpression;
}

void BBCBasicVParser::AddingExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddingExpression(this);
}

void BBCBasicVParser::AddingExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddingExpression(this);
}

BBCBasicVParser::AddingExpressionContext* BBCBasicVParser::addingExpression() {
  AddingExpressionContext *_localctx = _tracker.createInstance<AddingExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, BBCBasicVParser::RuleAddingExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    multiplyingExpression();
    setState(211);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BBCBasicVParser::PLUS

    || _la == BBCBasicVParser::MINUS) {
      setState(207);
      _la = _input->LA(1);
      if (!(_la == BBCBasicVParser::PLUS

      || _la == BBCBasicVParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(208);
      multiplyingExpression();
      setState(213);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

BBCBasicVParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BBCBasicVParser::AddingExpressionContext *> BBCBasicVParser::RelationalExpressionContext::addingExpression() {
  return getRuleContexts<BBCBasicVParser::AddingExpressionContext>();
}

BBCBasicVParser::AddingExpressionContext* BBCBasicVParser::RelationalExpressionContext::addingExpression(size_t i) {
  return getRuleContext<BBCBasicVParser::AddingExpressionContext>(i);
}

BBCBasicVParser::RelopContext* BBCBasicVParser::RelationalExpressionContext::relop() {
  return getRuleContext<BBCBasicVParser::RelopContext>(0);
}


size_t BBCBasicVParser::RelationalExpressionContext::getRuleIndex() const {
  return BBCBasicVParser::RuleRelationalExpression;
}

void BBCBasicVParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void BBCBasicVParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BBCBasicVListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}

BBCBasicVParser::RelationalExpressionContext* BBCBasicVParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, BBCBasicVParser::RuleRelationalExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    addingExpression();
    setState(218);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BBCBasicVParser::EQ)
      | (1ULL << BBCBasicVParser::GTE)
      | (1ULL << BBCBasicVParser::LTE)
      | (1ULL << BBCBasicVParser::GT)
      | (1ULL << BBCBasicVParser::LT))) != 0)) {
      setState(215);
      relop();
      setState(216);
      addingExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> BBCBasicVParser::_decisionToDFA;
atn::PredictionContextCache BBCBasicVParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN BBCBasicVParser::_atn;
std::vector<uint16_t> BBCBasicVParser::_serializedATN;

std::vector<std::string> BBCBasicVParser::_ruleNames = {
  "prog", "line", "linenumber", "amperoper", "amprstmt", "statement", "vardecl", 
  "relop", "neq", "ifstmt", "endstmt", "returnstmt", "number", "func", "var", 
  "varname", "varsuffix", "varlist", "exprlist", "expression", "signExpression", 
  "exponentExpression", "multiplyingExpression", "addingExpression", "relationalExpression"
};

std::vector<std::string> BBCBasicVParser::_literalNames = {
  "", "'$'", "'%'", "':'", "'&'", "", "", "", "", "", "", "", "", "'='", 
  "'>='", "'<='", "'>'", "'<'", "'('", "')'", "'+'", "'-'", "'*'", "'/'", 
  "','", "'^'"
};

std::vector<std::string> BBCBasicVParser::_symbolicNames = {
  "", "DOLLAR", "PERCENT", "COLON", "AMPERSAND", "IF", "REM", "END", "RETURN", 
  "THEN", "NOT", "AND", "OR", "EQ", "GTE", "LTE", "GT", "LT", "LPAREN", 
  "RPAREN", "PLUS", "MINUS", "TIMES", "DIV", "COMMA", "EXPONENT", "COMMENT", 
  "STRINGLITERAL", "LETTERS", "NUMBER", "FLOAT", "WS"
};

dfa::Vocabulary BBCBasicVParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> BBCBasicVParser::_tokenNames;

BBCBasicVParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x21, 0xdf, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x3, 0x2, 0x6, 0x2, 0x36, 
    0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x37, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x40, 0xa, 0x3, 0x7, 0x3, 0x42, 0xa, 
    0x3, 0xc, 0x3, 0xe, 0x3, 0x45, 0xb, 0x3, 0x3, 0x3, 0x5, 0x3, 0x48, 0xa, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x5, 0x6, 0x4f, 
    0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x53, 0xa, 0x6, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x5, 0x7, 0x58, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x5f, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x62, 
    0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x5, 0x9, 0x72, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x7a, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x5, 0xb, 0x7e, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xe, 0x5, 0xe, 0x85, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x8f, 0xa, 0xf, 0x3, 
    0x10, 0x3, 0x10, 0x5, 0x10, 0x93, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x7, 
    0x11, 0x97, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0x9a, 0xb, 0x11, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xa1, 0xa, 0x13, 
    0xc, 0x13, 0xe, 0x13, 0xa4, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x7, 0x14, 0xa9, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0xac, 0xb, 0x14, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x7, 0x15, 0xb2, 0xa, 0x15, 0xc, 
    0x15, 0xe, 0x15, 0xb5, 0xb, 0x15, 0x5, 0x15, 0xb7, 0xa, 0x15, 0x3, 0x16, 
    0x5, 0x16, 0xba, 0xa, 0x16, 0x3, 0x16, 0x5, 0x16, 0xbd, 0xa, 0x16, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x7, 0x17, 0xc4, 0xa, 
    0x17, 0xc, 0x17, 0xe, 0x17, 0xc7, 0xb, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x7, 0x18, 0xcc, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 0xcf, 0xb, 0x18, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x7, 0x19, 0xd4, 0xa, 0x19, 0xc, 0x19, 
    0xe, 0x19, 0xd7, 0xb, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x5, 0x1a, 0xdd, 0xa, 0x1a, 0x3, 0x1a, 0x2, 0x2, 0x1b, 0x2, 0x4, 0x6, 
    0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 
    0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x2, 0x9, 
    0x4, 0x2, 0x8, 0x8, 0x1c, 0x1c, 0x3, 0x2, 0x16, 0x17, 0x3, 0x2, 0x1f, 
    0x20, 0x3, 0x2, 0x1e, 0x1f, 0x3, 0x2, 0x3, 0x4, 0x3, 0x2, 0xd, 0xe, 
    0x3, 0x2, 0x18, 0x19, 0x2, 0xe8, 0x2, 0x35, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x3b, 0x3, 0x2, 0x2, 0x2, 0x6, 0x49, 0x3, 0x2, 0x2, 0x2, 0x8, 0x4b, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x52, 0x3, 0x2, 0x2, 0x2, 0xc, 0x57, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x59, 0x3, 0x2, 0x2, 0x2, 0x10, 0x71, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x73, 0x3, 0x2, 0x2, 0x2, 0x14, 0x76, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x18, 0x81, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x84, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x90, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x94, 0x3, 0x2, 0x2, 0x2, 0x22, 0x9b, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x26, 0xa5, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0xb6, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xb9, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0xc0, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xc8, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0xd0, 0x3, 0x2, 0x2, 0x2, 0x32, 0xd8, 0x3, 0x2, 0x2, 0x2, 0x34, 
    0x36, 0x5, 0x4, 0x3, 0x2, 0x35, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0x37, 0x35, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x3, 
    0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x2, 
    0x2, 0x3, 0x3a, 0x3, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x47, 0x5, 0x6, 0x4, 
    0x2, 0x3c, 0x43, 0x5, 0xa, 0x6, 0x2, 0x3d, 0x3f, 0x7, 0x5, 0x2, 0x2, 
    0x3e, 0x40, 0x5, 0xa, 0x6, 0x2, 0x3f, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3f, 
    0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 0x42, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3d, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x45, 0x3, 0x2, 0x2, 0x2, 0x43, 0x41, 0x3, 
    0x2, 0x2, 0x2, 0x43, 0x44, 0x3, 0x2, 0x2, 0x2, 0x44, 0x48, 0x3, 0x2, 
    0x2, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x46, 0x48, 0x9, 0x2, 0x2, 
    0x2, 0x47, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x47, 0x46, 0x3, 0x2, 0x2, 0x2, 
    0x48, 0x5, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x7, 0x1f, 0x2, 0x2, 0x4a, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0x6, 0x2, 0x2, 0x4c, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x4d, 0x4f, 0x5, 0x8, 0x5, 0x2, 0x4e, 0x4d, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x3, 0x2, 
    0x2, 0x2, 0x50, 0x53, 0x5, 0xc, 0x7, 0x2, 0x51, 0x53, 0x9, 0x2, 0x2, 
    0x2, 0x52, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x52, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x53, 0xb, 0x3, 0x2, 0x2, 0x2, 0x54, 0x58, 0x5, 0x16, 0xc, 0x2, 0x55, 
    0x58, 0x5, 0x14, 0xb, 0x2, 0x56, 0x58, 0x5, 0x18, 0xd, 0x2, 0x57, 0x54, 
    0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 0x2, 0x57, 0x56, 0x3, 
    0x2, 0x2, 0x2, 0x58, 0xd, 0x3, 0x2, 0x2, 0x2, 0x59, 0x60, 0x5, 0x1e, 
    0x10, 0x2, 0x5a, 0x5b, 0x7, 0x14, 0x2, 0x2, 0x5b, 0x5c, 0x5, 0x26, 0x14, 
    0x2, 0x5c, 0x5d, 0x7, 0x15, 0x2, 0x2, 0x5d, 0x5f, 0x3, 0x2, 0x2, 0x2, 
    0x5e, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x62, 0x3, 0x2, 0x2, 0x2, 0x60, 
    0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 0x2, 0x61, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 0x63, 0x72, 0x7, 
    0x10, 0x2, 0x2, 0x64, 0x65, 0x7, 0x12, 0x2, 0x2, 0x65, 0x72, 0x7, 0xf, 
    0x2, 0x2, 0x66, 0x67, 0x7, 0xf, 0x2, 0x2, 0x67, 0x72, 0x7, 0x12, 0x2, 
    0x2, 0x68, 0x72, 0x7, 0x11, 0x2, 0x2, 0x69, 0x6a, 0x7, 0x13, 0x2, 0x2, 
    0x6a, 0x72, 0x7, 0xf, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0xf, 0x2, 0x2, 0x6c, 
    0x72, 0x7, 0x13, 0x2, 0x2, 0x6d, 0x72, 0x5, 0x12, 0xa, 0x2, 0x6e, 0x72, 
    0x7, 0xf, 0x2, 0x2, 0x6f, 0x72, 0x7, 0x12, 0x2, 0x2, 0x70, 0x72, 0x7, 
    0x13, 0x2, 0x2, 0x71, 0x63, 0x3, 0x2, 0x2, 0x2, 0x71, 0x64, 0x3, 0x2, 
    0x2, 0x2, 0x71, 0x66, 0x3, 0x2, 0x2, 0x2, 0x71, 0x68, 0x3, 0x2, 0x2, 
    0x2, 0x71, 0x69, 0x3, 0x2, 0x2, 0x2, 0x71, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0x71, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x71, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x71, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x71, 0x70, 0x3, 0x2, 0x2, 0x2, 0x72, 0x11, 
    0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 0x7, 0x13, 0x2, 0x2, 0x74, 0x75, 0x7, 
    0x12, 0x2, 0x2, 0x75, 0x13, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x7, 0x7, 
    0x2, 0x2, 0x77, 0x79, 0x5, 0x28, 0x15, 0x2, 0x78, 0x7a, 0x7, 0xb, 0x2, 
    0x2, 0x79, 0x78, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 
    0x7a, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7e, 0x5, 0xc, 0x7, 0x2, 0x7c, 
    0x7e, 0x5, 0x6, 0x4, 0x2, 0x7d, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7c, 
    0x3, 0x2, 0x2, 0x2, 0x7e, 0x15, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x80, 0x7, 
    0x9, 0x2, 0x2, 0x80, 0x17, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x7, 0xa, 
    0x2, 0x2, 0x82, 0x19, 0x3, 0x2, 0x2, 0x2, 0x83, 0x85, 0x9, 0x3, 0x2, 
    0x2, 0x84, 0x83, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 
    0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x9, 0x4, 0x2, 0x2, 0x87, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0x88, 0x8f, 0x7, 0x1d, 0x2, 0x2, 0x89, 0x8f, 
    0x5, 0x1a, 0xe, 0x2, 0x8a, 0x8b, 0x7, 0x14, 0x2, 0x2, 0x8b, 0x8c, 0x5, 
    0x28, 0x15, 0x2, 0x8c, 0x8d, 0x7, 0x15, 0x2, 0x2, 0x8d, 0x8f, 0x3, 0x2, 
    0x2, 0x2, 0x8e, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x89, 0x3, 0x2, 0x2, 
    0x2, 0x8e, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x90, 0x92, 0x5, 0x20, 0x11, 0x2, 0x91, 0x93, 0x5, 0x22, 0x12, 0x2, 
    0x92, 0x91, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 0x2, 0x93, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0x94, 0x98, 0x7, 0x1e, 0x2, 0x2, 0x95, 0x97, 
    0x9, 0x5, 0x2, 0x2, 0x96, 0x95, 0x3, 0x2, 0x2, 0x2, 0x97, 0x9a, 0x3, 
    0x2, 0x2, 0x2, 0x98, 0x96, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x3, 0x2, 
    0x2, 0x2, 0x99, 0x21, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x98, 0x3, 0x2, 0x2, 
    0x2, 0x9b, 0x9c, 0x9, 0x6, 0x2, 0x2, 0x9c, 0x23, 0x3, 0x2, 0x2, 0x2, 
    0x9d, 0xa2, 0x5, 0xe, 0x8, 0x2, 0x9e, 0x9f, 0x7, 0x1a, 0x2, 0x2, 0x9f, 
    0xa1, 0x5, 0xe, 0x8, 0x2, 0xa0, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa4, 
    0x3, 0x2, 0x2, 0x2, 0xa2, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x3, 
    0x2, 0x2, 0x2, 0xa3, 0x25, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa2, 0x3, 0x2, 
    0x2, 0x2, 0xa5, 0xaa, 0x5, 0x28, 0x15, 0x2, 0xa6, 0xa7, 0x7, 0x1a, 0x2, 
    0x2, 0xa7, 0xa9, 0x5, 0x28, 0x15, 0x2, 0xa8, 0xa6, 0x3, 0x2, 0x2, 0x2, 
    0xa9, 0xac, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xaa, 
    0xab, 0x3, 0x2, 0x2, 0x2, 0xab, 0x27, 0x3, 0x2, 0x2, 0x2, 0xac, 0xaa, 
    0x3, 0x2, 0x2, 0x2, 0xad, 0xb7, 0x5, 0x1c, 0xf, 0x2, 0xae, 0xb3, 0x5, 
    0x32, 0x1a, 0x2, 0xaf, 0xb0, 0x9, 0x7, 0x2, 0x2, 0xb0, 0xb2, 0x5, 0x32, 
    0x1a, 0x2, 0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb5, 0x3, 0x2, 0x2, 
    0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x3, 0x2, 0x2, 0x2, 
    0xb4, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb6, 
    0xad, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xae, 0x3, 0x2, 0x2, 0x2, 0xb7, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0xb8, 0xba, 0x7, 0xc, 0x2, 0x2, 0xb9, 0xb8, 0x3, 
    0x2, 0x2, 0x2, 0xb9, 0xba, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbc, 0x3, 0x2, 
    0x2, 0x2, 0xbb, 0xbd, 0x9, 0x3, 0x2, 0x2, 0xbc, 0xbb, 0x3, 0x2, 0x2, 
    0x2, 0xbc, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 0x2, 
    0xbe, 0xbf, 0x5, 0x1c, 0xf, 0x2, 0xbf, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xc0, 
    0xc5, 0x5, 0x2a, 0x16, 0x2, 0xc1, 0xc2, 0x7, 0x1b, 0x2, 0x2, 0xc2, 0xc4, 
    0x5, 0x2a, 0x16, 0x2, 0xc3, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc7, 0x3, 
    0x2, 0x2, 0x2, 0xc5, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 0x2, 
    0x2, 0x2, 0xc6, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc5, 0x3, 0x2, 0x2, 
    0x2, 0xc8, 0xcd, 0x5, 0x2c, 0x17, 0x2, 0xc9, 0xca, 0x9, 0x8, 0x2, 0x2, 
    0xca, 0xcc, 0x5, 0x2c, 0x17, 0x2, 0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcc, 
    0xcf, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 
    0x3, 0x2, 0x2, 0x2, 0xce, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xcd, 0x3, 
    0x2, 0x2, 0x2, 0xd0, 0xd5, 0x5, 0x2e, 0x18, 0x2, 0xd1, 0xd2, 0x9, 0x3, 
    0x2, 0x2, 0xd2, 0xd4, 0x5, 0x2e, 0x18, 0x2, 0xd3, 0xd1, 0x3, 0x2, 0x2, 
    0x2, 0xd4, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd3, 0x3, 0x2, 0x2, 0x2, 
    0xd5, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd6, 0x31, 0x3, 0x2, 0x2, 0x2, 0xd7, 
    0xd5, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xdc, 0x5, 0x30, 0x19, 0x2, 0xd9, 0xda, 
    0x5, 0x10, 0x9, 0x2, 0xda, 0xdb, 0x5, 0x30, 0x19, 0x2, 0xdb, 0xdd, 0x3, 
    0x2, 0x2, 0x2, 0xdc, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 0x3, 0x2, 
    0x2, 0x2, 0xdd, 0x33, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x37, 0x3f, 0x43, 0x47, 
    0x4e, 0x52, 0x57, 0x60, 0x71, 0x79, 0x7d, 0x84, 0x8e, 0x92, 0x98, 0xa2, 
    0xaa, 0xb3, 0xb6, 0xb9, 0xbc, 0xc5, 0xcd, 0xd5, 0xdc, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

BBCBasicVParser::Initializer BBCBasicVParser::_init;
