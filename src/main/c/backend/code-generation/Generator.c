#include "Generator.h"
#include <sys/stat.h>
#include <sys/types.h>

#define TABSSENTENCECLASS 12345
#define SCORECLASS 67890
#define MAX_SCORES 50

/** PRIVATE FUNCTIONS */

char* parseComponents(char* str);
static char* parseChord(char* chordString);
static void _generateType(const unsigned int indentationLevel, type* type);
static void _generateId(const unsigned int indentationLevel, id* id);
static void _generateNote(const unsigned int indentationLevel, note* note, IDM id);
static void _generateNoteExpression(const unsigned int indentationLevel, noteExpression* noteExpression, IDM id);
static void _generateScore(const unsigned int indentationLevel, score* score);
static void _generateScoreExpressions(const unsigned int indentationLevel, scoreExpressions* scoreExpressions, IDM id);
static void _generateScoreExpression(const unsigned int indentationLevel, scoreExpression* scoreExpression, IDM id);
static void _generateDeclaration(const unsigned int indentationLevel, declaration* declaration, IDM id);
static void _generateSignature(const unsigned int indentationLevel, signature* signature, IDM id);
static void _generateTempo(const unsigned int indentationLevel, tempo* tempo, IDM id);
static void _generateInstruments(const unsigned int indentationLevel, instruments* instruments, IDM id);
static void _generateInstrument(const unsigned int indentationLevel, instrument* instrument, IDM id);
static void _generateClefDeclaration(const unsigned int indentationLevel, clefDeclaration* clefDeclaration, IDM id);
static void _generateClefSentence(const unsigned int indentationLevel, clefSentence* clefSentence, IDM id);
static void _generateSentences(const unsigned int indentationLevel, sentences* sentences, IDM id);
static void _generateSentence(const unsigned int indentationLevel, sentence* sentence, IDM id);
static void _generateChordExpression(const unsigned int indentationLevel, chordExpression* chordExpression, IDM id);
static void _generateChordValues(const unsigned int indentationLevel, chordValues* chordValues);
static void _generatePitch(const unsigned int indentationLevel, pitch* pitch, IDM id);
static void _generateTabExpression(const unsigned int indentationLevel, tabExpression* tabExpression, IDM id);
static void _generateTabValues(const unsigned int indentationLevel, tabValues* tabValues, IDM id);
static void _generateFormatedId(const unsigned int indentationLevel, id* id, IDM idm);
static void _generateRest(const unsigned int indentationLevel, rest* rest, IDM id);
static void _generateChord(const unsigned int indentationLevel, chord* chord, IDM id);
static void _generateTabsSentence(const unsigned int indentationLevel, tabsSentence* tabsSentence, IDM id);
static void _generateControlSentence(const unsigned int indentationLevel, controlSentence* controlSentence, IDM id);
static void _generateControl(const unsigned int indentationLevel, control* control, IDM id);
static void _generateTabs(const unsigned int indentationLevel, tabs* tabs, IDM id);
static void _generateTab(const unsigned int indentationLevel, tab* tab, IDM id);
static void _generateExpression(const unsigned int indentationLevel, Expression* expression, IDM id);
static void _generateAssignment(const unsigned int indentationLevel, assignment* assignment);
static void _generateProgramExpression(const unsigned int indentationLevel, programExpression* programExpression);
static void _generateExpressions(const unsigned int indentationLevel, expressions* expressions);
static void _generateProgram(Program* program);
static void _generatePrologue(void);
static void _generateClass(void);
static void _generateEpilogue(void);
static char* _indentation(const unsigned int level);
static void _output(FILE* file, const unsigned int indentationLevel, const char* const format, ...);
void generate(CompilerState* compilerState);
int correspondingExpression(int class);
int expressionType(Expression* e);
int assignmentType(assignment* a);
int idType(id* _id);
int noteType(note* n);
int pitchType(pitch* p);
int chordType(chord* c);
int chordValuesType(chordValues* _chordValues);
int tabType(tab* _tab);

/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;
int voices_amount = 0;
int score_amount = 0;
FILE * file = NULL;
FILE * pom = NULL;

void initializeDirectories() {
	mkdir("marimbash",0755);
	mkdir("marimbash/src", 0755);
	mkdir("marimbash/src/main", 0755);
	mkdir("marimbash/src/main/java", 0755);
	mkdir("marimbash/src/main/java/org", 0755);
	mkdir("marimbash/src/main/java/org/marimbash", 0755);
}

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
	initializeDirectories();
	file = fopen("marimbash/src/main/java/org/marimbash/MarimbaMusic.java", "w");
	pom = fopen("marimbash/pom.xml", "w");
	_output(pom, 0, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><project xmlns=\"http://maven.apache.org/POM/4.0.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\"><modelVersion>4.0.0</modelVersion><groupId>org.example</groupId><artifactId>MarimbaSh</artifactId><version>1.0-SNAPSHOT</version><repositories><repository><id>jitpack.io</id><url>https://jitpack.io</url></repository></repositories><dependencies><dependency><groupId>com.github.JensPiegsa</groupId><artifactId>jfugue</artifactId><version>5.0.9</version></dependency></dependencies><properties><maven.compiler.source>18</maven.compiler.source><maven.compiler.target>18</maven.compiler.target><project.build.sourceEncoding>UTF-8</project.build.sourceEncoding></properties></project>");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
		fclose(file);
		fclose(pom);
	}
}

void removeSpaces(char *str) {
    int count = 0;
     for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}




char* parseComponents(char* str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '(' && *src != ')' && *src != ',' && *src != ' ')
            *dst++ = *src;
        src++;
    }
    *dst = '\0';

    size_t len = strlen(str);
    if (len >= 3 && strcmp(str + len - 3, "arp") == 0) {
			char stringToCopy[5] = {0};
			stringToCopy[0] = ':';
			stringToCopy[1] = '$';
			stringToCopy[2] = '!';
			stringToCopy[3] = *(str+len-4);
			stringToCopy[4] = '\0';
      strcpy(str + len - 3, stringToCopy);
    }
    
    return str;
}

char chordS[32] = {0};

static char * parseChord(char * chordString) {
	int indexS = 4, indexOriginal = 1;
	if (chordString[1] == '(') {
		parseComponents(chordString);
		chordS[0] = chordString[0];
		chordS[1] = 'm';
		chordS[2] = 'a';
		chordS[3] = 'j';
		while (chordString[indexOriginal]) 
			chordS[indexS++] = chordString[indexOriginal++];
		chordS[indexS] = '\0';
		return chordS;
	} else {
		return parseComponents(chordString);
	}
	return "Should not get here\n";
}

static void _generateType(const unsigned int indentationLevel, type * type) {
	if (type->class == NOTECLASS || type->class == CHORDCLASS || type->class == TABCLASS || type->class == INTEGERCLASS ) {
		_output(file, indentationLevel, "String");
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", type->class);
	}
}

static void _generateId(const unsigned int indentationLevel, id * id) {
	_output(file, indentationLevel, " %s ", id->id);
}

static void _generateNote(const unsigned int indentationLevel, note * note, IDM id) {
	_output(file, indentationLevel, "%s += \" %s \";\n",id, parseComponents(note->note));
}

static void _generateNoteExpression(const unsigned int indentationLevel, noteExpression * noteExpression, IDM id) {
	pitchType(noteExpression->_pitch);
	_output(file, indentationLevel,"%s += \"I[%s]%s%d\";\n", id, noteExpression->_instrument->instrument, noteExpression->_note->note, noteExpression->_pitch->_pitch);
}

static void _generateScore(const unsigned int indentationLevel, score * score) {
	_output(file, indentationLevel, "String %s = \"\";\n", score->_id->id);
	voices_amount = 0;
	//para saber la cantidad de cosas que se tocan en simultaneo debe terminar de parsear todas las score
	_generateScoreExpressions(indentationLevel, score->scoreExpressions, score->_id->id);	
	addToTable(score->_id->id, SCORECLASS, NULL);
	_output(file, indentationLevel, "Pattern pattern%d = new Pattern(%s);\n", score_amount, score->_id->id);
	score_amount++;
}


//esta vaina pa la ejecucion simultanea >:D
static void _generateScoreExpressions(const unsigned int indentationLevel, scoreExpressions * scoreExpressions, IDM id) {
	if (scoreExpressions->type == SCOREEXPRESSIONSTYPE) {
		_output(file, indentationLevel, "%s += \" V%d \";\n", id, voices_amount);
		_generateScoreExpression(indentationLevel, scoreExpressions->_scoreExpression, id);
		voices_amount++; //un score es una sola voz
		//tantas voces como scores
		_generateScoreExpressions(indentationLevel, scoreExpressions->_scoreExpressions, id);
	} else {
		_output(file, indentationLevel, "%s += \" V%d \";\n", id, voices_amount);
		voices_amount++; //un score es una sola voz
		_generateScoreExpression(indentationLevel, scoreExpressions->_scoreExpression, id);
	}
}



static void _generateScoreExpression(const unsigned int indentationLevel, scoreExpression * scoreExpression, IDM id) {
	_generateDeclaration(indentationLevel, scoreExpression->_declaration, id);
	_generateInstruments(indentationLevel, scoreExpression->instruments, id);
}

static void _generateDeclaration(const unsigned int indentationLevel, declaration * declaration, IDM id) {
	_generateTempo(indentationLevel, declaration->_tempo, id);
	_generateSignature(indentationLevel, declaration->_signature, id);
}

static void _generateSignature(const unsigned int indentationLevel, signature * signature, IDM id) {
	removeSpaces(signature->signature);
	_output(file, indentationLevel, "%s += \" K%s \";\n",id,signature->signature);
}

static void _generateTempo(const unsigned int indentationLevel, tempo * tempo, IDM id) {
	_output(file, indentationLevel, "%s += \" T%d \";\n",id, tempo->tempo);
}

static void _generateInstruments(const unsigned int indentationLevel, instruments * instruments, IDM id) {
	_generateInstrument(indentationLevel, instruments->_instrument, id);
	_generateClefDeclaration(indentationLevel, instruments->_clefDeclaration, id);
	if (instruments->_instruments != NULL) {
		_generateInstruments(indentationLevel, instruments->_instruments, id);
	}
}

static void _generateInstrument(const unsigned int indentationLevel, instrument * instrument, IDM id) {
	_output(file, indentationLevel, "%s += \" I[%s] \";\n", id, instrument->instrument);
}

static void _generateClefDeclaration(const unsigned int indentationLevel, clefDeclaration * clefDeclaration, IDM id) {
	_generateClefSentence(indentationLevel, clefDeclaration->_clefSentence, id); 
	_generateSentences(indentationLevel, clefDeclaration->_sentences, id);
}

static void _generateClefSentence(const unsigned int indentationLevel, clefSentence * clefSentence, IDM id) {
	/** algo para hacer? */
}

static void _generateSentences(const unsigned int indentationLevel, sentences * sentences, IDM id) {
	if (sentences->sentencesType == SENTENCES) {
		_generateSentence(indentationLevel, sentences->_sentence_, id);
		_generateSentences(indentationLevel, sentences->_sentences, id);
	} else {
		_generateSentence(indentationLevel, sentences->_sentence, id);
	}
}

static void _generateSentence(const unsigned int indentationLevel, sentence * sentence, IDM id) {
	if (sentence->sentenceType == CLEFSENTENCE) {
		_generateClefSentence(indentationLevel, sentence->_clefSentence, id);
	} else {
		_generateTabsSentence(indentationLevel, sentence->_tabsSentence, id);
	}
}

static void _generateChordExpression(const unsigned int indentationLevel, chordExpression * chordExpression, IDM id) {
	_output(file, indentationLevel, "%s += ", id);
	_generateChordValues(indentationLevel, chordExpression->_chordValues);
}

static void _generateChordValues(const unsigned int indentationLevel, chordValues * chordValues) {
	chordValuesType(chordValues);
	if (chordValues->type == CHORDVALUES) {
		_output(file, indentationLevel, "\"%s+\" + ", chordValues->_note->note);
		_generateChordValues(indentationLevel, chordValues->_chordValues);
	} else if (chordValues->type == CHORDIDVALUES) { 
		_output(file, indentationLevel, "String.format(\"%%s\",%s) + ", chordValues->_id->id);
		_generateChordValues(indentationLevel, chordValues->_idChordVaues);
	} else if (chordValues->type == CHORDNOTE) {
		_output(file, indentationLevel, "\"%s\";\n", chordValues->note_->note);
	} else if (chordValues->type == CHORDIDNOTE) {
		_output(file, indentationLevel, "String.format(\"%%s\",%s);\n", chordValues->id_->id);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", chordValues->type);
	}
}

static void _generatePitch(const unsigned int indentationLevel, pitch * pitch, IDM id) {
	if (pitch->type == TERMINAL) {
		_output(file, indentationLevel, "%s += \"%d\";\n",id, pitch->_pitch);
	} else {
		_output(file, indentationLevel, "%s += String.format(\"%%s\",%s);\n", id, pitch->_id);
	}
}

static void _generateTabExpression(const unsigned int indentationLevel, tabExpression * tabExpression, IDM id) {
	_generateTabValues(indentationLevel, tabExpression->_tabValues, id);
}

static void _generateTabValues(const unsigned int indentationLevel, tabValues * tabValues, IDM id) {
	tabValuesTypeCheck(tabValues);
	if (tabValues->type == NOTETABVALUES) {
		_generateNote(indentationLevel, tabValues->_note, id);
		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == CHORDTABVALUES) {
		_generateChord(indentationLevel, tabValues->_chord, id);
		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == RESTTABVALUES) {
		_generateRest(indentationLevel, tabValues->_rest, id);
		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == IDTABVALUES) {
		_generateFormatedId(indentationLevel, tabValues->_id, id);
		_generateTabValues(indentationLevel, tabValues->_tabValues, id);
	} else if (tabValues->type == TABVALUESNOTE) {
		_generateNote(indentationLevel, tabValues->_note, id);
	} else if (tabValues->type == TABVALUESCHORD) {
		_generateChord(indentationLevel, tabValues->_chord, id);
	} else if (tabValues->type == TABVALUESREST) {
		_generateRest(indentationLevel, tabValues->_rest, id);
	} else if (tabValues->type == TABVALUESID) {
		_generateFormatedId(indentationLevel, tabValues->_id, id);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", tabValues->type);
	}
}

static void _generateFormatedId(const unsigned indentationLevel, id * id, IDM idm) {
	_output(file, indentationLevel,"%s += String.format(\"%%s\",%s);\n",idm, id->id);
}

static void _generateRest(const unsigned indentationLevel, rest * rest, IDM id) {
	_output(file, indentationLevel, "%s += \" %s \";\n", id, parseComponents(rest->rest));
} 

static void _generateChord(const unsigned indentationLevel, chord * chord, IDM id) {
	_output(file, indentationLevel, "%s += \" %s \";\n", id, parseChord(chord->chord));
}

static void _generateTabsSentence(const unsigned int indentationLevel, tabsSentence * tabsSentence, IDM id) {
	if (tabsSentence->type == TABSSENTENCEWITHID) {
		_output(file, indentationLevel, "String %s = \"\";\n", tabsSentence->_id->id);
		_generateTabs(indentationLevel, tabsSentence->_tabs, tabsSentence->_id->id);
		_output(file, indentationLevel, "%s += %s;\n", id, tabsSentence->_id->id);
		_generateControlSentence(indentationLevel, tabsSentence->_control, id);
		addToTable(tabsSentence->_id->id,TABSSENTENCECLASS, NULL);
	} else if (tabsSentence->type == TABSSENTENCEWITHONLYID) {
		tabsSentenceTypeCheck(tabsSentence);
		_generateControlSentence(indentationLevel, tabsSentence->_control, id);
		_output(file, indentationLevel, "%s += \" \" + String.format(\"%%s\",%s) +\" \";\n", id, tabsSentence->_id);
	} else if (tabsSentence->type == TABSSENTENCENOID) {
		_generateTabs(indentationLevel, tabsSentence->_tabs, id);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", tabsSentence->type);
	}
}

static void _generateControlSentence(const unsigned int indentationLevel, controlSentence * controlSentence, IDM id) {
	if (controlSentence->_control != NULL) {
		_generateControl(indentationLevel, controlSentence->_control, id);
	} else {
		/** algo para hacer? */
	}
}

static void _generateControl(const unsigned int indentationLevel, control * control, IDM id) {
	if (control->type == REPEATT) {
		_output(file, indentationLevel, "for (int bIkbl6iUiyoaLbBplOnLw8PWppO6PvlruJmXysx4RU=0;bIkbl6iUiyoaLbBplOnLw8PWppO6PvlruJmXysx4RU<%d;bIkbl6iUiyoaLbBplOnLw8PWppO6PvlruJmXysx4RU++) {\n", control->_repeat->_repeat);
		_output(file, indentationLevel, "%s += %s;\n", id, id);
		_output(file, indentationLevel, "}\n");
		_generateControl(indentationLevel, control->_control, id);
	} else if (control->type == AFTERT) {
		afterType(control->_after);
		_output(file, indentationLevel, "%s += %s;\n", control->_after->_id, id);
		_generateControl(indentationLevel, control->_control, id);
	} else if (control->type == BEFORET) {
		beforeType(control->_before);
		_output(file, indentationLevel, "%s = %s + %s;\n", control->_before->_id, id, control->_before->_id);
		_generateControl(indentationLevel, control->_control, id);
	} else if (control->type == ALONGT) {

		_generateControl(indentationLevel, control->_control, id);
	} else {
		/** algo para hacer? */
	}
}

static void _generateTabs(const unsigned int indentationLevel, tabs * tabs, IDM id) {
	if (tabs->tabsType == TABSTYPE) {
		_generateTab(indentationLevel, tabs->_tab_, id);
		_generateTabs(indentationLevel, tabs->_tabs, id);
	} else if (tabs->tabsType == TABTYPE) {
		_generateTab(indentationLevel, tabs->_tab, id);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", tabs->tabsType);
	}
}

static void _generateTab(const unsigned int indentationLevel, tab * tab, IDM id) {
	tabType(tab);
	if (tab->tabType == NOTETYPE && tab->_tab != NULL) {
		_output(file, indentationLevel, "%s += \" %s \";\n", id, parseComponents(tab->_note->note));
		_generateTab(indentationLevel, tab->_tab, id);
	} else if (tab->tabType == CHORDTYPE && tab->_tab != NULL) {
		_output(file, indentationLevel, "%s += \" %s \";\n", id, parseChord(tab->_chord->chord));
		_generateTab(indentationLevel, tab->_tab, id);
	} else if (tab->tabType == RESTTYPE && tab->_tab != NULL) {
		_output(file, indentationLevel, "%s += \" %s \";\n", id, parseComponents(tab->_rest->rest));
		_generateTab(indentationLevel, tab->_tab, id);
	} else if (tab->tabType == IDTYPE && tab->_tab != NULL) {
		_output(file, indentationLevel, "%s += \" \" + String.format(\"%%s\",%s) + \" \";\n", id, parseComponents(tab->_note->note));
		_generateTab(indentationLevel, tab->_tab, id);
	} else if (tab->tabType == NOTETYPE && tab->_tab == NULL) {
		_output(file, indentationLevel, "%s += \" %s \";\n", id, parseComponents(tab->_note->note));
	} else if (tab->tabType == CHORDTYPE && tab->_tab == NULL) {
		_output(file, indentationLevel, "%s += \" %s \";\n", id, parseChord(tab->_chord->chord));
	} else if (tab->tabType == RESTTYPE && tab->_tab == NULL) {
		_output(file, indentationLevel, "%s += \" %s \";\n", id, parseComponents(tab->_rest->rest));
	} else if (tab->tabType == IDTYPE && tab->_tab == NULL) {
		_output(file, indentationLevel, "%s += \" \" + String.format(\"%%s\",%s) + \" \";\n", id, parseComponents(tab->_note->note));
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", tab->tabType);
	}
}

static void _generateExpression(const unsigned int indentationLevel, Expression * expression, IDM id) {
	if (expression->type == NOTEEXPRESSION) {
		_generateNoteExpression(indentationLevel, expression->noteExpression, id);
	} else if (expression->type == SCOREEXPRESSION) {
		_generateScore(indentationLevel, expression->_score);
	} else if (expression->type == CHORDEXPRESSION) {
		_generateChordExpression(indentationLevel, expression->_chordExpression, id);
	} else if (expression->type == PITCHEXPRESSION) {
		_generatePitch(indentationLevel, expression->_pitch, id);
	} else if (expression->type == TABEXPRESSIONTYPE) {
		_generateTabExpression(indentationLevel, expression->_tabExpression, id);
	} else if (expression->type == TABSENTENCETYPE) {
		_generateTabsSentence(indentationLevel, expression->_tabsSentence, id);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d", expression->type);
	}
}

static void _generateAssignment(const unsigned int indentationLevel, assignment * assignment) {
	_generateType(indentationLevel, assignment->_class);
	_generateId(indentationLevel, assignment->_id);
	addToTable(assignment->_id, assignment->_class->class, NULL); //TODO init???????????????
	assignmentType(assignment);
	_output(file, indentationLevel, " = \"\";\n");
	_generateExpression(indentationLevel, assignment->expression, assignment->_id->id);
}


static void _generateProgramExpression(const unsigned int indentationLevel, programExpression * programExpression) {
	if (programExpression->type == ASSIGNMENT) {
		_generateAssignment(indentationLevel, programExpression->assignment);
	} else if (programExpression->type == EXPRESSION) {
		_generateExpression(indentationLevel, programExpression->expression, "");
	} else {
		logError(_logger, "The specified expressions type is unknown: %d\n", programExpression->type);
	}
}

static void _generateExpressions(const unsigned int indentationLevel, expressions * expressions) {
	if (expressions->type == EXPRESSIONSTYPE) {
			_generateProgramExpression(1 + indentationLevel, expressions->_programExpression);
			_generateExpressions(1 + indentationLevel, expressions->expressions);
	} else if (expressions->type == PROGRAMEXPRESSIONTYPE) {
			_generateProgramExpression(1 + indentationLevel, expressions->programExpression_);
	} else {
		logError(_logger, "The specified expressions type is unknown: %d\n", expressions->type);
	}
}

/**
 * Generates the output of the program.
 */
static void _generateProgram(Program * program) {
	_generateExpressions(3, program->_expressions);
}

static void _generatePrologue(void) {
	_output(file, 0, "%s",
		"package org.marimbash;\n"
		"import org.jfugue.*;\n"
		"import org.jfugue.player.Player;\n"
		"import org.jfugue.pattern.Pattern;\n"
		"import org.jfugue.midi.MidiFileManager;\n"
		"import java.io.File;\n"
		"import java.io.IOException;\n"
		"import java.util.List;\n"
		"import java.util.ArrayList;\n"
	);
}

static void _generateClass(void) {
	_output(file, 0, "%s",
		"public class MarimbaMusic {\n"
		"		public static void main(String[] args) throws Exception, RuntimeException {\n"
		"			Player player = new Player();\n"
		"			List<String> alongs = new ArrayList<>();\n"
	);
}

static void _generateEpilogue() {
	_output(file, 0, "%s",
		"			try {\n"
		"					File filePath = new File(\"marimbash/output.mid\");\n"
		"   			MidiFileManager.savePatternToMidi(pattern, filePath);\n"
		"					ProcessBuilder processBuilder = new ProcessBuilder(\"musescore\",\"-o\", \"marimbash/output.pdf\",\"marimbash/output.mid\");\n"
		"					Process process = processBuilder.start();\n"
		"					int exitCode = process.waitFor();\n"
		"			} catch (IOException | InterruptedException ex) {\n"
		"					ex.printStackTrace();\n"
		"			}\n"
		"		}\n"
		"}\n"
	);
}

/**
 * Generates an indentation string for the specified level.
 */
static char * _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}

/**
 * Outputs a formatted string to standard output.
 */
static void _output(FILE * file, const unsigned int indentationLevel, const char * const format, ...) {
	if (file == NULL) {
        // If file pointer is NULL, opening the file failed
        perror("Error opening file");
        return;
    }
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(file, effectiveFormat, arguments);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState * compilerState) {
	logDebugging(_logger, "Generating final output...");
	_generatePrologue();
	_generateClass();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue();
	logDebugging(_logger, "Generation is done.");
}


/* TYPE FUNCTIONS */
int correspondingExpression(int class){
	switch (class){
	case INTEGERCLASS: return PITCHEXPRESSION;
	case NOTECLASS: return NOTEEXPRESSION;
	case CHORDCLASS: return CHORDEXPRESSION;
	case TABCLASS: return TABEXPRESSIONTYPE;
	default: return -1;
	}
}

int expressionType(Expression * e) {
	return e->type;
}

int assignmentType(assignment * a) {
	int t = a->_class->class;
	if (correspondingExpression(t) == expressionType(a->expression)) return t;
	logError(_logger, "The expression does not match the declaration type.");
	return -1;
}

int idType(id * _id){
	return getType(_id->id);
}

int noteType(note * n) {
	if (n->type == NONTERMINAL) {
		if(idType(n->_id) != NOTECLASS) {
			logError(_logger, "Incorrect variable type. Expected: Note");
			return -1;
		}
	}
	return NOTECLASS;
}

int pitchType(pitch * p) {
	if (p->type == NONTERMINAL) {
		if(idType(p->_id) != INTEGERCLASS) {
			logError(_logger, "Incorrect variable type. Expected: Integer");
			return -1;
		}
	}
	return INTEGERCLASS;
}

int chordType(chord * c) {
	if (c->type == NONTERMINAL) {
		if(idType(c->_id) != CHORDCLASS) {
			logError(_logger, "Incorrect variable type. Expected: Chord");
			return -1;
		}
	}
	return CHORDCLASS;
}

int chordValuesType(chordValues * _chordValues) {
	if(_chordValues->type == CHORDIDVALUES){
		if(idType(_chordValues->_id) != NOTECLASS) {
			logError(_logger, "Incompatible variable type for chord. Expected: Note");
			return -1;
		}
	}
	if(_chordValues->type == CHORDIDNOTE){
		if(idType(_chordValues->id_) != NOTECLASS) {
			logError(_logger, "Incompatible variable type for chord. Expected: Note");
			return -1;
		}
	}
	return _chordValues->type;
}

int tabType(tab * _tab) {
	if(_tab->tabType == IDTYPE) {
		if(idType(_tab->_id) != CHORDCLASS || idType(_tab->_id) != NOTECLASS) {
			logError(_logger, "Incompatible variable type for tab. Expected: Note or Chord");
			return -1;
		}
	}
	return _tab->tabType;
}

int tabValuesTypeCheck(tabValues * _tabValues) {
	if(_tabValues->type == IDTABVALUES || _tabValues->type == TABVALUESID) {
		//los ids que se usan para generr un tab solo pueden ser notas o acordes
		if(idType(_tabValues->_id) != CHORDCLASS || idType(_tabValues->_id) != NOTECLASS) {
			logError(_logger, "Incompatible variable type for tab. Expected: Note or Chord");
			return -1;
		}
	}
	return _tabValues->type;
}

int tabsSentenceTypeCheck(tabsSentence * _tabsSentence) {
	if(_tabsSentence->type == TABSSENTENCEWITHONLYID) {
		if(idType(_tabsSentence->_id) != TABSSENTENCECLASS) {
			logError(_logger, "Incorrect variable type. Expected: tabs");
			return -1;
		}
	}
	return _tabsSentence->type;
}

int afterType(after * _after) {
	if(idType(_after->_id) != TABSSENTENCECLASS || idType(_after->_id) != TABCLASS) {
		logError(_logger, "Incorrect variable type. Expected: Tab or tabs");
		return -1;
	} 
}

int beforeType(before * _before) {
	if(idType(_before->_id) != TABSSENTENCECLASS || idType(_before->_id) != TABCLASS) {
		logError(_logger, "Incorrect variable type. Expected: Tab or tabs");
		return -1;
	} 
}


// int noteExpressionType(noteExpression * _noteExpression) {
// 	if(_noteExpression->_pitch->type == NONTERMINAL) {
// 		if(idType(_noteExpression->_pitch->_id) != INTEGERCLASS)
// 	}
// }


