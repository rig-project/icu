/*
 *******************************************************************************
 *
 *   Copyright (C) 1999-2000, International Business Machines
 *   Corporation and others.  All Rights Reserved.
 *
 *******************************************************************************
 *   file name:  gendata.cpp
 *
 *   created on: 11/03/2000
 *   created by: Eric R. Mader
 */

#include <stdio.h>

#include "unicode/utypes.h"
#include "unicode/uscript.h"
#include "unicode/unicode.h"
#include "unicode/locid.h"
#include "unicode/loengine.h"

#include "PortableFontInstance.h"

#define ARRAY_LENGTH(array) (sizeof array / sizeof array[0])

struct TestInput
{
	char *fontName;
	UChar *text;
	int32_t textLength;
	UScriptCode scriptCode;
	UBool rightToLeft;
};

/* 
 * FIXME: should use the output file name and the current date.
 */
char *header =
	"/*\n"
	" *******************************************************************************\n"
	" *\n"
	" *   Copyright (C) 1999-2000, International Business Machines\n"
	" *   Corporation and others.  All Rights Reserved.\n"
	" *\n"
	" *   WARNING: THIS FILE IS MACHINE GENERATED. DO NOT HAND EDIT IT\n"
	" *   UNLESS YOU REALLY KNOW WHAT YOU'RE DOING.\n"
	" *\n"
	" *******************************************************************************\n"
	" *\n"
	" *   file name:  testdata.cpp\n"
	" *   created on: 12/14/2000\n"
	" *   created by: gendata.cpp\n"
	" */\n"
	"\n"
	"#include \"unicode/utypes.h\"\n"
	"#include \"unicode/uscript.h\"\n"
	"#include \"letest.h\"\n"
	"\n";

char *scriptNames[] =
{
      "USCRIPT_COMMON",      /* Zyyy */
      "USCRIPT_INHERITED",   /* Qaai */
      "USCRIPT_ARABIC",      /* Arab */
      "USCRIPT_ARMENIAN",    /* Armn */
      "USCRIPT_BENGALI",     /* Beng */
      "USCRIPT_BOPOMOFO",    /* Bopo */
      "USCRIPT_CHEROKEE",    /* Cher */
      "USCRIPT_COPTIC",      /* Qaac */
      "USCRIPT_CYRILLIC",    /* Cyrl (Cyrs) */
      "USCRIPT_DESERET",     /* Dsrt */
      "USCRIPT_DEVANAGARI",  /* Deva */
      "USCRIPT_ETHIOPIC",    /* Ethi */
      "USCRIPT_GEORGIAN",    /* Geor (Geon, Geoa) */
      "USCRIPT_GOTHIC",      /* Goth */
      "USCRIPT_GREEK",       /* Grek */
      "USCRIPT_GUJARATI",    /* Gujr */
      "USCRIPT_GURMUKHI",    /* Guru */
      "USCRIPT_HAN",         /* Hani */
      "USCRIPT_HANGUL",      /* Hang */
      "USCRIPT_HEBREW",      /* Hebr */
      "USCRIPT_HIRAGANA",    /* Hira */
      "USCRIPT_KANNADA",     /* Knda */
      "USCRIPT_KATAKANA",    /* Kata */
      "USCRIPT_KHMER",       /* Khmr */
      "USCRIPT_LAO",         /* Laoo */
      "USCRIPT_LATIN",       /* Latn (Latf, Latg) */
      "USCRIPT_MALAYALAM",   /* Mlym */
      "USCRIPT_MONGOLIAN",   /* Mong */
      "USCRIPT_MYANMAR",     /* Mymr */
      "USCRIPT_OGHAM",       /* Ogam */
      "USCRIPT_OLD_ITALIC",  /* Ital */
      "USCRIPT_ORIYA",       /* Orya */
      "USCRIPT_RUNIC",       /* Runr */
      "USCRIPT_SINHALA",     /* Sinh */
      "USCRIPT_SYRIAC",      /* Syrc (Syrj, Syrn, Syre) */
      "USCRIPT_TAMIL",       /* Taml */
      "USCRIPT_TELUGU",      /* Telu */
      "USCRIPT_THAANA",      /* Thaa */
      "USCRIPT_THAI",        /* Thai */
      "USCRIPT_TIBETAN",     /* Tibt */
      "USCRIPT_UCAS",        /* Cans */
      "USCRIPT_YI",          /* Yiii */
};

UChar devaText[] =
{
    0x0936, 0x094d, 0x0930, 0x0940, 0x092e, 0x0926, 0x094d, 0x0020,
    0x092d, 0x0917, 0x0935, 0x0926, 0x094d, 0x0917, 0x0940, 0x0924,
	0x093e, 0x0020, 0x0905, 0x0927, 0x094d, 0x092f, 0x093e, 0x092f,
	0x0020, 0x0905, 0x0930, 0x094d, 0x091c, 0x0941, 0x0928, 0x0020,
    0x0935, 0x093f, 0x0937, 0x093e, 0x0926, 0x0020, 0x092f, 0x094b,
	0x0917, 0x0020, 0x0927, 0x0943, 0x0924, 0x0930, 0x093e, 0x0937,
	0x094d, 0x091f, 0x094d, 0x0930, 0x0020, 0x0909, 0x0935, 0x093E,
	0x091A, 0x0943, 0x0020, 0x0927, 0x0930, 0x094d, 0x092e, 0x0915,
	0x094d, 0x0937, 0x0947, 0x0924, 0x094d, 0x0930, 0x0947, 0x0020,
    0x0915, 0x0941, 0x0930, 0x0941, 0x0915, 0x094d, 0x0937, 0x0947,
	0x0924, 0x094d, 0x0930, 0x0947, 0x0020, 0x0938, 0x092e, 0x0935,
	0x0947, 0x0924, 0x093e, 0x0020, 0x092f, 0x0941, 0x092f, 0x0941,
	0x0924, 0x094d, 0x0938, 0x0935, 0x0903, 0x0020, 0x092e, 0x093e,
	0x092e, 0x0915, 0x093e, 0x0903, 0x0020, 0x092a, 0x093e, 0x0923,
	0x094d, 0x0921, 0x0935, 0x093e, 0x0936, 0x094d, 0x091a, 0x0948,
	0x0935, 0x0020, 0x0915, 0x093f, 0x092e, 0x0915, 0x0941, 0x0930,
	0x094d, 0x0935, 0x0924, 0x0020, 0x0938, 0x0902, 0x091c, 0x0935
};

int32_t devaTextLength = ARRAY_LENGTH(devaText);

UChar arabText[] =
{
	0x0623, 0x0633, 0x0627, 0x0633, 0x064B, 0x0627, 0x060C, 0x0020, 
	0x062A, 0x062A, 0x0639, 0x0627, 0x0645, 0x0644, 0x0020, 
	0x0627, 0x0644, 0x062D, 0x0648, 0x0627, 0x0633, 0x064A, 0x0628, 
	0x0020, 0x0641, 0x0642, 0x0637, 0x0020, 0x0645, 0x0639, 0x0020, 
	0x0627, 0x0644, 0x0623, 0x0631, 0x0642, 0x0627, 0x0645, 0x060C, 
	0x0020, 0x0648, 0x062A, 0x0642, 0x0648, 0x0645, 0x0020, 0x0628, 
	0x062A, 0x062E, 0x0632, 0x064A, 0x0646, 0x0020, 0x0627, 0x0644, 
	0x0623, 0x062D, 0x0631, 0x0641, 0x0020, 0x0648, 0x0627, 0x0644, 
	0x0645, 0x062D, 0x0627, 0x0631, 0x0641, 0x0020, 0x0627, 0x0644, 
	0x0623, 0x062E, 0x0631, 0x0649, 0x0020, 0x0628, 0x0639, 0x062F, 
	0x0020, 0x0623, 0x0646, 0x0020, 0x062A, 0x064F, 0x0639, 0x0637, 
	0x064A, 0x0020, 0x0631, 0x0642, 0x0645, 0x0627, 0x0020, 0x0645, 
	0x0639, 0x064A, 0x0646, 0x0627, 0x0020, 0x0644, 0x0643, 0x0644, 
	0x0020, 0x0648, 0x0627, 0x062D, 0x062F, 0x0020, 0x0645, 0x0646, 
	0x0647, 0x0627, 0x002E, 0x0020, 0x0648, 0x0642, 0x0628, 0x0644, 
	0x0020, 0x0627, 0x062E, 0x062A, 0x0631, 0x0627, 0x0639, 0x0020, 
	0x0022, 0x064A, 0x0648, 0x0646, 0x0650, 0x0643, 0x0648, 0x062F, 
	0x0022, 0x060C, 0x0020, 0x0643, 0x0627, 0x0646, 0x0020, 0x0647, 
	0x0646, 0x0627, 0x0643, 0x0020, 0x0645, 0x0626, 0x0627, 0x062A, 
	0x0020, 0x0627, 0x0644, 0x0623, 0x0646, 0x0638, 0x0645, 0x0629, 
	0x0020, 0x0644, 0x0644, 0x062A, 0x0634, 0x0641, 0x064A, 0x0631, 
	0x0020, 0x0648, 0x062A, 0x062E, 0x0635, 0x064A, 0x0635, 0x0020, 
	0x0647, 0x0630, 0x0647, 0x0020, 0x0627, 0x0644, 0x0623, 0x0631, 
	0x0642, 0x0627, 0x0645, 0x0020, 0x0644, 0x0644, 0x0645, 0x062D, 
	0x0627, 0x0631, 0x0641, 0x060C, 0x0020, 0x0648, 0x0644, 0x0645, 
	0x0020, 0x064A, 0x0648, 0x062C, 0x062F, 0x0020, 0x0646, 0x0638, 
	0x0627, 0x0645, 0x0020, 0x062A, 0x0634, 0x0641, 0x064A, 0x0631, 
	0x0020, 0x0648, 0x0627, 0x062D, 0x062F, 0x0020, 0x064A, 0x062D, 
	0x062A, 0x0648, 0x064A, 0x0020, 0x0639, 0x0644, 0x0649, 0x0020, 
	0x062C, 0x0645, 0x064A, 0x0639, 0x0020, 0x0627, 0x0644, 0x0645, 
	0x062D, 0x0627, 0x0631, 0x0641, 0x0020, 0x0627, 0x0644, 0x0636, 
	0x0631, 0x0648, 0x0631, 0x064A, 0x0629
	
	/* The next few sentences...
	0x002E, 0x0020, 0x0648, 
	0x0639, 0x0644, 0x0649, 0x0020, 0x0633, 0x0628, 0x064A, 0x0644, 
	0x0020, 0x0627, 0x0644, 0x0645, 0x062B, 0x0627, 0x0644, 0x060C, 
	0x0020, 0x0641, 0x0625, 0x0646, 0x0020, 0x0627, 0x0644, 0x0627, 
	0x062A, 0x062D, 0x0627, 0x062F, 0x0020, 0x0627, 0x0644, 0x0623, 
	0x0648, 0x0631, 0x0648, 0x0628, 0x064A, 0x0020, 0x0644, 0x0648, 
	0x062D, 0x062F, 0x0647, 0x060C, 0x0020, 0x0627, 0x062D, 0x062A, 
	0x0648, 0x0649, 0x0020, 0x0627, 0x0644, 0x0639, 0x062F, 0x064A, 
	0x062F, 0x0020, 0x0645, 0x0646, 0x0020, 0x0627, 0x0644, 0x0634, 
	0x0641, 0x0631, 0x0627, 0x062A, 0x0020, 0x0627, 0x0644, 0x0645, 
	0x062E, 0x062A, 0x0644, 0x0641, 0x0629, 0x0020, 0x0644, 0x064A, 
	0x063A, 0x0637, 0x064A, 0x0020, 0x062C, 0x0645, 0x064A, 0x0639, 
	0x0020, 0x0627, 0x0644, 0x0644, 0x063A, 0x0627, 0x062A, 0x0020, 
	0x0627, 0x0644, 0x0645, 0x0633, 0x062A, 0x062E, 0x062F, 0x0645, 
	0x0629, 0x0020, 0x0641, 0x064A, 0x0020, 0x0627, 0x0644, 0x0627, 
	0x062A, 0x062D, 0x0627, 0x062F, 0x002E, 0x0020, 0x0648, 0x062D, 
	0x062A, 0x0649, 0x0020, 0x0644, 0x0648, 0x0020, 0x0627, 0x0639, 
	0x062A, 0x0628, 0x0631, 0x0646, 0x0627, 0x0020, 0x0644, 0x063A, 
	0x0629, 0x0020, 0x0648, 0x0627, 0x062D, 0x062F, 0x0629, 0x060C, 
	0x0020, 0x0643, 0x0627, 0x0644, 0x0644, 0x063A, 0x0629, 0x0020, 
	0x0627, 0x0644, 0x0625, 0x0646, 0x062C, 0x0644, 0x064A, 0x0632, 
	0x064A, 0x0629, 0x060C, 0x0020, 0x0641, 0x0625, 0x0646, 0x0020, 
	0x062C, 0x062F, 0x0648, 0x0644, 0x0020, 0x0634, 0x0641, 0x0631, 
	0x0629, 0x0020, 0x0648, 0x0627, 0x062D, 0x062F, 0x0020, 0x0644, 
	0x0645, 0x0020, 0x064A, 0x0643, 0x0641, 0x0020, 0x0644, 0x0627, 
	0x0633, 0x062A, 0x064A, 0x0639, 0x0627, 0x0628, 0x0020, 0x062C, 
	0x0645, 0x064A, 0x0639, 0x0020, 0x0627, 0x0644, 0x0623, 0x062D, 
	0x0631, 0x0641, 0x0020, 0x0648, 0x0639, 0x0644, 0x0627, 0x0645, 
	0x0627, 0x062A, 0x0020, 0x0627, 0x0644, 0x062A, 0x0631, 0x0642, 
	0x064A, 0x0645, 0x0020, 0x0648, 0x0627, 0x0644, 0x0631, 0x0645, 
	0x0648, 0x0632, 0x0020, 0x0627, 0x0644, 0x0641, 0x0646, 0x064A, 
	0x0629, 0x0020, 0x0648, 0x0627, 0x0644, 0x0639, 0x0644, 0x0645, 
	0x064A, 0x0629, 0x0020, 0x0627, 0x0644, 0x0634, 0x0627, 0x0626, 
	0x0639, 0x0629, 0x0020, 0x0627, 0x0644, 0x0627, 0x0633, 0x062A, 
	0x0639, 0x0645, 0x0627, 0x0644, 0x002E */
};
int32_t arabTextLength = ARRAY_LENGTH(arabText);


UChar thaiSample[] =
{
	0x0E1A, 0x0E17, 0x0E17, 0x0E35, 0x0E48, 0x0E51, 0x0E1E, 0x0E32,
	0x0E22, 0x0E38, 0x0E44, 0x0E0B, 0x0E42, 0x0E04, 0x0E25, 0x0E19,
	0x0E42, 0x0E14, 0x0E42, 0x0E23, 0x0E18, 0x0E35, 0x0E2D, 0x0E32, 
	0x0E28, 0x0E31, 0x0E22, 0x0E2D, 0x0E22, 0x0E39, 0x0E48, 0x0E17,
	0x0E48, 0x0E32, 0x0E21, 0x0E01, 0x0E25, 0x0E32, 0x0E07, 0x0E17,
	0x0E38, 0x0E48, 0x0E07, 0x0E43, 0x0E2B, 0x0E0D, 0x0E48, 0x0E43,
	0x0E19, 0x0E41, 0x0E04, 0x0E19, 0x0E0B, 0x0E31, 0x0E2A, 0x0E01, 
	0x0E31, 0x0E1A, 0x0E25, 0x0E38, 0x0E07, 0x0E40, 0x0E2E, 0x0E19,
	0x0E23, 0x0E35, 0x0E0A, 0x0E32, 0x0E27, 0x0E44, 0x0E23, 0x0E48,
	0x0E41, 0x0E25, 0x0E30, 0x0E1B, 0x0E49, 0x0E32, 0x0E40, 0x0E2D,
	0x0E47, 0x0E21, 0x0E20, 0x0E23, 0x0E23, 0x0E22, 0x0E32, 0x0E0A,
	0x0E32, 0x0E27, 0x0E44, 0x0E23, 0x0E48, 0x0E1A, 0x0E49, 0x0E32,
	0x0E19, 0x0E02, 0x0E2D, 0x0E07, 0x0E1E, 0x0E27, 0x0E01, 0x0E40, 
	0x0E02, 0x0E32, 0x0E2B, 0x0E25, 0x0E31, 0x0E07, 0x0E40, 0x0E25,
	0x0E47, 0x0E01, 0x0E40, 0x0E1E, 0x0E23, 0x0E32, 0x0E30, 0x0E44,
	0x0E21, 0x0E49, 0x0E2A, 0x0E23, 0x0E49, 0x0E32, 0x0E07, 0x0E1A,
	0x0E49, 0x0E32, 0x0E19, 0x0E15, 0x0E49, 0x0E2D, 0x0E07, 0x0E02, 
	0x0E19, 0x0E21, 0x0E32, 0x0E14, 0x0E49, 0x0E27, 0x0E22, 0x0E40,
	0x0E01, 0x0E27, 0x0E35, 0x0E22, 0x0E19, 0x0E40, 0x0E1B, 0x0E47,
	0x0E19, 0x0E23, 0x0E30, 0x0E22, 0x0E30, 0x0E17, 0x0E32, 0x0E07,
	0x0E2B, 0x0E25, 0x0E32, 0x0E22, 0x0E44, 0x0E21, 0x0E25, 0x0E4C
	/* A few more lines...
	0x0E1A, 0x0E49, 0x0E32, 0x0E19, 0x0E21, 0x0E35, 0x0E2A, 0x0E35,
	0x0E48, 0x0E1D, 0x0E32, 0x0E21, 0x0E35, 0x0E1E, 0x0E37, 0x0E49,
	0x0E19, 0x0E01, 0x0E31, 0x0E1A, 0x0E2B, 0x0E25, 0x0E31, 0x0E07,
	0x0E04, 0x0E32, 0x0E23, 0x0E27, 0x0E21, 0x0E17, 0x0E33, 0x0E40,
	0x0E1B, 0x0E47, 0x0E19, 0x0E2B, 0x0E49, 0x0E2D, 0x0E07, 0x0E40,
	0x0E14, 0x0E35, 0x0E22, 0x0E27, 0x0E43, 0x0E19, 0x0E2B, 0x0E49, 
	0x0E2D, 0x0E07, 0x0E21, 0x0E35, 0x0E17, 0x0E31, 0x0E49, 0x0E07,
	0x0E40, 0x0E15, 0x0E32, 0x0E2B, 0x0E38, 0x0E07, 0x0E15, 0x0E49,
	0x0E21, 0x0E17, 0x0E35, 0x0E48, 0x0E2A, 0x0E19, 0x0E34, 0x0E21,
	0x0E14, 0x0E39, 0x0E02, 0x0E36, 0x0E49, 0x0E19, 0x0E40, 0x0E25,
	0x0E2D, 0x0E30, 0x0E21, 0x0E35, 0x0E15, 0x0E39, 0x0E49, 0x0E43, 
	0x0E2A, 0x0E48, 0x0E16, 0x0E49, 0x0E27, 0x0E22, 0x0E0A, 0x0E32,
	0x0E21, 0x0E42, 0x0E15, 0x0E4A, 0x0E30, 0x0E40, 0x0E01, 0x0E49,
	0x0E32, 0x0E2D, 0x0E35, 0x0E49, 0x0E2A, 0x0E32, 0x0E21, 0x0E2B,
	0x0E23
	*/
};

int32_t thaiSampleLength = ARRAY_LENGTH(thaiSample);

TestInput testInputs[] = {
	{"Devamt.ttf",            devaText,   devaTextLength,   USCRIPT_DEVANAGARI, false},
	{"Times.TTF",             arabText,   arabTextLength,   USCRIPT_ARABIC,     true},
	{"LucidaSansRegular.ttf", arabText,   arabTextLength,   USCRIPT_ARABIC,     true},
	{"Thonburi.ttf",          thaiSample, thaiSampleLength, USCRIPT_THAI,       false}
};

#define TEST_COUNT ARRAY_LENGTH(testInputs)

int32_t testCount = TEST_COUNT;

void dumpShorts(FILE *file, char *label, int32_t id, uint16_t *shorts, int32_t count) {
	char lineBuffer[8 * 8 + 2];
	int32_t bufp = 0;

	fprintf(file, label, id);

	for (int i = 0; i < count; i += 1) {
		if (i % 8 == 0 && bufp != 0) {
			fprintf(file, "    %s\n", lineBuffer);
			bufp = 0;
		}
			
		bufp += sprintf(&lineBuffer[bufp], "0x%4.4X, ", shorts[i]);
	}

	if (bufp != 0) {
		lineBuffer[bufp - 2] = '\0';
		fprintf(file, "    %s\n", lineBuffer);
	}

	fprintf(file, "};\n\n");
}

void dumpLongs(FILE *file, char *label, int32_t id, int32_t *longs, int32_t count) {
	char lineBuffer[8 * 12 + 2];
	int32_t bufp = 0;

	fprintf(file, label, id);

	for (int i = 0; i < count; i += 1) {
		if (i % 8 == 0 && bufp != 0) {
			fprintf(file, "    %s\n", lineBuffer);
			bufp = 0;
		}
			
		bufp += sprintf(&lineBuffer[bufp], "0x%8.8X, ", longs[i]);
	}

	if (bufp != 0) {
		lineBuffer[bufp - 2] = '\0';
		fprintf(file, "    %s\n", lineBuffer);
	}

	fprintf(file, "};\n\n");
}

void dumpFloats(FILE *file, char *label, int32_t id, float *floats, int32_t count) {
	char lineBuffer[8 * 16 + 2];
	int32_t bufp = 0;

	fprintf(file, label, id);

	for (int i = 0; i < count; i += 1) {
		if (i % 8 == 0 && bufp != 0) {
			fprintf(file, "    %s\n", lineBuffer);
			bufp = 0;
		}
			
		bufp += sprintf(&lineBuffer[bufp], "%fF, ", floats[i]);
	}

	if (bufp != 0) {
		lineBuffer[bufp - 2] = '\0';
		fprintf(file, "    %s\n", lineBuffer);
	}

	fprintf(file, "};\n\n");
}

int main(int argc, char *argv[])
{
	Locale dummyLocale;
	int32_t test;
	FILE *outputFile = fopen(argv[1], "w");

	fprintf(outputFile, header);

	for (test = 0; test < testCount; test += 1) {
        PFIErrorCode fontStatus = PFI_NO_ERROR;
		PortableFontInstance fontInstance(testInputs[test].fontName, 12, fontStatus);

        if (LE_FAILURE(fontStatus)) {
            printf("ERROR: test case %d, could not get a font instance for %s\n", test, testInputs[test].fontName);
            continue;
        }

		UErrorCode success = U_ZERO_ERROR;
		ICULayoutEngine *engine = ICULayoutEngine::createInstance(&fontInstance, testInputs[test].scriptCode, dummyLocale, success);
		uint32_t glyphCount;
		uint16_t *glyphs;
		int32_t *indices;
		float *positions;

        if (LE_FAILURE(success)) {
            printf("ERROR: test case %d, could not create a LayoutEngine for script %s.\n", test, scriptNames[testInputs[test].scriptCode]);
            continue;
        }

		glyphCount = engine->layoutChars(testInputs[test].text, 0, testInputs[test].textLength, testInputs[test].textLength, testInputs[test].rightToLeft, 0, 0, success);

		glyphs = new uint16_t[glyphCount];
		indices = new int32_t[glyphCount];
		positions = new float[glyphCount * 2 + 2];

		engine->getGlyphs(glyphs, success);
		engine->getCharIndices(indices, success);
		engine->getGlyphPositions(positions, success);

		//fprintf(outputFile, "font: %s\n", testInputs[test].fontName);
		dumpShorts(outputFile, "UChar inputText%d[] =\n{\n", test, testInputs[test].text, testInputs[test].textLength);

		dumpShorts(outputFile, "uint16_t resultGlyphs%d[] =\n{\n", test, glyphs, glyphCount);
		fprintf(outputFile, "int32_t resultGlyphCount%d = %d;\n\n", test, glyphCount);

		dumpLongs(outputFile, "int32_t resultIndices%d[] =\n{\n", test, indices, glyphCount);

		dumpFloats(outputFile, "float resultPositions%d[] =\n{\n", test, positions, glyphCount * 2 + 2);

		fprintf(outputFile, "\n");
		
		delete[] positions;
		delete[] indices;
		delete[] glyphs;
		delete engine;
	}

	fprintf(outputFile, "TestInput testInputs[] = \n{\n");

	for (test = 0; test < testCount; test += 1) {
		fprintf(outputFile, "    {\"%s\", inputText%d, %d, %s, %s},\n",
			testInputs[test].fontName, test, testInputs[test].textLength, scriptNames[testInputs[test].scriptCode],
			testInputs[test].rightToLeft? "true" : "false");
	}

	fprintf(outputFile, "};\n\nint32_t testCount = ARRAY_LENGTH(testInputs);\n\n");

	fprintf(outputFile, "TestResult testResults[] = \n{\n");

	for (test = 0; test < testCount; test += 1) {
		fprintf(outputFile, "    {resultGlyphCount%d, resultGlyphs%d, resultIndices%d, resultPositions%d},\n",
			test, test, test, test);
	}

	fprintf(outputFile, "};\n\n");

	fclose(outputFile);
	return 0;
}
