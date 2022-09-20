
// Generated from Dork.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  DorkLexer : public antlr4::Lexer {
public:
  enum {
    COMMENT = 1, TICK = 2, SEMICOLON = 3, UNDERSCORE = 4, DOT = 5, PLUS = 6, 
    PERCENT = 7, MINUS = 8, ASSIGN = 9, BINARYPART = 10, BINARY = 11, STRINGLITERAL = 12, 
    HEXNUMBER = 13, BINARYNUMBER = 14, INTEGERLITERAL = 15, FLOATLITERAL = 16, 
    IDENTIFIER = 17, WS = 18
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

