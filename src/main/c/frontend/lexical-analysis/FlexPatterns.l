%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x MULTILINE_COMMENT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

("c"|"d"|"e"|"f"|"g"|"a"|"b")("#"|"b")?([:digit:]|"10")?(\(("w"|"h"|"q"|"i"|"s"|"t"|"x"|"o")\))?                                                { return NoteLexemeAction(createLexicalAnalyzerContext()); }
("C"|"D"|"E"|"F"|"G"|"A"|"B")("m"|"7"|"maj7"|"dim"|"aug"|"sus2"|"sus4")?(\(([:digit:]|"10")","([:space:])?("w"|"h"|"q"|"i"|"s"|"t"|"x"|"o")\))?("arp")?    { return ChordLexemeAction(createLexicalAnalyzerContext()); }
"R"(\(("w"|"h"|"q"|"i"|"s"|"t"|"x"|"o")\))?                                                                                                       { return RestLexemeAction(createLexicalAnalyzerContext()); }
("Note"|"Chord"|"Rest"|"Tab")[:space:][:alnum:]+
("Note"|"Chord"|"Rest"|"Tab")\(("c"|"d"|"e"|"f"|"g"|"a"|"b")("#"|"b")?","[:space:]?([:digit:]|"10")","\)             
("piano")           { return InstrumentLexemeAction(createLexicalAnalyzerContext()); }

"-"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"*"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"/"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"+"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
