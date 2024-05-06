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
	SCOREEXPRESSION
};

// enum FactorType {
// 	CONSTANT,
// 	EXPRESSION
// };

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

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;
typedef enum SentencesType SentencesType;
typedef enum SentenceType SentenceType;
typedef enum TabsType TabsType;
typedef enum TabType TabType;
typedef enum ProgramType ProgramType;


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

struct instrument {
	Instrument instrument;
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

/*
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

*/

struct id {
	IDM id;
};

struct tabsSentence {
	tabs * _tabs;
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

struct scoreExpression {
	instrument * instrument;
	sentences * _sentences;
};


struct assignment {
	type * class;
	IDM id;
	Expression * expression;
};



//Cm(C, 2, marimba)
struct noteExpression {
	note * _note;
	int pitch;
	instrument * _instrument;
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
		scoreExpression * scoreExpression;
	};
	ExpressionType type;
};

struct Program {
	union {
		assignment * assignment;
		Expression * expression;
	};
	ProgramType type;
};

/**
 * Node recursive destructors.
 */
// void releaseConstant(Constant * constant);  // check
// void releaseFactor(Factor * factor); 
void releaseProgram(Program * program);
void releaseAssignment(assignment * assignment);
void releaseExpression(Expression * expression);
// void releaseType(Type * type);
void releaseNoteExpression(noteExpression * noteExpression); // check
void releaseScoreExpression(scoreExpression * scoreExpression); // check
void releaseChord(chord * chord); // check
void releaseNote(note * note); // check 
void releaseInstrument(instrument * instrument); // check
void releaseSentences(sentences * sentences); // check
void releaseSentence(sentence * sentence); // check
void releaseClefSentence(clefSentence * clefSentence); // check
void releaseTabsSentence(tabsSentence * tabsSentence); // check
void releaseClef(clef * clef); // check
void releaseTabs(tabs * tabs); // check
void releaseTab(tab * tab); // check
void releaseRest(rest * rest); // check


#endif
