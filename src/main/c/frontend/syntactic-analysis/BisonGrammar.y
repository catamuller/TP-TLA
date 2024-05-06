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
	Signature signature;

	/** Non-terminals. */
	assignment * assignment;
	type * type;
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
	tabs * tabsType;
	tab * tabType;
	rest * restType;
	id * idType;
	declaration * declarationType;
	tempo * tempoType;
	signature * signatureType;
	score * scoreType;
	pitch * pitchType;

	Expression * expression;
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
%token <signature> SIGNATUREVALUE

%token <token> SCORE
%token <token> TEMPO
%token <token> SIGNATURE
%token <token> CLEF
%token <token> TABS

%token <integer> TEMPOVALUE

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
%type <tabsType> tabs
%type <tabType> tab
%type <restType> rest
%type <idType> id
%type <declarationType> declaration
%type <tempoType> tempo
%type <signatureType> signature
%type <scoreType> score
%type <pitchType> pitch

%type <expression> expression
%type <program> program

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */


%%
program: assignment 												{ $$ = AssignmentProgramSemanticAction(currentCompilerState(), $1); }
	| expression													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }		
	;

assignment: type id EQUAL expression								{ $$ = AssignmentSemanticAction($1, $2, $4); }
	;

id: ID																{ $$ = IDSemanticAction($1); }							
	;

type: NOTECLASS 	{ $$ = TypeSemanticAction($1); }
	| CHORDCLASS 		{ $$ = TypeSemanticAction($1); }
	| TABCLASS 			{ $$ = TypeSemanticAction($1); }
	| RESTCLASS 		{ $$ = TypeSemanticAction($1); }
	| INTEGERCLASS	{ $$ = TypeSemanticAction($1); }
	;


expression: noteExpression 											{ $$ = expressionNoteExpresionSemanticAction($1); }
	| score												{ $$ = expressionScoreExpressionSemanticAction($1); }
	;

noteExpression: NOTECLASS OPEN_PARENTHESIS note COMMA pitch COMMA instrument CLOSE_PARENTHESIS SEMICOLON		{ $$ = noteExpressionSemanticAction($3, $5, $7); }	
	;

pitch: INTEGER													{ $$ = PitchSemanticAction($1); }
	;

note: NOTE															{ $$ = NoteSemanticAction($1); }
	;

chord: CHORD														{ $$ = ChordSemanticAction($1); }
	;

instrument: INSTRUMENT												{ $$ = InstrumentSemanticAction($1); }
	;

score: SCORE id OPEN_BRACES scoreExpression CLOSE_BRACES		{ $$ = scoreSemanticAction($2, $4); }
	;

scoreExpression: declaration instrument OPEN_BRACES sentences CLOSE_BRACES		{ $$ = ScoreExpressionSemanticAction($1, $2, $4); }
	;

declaration: tempo signature				{ $$ = DeclarationSemanticAction($1, $2); }
	;

tempo: TEMPO TEMPOVALUE SEMICOLON			{ $$ = tempoSemanticAction($2); }
	;

signature: SIGNATURE SIGNATUREVALUE SEMICOLON		{ $$ = signatureSemanticAction($2); }
	;

sentences: sentence sentences							{ $$ = sentencesSentenceSentencesSemanticAction($1, $2, SENTENCES); }
	| sentence											{ $$ = sentencesSentenceSemanticAction($1, SENTENCE); }
	;

sentence: clefSentence									{ $$ = sentenceClefSentenceSemanticAction($1); }
	| tabsSentence										{ $$ = sentenceTabsSentenceSemanticAction($1); }
	;

clefSentence: CLEF clef SEMICOLON						{ $$ = clefSentenceSemanticAction($2); }
	;

clef: CLEFVALUE											{ $$ = clefSemanticAction($1); }
	;

tabsSentence: TABS OPEN_BRACES tabs CLOSE_BRACES		{ $$ = tabsSentenceSemanticAction($3); }
	;

tabs: tab PIPE tabs 			{ $$ = tabsPipeSemanticAction($1, $3); }
	| tab						{ $$ = tabsTabSemanticAction($1); }
	;

tab: note tab 					{ $$ = tabNoteTabSemanticAction($1, $2); }
	| chord tab 				{ $$ = tabChordTabSemanticAction($1, $2); }
	| rest tab 					{ $$ = tabRestTabSemanticAction($1, $2); }
	| note 						{ $$ = tabNoteTabSemanticAction($1, NULL); }
	| chord						{ $$ = tabChordTabSemanticAction($1, NULL); }
	| rest 						{ $$ = tabRestTabSemanticAction($1, NULL); }
	;

rest: REST					{ $$ = restSemanticAction($1); }
// expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
//	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
//	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
//	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
//	| factor														{ $$ = FactorExpressionSemanticAction($1); }
//	;
/* 
factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;
*/
%% 
