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

("c"|"d"|"e"|"f"|"g"|"a"|"b")("#"|"b")?([[:digit:]]|"10")?("("("w"|"h"|"q"|"i"|"s"|"t"|"x"|"o")")")? { return NoteLexemeAction(createLexicalAnalyzerContext()); }
("C"|"D"|"E"|"F"|"G"|"A"|"B")("m"|"7"|"maj7"|"dim"|"aug"|"sus2"|"sus4")?("("(([[:digit:]]|"10")",")?([[:space:]]+)?("w"|"h"|"q"|"i"|"s"|"t"|"x"|"o")")")?("arp")? { return ChordLexemeAction(createLexicalAnalyzerContext()); }
"R"("("("w"|"h"|"q"|"i"|"s"|"t"|"x"|"o")")")? { return RestLexemeAction(createLexicalAnalyzerContext()); }
("clefF"|"clefG"|"clefC")   { return ClefValueLexemeAction(createLexicalAnalyzerContext()); }

"Integer"           { return ClassLexemeAction(createLexicalAnalyzerContext()); }                                                                                                       
"Note"              { return ClassLexemeAction(createLexicalAnalyzerContext()); }
"Chord"             { return ClassLexemeAction(createLexicalAnalyzerContext()); }
"Rest"              { return ClassLexemeAction(createLexicalAnalyzerContext()); }
"Tab"               { return ClassLexemeAction(createLexicalAnalyzerContext()); }

"|"                 { return PipeLexemeAction(createLexicalAnalyzerContext()); }

[[:digit:]]([[:space:]]+)?"/"([[:space:]]+)?("2"|"4"|"8"|"16"|"32"|"64"|"128") { return SignatureValueLexemeAction(createLexicalAnalyzerContext()); } 

("piano"|"marimba"|"guitar"|"trumpet"|"trombone")           { return InstrumentLexemeAction(createLexicalAnalyzerContext()); }

"score"                             { return ScoreLexemeAction(createLexicalAnalyzerContext()); }
"tempo"                             { return TempoLexemeAction(createLexicalAnalyzerContext()); }
"signature"                         { return SignatureLexemeAction(createLexicalAnalyzerContext()); }
"clef"                              { return ClefLexemeAction(createLexicalAnalyzerContext()); }
"tabs"                              { return TabsLexemeAction(createLexicalAnalyzerContext()); }
"."                                 { return DotLexemeAction(createLexicalAnalyzerContext()); }
"after"                             { return ConditionalLexemeAction(createLexicalAnalyzerContext()); }
"before"                            { return ConditionalLexemeAction(createLexicalAnalyzerContext()); }
"along"                             { return ConditionalLexemeAction(createLexicalAnalyzerContext()); }
"repeat("[[:digit:]]+")"            { return RepetitionLexemeAction(createLexicalAnalyzerContext()); }
"transpose("("-")?[[:digit:]]+")"   { return TranspositionLexemeAction(createLexicalAnalyzerContext()); }
";"                                 { return SemicolonLexemeAction(createLexicalAnalyzerContext()); }
                                            
"="                                 { return EqualLexemeAction(createLexicalAnalyzerContext()); }
                
","                                 { return CommaLexemeAction(createLexicalAnalyzerContext()); }
                
"{"                                 { return BracesLexemeAction(createLexicalAnalyzerContext()); }
"}"                                 { return BracesLexemeAction(createLexicalAnalyzerContext()); }
                
"("									                { return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									                { return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
                
[[:digit:]]+				                { return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:alnum:]]+                        { return IDLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+			                	{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									                  { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
