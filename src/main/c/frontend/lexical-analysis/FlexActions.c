#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Note NoteLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->note = lexicalAnalyzerContext->lexeme;
	return NOTE;
}

Class ClassLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Integer") == 0)
		token = INTEGER;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Note") == 0)
		token = NOTE;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Chord") == 0)
		token = CHORD;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Rest") == 0)
		token = REST;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Tab") == 0)
		token = TAB;
		
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token EqualLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->token = EQUAL;
	return EQUAL;
}

Chord ChordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->chord = lexicalAnalyzerContext->lexeme;
	return CHORD;
}

Rest RestLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->rest = lexicalAnalyzerContext->lexeme;
	return REST;
}

Instrument InstrumentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->instrument = lexicalAnalyzerContext->lexeme;
	return INSTRUMENT;
}

Token ScoreLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->token = SCORE;
	return SCORE;
}

Token TempoLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->token = TEMPO;
	return TEMPO;
}

Token SignatureLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->token = SIGNATURE;
	return SIGNATURE;
}

Token ClefLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->token = CLEF;
	return CLEF;
}

Token TabsLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);

	lexicalAnalyzerContext->semanticValue->token = TABS;
	return TABS;
}

Token BracesLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '{': token = OPEN_BRACES; break;
		case '}': token = CLOSE_BRACES; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token CommaLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = COMMA;
	return COMMA;
}

IDM IDLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = lexicalAnalyzerContext->lexeme;
	return ID;
}


Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '-': token = SUB; break;
		case '*': token = MUL; break;
		case '/': token = DIV; break;
		case '+': token = ADD; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}

Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '(': token = OPEN_PARENTHESIS; break;
		case ')': token = CLOSE_PARENTHESIS; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}
