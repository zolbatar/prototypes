
// Generated from Dork.g4 by ANTLR 4.10.1


#include "DorkLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct DorkLexerStaticData final {
  DorkLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  DorkLexerStaticData(const DorkLexerStaticData&) = delete;
  DorkLexerStaticData(DorkLexerStaticData&&) = delete;
  DorkLexerStaticData& operator=(const DorkLexerStaticData&) = delete;
  DorkLexerStaticData& operator=(DorkLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag dorklexerLexerOnceFlag;
DorkLexerStaticData *dorklexerLexerStaticData = nullptr;

void dorklexerLexerInitialize() {
  assert(dorklexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<DorkLexerStaticData>(
    std::vector<std::string>{
      "COMMENT", "TICK", "SEMICOLON", "UNDERSCORE", "DOT", "PLUS", "PERCENT", 
      "MINUS", "ASSIGN", "BINARYPART", "BINARY", "STRINGLITERAL", "HEXNUMBER", 
      "BINARYNUMBER", "INTEGERLITERAL", "FLOATLITERAL", "IDENTIFIER", "NAME", 
      "ALPHA", "DIGIT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,18,145,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,
  	1,0,5,0,46,8,0,10,0,12,0,49,9,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,
  	5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,9,1,9,1,10,1,10,3,10,72,8,10,1,11,1,11,
  	5,11,76,8,11,10,11,12,11,79,9,11,1,11,1,11,1,12,1,12,4,12,85,8,12,11,
  	12,12,12,86,1,13,1,13,4,13,91,8,13,11,13,12,13,92,1,14,4,14,96,8,14,11,
  	14,12,14,97,1,15,5,15,101,8,15,10,15,12,15,104,9,15,1,15,1,15,5,15,108,
  	8,15,10,15,12,15,111,9,15,1,15,1,15,4,15,115,8,15,11,15,12,15,116,5,15,
  	119,8,15,10,15,12,15,122,9,15,1,16,1,16,1,17,1,17,1,17,1,17,5,17,130,
  	8,17,10,17,12,17,133,9,17,1,18,1,18,1,19,1,19,1,20,4,20,140,8,20,11,20,
  	12,20,141,1,20,1,20,0,0,21,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,
  	10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,0,37,0,39,0,41,18,1,0,
  	9,2,0,10,10,13,13,8,0,33,33,37,38,42,45,47,47,60,64,92,92,124,124,126,
  	126,3,0,10,10,13,13,34,34,3,0,48,57,65,70,97,102,2,0,48,49,124,124,3,
  	0,69,69,101,101,124,124,1,0,48,57,2,0,65,90,97,122,3,0,9,9,13,13,32,32,
  	155,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,
  	1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,
  	0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,
  	0,33,1,0,0,0,0,41,1,0,0,0,1,43,1,0,0,0,3,50,1,0,0,0,5,52,1,0,0,0,7,54,
  	1,0,0,0,9,56,1,0,0,0,11,58,1,0,0,0,13,60,1,0,0,0,15,62,1,0,0,0,17,64,
  	1,0,0,0,19,67,1,0,0,0,21,69,1,0,0,0,23,73,1,0,0,0,25,82,1,0,0,0,27,88,
  	1,0,0,0,29,95,1,0,0,0,31,102,1,0,0,0,33,123,1,0,0,0,35,125,1,0,0,0,37,
  	134,1,0,0,0,39,136,1,0,0,0,41,139,1,0,0,0,43,47,3,3,1,0,44,46,8,0,0,0,
  	45,44,1,0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,2,1,0,0,0,
  	49,47,1,0,0,0,50,51,5,39,0,0,51,4,1,0,0,0,52,53,5,59,0,0,53,6,1,0,0,0,
  	54,55,5,95,0,0,55,8,1,0,0,0,56,57,5,46,0,0,57,10,1,0,0,0,58,59,5,43,0,
  	0,59,12,1,0,0,0,60,61,5,37,0,0,61,14,1,0,0,0,62,63,5,45,0,0,63,16,1,0,
  	0,0,64,65,5,45,0,0,65,66,5,62,0,0,66,18,1,0,0,0,67,68,7,1,0,0,68,20,1,
  	0,0,0,69,71,3,19,9,0,70,72,3,19,9,0,71,70,1,0,0,0,71,72,1,0,0,0,72,22,
  	1,0,0,0,73,77,5,34,0,0,74,76,8,2,0,0,75,74,1,0,0,0,76,79,1,0,0,0,77,75,
  	1,0,0,0,77,78,1,0,0,0,78,80,1,0,0,0,79,77,1,0,0,0,80,81,5,34,0,0,81,24,
  	1,0,0,0,82,84,5,38,0,0,83,85,7,3,0,0,84,83,1,0,0,0,85,86,1,0,0,0,86,84,
  	1,0,0,0,86,87,1,0,0,0,87,26,1,0,0,0,88,90,3,13,6,0,89,91,7,4,0,0,90,89,
  	1,0,0,0,91,92,1,0,0,0,92,90,1,0,0,0,92,93,1,0,0,0,93,28,1,0,0,0,94,96,
  	3,39,19,0,95,94,1,0,0,0,96,97,1,0,0,0,97,95,1,0,0,0,97,98,1,0,0,0,98,
  	30,1,0,0,0,99,101,3,39,19,0,100,99,1,0,0,0,101,104,1,0,0,0,102,100,1,
  	0,0,0,102,103,1,0,0,0,103,105,1,0,0,0,104,102,1,0,0,0,105,109,5,46,0,
  	0,106,108,3,39,19,0,107,106,1,0,0,0,108,111,1,0,0,0,109,107,1,0,0,0,109,
  	110,1,0,0,0,110,120,1,0,0,0,111,109,1,0,0,0,112,114,7,5,0,0,113,115,7,
  	6,0,0,114,113,1,0,0,0,115,116,1,0,0,0,116,114,1,0,0,0,116,117,1,0,0,0,
  	117,119,1,0,0,0,118,112,1,0,0,0,119,122,1,0,0,0,120,118,1,0,0,0,120,121,
  	1,0,0,0,121,32,1,0,0,0,122,120,1,0,0,0,123,124,3,35,17,0,124,34,1,0,0,
  	0,125,131,3,37,18,0,126,130,3,37,18,0,127,130,3,39,19,0,128,130,3,7,3,
  	0,129,126,1,0,0,0,129,127,1,0,0,0,129,128,1,0,0,0,130,133,1,0,0,0,131,
  	129,1,0,0,0,131,132,1,0,0,0,132,36,1,0,0,0,133,131,1,0,0,0,134,135,7,
  	7,0,0,135,38,1,0,0,0,136,137,7,6,0,0,137,40,1,0,0,0,138,140,7,8,0,0,139,
  	138,1,0,0,0,140,141,1,0,0,0,141,139,1,0,0,0,141,142,1,0,0,0,142,143,1,
  	0,0,0,143,144,6,20,0,0,144,42,1,0,0,0,14,0,47,71,77,86,92,97,102,109,
  	116,120,129,131,141,1,0,1,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  dorklexerLexerStaticData = staticData.release();
}

}

DorkLexer::DorkLexer(CharStream *input) : Lexer(input) {
  DorkLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *dorklexerLexerStaticData->atn, dorklexerLexerStaticData->decisionToDFA, dorklexerLexerStaticData->sharedContextCache);
}

DorkLexer::~DorkLexer() {
  delete _interpreter;
}

std::string DorkLexer::getGrammarFileName() const {
  return "Dork.g4";
}

const std::vector<std::string>& DorkLexer::getRuleNames() const {
  return dorklexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& DorkLexer::getChannelNames() const {
  return dorklexerLexerStaticData->channelNames;
}

const std::vector<std::string>& DorkLexer::getModeNames() const {
  return dorklexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& DorkLexer::getVocabulary() const {
  return dorklexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView DorkLexer::getSerializedATN() const {
  return dorklexerLexerStaticData->serializedATN;
}

const atn::ATN& DorkLexer::getATN() const {
  return *dorklexerLexerStaticData->atn;
}




void DorkLexer::initialize() {
  std::call_once(dorklexerLexerOnceFlag, dorklexerLexerInitialize);
}
