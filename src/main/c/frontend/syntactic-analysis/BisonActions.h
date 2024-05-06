#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

/*
Constant * IntegerConstantSemanticAction(const int value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);
*/

// Constant * IntegerConstantSemanticAction(const int value) {
// 	_logSyntacticAnalyzerAction(__FUNCTION__);
// 	Constant * constant = calloc(1, sizeof(Constant));
// 	constant->value = value;
// 	return constant;
// }
// 
// 
// Expression * FactorExpressionSemanticAction(Factor * factor) {
// 	_logSyntacticAnalyzerAction(__FUNCTION__);
// 	Expression * expression = calloc(1, sizeof(Expression));
// 	expression->factor = factor;
// 	expression->type = FACTOR;
// 	return expression;
// }

/*
Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}
*/
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);

Program * AssignmentProgramSemanticAction(CompilerState * compilerState, assignment * _assignment);

//aca empieza nuestro codigo :D
Program * ProgramSemanticAction(assignment * _assignment);

Expression * expressionNoteExpresionSemanticAction(noteExpression * _noteExpression);

assignment * AssignmentSemanticAction(type * _type, id * _id, Expression * expression);

type * TypeSemanticAction(Class class);

noteExpression * noteExpressionSemanticAction(note * _note, int pitch, instrument * instrument);

note * NoteSemanticAction(Note _note);

id * IDSemanticAction(IDM _id);

chord * ChordSemanticAction(Chord _chord);

instrument * InstrumentSemanticAction(Instrument _instrument);

scoreExpression * ScoreExpressionSemanticAction(declaration * _declaration, instrument * _instrument, sentences * _sentences);

Expression * expressionNoteExpressionSemanticAction(noteExpression * _noteExpression);

Expression * expressionScoreExpressionSemanticAction(score * _scoreExpression);

clefSentence * clefSentenceSemanticAction(clef * _clef);

clef * clefSemanticAction(Clef _clef);

tabsSentence * tabsSentenceSemanticAction(tabs * _tabs);

tabs * tabsPipeSemanticAction(tab * _tab, tabs * _tabs);

tabs * tabsTabSemanticAction(tab * _tab);

tab * tabNoteTabSemanticAction(note * _note, tab * _tab);

tab * tabChordTabSemanticAction(chord * _chord, tab * _tab);

tab * tabRestTabSemanticAction(rest * _rest, tab * _tab);

sentence * sentenceClefSentenceSemanticAction(clefSentence * _clefSentence);

sentence * sentenceTabsSentenceSemanticAction(tabsSentence * _tabsSentence);

sentences * sentencesSentenceSentencesSemanticAction(sentence * param_sentence,sentences * param_sentences, SentencesType type);

sentences * sentencesSemanticAction(sentence * param_sentence, SentencesType type);

#endif
