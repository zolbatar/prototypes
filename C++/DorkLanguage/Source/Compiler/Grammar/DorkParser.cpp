
// Generated from Dork.g4 by ANTLR 4.10.1


#include "DorkVisitor.h"

#include "DorkParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct DorkParserStaticData final {
  DorkParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  DorkParserStaticData(const DorkParserStaticData&) = delete;
  DorkParserStaticData(DorkParserStaticData&&) = delete;
  DorkParserStaticData& operator=(const DorkParserStaticData&) = delete;
  DorkParserStaticData& operator=(DorkParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag dorkParserOnceFlag;
DorkParserStaticData *dorkParserStaticData = nullptr;

void dorkParserInitialize() {
  assert(dorkParserStaticData == nullptr);
  auto staticData = std::make_unique<DorkParserStaticData>(
    std::vector<std::string>{
      "prog", "statement", "statementAssign", "statementUnary", "expr", 
      "literal", "integerLiteral", "floatLiteral", "stringLiteral"
    },
    std::vector<std::string>{
      "", "", "'''", "';'", "'_'", "'.'", "'+'", "'%'", "'-'", "'->'"
    },
    std::vector<std::string>{
      "", "COMMENT", "TICK", "SEMICOLON", "UNDERSCORE", "DOT", "PLUS", "PERCENT", 
      "MINUS", "ASSIGN", "BINARYPART", "BINARY", "STRINGLITERAL", "HEXNUMBER", 
      "BINARYNUMBER", "INTEGERLITERAL", "FLOATLITERAL", "IDENTIFIER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,18,74,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,1,0,1,0,1,0,5,0,22,8,0,10,0,12,0,25,9,0,1,0,1,0,1,1,1,1,1,
  	1,3,1,32,8,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,5,4,49,8,4,10,4,12,4,52,9,4,1,5,1,5,1,5,3,5,57,8,5,1,6,1,6,1,6,3,
  	6,62,8,6,1,6,3,6,65,8,6,1,7,3,7,68,8,7,1,7,1,7,1,8,1,8,1,8,0,1,8,9,0,
  	2,4,6,8,10,12,14,16,0,1,2,0,6,6,8,8,75,0,23,1,0,0,0,2,31,1,0,0,0,4,33,
  	1,0,0,0,6,37,1,0,0,0,8,40,1,0,0,0,10,56,1,0,0,0,12,64,1,0,0,0,14,67,1,
  	0,0,0,16,71,1,0,0,0,18,19,3,2,1,0,19,20,5,5,0,0,20,22,1,0,0,0,21,18,1,
  	0,0,0,22,25,1,0,0,0,23,21,1,0,0,0,23,24,1,0,0,0,24,26,1,0,0,0,25,23,1,
  	0,0,0,26,27,5,0,0,1,27,1,1,0,0,0,28,32,3,4,2,0,29,32,3,6,3,0,30,32,3,
  	8,4,0,31,28,1,0,0,0,31,29,1,0,0,0,31,30,1,0,0,0,32,3,1,0,0,0,33,34,3,
  	8,4,0,34,35,5,9,0,0,35,36,5,17,0,0,36,5,1,0,0,0,37,38,3,8,4,0,38,39,5,
  	17,0,0,39,7,1,0,0,0,40,41,6,4,-1,0,41,42,3,10,5,0,42,50,1,0,0,0,43,44,
  	10,2,0,0,44,45,5,11,0,0,45,49,3,8,4,3,46,47,10,3,0,0,47,49,5,17,0,0,48,
  	43,1,0,0,0,48,46,1,0,0,0,49,52,1,0,0,0,50,48,1,0,0,0,50,51,1,0,0,0,51,
  	9,1,0,0,0,52,50,1,0,0,0,53,57,3,12,6,0,54,57,3,14,7,0,55,57,3,16,8,0,
  	56,53,1,0,0,0,56,54,1,0,0,0,56,55,1,0,0,0,57,11,1,0,0,0,58,65,5,13,0,
  	0,59,65,5,14,0,0,60,62,7,0,0,0,61,60,1,0,0,0,61,62,1,0,0,0,62,63,1,0,
  	0,0,63,65,5,15,0,0,64,58,1,0,0,0,64,59,1,0,0,0,64,61,1,0,0,0,65,13,1,
  	0,0,0,66,68,7,0,0,0,67,66,1,0,0,0,67,68,1,0,0,0,68,69,1,0,0,0,69,70,5,
  	16,0,0,70,15,1,0,0,0,71,72,5,12,0,0,72,17,1,0,0,0,8,23,31,48,50,56,61,
  	64,67
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  dorkParserStaticData = staticData.release();
}

}

DorkParser::DorkParser(TokenStream *input) : DorkParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

DorkParser::DorkParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  DorkParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *dorkParserStaticData->atn, dorkParserStaticData->decisionToDFA, dorkParserStaticData->sharedContextCache, options);
}

DorkParser::~DorkParser() {
  delete _interpreter;
}

const atn::ATN& DorkParser::getATN() const {
  return *dorkParserStaticData->atn;
}

std::string DorkParser::getGrammarFileName() const {
  return "Dork.g4";
}

const std::vector<std::string>& DorkParser::getRuleNames() const {
  return dorkParserStaticData->ruleNames;
}

const dfa::Vocabulary& DorkParser::getVocabulary() const {
  return dorkParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView DorkParser::getSerializedATN() const {
  return dorkParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

DorkParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DorkParser::ProgContext::EOF() {
  return getToken(DorkParser::EOF, 0);
}

std::vector<DorkParser::StatementContext *> DorkParser::ProgContext::statement() {
  return getRuleContexts<DorkParser::StatementContext>();
}

DorkParser::StatementContext* DorkParser::ProgContext::statement(size_t i) {
  return getRuleContext<DorkParser::StatementContext>(i);
}

std::vector<tree::TerminalNode *> DorkParser::ProgContext::DOT() {
  return getTokens(DorkParser::DOT);
}

tree::TerminalNode* DorkParser::ProgContext::DOT(size_t i) {
  return getToken(DorkParser::DOT, i);
}


size_t DorkParser::ProgContext::getRuleIndex() const {
  return DorkParser::RuleProg;
}


std::any DorkParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::ProgContext* DorkParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, DorkParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << DorkParser::PLUS)
      | (1ULL << DorkParser::MINUS)
      | (1ULL << DorkParser::STRINGLITERAL)
      | (1ULL << DorkParser::HEXNUMBER)
      | (1ULL << DorkParser::BINARYNUMBER)
      | (1ULL << DorkParser::INTEGERLITERAL)
      | (1ULL << DorkParser::FLOATLITERAL))) != 0)) {
      setState(18);
      statement();
      setState(19);
      match(DorkParser::DOT);
      setState(25);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(26);
    match(DorkParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

DorkParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DorkParser::StatementAssignContext* DorkParser::StatementContext::statementAssign() {
  return getRuleContext<DorkParser::StatementAssignContext>(0);
}

DorkParser::StatementUnaryContext* DorkParser::StatementContext::statementUnary() {
  return getRuleContext<DorkParser::StatementUnaryContext>(0);
}

DorkParser::ExprContext* DorkParser::StatementContext::expr() {
  return getRuleContext<DorkParser::ExprContext>(0);
}


size_t DorkParser::StatementContext::getRuleIndex() const {
  return DorkParser::RuleStatement;
}


std::any DorkParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::StatementContext* DorkParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, DorkParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(31);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(28);
      statementAssign();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(29);
      statementUnary();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(30);
      expr(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementAssignContext ------------------------------------------------------------------

DorkParser::StatementAssignContext::StatementAssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DorkParser::ExprContext* DorkParser::StatementAssignContext::expr() {
  return getRuleContext<DorkParser::ExprContext>(0);
}

tree::TerminalNode* DorkParser::StatementAssignContext::ASSIGN() {
  return getToken(DorkParser::ASSIGN, 0);
}

tree::TerminalNode* DorkParser::StatementAssignContext::IDENTIFIER() {
  return getToken(DorkParser::IDENTIFIER, 0);
}


size_t DorkParser::StatementAssignContext::getRuleIndex() const {
  return DorkParser::RuleStatementAssign;
}


std::any DorkParser::StatementAssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitStatementAssign(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::StatementAssignContext* DorkParser::statementAssign() {
  StatementAssignContext *_localctx = _tracker.createInstance<StatementAssignContext>(_ctx, getState());
  enterRule(_localctx, 4, DorkParser::RuleStatementAssign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    expr(0);
    setState(34);
    match(DorkParser::ASSIGN);
    setState(35);
    match(DorkParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementUnaryContext ------------------------------------------------------------------

DorkParser::StatementUnaryContext::StatementUnaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DorkParser::ExprContext* DorkParser::StatementUnaryContext::expr() {
  return getRuleContext<DorkParser::ExprContext>(0);
}

tree::TerminalNode* DorkParser::StatementUnaryContext::IDENTIFIER() {
  return getToken(DorkParser::IDENTIFIER, 0);
}


size_t DorkParser::StatementUnaryContext::getRuleIndex() const {
  return DorkParser::RuleStatementUnary;
}


std::any DorkParser::StatementUnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitStatementUnary(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::StatementUnaryContext* DorkParser::statementUnary() {
  StatementUnaryContext *_localctx = _tracker.createInstance<StatementUnaryContext>(_ctx, getState());
  enterRule(_localctx, 6, DorkParser::RuleStatementUnary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    expr(0);
    setState(38);
    match(DorkParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

DorkParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DorkParser::LiteralContext* DorkParser::ExprContext::literal() {
  return getRuleContext<DorkParser::LiteralContext>(0);
}

std::vector<DorkParser::ExprContext *> DorkParser::ExprContext::expr() {
  return getRuleContexts<DorkParser::ExprContext>();
}

DorkParser::ExprContext* DorkParser::ExprContext::expr(size_t i) {
  return getRuleContext<DorkParser::ExprContext>(i);
}

tree::TerminalNode* DorkParser::ExprContext::BINARY() {
  return getToken(DorkParser::BINARY, 0);
}

tree::TerminalNode* DorkParser::ExprContext::IDENTIFIER() {
  return getToken(DorkParser::IDENTIFIER, 0);
}


size_t DorkParser::ExprContext::getRuleIndex() const {
  return DorkParser::RuleExpr;
}


std::any DorkParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


DorkParser::ExprContext* DorkParser::expr() {
   return expr(0);
}

DorkParser::ExprContext* DorkParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  DorkParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  DorkParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, DorkParser::RuleExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(41);
    literal();
    _ctx->stop = _input->LT(-1);
    setState(50);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(48);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(43);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(44);
          match(DorkParser::BINARY);
          setState(45);
          expr(3);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(46);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(47);
          match(DorkParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(52);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

DorkParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DorkParser::IntegerLiteralContext* DorkParser::LiteralContext::integerLiteral() {
  return getRuleContext<DorkParser::IntegerLiteralContext>(0);
}

DorkParser::FloatLiteralContext* DorkParser::LiteralContext::floatLiteral() {
  return getRuleContext<DorkParser::FloatLiteralContext>(0);
}

DorkParser::StringLiteralContext* DorkParser::LiteralContext::stringLiteral() {
  return getRuleContext<DorkParser::StringLiteralContext>(0);
}


size_t DorkParser::LiteralContext::getRuleIndex() const {
  return DorkParser::RuleLiteral;
}


std::any DorkParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::LiteralContext* DorkParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 10, DorkParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(56);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(53);
      integerLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(54);
      floatLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(55);
      stringLiteral();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

DorkParser::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DorkParser::IntegerLiteralContext::HEXNUMBER() {
  return getToken(DorkParser::HEXNUMBER, 0);
}

tree::TerminalNode* DorkParser::IntegerLiteralContext::BINARYNUMBER() {
  return getToken(DorkParser::BINARYNUMBER, 0);
}

tree::TerminalNode* DorkParser::IntegerLiteralContext::INTEGERLITERAL() {
  return getToken(DorkParser::INTEGERLITERAL, 0);
}

tree::TerminalNode* DorkParser::IntegerLiteralContext::PLUS() {
  return getToken(DorkParser::PLUS, 0);
}

tree::TerminalNode* DorkParser::IntegerLiteralContext::MINUS() {
  return getToken(DorkParser::MINUS, 0);
}


size_t DorkParser::IntegerLiteralContext::getRuleIndex() const {
  return DorkParser::RuleIntegerLiteral;
}


std::any DorkParser::IntegerLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitIntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::IntegerLiteralContext* DorkParser::integerLiteral() {
  IntegerLiteralContext *_localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 12, DorkParser::RuleIntegerLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(64);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DorkParser::HEXNUMBER: {
        enterOuterAlt(_localctx, 1);
        setState(58);
        match(DorkParser::HEXNUMBER);
        break;
      }

      case DorkParser::BINARYNUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(59);
        match(DorkParser::BINARYNUMBER);
        break;
      }

      case DorkParser::PLUS:
      case DorkParser::MINUS:
      case DorkParser::INTEGERLITERAL: {
        enterOuterAlt(_localctx, 3);
        setState(61);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == DorkParser::PLUS

        || _la == DorkParser::MINUS) {
          setState(60);
          _la = _input->LA(1);
          if (!(_la == DorkParser::PLUS

          || _la == DorkParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
        }
        setState(63);
        match(DorkParser::INTEGERLITERAL);
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

//----------------- FloatLiteralContext ------------------------------------------------------------------

DorkParser::FloatLiteralContext::FloatLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DorkParser::FloatLiteralContext::FLOATLITERAL() {
  return getToken(DorkParser::FLOATLITERAL, 0);
}

tree::TerminalNode* DorkParser::FloatLiteralContext::PLUS() {
  return getToken(DorkParser::PLUS, 0);
}

tree::TerminalNode* DorkParser::FloatLiteralContext::MINUS() {
  return getToken(DorkParser::MINUS, 0);
}


size_t DorkParser::FloatLiteralContext::getRuleIndex() const {
  return DorkParser::RuleFloatLiteral;
}


std::any DorkParser::FloatLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitFloatLiteral(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::FloatLiteralContext* DorkParser::floatLiteral() {
  FloatLiteralContext *_localctx = _tracker.createInstance<FloatLiteralContext>(_ctx, getState());
  enterRule(_localctx, 14, DorkParser::RuleFloatLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DorkParser::PLUS

    || _la == DorkParser::MINUS) {
      setState(66);
      _la = _input->LA(1);
      if (!(_la == DorkParser::PLUS

      || _la == DorkParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(69);
    match(DorkParser::FLOATLITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

DorkParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DorkParser::StringLiteralContext::STRINGLITERAL() {
  return getToken(DorkParser::STRINGLITERAL, 0);
}


size_t DorkParser::StringLiteralContext::getRuleIndex() const {
  return DorkParser::RuleStringLiteral;
}


std::any DorkParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DorkVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

DorkParser::StringLiteralContext* DorkParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 16, DorkParser::RuleStringLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(DorkParser::STRINGLITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool DorkParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 4: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool DorkParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void DorkParser::initialize() {
  std::call_once(dorkParserOnceFlag, dorkParserInitialize);
}
