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

Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

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

//aca empieza nuestro codigo :D
Program * ProgramSemanticAction(Assignment * assignment) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	Program->assignment = assignment;
	factor->type = EXPRESSION;
	return factor;
}

Assignment * AssignmentSemanticAction(Type type, char * id, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Assignment * assignment = calloc(1, sizeof(Assignment));
	assignment->id = id;
	assignment->expression = expression;
	assignment->type = type;
	return assignment;
}

Type * TypeSemanticAction(Class class) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Type * type = calloc(1, sizeof(Type));
	type->class = class;
	return type;
}

noteExpression * noteExpressionSemanticAction(Note note, int pitch, Instrument instrument) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	noteExpression * note_expression = calloc(1, sizeof(noteExpression));
	note_expression->note = note;
	note_expression->pitch = pitch;
	note_expression->instrument = instrument;
	return noteExpression;
}

Note * NoteSemanticAction(Note note) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Note * note = calloc(1, sizeof(Note));
	note -> note = note;
	return note;
}

Chord * ChordSemanticAction(Chord chord) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Chord * chord = calloc(1, sizeof(Chord));
	chord -> chord = chord;
	return chord;
}

Instrument * InstrumentSemanticAction(Instrument instrument) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Instrument * instrument = calloc(1, sizeof(Instrument));
	instrument -> instrument = instrument;
	return instrument;
}

scoreExpression * InstrumentSemanticAction(Instrument instrument, sentences sentences) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	scoreExpression * score_expression = calloc(1, sizeof(scoreExpression));
	score_expression->instrument = instrument;
	score_expression->sentences = sentences;
	return score_expression;
}

sentences * sentencesSemanticAction(sentences _sentences) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	sentence * _sentences = calloc(1, sizeof(_sentences));
	_sentences -> _sentences = _sentences;

	return sentences;
}