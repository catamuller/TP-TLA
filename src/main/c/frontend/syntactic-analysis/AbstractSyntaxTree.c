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
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_assignment != NULL) {
		free(_assignment->_class);
		releaseExpression(_assignment->expression);
		free(_assignment);
	}
}
void releaseProgram(Program * _program){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_program != NULL) {
		releaseExpressions(_program->_expressions);
		free(_program);
	}
	
}

void releaseExpressions(expressions * _expressions) {
		logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
		if (_expressions != NULL) {
			switch (_expressions->type)
			{
			case EXPRESSIONSTYPE:
				releaseProgramExpression(_expressions->programExpression_);
				releaseExpressions(_expressions->expressions);
				break;
			case PROGRAMEXPRESSIONTYPE:
				releaseProgramExpression(_expressions->_programExpression);
				break;
			}
			free(_expressions);
		}
		
}

void releaseId(id * _id) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_id != NULL) {
		if (_id->id != NULL) {
			free(_id->id);
		}
		free(_id);
	}
}

void releaseTransposition(transpose * _transposition) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_transposition != NULL) {
		free(_transposition);
	}
}

void releaseScore(score * _score) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_score != NULL) {
		releaseId(_score->_id);
		releaseScoreExpressions(_score->scoreExpressions);
		releaseTransposition(_score->_transpose);
		free(_score);
	}
}

void releaseScoreExpressions(scoreExpressions * _scoreExpressions) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_scoreExpressions != NULL) {
		switch (_scoreExpressions->type) {
			case SCOREEXPRESSIONSTYPE:
				releaseScoreExpression(_scoreExpressions->_scoreExpression);
				releaseScoreExpressions(_scoreExpressions->_scoreExpressions);
				break;
			case SCOREEXPRESSIONTYPE:
				releaseScoreExpression(_scoreExpressions->_scoreExpression);
				break;
		}
		free(_scoreExpressions);
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
				releaseScore(expression->_score);
				break;
			case PITCHEXPRESSION:
				releasePitch(expression->_pitch);
				break;
			case CHORDEXPRESSION:
				releaseChordExpression(expression->_chordExpression);
				break;
			case TABEXPRESSIONTYPE:
				releaseTabExpression(expression->_tabExpression);
				break;
		}
		free(expression);
	}	
}

void releaseChordExpression(chordExpression * _chordExpression){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_chordExpression != NULL) {
		releaseChordValues(_chordExpression->_chordValues);
		free(_chordExpression);
	}
}

void releasePitch(pitch * _pitch){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_pitch!=NULL){
		free(_pitch);
	}
}

void releaseChordValues(chordValues * _chordValues){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_chordValues!=NULL){
		switch(_chordValues->type){
			case CHORDVALUES:
				releaseNote(_chordValues->_note);
				break;
			case CHORDNOTE:
				releaseChordValues(_chordValues->_chordValues);
				break;
		}
		free(_chordValues);
	}
}

void releaseProgramExpression(programExpression * _programExpression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_programExpression != NULL) {
		switch(_programExpression->type){
		case ASSIGNMENT:
			releaseAssignment(_programExpression->assignment);
			break;
		case EXPRESSION:
			releaseExpression(_programExpression->expression);
			break;
		}
		free(_programExpression);
	}
}

void releaseNoteExpression(noteExpression * noteExpression){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (noteExpression != NULL) {
		free(noteExpression);
	}
}

void releaseClefDeclaration(clefDeclaration * _clefDeclaration) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_clefDeclaration!=NULL) {
		releaseClefSentence(_clefDeclaration->_clefSentence);
		releaseSentences(_clefDeclaration->_sentences);
		free(_clefDeclaration);
	}
}

void releaseInstruments(instruments * _instruments) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_instruments != NULL) {
		releaseInstrument(_instruments->_instrument);
		releaseClefDeclaration(_instruments->_clefDeclaration);
		releaseInstruments(_instruments->_instruments);

		free(_instruments);
	}
}

void releaseScoreExpression(scoreExpression * scoreExpression){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (scoreExpression != NULL) {
		if (scoreExpression->instruments != NULL) {
			releaseInstruments(scoreExpression->instruments);
		}
		if(scoreExpression->_declaration != NULL){
			releaseDeclaration(scoreExpression->_declaration);
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

void releaseRepeat(repeat * _repeat) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_repeat != NULL) {
		free(_repeat);
	}
}

void releaseControl(control * _control) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_control != NULL) {
		switch(_control->type){
			case REPEAT:
				releaseRepeat(_control->_repeat);
				releaseControl(_control->_control);
				break;
			case AFTER:
				releaseAfter(_control->_after);
				releaseControl(_control->_control);
				break;
			case BEFORE:
				releaseBefore(_control->_before);
				releaseControl(_control->_control);
				break;
			case ALONG:
				releaseAlong(_control->_along);
				releaseControl(_control->_control);
				break;
		}
		free(_control);
	}
}

releaseAfer(after * _after){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_after!=NULL){
		releaseTab(_after->_id);
		free(_after);
	}
}
releaseBefore(before * _before){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_before!=NULL){
		releaseTab(_before->_id);
		free(_before);
	}
}
releaseAlong(along * _along){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_along!=NULL){
		releaseTab(_along->_id);
		free(_along);
	}
}

void releaseTabsSentence(tabsSentence * tabsSentence){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tabsSentence != NULL) {
		releaseId(tabsSentence->_id);
		releaseTabs(tabsSentence->_tabs);
		releaseControl(tabsSentence->_control);
	
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

void releaseType(type * _type){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_type != NULL) {
		free(_type);
	}
}

void releaseDeclaration(declaration * _declaration){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_declaration != NULL) {
		if (_declaration->_tempo != NULL) {
			releaseTempo(_declaration->_tempo);
		}
		if(_declaration->_signature != NULL){
			releaseSignature(_declaration->_signature);
		}
		free(_declaration);
	}
}

void releaseTempo(tempo * _tempo) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (_tempo != NULL) {
		free(_tempo);
	}
}

void releaseSignature(signature * _signature) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_signature!=NULL){
		free(_signature->signature);
		free(_signature);
	}
}

void releaseTabExpression(tabExpression * _tabExpression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_tabExpression!=NULL){
		releaseTabValues(_tabExpression->_tabValues);
		free(_tabExpression);
	}
}

void releaseTabValues(tabValues * _tabValues){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(_tabValues!=NULL){
		switch(_tabValues->type){
			case NOTETABVALUES:
				releaseNote(_tabValues->_note);
				releaseTabValues(_tabValues->_tabValues);
				break;
			case CHORDTABVALUES:
				releaseChord(_tabValues->_chord);
				releaseTabValues(_tabValues->_tabValues);
				break;
			case RESTTABVALUES:
				releaseRest(_tabValues->_rest);
				releaseTabValues(_tabValues->_tabValues);
				break;
			case TABVALUESNOTE:
				releaseNote(_tabValues->_note);
				break;
			case TABVALUESCHORD:
				releaseChord(_tabValues->_chord);
				break;
			case TABVALUESREST:
				releaseRest(_tabValues->_rest);
				break;
		}
		free(_tabValues);
	}
}
