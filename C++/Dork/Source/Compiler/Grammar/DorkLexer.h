
// Generated from Dork.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  DorkLexer : public antlr4::Lexer {
public:
  enum {
    COMMENT = 1, TICK = 2, PLING = 3, HASH = 4, DOLLAR = 5, COLON = 6, COMMA = 7, 
    PERCENT = 8, LPAREN = 9, RPAREN = 10, SOPEN = 11, SCLOSE = 12, SEMICOLON = 13, 
    UNDERSCORE = 14, DOT = 15, COPEN = 16, CCLOSE = 17, PLUS = 18, MINUS = 19, 
    ASSIGN = 20, STRINGLITERAL = 21, HEXNUMBER = 22, BINARYNUMBER = 23, 
    INTEGERLITERAL = 24, FLOATLITERAL = 25, IDENTIFIER = 26, WS = 27
  };

  explicit DorkLexer(antlr4::CharStream *input);

  ~DorkLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

