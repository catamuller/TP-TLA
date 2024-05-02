%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	Note note;
	Class classType;
	Chord chord;
	Rest rest;
	Tab tab;
	IDM id;
	Clef clef;
	Integer integer;
	Instrument instrument;
	Token token;

	/** Non-terminals. */
	Assignment * assignment;
	Type * type;
	noteExpression * noteExpression;
	scoreExpression * scoreExpression;
	chord * chordType;
	instrument * instrumentType;
	note * noteType;
	sentences * sentences;
	sentence * sentence;
	clefSentence * clefSentence;
	tabsSentence * tabsSentence;
	clef * clefType;

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */
%token <id> ID
%token <note> NOTE
%token <classType> NOTECLASS
%token <chord> CHORD
%token <classType> CHORDCLASS
%token <rest> REST
%token <classType> RESTCLASS
%token <tab> TAB
%token <classType> TABCLASS
%token <instrument> INSTRUMENT
%token <clef> CLEFVALUE
%token <token> PIPE

%token <token> SCORE
%token <token> TEMPO
%token <token> SIGNATURE
%token <token> CLEF
%token <token> TABS

%token <integer> INTEGER
%token <classType> INTEGERCLASS

%token <token> OPEN_BRACES
%token <token> CLOSE_BRACES
%token <token> COMMA
%token <token> DOT
%token <token> EQUAL
%token <token> SEMICOLON

%token <token> AFTER
%token <token> BEFORE
%token <token> ALONG

%token <token> REPEAT

%token <token> TRANSPOSE

%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_PARENTHESIS

%token <token> UNKNOWN

/** Non-terminals. */
%type <assignment> assignment
%type <type> type
%type <noteExpression> noteExpression
%type <scoreExpression> scoreExpression
%type <chordType> chord
%type <instrumentType> instrument
%type <noteType> note
%type <sentences> sentences
%type <sentence> sentence
%type <clefSentence> clefSentence
%type <tabsSentence> tabsSentence
%type <clefType> clef

%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

program: assignment													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

assignment: type ID EQUAL expression								{ $$ = AssignmentSemanticAction(currentCompilerState(), $1, $2, $4); }
	;

type: NOTECLASS | CHORDCLASS | TABCLASS | RESTCLASS | INTEGERCLASS	{ $$ = TypeSemanticAction(currentCompilerState(), $1); }
	;

/*TODO #################################### ∇×E=-∂B/∂t*/
expression: noteExpression | scoreExpression						{ $$ = ExpressionSemanticAction(currentCompilerState(), $1); }							
	;

noteExpression: NOTECLASS OPEN_PARENTHESIS note COMMA INTEGER COMMA instrument CLOSE_PARENTHESIS		{ $$ = ExpressionSemanticAction(currentCompilerState(), $1, $3, $5, $7); }	
	;

note: NOTE
	;

chord: CHORD
	;

instrument: INSTRUMENT
	;

scoreExpression: instrument OPEN_BRACES sentences CLOSE_BRACES
	;

sentences: sentence sentences | sentence
	;

sentence: clefSentence | tabsSentence
	;

clefSentence: CLEF clef SEMICOLON
	;

clef: CLEFVALUE
	;

tabsSentence: TABS OPEN_BRACES tabs CLOSE_BRACES
	;

tabs: tabs
	;
// expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
//	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
//	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
//	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
//	| factor														{ $$ = FactorExpressionSemanticAction($1); }
//	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;

%%
