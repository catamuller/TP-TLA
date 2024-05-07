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

/**
Constant * IntegerConstantSemanticAction(const int value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);


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
*/
/**
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

Program * ExpressionsProgramSemanticAction(CompilerState * compilerState, expressions * expressions);

Expression * expressionChordExpressionSemanticAction(chordExpression * _chordExpression);

chordExpression * chordExpressionSemanticAction(chordValues * _chordValues);

chordValues * chordValuesChordValuesSemanticAction(note * _note, chordValues * _chordValues);

expressions * ExpressionsProgramExpressionExpressionsSemanticAction(programExpression * _programExpression, expressions * _expressions);

expressions * ExpressionsProgramExpressionSemanticAction(programExpression * _programExpression);

programExpression * ProgramExpressionAssignmentSemanticAction(assignment * _assignment);

programExpression * ProgramExpressionExpressionSemanticAction(Expression * _expression);

Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);

Program * AssignmentProgramSemanticAction(CompilerState * compilerState, assignment * _assignment);

//aca empieza nuestro codigo :D
Program * ProgramSemanticAction(assignment * _assignment);

Expression * expressionNoteExpresionSemanticAction(noteExpression * _noteExpression);

pitch * PitchSemanticAction(Integer _pitch);

assignment * AssignmentSemanticAction(type * _type, id * _id, Expression * expression);

type * TypeSemanticAction(Class class);

noteExpression * noteExpressionSemanticAction(note * _note, pitch * pitch, instrument * instrument);

declaration * DeclarationSemanticAction(tempo * _tempo, signature * _signature);

scoreExpressions * scoreExpressionsScoreExpressionsScoreExpressionSemanticAction(scoreExpression * _scoreExpression, scoreExpressions * _scoreExpressions);

scoreExpressions * scoreExpressionsScoreExpressionSemanticAction(scoreExpression * _scoreExpression);

score * scoreSemanticAction(id * _id, scoreExpressions * _scoreExpressions, transpose * _transposition);

transpose * transposeSemanticAction(int transposition);

tempo * tempoSemanticAction(Integer _tempo);

signature * signatureSemanticAction(Signature signature_);

note * NoteSemanticAction(Note _note);

id * IDSemanticAction(IDM _id);

chord * ChordSemanticAction(Chord _chord);

instrument * InstrumentSemanticAction(Instrument _instrument);

scoreExpression * ScoreExpressionSemanticAction(declaration * _declaration, instruments * _instruments);

Expression * expressionNoteExpressionSemanticAction(noteExpression * _noteExpression);

chordValues * chordValuesNoteSemanticAction(note * note_);

Expression * expressionPitchSemanticAction(pitch * _pitch);

tabExpression * tabExpressionSemanticAction(tabValues * _tabValues);

tabValues * tabValuesNoteTabValuesSemanticAction(note * _note, tabValues * _tabValues);

tabValues * tabValuesChordTabValuesSemanticAction(chord * _chord, tabValues * _tabValues);

tabValues * tabValuesRestTabValuesSemanticAction(rest * _rest, tabValues * _tabValues);

Expression * expressionTabExpression(tabExpression * _tabExpression);

Expression * expressionScoreExpressionSemanticAction(score * _scoreExpression);

instruments * instrumentsInstrumentInstrumentsSemanticAction(instrument * _instrument, clefDeclaration * _clefDeclaration, instruments * _instruments);

clefDeclaration * clefDeclarationSemanticAction(clefSentence * _clefSentence, sentences * _sentences);

clefSentence * clefSentenceSemanticAction(clef * _clef);

control * controlSemanticAction(repeat * _repeat, control * _control);

repeat * repeatSemanticAction(Integer _repeat);

clef * clefSemanticAction(Clef _clef);

tabsSentence * tabsSentenceSemanticAction(id * _id, tabs * _tabs, control * _control);

tabs * tabsPipeSemanticAction(tab * _tab, tabs * _tabs);

tabs * tabsTabSemanticAction(tab * _tab);

tab * tabNoteTabSemanticAction(note * _note, tab * _tab);

tab * tabChordTabSemanticAction(chord * _chord, tab * _tab);

tab * tabRestTabSemanticAction(rest * _rest, tab * _tab);

sentence * sentenceClefSentenceSemanticAction(clefSentence * _clefSentence);

sentence * sentenceTabsSentenceSemanticAction(tabsSentence * _tabsSentence);

sentences * sentencesSentenceSentencesSemanticAction(sentence * param_sentence,sentences * param_sentences, int type);

sentences * sentencesSentenceSemanticAction(sentence * param_sentence, SentencesType type);

rest * restSemanticAction(Rest _rest);

#endif
