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

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;

typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;

typedef struct Assignment Assignment;
typedef struct Type Type;
typedef struct noteExpression noteExpression;
typedef struct scoreExpression scoreExpression;
typedef struct chord chord;
typedef struct note note;
typedef struct instrument instrument;
typedef struct sentences sentences;
typedef struct sentence sentence;
typedef struct clefSentence clefSentence;
typedef struct tabsSentence tabsSentence;
typedef struct clef clef;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION
};

enum FactorType {
	CONSTANT,
	EXPRESSION
};

struct Assignment {
	Type * class;
	IDM id;
	Expression * expression;
};

struct Type {
	Class class;
};

//Cm(C, 2, marimba)
struct noteExpression {
	Note note;
	int pitch;
	Instrument instrument;
};

struct scoreExpression {
	Instrument instrument;
	sentences sentences;
};

struct chord {
	Chord chord;
};

struct note {
	Note note;
};

struct instrument {
	Instrument instrument;
};

struct sentences {
	union {
		sentence * _sentence;
		struct {
			sentence * _sentence;
			sentences * _sentences;
		};
	};
};

struct sentence {

};

struct clefSentence {

};

struct tabsSentence {

};

struct clef {

};

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

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
	};
	ExpressionType type;
};

struct Program {
	Assignment * assignment;
};

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor);
void releaseProgram(Program * program);

#endif
