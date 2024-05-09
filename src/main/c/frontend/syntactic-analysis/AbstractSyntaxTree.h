#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */
enum ExpressionType {
	NOTEEXPRESSION,
	SCOREEXPRESSION,
	CHORDEXPRESSION,
	PITCHEXPRESSION,
	TABEXPRESSIONTYPE
};

// enum FactorType {
// 	CONSTANT,
// 	EXPRESSION
// };

enum ScoreExpressionsType {
	SCOREEXPRESSIONSTYPE,
	SCOREEXPRESSIONTYPE
};

enum ExpressionsType {
	EXPRESSIONSTYPE,
	PROGRAMEXPRESSIONTYPE
};

enum tabValuesType {
	NOTETABVALUES,
	CHORDTABVALUES,
	RESTTABVALUES,
	TABVALUESNOTE,
	TABVALUESCHORD,
	TABVALUESREST
};

enum SentencesType {
	SENTENCE,
	SENTENCES
};
enum SentenceType {
	CLEFSENTENCE,
	TABSSENTENCE
};
enum TabsType {
	TABTYPE,
	TABSTYPE
};
enum TabType {
	NOTETYPE,
	CHORDTYPE,
	RESTTYPE
};
enum ProgramType {
	ASSIGNMENT,
	EXPRESSION
};
enum ChordValuesType{
	CHORDVALUES,
	CHORDNOTE
};

enum tabsSentenceType {
	TABSSENTENCEWITHID,
	TABSSENTENCENOID
};
enum controlType{
	REPEAT,
	AFTER,
	BEFORE,
	ALONG
};

typedef enum tabValuesType tabValuesType;
typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;
typedef enum SentencesType SentencesType;
typedef enum SentenceType SentenceType;
typedef enum TabsType TabsType;
typedef enum TabType TabType;
typedef enum ProgramType ProgramType;
typedef enum ExpressionsType ExpressionsType;
typedef enum ChordValuesType ChordValuesType;
typedef enum ScoreExpressionsType ScoreExpressionsType;
typedef enum tabsSentenceType tabsSentenceType;
typedef enum controlType controlType;


typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;

typedef struct assignment assignment;
typedef struct type type;
typedef struct noteExpression noteExpression;
typedef struct scoreExpression scoreExpression;
typedef struct chord chord;
typedef struct note note;
typedef struct instrument instrument;
typedef struct id id;
typedef struct sentences sentences;
typedef struct sentence sentence;
typedef struct clefSentence clefSentence;
typedef struct tabsSentence tabsSentence;
typedef struct clef clef;
typedef struct tabs tabs;
typedef struct tab tab;
typedef struct rest rest;
typedef struct declaration declaration;
typedef struct tempo tempo;
typedef struct signature signature;
typedef struct score score;
typedef struct pitch pitch;
typedef struct expressions expressions;
typedef struct programExpression programExpression;
typedef struct chordExpression chordExpression;
typedef struct chordValues chordValues;
typedef struct tabExpression tabExpression;
typedef struct tabValues tabValues;
typedef struct scoreExpressions scoreExpressions;
typedef struct instruments instruments;
typedef struct control control;
typedef struct repeat repeat;
typedef struct transpose transpose;
typedef struct clefDeclaration clefDeclaration;
typedef struct after after;
typedef struct before before;
typedef struct along along;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

struct rest {
	Rest rest;
};	

struct type {
	Class class;
};

struct chord {
	Chord chord;
};

struct note {
	Note note;
};

struct clef {
	Clef clef;
};

struct instruments {
	instrument * _instrument;
	clefDeclaration * _clefDeclaration;
	instruments * _instruments;
};

struct instrument {
	Instrument instrument;
};

struct control {
	control * _control;
	union {
		repeat * _repeat;
		after * _after;
		before * _before;
		along * _along;
	};
	controlType type;
};

struct repeat {
	Integer _repeat;
};

struct after{
	id * _id;
};
struct before{
	id * _id;
};
struct along{
	id * _id;
};

struct transpose {
	Integer _transpose;
};

struct clefSentence {
	clef * _clef;
};

struct tab {
	union {
		note * _note;
		chord * _chord;
		rest * _rest;
	};
	tab * _tab;
	TabType tabType;
};

struct tabs {
	union {
		struct {
			tab * _tab_;
			tabs * _tabs; 
		};
		tab * _tab;
	};
	TabsType tabsType;
};

struct id {
	IDM id;
};

struct tabsSentence {
	id * _id;
	tabs * _tabs;
	control * _control;

	tabsSentenceType type;
};

struct sentence {
	union {
		clefSentence * _clefSentence;
		tabsSentence * _tabsSentence;
	};
	SentenceType sentenceType;
};

struct sentences {
	union {
		sentence * _sentence;
		struct {
			sentence * _sentence_;
			sentences * _sentences;
		};
	};
	SentencesType sentencesType;
};

struct scoreExpressions {
	scoreExpression * _scoreExpression;
	scoreExpressions * _scoreExpressions;


	ScoreExpressionsType type;
};

struct scoreExpression {
	declaration * _declaration;
	instruments * instruments;
};


struct assignment {
	type * _class;
	id * _id;
	Expression * expression;
};

struct score {
	id * _id;
	scoreExpressions * scoreExpressions;
	transpose * _transpose;;
};

struct clefDeclaration {
	clefSentence * _clefSentence;
	sentences * _sentences;
};

struct declaration {
	tempo * _tempo;
	signature * _signature;
};

struct tempo {
	Integer tempo;
};

struct signature {
	Signature signature;
};

struct pitch {
	Integer _pitch;
};



//Cm(C, 2, marimba)
struct noteExpression {
	note * _note;
	pitch * _pitch;
	instrument * _instrument;
};

struct chordExpression {
	chordValues * _chordValues;
};

struct chordValues {
	union {
		struct {
			note * _note;
			chordValues * _chordValues;
		};
		note * note_;
	};
	ChordValuesType type;
};

struct tabExpression {
	tabValues * _tabValues;
};

struct tabValues {
	union {
		note * _note;
		chord * _chord;
		rest * _rest;
	};
	tabValues * _tabValues;
	tabValuesType type;
};

/*
struct Constant {
	int value;
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
};
*/
struct Expression {
	union {
		noteExpression * noteExpression;
		score * _score;
		chordExpression * _chordExpression;
		pitch * _pitch;
		tabExpression * _tabExpression;
	};
	ExpressionType type;
};

struct programExpression {
	union {
		assignment * assignment;
		Expression * expression;
	};
	ProgramType type;
};


struct expressions {
	union {
		struct {
			programExpression * _programExpression;
			expressions * expressions;
		};
		programExpression * programExpression_;
	};
	ExpressionsType type;
};

struct Program {
	expressions * _expressions;
};

/**
 * Node recursive destructors.
 */
// void releaseConstant(Constant * constant); 
// void releaseFactor(Factor * factor); 
void releaseProgram(Program * program);
void releaseAssignment(assignment * assignment);
void releaseExpression(Expression * expression);
void releaseScore(score * _score);
void releaseId(id * _id);
// void releaseType(Type * type);
void releaseProgramExpression(programExpression * _programExpression);
void releaseNoteExpression(noteExpression * noteExpression);
void releaseScoreExpression(scoreExpression * scoreExpression);
void releaseChord(chord * chord);
void releaseNote(note * note);
void releaseInstrument(instrument * instrument);
void releaseSentences(sentences * sentences);
void releaseSentence(sentence * sentence);
void releaseClefSentence(clefSentence * clefSentence);
void releaseTabsSentence(tabsSentence * tabsSentence);
void releaseClef(clef * clef);
void releaseTabs(tabs * tabs);
void releaseTab(tab * tab);
void releaseRest(rest * rest);
void releaseExpressions(expressions * _expressions);
void releaseChordExpression(chordExpression * _chordExpression);
void releaseChordValues(chordValues * _chordValues);
void releasePitch(pitch * _pitch);
void releaseDeclaration(declaration * _declaration);
void releaseTempo(tempo * _tempo);
void releaseSignature(signature * _signature);
void releaseTabValues(tabValues * _tabValues);
void releaseTabExpression(tabExpression * _tabExpression);
void releaseScoreExpressions(scoreExpressions * _scoreExpressions);
void releaseControl(control * _control);
void releaseRepeat(repeat * _repeat);
void releaseTransposition(transpose * _transposition);
#endif
