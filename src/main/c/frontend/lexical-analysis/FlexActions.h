#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token NoteLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ChordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token RestLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token InstrumentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ClassLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token EqualLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token BracesLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token CommaLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token DotLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token SemicolonLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token SignatureValueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ConditionalLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token RepetitionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token TranspositionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ClefValueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token PipeLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);


Token IDLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ScoreLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token TempoLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token SignatureLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ClefLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token TabsLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);


Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

#endif
