
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
      "COMMENT", "TICK", "PLING", "HASH", "DOLLAR", "COLON", "COMMA", "PERCENT", 
      "LPAREN", "RPAREN", "SOPEN", "SCLOSE", "SEMICOLON", "UNDERSCORE", 
      "DOT", "COPEN", "CCLOSE", "PLUS", "MINUS", "ASSIGN", "STRINGLITERAL", 
      "HEXNUMBER", "BINARYNUMBER", "INTEGERLITERAL", "FLOATLITERAL", "IDENTIFIER", 
      "NAME", "ALPHA", "DIGIT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "'''", "'!'", "'#'", "'$'", "':'", "','", "'%'", "'('", "')'", 
      "'['", "']'", "';'", "'_'", "'.'", "'{'", "'}'", "'+'", "'-'", "'->'"
    },
    std::vector<std::string>{
      "", "COMMENT", "TICK", "PLING", "HASH", "DOLLAR", "COLON", "COMMA", 
      "PERCENT", "LPAREN", "RPAREN", "SOPEN", "SCLOSE", "SEMICOLON", "UNDERSCORE", 
      "DOT", "COPEN", "CCLOSE", "PLUS", "MINUS", "ASSIGN", "STRINGLITERAL", 
      "HEXNUMBER", "BINARYNUMBER", "INTEGERLITERAL", "FLOATLITERAL", "IDENTIFIER", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,27,179,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,1,0,1,0,5,0,64,8,0,10,0,12,0,67,9,0,1,1,1,1,1,2,1,2,1,
  	3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,
  	1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,
  	1,18,1,19,1,19,1,19,1,20,1,20,5,20,110,8,20,10,20,12,20,113,9,20,1,20,
  	1,20,1,21,1,21,4,21,119,8,21,11,21,12,21,120,1,22,1,22,4,22,125,8,22,
  	11,22,12,22,126,1,23,4,23,130,8,23,11,23,12,23,131,1,24,5,24,135,8,24,
  	10,24,12,24,138,9,24,1,24,1,24,5,24,142,8,24,10,24,12,24,145,9,24,1,24,
  	1,24,4,24,149,8,24,11,24,12,24,150,5,24,153,8,24,10,24,12,24,156,9,24,
  	1,25,1,25,1,26,1,26,1,26,1,26,5,26,164,8,26,10,26,12,26,167,9,26,1,27,
  	1,27,1,28,1,28,1,29,4,29,174,8,29,11,29,12,29,175,1,29,1,29,0,0,30,1,
  	1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,
  	15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,
  	53,0,55,0,57,0,59,27,1,0,8,2,0,10,10,13,13,3,0,10,10,13,13,34,34,3,0,
  	48,57,65,70,97,102,2,0,48,49,124,124,3,0,69,69,101,101,124,124,1,0,48,
  	57,2,0,65,90,97,122,3,0,9,9,13,13,32,32,188,0,1,1,0,0,0,0,3,1,0,0,0,0,
  	5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,
  	0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,
  	0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,
  	1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,
  	0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,59,1,0,0,0,1,61,1,0,0,0,3,68,1,0,0,0,
  	5,70,1,0,0,0,7,72,1,0,0,0,9,74,1,0,0,0,11,76,1,0,0,0,13,78,1,0,0,0,15,
  	80,1,0,0,0,17,82,1,0,0,0,19,84,1,0,0,0,21,86,1,0,0,0,23,88,1,0,0,0,25,
  	90,1,0,0,0,27,92,1,0,0,0,29,94,1,0,0,0,31,96,1,0,0,0,33,98,1,0,0,0,35,
  	100,1,0,0,0,37,102,1,0,0,0,39,104,1,0,0,0,41,107,1,0,0,0,43,116,1,0,0,
  	0,45,122,1,0,0,0,47,129,1,0,0,0,49,136,1,0,0,0,51,157,1,0,0,0,53,159,
  	1,0,0,0,55,168,1,0,0,0,57,170,1,0,0,0,59,173,1,0,0,0,61,65,3,3,1,0,62,
  	64,8,0,0,0,63,62,1,0,0,0,64,67,1,0,0,0,65,63,1,0,0,0,65,66,1,0,0,0,66,
  	2,1,0,0,0,67,65,1,0,0,0,68,69,5,39,0,0,69,4,1,0,0,0,70,71,5,33,0,0,71,
  	6,1,0,0,0,72,73,5,35,0,0,73,8,1,0,0,0,74,75,5,36,0,0,75,10,1,0,0,0,76,
  	77,5,58,0,0,77,12,1,0,0,0,78,79,5,44,0,0,79,14,1,0,0,0,80,81,5,37,0,0,
  	81,16,1,0,0,0,82,83,5,40,0,0,83,18,1,0,0,0,84,85,5,41,0,0,85,20,1,0,0,
  	0,86,87,5,91,0,0,87,22,1,0,0,0,88,89,5,93,0,0,89,24,1,0,0,0,90,91,5,59,
  	0,0,91,26,1,0,0,0,92,93,5,95,0,0,93,28,1,0,0,0,94,95,5,46,0,0,95,30,1,
  	0,0,0,96,97,5,123,0,0,97,32,1,0,0,0,98,99,5,125,0,0,99,34,1,0,0,0,100,
  	101,5,43,0,0,101,36,1,0,0,0,102,103,5,45,0,0,103,38,1,0,0,0,104,105,5,
  	45,0,0,105,106,5,62,0,0,106,40,1,0,0,0,107,111,5,34,0,0,108,110,8,1,0,
  	0,109,108,1,0,0,0,110,113,1,0,0,0,111,109,1,0,0,0,111,112,1,0,0,0,112,
  	114,1,0,0,0,113,111,1,0,0,0,114,115,5,34,0,0,115,42,1,0,0,0,116,118,5,
  	38,0,0,117,119,7,2,0,0,118,117,1,0,0,0,119,120,1,0,0,0,120,118,1,0,0,
  	0,120,121,1,0,0,0,121,44,1,0,0,0,122,124,3,15,7,0,123,125,7,3,0,0,124,
  	123,1,0,0,0,125,126,1,0,0,0,126,124,1,0,0,0,126,127,1,0,0,0,127,46,1,
  	0,0,0,128,130,3,57,28,0,129,128,1,0,0,0,130,131,1,0,0,0,131,129,1,0,0,
  	0,131,132,1,0,0,0,132,48,1,0,0,0,133,135,3,57,28,0,134,133,1,0,0,0,135,
  	138,1,0,0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,139,1,0,0,0,138,136,1,
  	0,0,0,139,143,5,46,0,0,140,142,3,57,28,0,141,140,1,0,0,0,142,145,1,0,
  	0,0,143,141,1,0,0,0,143,144,1,0,0,0,144,154,1,0,0,0,145,143,1,0,0,0,146,
  	148,7,4,0,0,147,149,7,5,0,0,148,147,1,0,0,0,149,150,1,0,0,0,150,148,1,
  	0,0,0,150,151,1,0,0,0,151,153,1,0,0,0,152,146,1,0,0,0,153,156,1,0,0,0,
  	154,152,1,0,0,0,154,155,1,0,0,0,155,50,1,0,0,0,156,154,1,0,0,0,157,158,
  	3,53,26,0,158,52,1,0,0,0,159,165,3,55,27,0,160,164,3,55,27,0,161,164,
  	3,57,28,0,162,164,3,27,13,0,163,160,1,0,0,0,163,161,1,0,0,0,163,162,1,
  	0,0,0,164,167,1,0,0,0,165,163,1,0,0,0,165,166,1,0,0,0,166,54,1,0,0,0,
  	167,165,1,0,0,0,168,169,7,6,0,0,169,56,1,0,0,0,170,171,7,5,0,0,171,58,
  	1,0,0,0,172,174,7,7,0,0,173,172,1,0,0,0,174,175,1,0,0,0,175,173,1,0,0,
  	0,175,176,1,0,0,0,176,177,1,0,0,0,177,178,6,29,0,0,178,60,1,0,0,0,13,
  	0,65,111,120,126,131,136,143,150,154,163,165,175,1,0,1,0
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
