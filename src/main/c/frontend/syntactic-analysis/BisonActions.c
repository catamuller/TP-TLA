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
Program * ExpressionsProgramSemanticAction(CompilerState * compilerState, expressions * _expressions) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->_expressions = _expressions;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	} else {
		compilerState->succeed = true;
	}
	return program;
}
/**
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
*/
/**
Program * ProgramSemanticAction(assignment * _assignment) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->assignment = _assignment;
	return program;
}
*/

assignment * AssignmentSemanticAction(type * _type, id * id, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	assignment * toReturn = calloc(1, sizeof(assignment));
	toReturn->_id = id;
	toReturn->expression = expression;
	toReturn->_class = _type;
	return toReturn;
}

chordExpression * chordExpressionSemanticAction(chordValues * _chordValues) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	chordExpression * toReturn = calloc(1, sizeof(chordExpression));
	toReturn->_chordValues = _chordValues;
	return toReturn;
}

chordValues * chordValuesChordValuesSemanticAction(note * _note, chordValues * _chordValues) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	chordValues * toReturn = calloc(1, sizeof(chordValues));
	toReturn->_chordValues = _chordValues;
	toReturn->_note = _note;
	return toReturn;
}

chordValues * chordValuesNoteSemanticAction(note * note_) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	chordValues * toReturn = calloc(1, sizeof(chordValues));
	toReturn->note_ = note_;
	return toReturn;
}

expressions * ExpressionsProgramExpressionExpressionsSemanticAction(programExpression * _programExpression, expressions * _expressions) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	expressions * toReturn = calloc(1, sizeof(expressions));
	toReturn->expressions = _expressions;
	toReturn->_programExpression = _programExpression;
	return toReturn;
}

expressions * ExpressionsProgramExpressionSemanticAction(programExpression * _programExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	expressions * toReturn = calloc(1, sizeof(expressions));
	toReturn->programExpression_ = _programExpression;
	return toReturn;
}

programExpression * ProgramExpressionAssignmentSemanticAction(assignment * _assignment) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	programExpression * toReturn = calloc(1, sizeof(programExpression));
	toReturn->assignment = _assignment;
	toReturn->type = ASSIGNMENT;
	return toReturn;
}

programExpression * ProgramExpressionExpressionSemanticAction(Expression * _expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	programExpression * toReturn = calloc(1, sizeof(programExpression));
	toReturn->expression = _expression;
	toReturn->type = EXPRESSION;
	return toReturn;
}


type * TypeSemanticAction(Class class) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	type * _type = calloc(1, sizeof(type));
	_type->class = class;
	return _type;
}

noteExpression * noteExpressionSemanticAction(note * _note, pitch * _pitch, instrument * instrument) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	noteExpression * note_expression = calloc(1, sizeof(noteExpression));
	note_expression->_note = _note;
	note_expression->_pitch = _pitch;
	note_expression->_instrument = instrument;
	return note_expression;
}

declaration * DeclarationSemanticAction(tempo * _tempo, signature * _signature) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	declaration * declaration = calloc(1, sizeof(declaration));
	declaration->_tempo = _tempo;
	declaration->_signature = _signature;
	return declaration;
}

score * scoreSemanticAction(id * _id, scoreExpression * _scoreExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	score * _score = calloc(1, sizeof(score));
	_score->_id = _id;
	_score->scoreExpression = _scoreExpression;
	return _score;
}

tempo * tempoSemanticAction(Integer _tempo) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tempo * tempoT = calloc(1, sizeof(tempo));
	tempoT->tempo = _tempo;
	return tempoT;
}

signature * signatureSemanticAction(Signature signature_) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	signature * _signature = calloc(1, sizeof(signature));
	_signature->signature = signature_;
	return _signature;
}

note * NoteSemanticAction(Note _note) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	note * toReturn = calloc(1, sizeof(note));
	toReturn->note = _note;
	return toReturn;
}

pitch * PitchSemanticAction(Integer _pitch) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	pitch * toReturn = calloc(1, sizeof(pitch));
	toReturn->_pitch = _pitch;
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

scoreExpression * ScoreExpressionSemanticAction(declaration * _declaration, instrument * _instrument, sentences * _sentences) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	scoreExpression * score_expression = calloc(1, sizeof(scoreExpression));
	score_expression->_declaration = _declaration;
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

Expression * expressionNoteExpresionSemanticAction(noteExpression * _noteExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * toReturn = calloc(1, sizeof(Expression));
	toReturn->noteExpression = _noteExpression;
	toReturn->type = NOTEEXPRESSION;
	return toReturn;
}

Expression * expressionScoreExpressionSemanticAction(score * _scoreExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * toReturn = calloc(1, sizeof(Expression));
	toReturn->_score = _scoreExpression;
	toReturn->type = SCOREEXPRESSION;
	return toReturn;
}

Expression * expressionChordExpressionSemanticAction(chordExpression * _chordExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * toReturn = calloc(1, sizeof(Expression));
	toReturn->_chordExpression = _chordExpression;
	toReturn->type = CHORDEXPRESSION;
	return toReturn;
}

Expression * expressionTabExpression(tabExpression * _tabExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * toReturn = calloc(1, sizeof(Expression));
	toReturn->_tabExpression = _tabExpression;
	toReturn->type = TABEXPRESSIONTYPE;
	return toReturn;
}

tabExpression * tabExpressionSemanticAction(tabValues * _tabValues) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabExpression * toReturn = calloc(1, sizeof(tabExpression));
	toReturn->_tabValues = _tabValues;
	return toReturn;
}

Expression * expressionPitchSemanticAction(pitch * _pitch) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * toReturn = calloc(1, sizeof(Expression));
	toReturn->_pitch = _pitch;
	toReturn->type = PITCHEXPRESSION;
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
	tabsSentence * toReturn = calloc(1, sizeof(tabsSentence));
	toReturn->_tabs = _tabs;
	return toReturn;
}

sentence * sentenceTabsSentenceSemanticAction(tabsSentence * _tabsSentence) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	sentence * toReturn = calloc(1, sizeof(sentence));
	toReturn->_tabsSentence = _tabsSentence;
	toReturn->sentenceType = TABSSENTENCE;	//el tipo sirve para hacer el free luego
	return toReturn;
}


sentence * sentenceClefSentenceSemanticAction(clefSentence * _clefSentence) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	sentence * toReturn = calloc(1, sizeof(sentence));
	toReturn->_clefSentence = _clefSentence;
	toReturn->sentenceType = CLEFSENTENCE;
	return toReturn;
}

tabs * tabsPipeSemanticAction(tab * _tab, tabs * _tabs) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabs * toReturn = calloc(1, sizeof(tabs));
	toReturn->_tab_ = _tab;
	toReturn->_tabs = _tabs;
	toReturn->tabsType = TABSTYPE;	//para el free luego
	return toReturn;
}

tabs * tabsTabSemanticAction(tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabs * toReturn = calloc(1, sizeof(tabs));
	toReturn->_tab = _tab;
	toReturn->tabsType = TABTYPE;	//para el free luego ;D
	return toReturn;
}

tab * tabNoteTabSemanticAction(note * _note, tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tab * toReturn = calloc(1, sizeof(tab));
	toReturn->_note = _note;
	toReturn->_tab = _tab;			//ciudado que puede ser NULL
	toReturn->tabType = NOTETYPE;
	return toReturn;
}

tab * tabChordTabSemanticAction(chord * _chord, tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tab * toReturn = calloc(1, sizeof(tab));
	toReturn->_chord = _chord;
	toReturn->_tab = _tab;			//cuidado!!! puede ser null
	toReturn->tabType = CHORDTYPE;
	return toReturn;
}

tab * tabRestTabSemanticAction(rest * _rest, tab * _tab) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tab * toReturn = calloc(1, sizeof(tab));
	toReturn->_rest = _rest;
	toReturn->_tab = _tab;			
	toReturn->tabType = NOTETYPE;
	return toReturn;
}

sentences * sentencesSentenceSentencesSemanticAction(sentence * param_sentence,sentences * param_sentences, int type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	sentences * toReturn = calloc(1, sizeof(sentences));
	toReturn -> _sentences = param_sentences;
	toReturn -> _sentence_ = param_sentence;
	toReturn -> sentencesType = type;
	return toReturn;
}

rest * restSemanticAction(Rest _rest) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	rest * toReturn = calloc(1, sizeof(rest));
	toReturn->rest = _rest;
	return toReturn;
}

sentences * sentencesSentenceSemanticAction(sentence * param_sentence, SentencesType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	sentences * toReturn = calloc(1, sizeof(sentences));
	toReturn -> _sentence = param_sentence;
	toReturn -> sentencesType = type;
	return toReturn;
}

tabValues * tabValuesNoteTabValuesSemanticAction(note * _note, tabValues * _tabValues) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabValues * toReturn = calloc(1, sizeof(tabValues));
	toReturn -> _note = _note;
	toReturn -> _tabValues = _tabValues;
	if(_tabValues!=NULL){
		toReturn -> type = NOTETABVALUES;
	}
	else{
		toReturn -> type = TABVALUESNOTE;
	}
	return toReturn;
}
tabValues * tabValuesChordTabValuesSemanticAction(chord * _chord, tabValues * _tabValues) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabValues * toReturn = calloc(1, sizeof(tabValues));
	toReturn -> _chord = _chord;
	toReturn -> _tabValues = _tabValues;
	if(_tabValues!=NULL){
		toReturn -> type = CHORDTABVALUES;
	}
	else{
		toReturn -> type = TABVALUESCHORD;
	}	
	return toReturn;
}
tabValues * tabValuesRestTabValuesSemanticAction(rest * _rest, tabValues * _tabValues) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tabValues * toReturn = calloc(1, sizeof(tabValues));
	toReturn -> _rest = _rest;
	toReturn -> _tabValues = _tabValues;
	if(_tabValues!=NULL){
		toReturn -> type = RESTTABVALUES;
	}
	else{
		toReturn -> type = TABVALUESREST;
	}
	return toReturn;
}
