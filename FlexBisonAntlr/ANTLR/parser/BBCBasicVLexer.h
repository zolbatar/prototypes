
// Generated from BBCBasicV.g by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  BBCBasicVLexer : public antlr4::Lexer {
public:
  enum {
    DOLLAR = 1, PERCENT = 2, COLON = 3, AMPERSAND = 4, IF = 5, REM = 6, 
    END = 7, RETURN = 8, THEN = 9, NOT = 10, AND = 11, OR = 12, EQ = 13, 
    GTE = 14, LTE = 15, GT = 16, LT = 17, LPAREN = 18, RPAREN = 19, PLUS = 20, 
    MINUS = 21, TIMES = 22, DIV = 23, COMMA = 24, EXPONENT = 25, COMMENT = 26, 
    STRINGLITERAL = 27, LETTERS = 28, NUMBER = 29, FLOAT = 30, WS = 31
  };

  BBCBasicVLexer(antlr4::CharStream *input);
  ~BBCBasicVLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

