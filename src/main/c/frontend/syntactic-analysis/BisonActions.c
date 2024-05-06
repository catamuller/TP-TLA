#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

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
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->expression = expression;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	} else {
		compilerState->succeed = true;
	}
	return program;
}

Program * AssignmentProgramSemanticAction(CompilerState * compilerState, assignment * _assignment) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->assignment = _assignment;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	} else {
		compilerState->succeed = true;
	}
	return program;
}

//aca empieza nuestro codigo :D
Program * ProgramSemanticAction(assignment * _assignment) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->assignment = _assignment;
	return program;
}

assignment * AssignmentSemanticAction(type * _type, char * id, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	assignment * toReturn = calloc(1, sizeof(assignment));
	toReturn->id = id;
	toReturn->expression = expression;
	toReturn->class = _type;
	return toReturn;
}

type * TypeSemanticAction(Class class) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	type * _type = calloc(1, sizeof(type));
	_type->class = class;
	return _type;
}

noteExpression * noteExpressionSemanticAction(note * _note, int pitch, instrument * instrument) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	noteExpression * note_expression = calloc(1, sizeof(noteExpression));
	note_expression->_note = _note;
	note_expression->pitch = pitch;
	note_expression->_instrument = instrument;
	return note_expression;
}

note * NoteSemanticAction(Note _note) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	note * toReturn = calloc(1, sizeof(note));
	toReturn->note = _note;
	return toReturn;
}

id * IDSemanticAction(IDM _id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	id * toReturn = calloc(1, sizeof(id));
	toReturn->id = _id;
	return toReturn;
}

chord * ChordSemanticAction(Chord _chord) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	chord * toReturn = calloc(1, sizeof(chord));
	toReturn->chord = _chord;
	return toReturn;
}

instrument * InstrumentSemanticAction(Instrument _instrument) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	instrument * toReturn = calloc(1, sizeof(instrument));
	toReturn->instrument = _instrument;
	return toReturn;
}

scoreExpression * ScoreExpressionSemanticAction(instrument * _instrument, sentences * _sentences) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	scoreExpression * score_expression = calloc(1, sizeof(scoreExpression));
	score_expression->instrument = _instrument;
	score_expression->_sentences = _sentences;
	return score_expression;
}

clefSentence * clefSentenceSemanticAction(clef * _clef) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	clefSentence * toReturn = calloc(1, sizeof(clefSentence));
	toReturn->_clef = _clef;
	return toReturn;
}

Expression * expressionScoreExpressionSemanticAction(scoreExpression * _scoreExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * toReturn = calloc(1, sizeof(Expression));
	toReturn->scoreExpression = _scoreExpression;
	return toReturn;
}

Expression * expressionNoteExpressionSemanticAction(noteExpression * _noteExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * toReturn = calloc(1, sizeof(Expression));
	toReturn->noteExpression = _noteExpression;
	return toReturn;
}

clef * clefSemanticAction(Clef _clef) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	clef * toReturn = calloc(1, sizeof(clef));
	toReturn->clef = _clef;
	return toReturn;
}

tabsSentence * tabsSentenceSemanticAction(tabs * _tabs){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabs * toReturn = calloc(1, sizeof(tabs));
	toReturn->_tabs = _tabs;
	return toReturn;
}

tabs * tabsPipeSemanticAction(tab * _tab, tabs * _tabs) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabs * toReturn = calloc(1, sizeof(tabs));
	toReturn->_tab_ = _tab;
	toReturn->_tabs = _tabs;
	return toReturn;
}

tabs * tabsTabSemanticAction(tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabs * toReturn = calloc(1, sizeof(tabs));
	toReturn->_tab = _tab;
	return toReturn;
}

tab * tabNoteTabSemanticAction(note * _note, tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tab * toReturn = calloc(1, sizeof(tab));
	toReturn->_note = _note;
	toReturn->_tab = _tab;
	return toReturn;
}

tab * tabChordTabSemanticAction(chord * _chord, tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tab * toReturn = calloc(1, sizeof(tab));
	toReturn->_chord = _chord;
	toReturn->_tab = _tab;
	return toReturn;
}

tab * tabRestTabSemanticAction(rest * _rest, tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tab * toReturn = calloc(1, sizeof(tab));
	toReturn->_rest = _rest;
	toReturn->_tab = _tab;
	return toReturn;
}


sentences * sentencesSentenceSentencesSemanticAction(sentence * param_sentence,sentences * param_sentences, SentencesType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	sentences * toReturn = calloc(1, sizeof(sentences));
	toReturn -> _sentences = param_sentences;
	toReturn -> _sentence_ = param_sentence;
	toReturn -> sentencesType = type;
	return toReturn;
}

sentences * sentencesSentenceSemanticAction(sentence * param_sentence, SentencesType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	sentences * toReturn = calloc(1, sizeof(sentences));
	toReturn -> _sentence = param_sentence;
	toReturn -> sentencesType = type;
	return toReturn;
}
