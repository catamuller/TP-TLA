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
	expressions * expressionsType;
	programExpression * programExpressionType;
	chordExpression * chordExpressionType;
	chordValues * chordValuesType;
	tabExpression * tabExpressionType;
	tabValues * tabValuesType;
	scoreExpressions * scoreExpressionsType;
	instruments * instrumentsType;
	repeat * repeatType;
	transpose * transposeType;
	control * controlType;
	clefDeclaration * clefDeclarationType;
	before * beforeType;
	after * afterType;
	along * alongType;
	controlSentence * controlSentenceType;

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
%type <expressionsType> expressions
%type <programExpressionType> programExpression
%type <chordExpressionType> chordExpression
%type <chordValuesType> chordValues
%type <tabExpressionType> tabExpression
%type <tabValuesType> tabValues
%type <scoreExpressionsType> scoreExpressions
%type <instrumentsType> instruments
%type <repeatType> repeat
%type <transposeType> transpose
%type <controlType> control
%type <clefDeclarationType> clefDeclaration
%type <beforeType> before
%type <afterType> after
%type <alongType> along
%type <controlSentenceType> controlSentence

%type <expression> expression
%type <program> program

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */


%%
/**
program: assignment 							{ $$ = AssignmentProgramSemanticAction(currentCompilerState(), $1); }
	| expression								{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }		
	;
*/
program: expressions 							{ $$ = ExpressionsProgramSemanticAction(currentCompilerState(), $1); }

expressions: programExpression expressions		{ $$ = ExpressionsProgramExpressionExpressionsSemanticAction($1, $2); }
	| programExpression 						{ $$ = ExpressionsProgramExpressionSemanticAction($1); }

programExpression: assignment					{ $$ = ProgramExpressionAssignmentSemanticAction($1); }
	| expression								{ $$ = ProgramExpressionExpressionSemanticAction($1); }

assignment: type id EQUAL expression			{ $$ = AssignmentSemanticAction($1, $2, $4); }
	;

id: ID											{ $$ = IDSemanticAction($1); }							
	;

type: NOTECLASS 								{ $$ = TypeSemanticAction($1); }
	| CHORDCLASS 								{ $$ = TypeSemanticAction($1); }
	| TABCLASS 									{ $$ = TypeSemanticAction($1); }
	| RESTCLASS 								{ $$ = TypeSemanticAction($1); }
	| INTEGERCLASS								{ $$ = TypeSemanticAction($1); }
	;


expression: noteExpression 						{ $$ = expressionNoteExpresionSemanticAction($1); }
	| score										{ $$ = expressionScoreExpressionSemanticAction($1); }
	| chordExpression							{ $$ = expressionChordExpressionSemanticAction($1); }
	| pitch SEMICOLON							{ $$ = expressionPitchSemanticAction($1); }
	| tabExpression								{ $$ = expressionTabExpression($1); }
	| tabsSentence								{ $$ = expressionTabSentenceSemanticAction($1); }
	;

noteExpression: NOTECLASS OPEN_PARENTHESIS note COMMA pitch COMMA instrument CLOSE_PARENTHESIS SEMICOLON	{ $$ = noteExpressionSemanticAction($3, $5, $7); }	
	;

chordExpression: CHORDCLASS OPEN_PARENTHESIS chordValues CLOSE_PARENTHESIS SEMICOLON						{ $$ = chordExpressionSemanticAction($3); }
	;

chordValues: note COMMA chordValues				{ $$ = chordValuesChordValuesSemanticAction($1, $3); }
	| id COMMA chordValues						{ $$ = chordValuesIdChordValuesSemanticAction($1, $3); }
	| note										{ $$ = chordValuesNoteSemanticAction($1); }
	| id										{ $$ = chordValuesIdNoteSemanticAction($1); }
	;

tabExpression: TABCLASS OPEN_PARENTHESIS tabValues CLOSE_PARENTHESIS SEMICOLON			{ $$ = tabExpressionSemanticAction($3); }
	;

tabValues: note tabValues			{ $$ = tabValuesNoteTabValuesSemanticAction($1, $2); }
	| chord tabValues				{ $$ = tabValuesChordTabValuesSemanticAction($1, $2); }
	| rest tabValues				{ $$ = tabValuesRestTabValuesSemanticAction($1, $2); }
	| id tabValues					{ $$ = tabValuesIdTabValuesSemanticAction($1, $2); }
	| note							{ $$ = tabValuesNoteTabValuesSemanticAction($1, NULL); }
	| chord							{ $$ = tabValuesChordTabValuesSemanticAction($1, NULL); }
	| rest							{ $$ = tabValuesRestTabValuesSemanticAction($1, NULL); }
	| id							{ $$ = tabValuesIdTabValuesSemanticAction($1, NULL); }

pitch: INTEGER						{ $$ = PitchSemanticAction($1); }
	| id							{ $$ = PitchIdSemanticAction($1); }
	;

note: NOTE							{ $$ = NoteSemanticAction($1); }
// | id								{ $$ = NoteIdSemanticAction($1); }
	;

chord: CHORD						{ $$ = ChordSemanticAction($1); }
//	| id							{ $$ = ChordIdSemanticAction($1); }
	;

rest: REST							{ $$ = restSemanticAction($1); }
//	| id							{ $$ = restIdSemanticAction($1); }

instrument: INSTRUMENT				{ $$ = InstrumentSemanticAction($1); }
	;

score: SCORE id OPEN_BRACES scoreExpressions CLOSE_BRACES transpose					{ $$ = scoreSemanticAction($2, $4, $6); }
	;
	
scoreExpressions: OPEN_BRACES scoreExpression CLOSE_BRACES scoreExpressions			{ $$ = scoreExpressionsScoreExpressionsScoreExpressionSemanticAction($2, $4); }
	| OPEN_BRACES scoreExpression CLOSE_BRACES										{ $$ = scoreExpressionsScoreExpressionSemanticAction($2); }

scoreExpression: declaration instruments											{ $$ = ScoreExpressionSemanticAction($1, $2); }
	;

instruments: instrument OPEN_BRACES clefDeclaration CLOSE_BRACES instruments		{ $$ = instrumentsInstrumentInstrumentsSemanticAction($1, $3, $5); }
	| instrument OPEN_BRACES clefDeclaration CLOSE_BRACES																	{ $$ = instrumentsInstrumentInstrumentsSemanticAction($1, $3, NULL); }

declaration: tempo signature							{ $$ = DeclarationSemanticAction($1, $2); }
	;

tempo: TEMPO INTEGER SEMICOLON							{ $$ = tempoSemanticAction($2); }
	;

signature: SIGNATURE SIGNATUREVALUE SEMICOLON			{ $$ = signatureSemanticAction($2); }
	;

clefDeclaration: clefSentence sentences					{ $$ = clefDeclarationSemanticAction($1, $2); }
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

tabsSentence: TABS id OPEN_BRACES tabs CLOSE_BRACES	controlSentence	{ $$ = tabsSentenceSemanticAction($2, $4, $6); }
	| TABS OPEN_BRACES tabs CLOSE_BRACES controlSentence			{ $$ = tabsSentenceSemanticAction(NULL, $3, $5); }
	| id 															//TODO													{ $$ = tabsSentenceSemanticAction($1, NULL, NULL); }	
	;

controlSentence: control			{ $$ = controlSentenceSemanticAction($1); }
	| %empty																													{ $$ = controlSentenceSemanticAction(NULL); }

control: DOT repeat control			{ $$ = controlSemanticAction($2, $3); }
	| DOT after control				{ $$ = controlAfterSemanticAction($2, $3); }
	| DOT before control			{ $$ = controlBeforeSemanticAction($2, $3); }
	| DOT along control				{ $$ = controlAlongSemanticAction($2, $3); }
	| SEMICOLON						{ $$ = controlSemanticAction(NULL, NULL); }
	;

repeat: REPEAT						{ $$ = repeatSemanticAction($1); }
	;

after: AFTER OPEN_PARENTHESIS id CLOSE_PARENTHESIS			{ $$ = afterSemanticAction($3); }
	;
before: BEFORE OPEN_PARENTHESIS id CLOSE_PARENTHESIS		{ $$ = beforeSemanticAction($3); }
	;
along: ALONG OPEN_PARENTHESIS id CLOSE_PARENTHESIS			{ $$ = alongSemanticAction($3); }
	;


transpose: DOT TRANSPOSE		{ $$ = transposeSemanticAction($2); }
	| %empty					{ $$ = transposeSemanticAction(0); }
	;

tabs: tab PIPE tabs 			{ $$ = tabsPipeSemanticAction($1, $3); }
	| tab						{ $$ = tabsTabSemanticAction($1); }
	;

tab:  note tab 					{ $$ = tabNoteTabSemanticAction($1, $2); }
	| chord tab 				{ $$ = tabChordTabSemanticAction($1, $2); }
	| rest tab 					{ $$ = tabRestTabSemanticAction($1, $2); }
	| id tab					{ $$ = tabIdTabSemanticAction($1, $2); }
	| note 						{ $$ = tabNoteTabSemanticAction($1, NULL); }
	| chord						{ $$ = tabChordTabSemanticAction($1, NULL); }
	| rest 						{ $$ = tabRestTabSemanticAction($1, NULL); }
	| id 						{ $$ = tabIdTabSemanticAction($1, NULL); }
	;

/**
// expression: expression[left] ADD expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
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
*/
%% 
