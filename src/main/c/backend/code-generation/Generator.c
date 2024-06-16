#include "Generator.h"



/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;
FILE * file = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
	file = stdout;//fopen("output.txt", "w");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
		fclose(file);
	}
}

void removeSpaces(char *str) {
    int count = 0;
     for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}

/** PRIVATE FUNCTIONS */

static void _generateType(const unsigned int indentationLevel, type * type);

static void _generateId(const unsigned int indentationLevel, id * id);

static void _generateNote(const unsigned int indentationLevel, note * note, IDM id);

static void _generateNoteExpression(const unsigned int indentationLevel, noteExpression * noteExpression, IDM id);

static void _generateScore(const unsigned int indentationLevel, score * score);

static void _generateScoreExpressions(const unsigned int indentationLevel, scoreExpressions * scoreExpressions, IDM id);

static void _generateScoreExpression(const unsigned int indentationLevel, scoreExpression * scoreExpression, IDM id);

static void _generateDeclaration(const unsigned int indentationLevel, declaration * declaration, IDM id);

static void _generateSignature(const unsigned int indentationLevel, signature * signature, IDM id);

static void _generateTempo(const unsigned int indentationLevel, tempo * tempo, IDM id);

static void _generateInstruments(const unsigned int indentationLevel, instruments * instruments, IDM id);

static void _generateInstrument(const unsigned int indentationLevel, instrument * instrument, IDM id);

static void _generateClefDeclaration(const unsigned int indentationLevel, clefDeclaration * clefDeclaration, IDM id);

static void _generateClefSentence(const unsigned int indentationLevel, clefSentence * clefSentence, IDM id);

static void _generateSentences(const unsigned int indentationLevel, sentences * sentences, IDM id);

static void _generateSentence(const unsigned int indentationLevel, sentence * sentence, IDM id);

static void _generateChordExpression(const unsigned int indentationLevel, chordExpression * chordExpression, IDM id);

static void _generateChordValues(const unsigned int indentationLevel, chordValues * chordValues);

static void _generatePitch(const unsigned int indentationLevel, pitch * pitch, IDM id);

static void _generateTabExpression(const unsigned int indentationLevel, tabExpression * tabExpression, IDM id);

static void _generateTabValues(const unsigned int indentationLevel, tabValues * tabValues, IDM id);

static void _generateTabsSentence(const unsigned int indentationLevel, tabsSentence * tabsSentence, IDM id);

static void _generateExpression(const unsigned int indentationLevel, Expression * expression, IDM id);

static void _generateAssignment(const unsigned int indentationLevel, assignment * assignment);

static void _generateProgramExpression(const unsigned int indentationLevel, programExpression * programExpression);

static void _generateChord(const unsigned indentationLevel, chord * chord, IDM id);

static void _generateExpressions(const unsigned int indentationLevel, expressions * expressions);

static void _generateProgram(Program * program);

static void _generatePrologue(void);

static void _generateClass(void);

static void _generateEpilogue(void);

static char * _indentation(const unsigned int level);

static void _output(FILE * file, const unsigned int indentationLevel, const char * const format, ...);

void generate(CompilerState * compilerState);

int expressionType(Expression * e);

int assignmentType(assignment * a);

int noteType(note * n);

int pitchType(pitch * p);

int chordType(chord * c);


/**
 * Converts and expression type to the proper character of the operation
 * involved, or returns '\0' if that's not possible.
 */

/*
static const char _expressionTypeToCharacter(const ExpressionType type) {
	switch (type) {
		case ADDITION: return '+';
		case DIVISION: return '/';
		case MULTIPLICATION: return '*';
		case SUBTRACTION: return '-';
		default:
			logError(_logger, "The specified expression type cannot be converted into character: %d", type);
			return '\0';
	}
}
*/

/**
 * Generates the output of a constant.
 */

/*
static void _generateConstant(const unsigned int indentationLevel, Constant * constant) {
	_output(indentationLevel, "%s", "[ $C$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%d%s", "[ $", constant->value, "$, circle, draw ]\n");
	_output(indentationLevel, "%s", "]\n");
}
*/


/**
 * Generates the output of an expression.
 */

/*
static void _generateExpression(const unsigned int indentationLevel, Expression * expression) {
	_output(indentationLevel, "%s", "[ $E$, circle, draw, black!20\n");
	switch (expression->type) {
		case ADDITION:
		case DIVISION:
		case MULTIPLICATION:
		case SUBTRACTION:
			_generateExpression(1 + indentationLevel, expression->leftExpression);
			_output(1 + indentationLevel, "%s%c%s", "[ $", _expressionTypeToCharacter(expression->type), "$, circle, draw, purple ]\n");
			_generateExpression(1 + indentationLevel, expression->rightExpression);
			break;
		case FACTOR:
			_generateFactor(1 + indentationLevel, expression->factor);
			break;
		default:
			logError(_logger, "The specified expression type is unknown: %d", expression->type);
			break;
	}
	_output(indentationLevel, "%s", "]\n");
}
*/

/**
 * Generates the output of a factor.
 */

/*
static void _generateFactor(const unsigned int indentationLevel, Factor * factor) {
	_output(indentationLevel, "%s", "[ $F$, circle, draw, black!20\n");
	switch (factor->type) {
		case CONSTANT:
			_generateConstant(1 + indentationLevel, factor->constant);
			break;
		case EXPRESSION:
			_output(1 + indentationLevel, "%s", "[ $($, circle, draw, purple ]\n");
			_generateExpression(1 + indentationLevel, factor->expression);
			_output(1 + indentationLevel, "%s", "[ $)$, circle, draw, purple ]\n");
			break;
		default:
			logError(_logger, "The specified factor type is unknown: %d", factor->type);
			break;
	}
	_output(indentationLevel, "%s", "]\n");
}
*/

static char * parseNote(char * noteString) {
	int i = 0, j = 0;
	while (noteString[i]) {
		if (noteString[i] != '(' || noteString[i] != ')')
			j++;
		noteString[i] = noteString[j];
	}
	return noteString;
}

static void _generateType(const unsigned int indentationLevel, type * type) {
	if (type->class == NOTECLASS || type->class == CHORDCLASS || type->class == TABCLASS || type->class == RESTCLASS || type->class == INTEGERCLASS ) {
		_output(file, indentationLevel, "String");
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", type->class);
	}
}

static void _generateId(const unsigned int indentationLevel, id * id) {
	_output(file, indentationLevel, " %s ", id->id);
}

static void _generateNote(const unsigned int indentationLevel, note * note, IDM id) {
	_output(file, indentationLevel, "%s += \" %s \";\n",id, parseNote(note->note));
}

static void _generateNoteExpression(const unsigned int indentationLevel, noteExpression * noteExpression, IDM id) {
	if (noteExpression->_note->type == TERMINAL) {
		_output(file, indentationLevel,"%s += \"I[%s]%s%d\";\n", id, noteExpression->_instrument->instrument, noteExpression->_note->note, noteExpression->_pitch->_pitch);
	} else {
		_output(file, indentationLevel,"%s += \"I[%s]%s%d\";\n", id, noteExpression->_instrument->instrument, noteExpression->_note->_id, noteExpression->_pitch->_pitch);
	}
}

static void _generateScore(const unsigned int indentationLevel, score * score) {
	_output(file, 0, "String %s = \"\";\n", score->_id->id);
	_generateScoreExpressions(indentationLevel, score->scoreExpressions, score->_id->id);
}

static void _generateScoreExpressions(const unsigned int indentationLevel, scoreExpressions * scoreExpressions, IDM id) {
	if (scoreExpressions->type == SCOREEXPRESSIONSTYPE) {
		_generateScoreExpression(indentationLevel, scoreExpressions->_scoreExpression, id);
		_generateScoreExpressions(indentationLevel, scoreExpressions->_scoreExpressions, id);
	} else {
		_generateScoreExpression(indentationLevel, scoreExpressions->_scoreExpression, id);
	}
}

static void _generateScoreExpression(const unsigned int indentationLevel, scoreExpression * scoreExpression, IDM id) {
	_generateDeclaration(indentationLevel, scoreExpression->_declaration, id);
	_generateInstruments(indentationLevel, scoreExpression->instruments, id);
}

static void _generateDeclaration(const unsigned int indentationLevel, declaration * declaration, IDM id) {
	_generateTempo(indentationLevel, declaration->_tempo, id);
	_generateSignature(indentationLevel, declaration->_signature, id);
}

static void _generateSignature(const unsigned int indentationLevel, signature * signature, IDM id) {
	removeSpaces(signature->signature);
	_output(file, indentationLevel, "%s += \" K%s \";\n",id,signature->signature);
}

static void _generateTempo(const unsigned int indentationLevel, tempo * tempo, IDM id) {
	_output(file, indentationLevel, "%s += \" T%d \";\n",id, tempo->tempo);
}

static void _generateInstruments(const unsigned int indentationLevel, instruments * instruments, IDM id) {
	_generateInstrument(indentationLevel, instruments->_instrument, id);
	_generateClefDeclaration(indentationLevel, instruments->_clefDeclaration, id);
	if (instruments->_instruments != NULL) {
		_generateInstruments(indentationLevel, instruments->_instruments, id);
	}
}

static void _generateInstrument(const unsigned int indentationLevel, instrument * instrument, IDM id) {
	_output(file, indentationLevel, "%s += \" I[%s] \";\n", id, instrument->instrument);
}

static void _generateClefDeclaration(const unsigned int indentationLevel, clefDeclaration * clefDeclaration, IDM id) {
	_generateClefSentence(indentationLevel, clefDeclaration->_clefSentence, id); 
	_generateSentences(indentationLevel, clefDeclaration->_sentences, id);
}

static void _generateClefSentence(const unsigned int indentationLevel, clefSentence * clefSentence, IDM id) {

}

static void _generateSentences(const unsigned int indentationLevel, sentences * sentences, IDM id) {
	if (sentences->sentencesType == SENTENCES) {
		_generateSentence(indentationLevel, sentences->_sentence_, id);
		_generateSentences(indentationLevel, sentences->_sentences, id);
	} else {
		_generateSentence(indentationLevel, sentences->_sentence, id);
	}
}

static void _generateSentence(const unsigned int indentationLevel, sentence * sentence, IDM id) {
	if (sentence->sentenceType == CLEFSENTENCE) {
		_generateClefSentence(indentationLevel, sentence->_clefSentence, id);
	} else {
		_generateTabsSentence(indentationLevel, sentence->_tabsSentence, id);
	}
}

static void _generateChordExpression(const unsigned int indentationLevel, chordExpression * chordExpression, IDM id) {
	_output(file, indentationLevel, "%s += ", id);
	_generateChordValues(indentationLevel, chordExpression->_chordValues);
}

static void _generateChordValues(const unsigned int indentationLevel, chordValues * chordValues) {
	if (chordValues->type == CHORDVALUES) {
		_output(file, indentationLevel, "\"%s+\" + ", chordValues->_note->note);
		_generateChordValues(indentationLevel, chordValues->_chordValues);
	} else if (chordValues->type == CHORDIDVALUES) { 
		_output(file, indentationLevel, "String.format(\"\%s\",%s)", chordValues->_id->id);
		_generateChordValues(indentationLevel, chordValues->_idChordVaues);
	} else if (chordValues->type == CHORDNOTE) {
		_output(file, indentationLevel, "\"%s\";\n", chordValues->note_->note);
	} else if (chordValues->type == CHORDIDNOTE) {
		_output(file, indentationLevel, "String.format(\"\%s\",%s);\n", chordValues->id_->id);
	} else {
		/* TODO: log error*/
	}
}

static void _generatePitch(const unsigned int indentationLevel, pitch * pitch, IDM id) {
	if (pitch->type == TERMINAL) {
		_output(file, indentationLevel, "%s += \"%d\";\n",id, pitch->_pitch);
	} else {
		_output(file, indentationLevel, "%s += String.format(\"\%s\",%s);\n", id, pitch->_id);
	}
}

static void _generateTabExpression(const unsigned int indentationLevel, tabExpression * tabExpression, IDM id) {
	_generateTabValues(indentationLevel, tabExpression->_tabValues, id);
}

static void _generateTabValues(const unsigned int indentationLevel, tabValues * tabValues, IDM id) {
	if (tabValues->type == NOTETABVALUES) {
		_generateNote(indentationLevel, tabValues->_note, id);
		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == CHORDTABVALUES) {
		_generateChord(indentationLevel, tabValues->_chord, id);
		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == RESTTABVALUES) {

		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == IDTABVALUES) {

		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == TABVALUESNOTE) {

	} else if (tabValues->type == TABVALUESCHORD) {

	} else if (tabValues->type == TABVALUESREST) {

	} else if (tabValues->type == TABVALUESID) {

	} else {
		/* TODO: log error */
	}
}

static void _generateChord(const unsigned indentationLevel, chord * chord, IDM id) {

}

static void _generateTabsSentence(const unsigned int indentationLevel, tabsSentence * tabsSentence, IDM id) {

}

static void _generateExpression(const unsigned int indentationLevel, Expression * expression, IDM id) {
	if (expression->type == NOTEEXPRESSION) {
		_generateNoteExpression(indentationLevel, expression->noteExpression, id);
	} else if (expression->type == SCOREEXPRESSION) {
		_generateScore(indentationLevel, expression->_score);
	} else if (expression->type == CHORDEXPRESSION) {
		_generateChordExpression(indentationLevel, expression->_chordExpression, id);
	} else if (expression->type == PITCHEXPRESSION) {
		_generatePitch(indentationLevel, expression->_pitch, id);
	} else if (expression->type == TABEXPRESSIONTYPE) {
		_generateTabExpression(indentationLevel, expression->_tabExpression, id);
	} else if (expression->type == TABSENTENCETYPE) {
		_generateTabsSentence(indentationLevel, expression->_tabsSentence, id);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", expression->type);
	}
}

static void _generateAssignment(const unsigned int indentationLevel, assignment * assignment) {
	_generateType(indentationLevel, assignment->_class);
	_generateId(indentationLevel, assignment->_id);
	_output(file, indentationLevel, " = \"\";\n");
	_generateExpression(indentationLevel, assignment->expression, assignment->_id->id);
}


static void _generateProgramExpression(const unsigned int indentationLevel, programExpression * programExpression) {
	if (programExpression->type == ASSIGNMENT) {
		_generateAssignment(indentationLevel, programExpression->assignment);
	} else if (programExpression->type == EXPRESSION) {
		_generateExpression(indentationLevel, programExpression->expression, "");
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", programExpression->type);
	}
}

static void _generateExpressions(const unsigned int indentationLevel, expressions * expressions) {
	if (expressions->type == EXPRESSIONSTYPE) {
			_generateProgramExpression(1 + indentationLevel, expressions->_programExpression);
			_generateExpressions(0, expressions->expressions);
	} else if (expressions->type == PROGRAMEXPRESSIONTYPE) {
			_generateProgramExpression(1 + indentationLevel, expressions->programExpression_);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", expressions->type);
	}
}

/**
 * Generates the output of the program.
 */
static void _generateProgram(Program * program) {
	_generateExpressions(3, program->_expressions);
}

static void _generatePrologue(void) {
	_output(file, 0, "%s",
		"package org.marimba#;\n"
		"import org.jfugue.*;\n"
	);
}

static void _generateClass(void) {
	_output(file, 0, "%s",
		"public class MarimbaMusic {\n"
		"		public static void main(String[] args) throws Exception, RuntimeException {\n"
	);
}

static void _generateEpilogue() {
	_output(file, 0, "%s",
		"		}\n"
		"}\n"
	);
}

/**
 * Generates an indentation string for the specified level.
 */
static char * _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}

/**
 * Outputs a formatted string to standard output.
 */
static void _output(FILE * file, const unsigned int indentationLevel, const char * const format, ...) {
	if (file == NULL) {
        // If file pointer is NULL, opening the file failed
        perror("Error opening file");
        return;
    }
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(file, effectiveFormat, arguments);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState * compilerState) {
	logDebugging(_logger, "Generating final output...");
	_generatePrologue();
	_generateClass();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue();
	logDebugging(_logger, "Generation is done.");
}


/* TYPE FUNCTIONS */
int correspondingExpression(int class){
	switch (class){
	case INTEGERCLASS: return PITCHEXPRESSION;
	case NOTECLASS: return NOTEEXPRESSION;
	case CHORDCLASS: return CHORDEXPRESSION;
	case TABCLASS: return TABEXPRESSIONTYPE;
	default: return -1;
	}
}

int expressionType(Expression * e) {
	return e->type;
}

int assignmentType(assignment * a) {
	int t = a->_class->class;
	if (correspondingExpression(t) == expressionType(a->expression)) return t;
	logError(_logger, "The expression does not match the declaration type.");
	return -1;
}

int idType(id * _id){
	return getType(_id->id);
}

int noteType(note * n) {
	if (n->type == NONTERMINAL) {
		if(idType(n->_id) != NOTECLASS) {
			logError(_logger, "Incorrect variable type. Expected: Note");
			return -1;
		}
	}
	return NOTECLASS;
}

int pitchType(pitch * p) {
	if (p->type == NONTERMINAL) {
		if(idType(p->_id) != INTEGER) {
			logError(_logger, "Incorrect variable type. Expected: Integer");
			return -1;
		}
	}
	return INTEGER;
}

int chordType(chord * c) {
	if (c->type == NONTERMINAL) {
		if(idType(c->_id) != CHORDCLASS) {
			logError(_logger, "Incorrect variable type. Expected: Chord");
			return -1;
		}
	}
	return CHORDCLASS;
}

int chordValuesType(chordValues * _chordValues) {
	if(_chordValues->type == CHORDIDVALUES){
		if(idType(_chordValues->_id) != NOTECLASS) {
			logError(_logger, "Incompatible variable type for chord. Expected: Note");
			return -1;
		}
	}
	if(_chordValues->type == CHORDIDNOTE){
		if(idType(_chordValues->id_) != NOTECLASS) {
			logError(_logger, "Incompatible variable type for chord. Expected: Note");
			return -1;
		}
	}
	return _chordValues->type;
}

int tabType(tab * _tab) {
	if(_tab->tabType == IDTYPE) {
		if(_tab->_id != CHORDCLASS || _tab->_id != NOTECLASS) {
			logError(_logger, "Incompatible variable type for tab. Expected: Note or Chord");
			return -1;
		}
	}
	return _tab->tabType;
}



// int noteType(note * n) {
// 	if (n->type == NONTERMINAL) {
// 		if(getType(n->_id->id) != NOTECLASS) {
// 			logError(_logger, "Incorrect variable type. Expected: Note");
// 			return -1;
// 		}
// 	}
// 	return NOTECLASS;
// }
