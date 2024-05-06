#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PUBLIC FUNCTIONS */
/*
void releaseConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		free(constant);
	}
}

void releaseExpression(Expression * expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case ADDITION:
			case DIVISION:
			case MULTIPLICATION:
			case SUBTRACTION:
				releaseExpression(expression->leftExpression);
				releaseExpression(expression->rightExpression);
				break;
			case FACTOR:
				releaseFactor(expression->factor);
				break;
		}
		free(expression);
	}
}


void releaseFactor(Factor * factor) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (factor != NULL) {
		switch (factor->type) {
			case CONSTANT:
				releaseConstant(factor->constant);
				break;
			case EXPRESSION:
				releaseExpression(factor->expression);
				break;
		}
		free(factor);
	}
}
*/

void releaseAssignment(assignment * _assignment){
	logDebugging(_logger, "Executeing destructor: %s", __FUNCTION__);
	if (_assignment != NULL) {
		free(_assignment->class);
		releaseExpression(_assignment->expression);
		free(_assignment);
	}
}
void releaseProgram(Program * _program){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_program != NULL) {
		switch (_program->type)
		{
		case EXPRESSION:
			releaseExpression(_program->expression);
			break;
		case ASSIGNMENT:
			releaseAssignment(_program->assignment);
			break;
		}
	}
}

void releaseExpression(Expression * expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case NOTEEXPRESSION:
				releaseNoteExpression(expression->noteExpression);
				break;
			case SCOREEXPRESSION:
				releaseScoreExpression(expression->scoreExpression);
				break;
		}
		free(expression);
	}	
}


void releaseNoteExpression(noteExpression * noteExpression){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (noteExpression != NULL) {
		free(noteExpression);
	}
}

void releaseScoreExpression(scoreExpression * scoreExpression){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (scoreExpression != NULL) {
		if (scoreExpression->instrument != NULL) {
			releaseInstrument(scoreExpression->instrument);
		}
		free(scoreExpression);
	}
}

void releaseChord(chord * chord){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (chord != NULL) {
		if (chord->chord != NULL) {
			free(chord->chord);
		}
		free(chord);
	}
}

void releaseNote(note * note){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (note != NULL) {
		if (note->note != NULL) {
			free(note->note);
		}
		free(note);
	}
}


void releaseInstrument(instrument * instrument){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (instrument != NULL) {
		// if (instrument->instrument != NULL) {
		// 	free(instrument->instrument);
		// }
		free(instrument);
	}

}
void releaseSentences(sentences * sentences){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (sentences != NULL) {
		switch (sentences->sentencesType)
		{
		case SENTENCE:
			free(sentences->_sentence);
		
		case SENTENCES:
			free(sentences->_sentences);
		}
	}
}

void releaseSentence(sentence * sentence){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (sentence != NULL) {
		switch (sentence->sentenceType)
		{
		case CLEFSENTENCE:
			free(sentence->_clefSentence);
		
		case TABSSENTENCE:
			free(sentence->_tabsSentence);
		}
		
		free(sentence);
	}
}
void releaseClefSentence(clefSentence * clefSentence){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (clefSentence != NULL) {
		if (clefSentence->_clef != NULL) {
			releaseClef(clefSentence->_clef);
		}
		free(clefSentence);
	}
}
void releaseTabsSentence(tabsSentence * tabsSentence){

	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tabsSentence != NULL) {
		if (tabsSentence->_tabs!= NULL) {
			releaseTabs(tabsSentence->_tabs);
		}
		free(tabsSentence);
	}

}
void releaseClef(clef * clef){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (clef != NULL) {
		if (clef->clef != NULL) {
			free(clef->clef);
		}
		free(clef);
	}

}
void releaseTabs(tabs * tabs){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tabs != NULL) {
		switch (tabs->tabsType)
		{
		case TABTYPE:
			releaseTab(tabs->_tab);
			break;
		case TABSTYPE:
			releaseTabs(tabs->_tabs);
			releaseTab(tabs->_tab_);
			break;
		}
		free(tabs);
	}

}
void releaseTab(tab * tab){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tab != NULL) {
		switch (tab->tabType)
		{
		case NOTETYPE:
			releaseNote(tab->_note);
			if (tab->_tab != NULL)
				releaseTab(tab->_tab);
			break;
		case CHORDTYPE:
			releaseChord(tab->_chord);
			if (tab->_tab != NULL)
				releaseTab(tab->_tab);
			break;
		case RESTTYPE:
			releaseRest(tab->_rest);
			if (tab->_tab != NULL)
				releaseTab(tab->_tab);
			break;
		}
		free(tab);
	}


}
void releaseRest(rest * rest){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (rest != NULL) {
		if (rest->rest != NULL) {
			free(rest->rest);
		}
		free(rest);
	}
}
