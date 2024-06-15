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

/** PRIVATE FUNCTIONS */

static const char _expressionTypeToCharacter(const ExpressionType type);
static void _generateConstant(const unsigned int indentationLevel, Constant * constant);
static void _generateEpilogue();
static void _generateExpression(const unsigned int indentationLevel, Expression * expression);
static void _generateFactor(const unsigned int indentationLevel, Factor * factor);
static void _generateProgram(Program * program);
static void _generatePrologue(void);
static char * _indentation(const unsigned int indentationLevel);
static void _output(FILE * file,const unsigned int indentationLevel, const char * const format, ...);

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
static void _generateType(const unsigned int identationLevel, type * type) {
	if (type->class == NOTECLASS) {
		_output(file, 0, "%s", " String ");
	} else if (type->class == CHORDCLASS) {
		_output(file, 0, "%s", " String ");
	} else if (type->class == TABCLASS) {
		_output(file, 0, "%s", " String ");
	} else if (type->class == RESTCLASS) {
		_output(file, 0, "%s", " String ");
	} else if (type->class == INTEGERCLASS) {
		_output(file, 0, "%s", " String ");
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", type->class);
	}
}

static void _generateId(const unsigned int identationLevel, id * id) {
	_output(file, 0, " %s ", id->id);
}

static void _generateNote(const unsigned int identationLevel, note * note) {
	
}

static void _generateNoteExpression(const unsigned int identationLevel, noteExpression * noteExpression) {
	char noteOrId;
	if (noteExpression->_note->type == TERMINAL) {
		_output(file, 0,"\"[%s]%s%d\";\n", noteExpression->_instrument->instrument, noteExpression->_note->note, noteExpression->_pitch->_pitch);
	} else {
		_output(file, 0,"\"[%s]%s%d\";\n", noteExpression->_instrument->instrument, noteExpression->_note->_id, noteExpression->_pitch->_pitch);
	}
}

static void _generateScore(const unsigned int identationLevel, score * score) {

}

static void _generateChordExpression(const unsigned int identationLevel, chordExpression * chordExpression) {

}

static void _generatePitch(const unsigned int identationLevel, pitch * pitch) {

}

static void _generateTabExpression(const unsigned int identationLevel, tabExpression * tabExpression) {

}

static void _generateTabsSentence(const unsigned int identationLevel, tabsSentence * tabsSentence) {

}

static void _generateExpression(const unsigned int identationLevel, Expression * expression) {
	if (expression->type == NOTEEXPRESSION) {
		_generateNoteExpression(0, expression->noteExpression);
	} else if (expression->type == SCOREEXPRESSION) {
		_generateScore(0, expression->_score);
	} else if (expression->type == CHORDEXPRESSION) {
		_generateChordExpression(0, expression->_chordExpression);
	} else if (expression->type == PITCHEXPRESSION) {
		_generatePitch(0, expression->_pitch);
	} else if (expression->type == TABEXPRESSIONTYPE) {
		_generateTabExpression(0, expression->_tabExpression);
	} else if (expression->type == TABSENTENCETYPE) {
		_generateTabsSentence(0, expression->_tabsSentence);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", expression->type);
	}
}

static void _generateAssignment(const unsigned int identationLevel, assignment * assignment) {
	_generateType(0, assignment->_class);
	_generateId(0, assignment->_id);
	_output(file, 0, "%s", " = ");
	_generateExpression(0, assignment->expression);
}


static void _generateProgramExpression(const unsigned int identationLevel, programExpression * programExpression) {
	if (programExpression->type == ASSIGNMENT) {
		_generateAssignment(0, programExpression->assignment);
	} else if (programExpression->type == EXPRESSION) {
		_generateExpression(0, programExpression->expression);
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
int expressionType(Expression * e) {
	return e->type;
}

int assignmentType(assignment * a) {
	int t = a->_class->class;
	if (t == expressionType(a->expression)) return t;
	logError(_logger, "The expression does not match the declaration type.");
	return -1;
}

int noteType(note * n) {
	if (n->type == NONTERMINAL) {
		if(getType(n->_id->id) != NOTECLASS) {
			logError(_logger, "Incorrect variable type. Expected: Note");
			return -1;
		}
	}
	return NOTECLASS;
}

int pitchType(pitch * p) {
	if (p->type == NONTERMINAL) {
		if(getType(p->_id->id) != INTEGER) {
			logError(_logger, "Incorrect variable type. Expected: Integer");
			return -1;
		}
	}
	return INTEGER;
}

int chordType(chord * c) {
	if (c->type == NONTERMINAL) {
		if(getType(c->_id->id) != CHORDCLASS) {
			logError(_logger, "Incorrect variable type. Expected: Chord");
			return -1;
		}
	}
	return CHORDCLASS
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
