/*
******************************************************************************
*
*   Copyright (C) 2001, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
******************************************************************************
*   file name:  trietest.c
*   encoding:   US-ASCII
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 2001nov20
*   created by: Markus W. Scherer
*/

#include <stdio.h>
#include "unicode/utypes.h"
#include "utrie.h"
#include "cstring.h"

#if 1
#include "cintltst.h"
#else
/* definitions from standalone utrie development */
#define log_err printf
#define log_verbose printf

#undef u_errorName
#define u_errorName(errorCode) "some error code"
#endif

#define ARRAY_LENGTH(array) (sizeof(array)/sizeof(array[0]))

/* Values for setting possibly overlapping, out-of-order ranges of values */
typedef struct SetRange {
    UChar32 start, limit;
    uint32_t value;
    UBool overwrite;
} SetRange;

/*
 * Values for testing:
 * value is set from the previous boundary's limit to before
 * this boundary's limit
 */
typedef struct CheckRange {
    UChar32 limit;
    uint32_t value;
} CheckRange;

static uint8_t storage[100000];

static uint32_t U_CALLCONV
_testFoldedValue32(UNewTrie *trie, UChar32 start, int32_t offset) {
    uint32_t foldedValue, value;
    UChar32 limit;
    UBool inBlockZero;

    foldedValue=0;

    limit=start+0x400;
    while(start<limit) {
        value=utrie_get32(trie, start, &inBlockZero);
        if(inBlockZero) {
            start+=UTRIE_DATA_BLOCK_LENGTH;
        } else {
            foldedValue|=value;
            ++start;
        }
    }

    if(foldedValue!=0) {
        return ((uint32_t)offset<<16)|foldedValue;
    } else {
        return 0;
    }
}

static int32_t U_CALLCONV
_testFoldingOffset32(uint32_t data) {
    return (int32_t)(data>>16);
}

static uint32_t U_CALLCONV
_testFoldedValue16(UNewTrie *trie, UChar32 start, int32_t offset) {
    uint32_t foldedValue, value;
    UChar32 limit;
    UBool inBlockZero;

    foldedValue=0;

    limit=start+0x400;
    while(start<limit) {
        value=utrie_get32(trie, start, &inBlockZero);
        if(inBlockZero) {
            start+=UTRIE_DATA_BLOCK_LENGTH;
        } else {
            foldedValue|=value;
            ++start;
        }
    }

    if(foldedValue!=0) {
        return (uint32_t)(offset|0x8000);
    } else {
        return 0;
    }
}

static int32_t U_CALLCONV
_testFoldingOffset16(uint32_t data) {
    if(data&0x8000) {
        return (int32_t)(data&0x7fff);
    } else {
        return 0;
    }
}

static uint32_t U_CALLCONV
_testEnumValue(const void *context, uint32_t value) {
    return value^0x5555;
}

static void U_CALLCONV
_testEnumRange(const void *context, UChar32 start, UChar32 limit, uint32_t value) {
    const CheckRange **pb=(const CheckRange **)context;
    const CheckRange *b=(*pb)++;

    value^=0x5555;
    if(start!=(b-1)->limit || limit!=b->limit || value!=b->value) {
        log_err("error: utrie_enum() delivers wrong range [U+%04lx..U+%04lx[.0x%lx instead of [U+%04lx..U+%04lx[.0x%lx\n",
            start, limit, value,
            (b-1)->limit, b->limit, b->value);
    }
}

static void
testTrieIteration(const char *testName,
                  const UTrie *trie,
                  const CheckRange checkRanges[], int32_t countCheckRanges) {
    UChar s[100];
    uint32_t values[30];

    const UChar *p, *limit;

    uint32_t value;
    UChar32 c;
    int32_t i, length, countValues;
    UChar c2;

    /* write a string */
    length=countValues=0;
    for(i=0; i<countCheckRanges; ++i) {
        c=checkRanges[i].limit;
        if(c!=0) {
            --c;
            UTF_APPEND_CHAR_UNSAFE(s, length, c);
            values[countValues++]=checkRanges[i].value;
        }
    }
    limit=s+length;

    /* try forward */
    p=s;
    i=0;
    while(p<limit) {
        c=c2=0x33;
        if(trie->data32!=NULL) {
            UTRIE_NEXT32(trie, p, limit, c, c2, value);
        } else {
            UTRIE_NEXT16(trie, p, limit, c, c2, value);
        }
        if(value!=values[i]) {
            log_err("error: wrong value from UTRIE_NEXT(%s)(U+%04lx, U+%04lx): 0x%lx instead of 0x%lx\n",
                    testName, c, c2, value, values[i]);
        }
        if(
            c2==0 ?
                c!=*(p-1) :
                !UTF_IS_LEAD(c) || !UTF_IS_TRAIL(c2) || c!=*(p-2) || c2!=*(p-1)
        ) {
            log_err("error: wrong (c, c2) from UTRIE_NEXT(%s): (U+%04lx, U+%04lx)\n",
                    testName, c, c2);
            continue;
        }
        if(c2!=0) {
            int32_t offset;

            if(trie->data32==NULL) {
                value=UTRIE_GET16_FROM_LEAD(trie, c);
                offset=trie->getFoldingOffset(value);
                if(offset>0) {
                    value=UTRIE_GET16_FROM_OFFSET_TRAIL(trie, offset, c2);
                } else {
                    value=0;
                }
            } else {
                value=UTRIE_GET32_FROM_LEAD(trie, c);
                offset=trie->getFoldingOffset(value);
                if(offset>0) {
                    value=UTRIE_GET32_FROM_OFFSET_TRAIL(trie, offset, c2);
                } else {
                    value=0;
                }
            }
            if(value!=values[i]) {
                log_err("error: wrong value from UTRIE_GETXX_FROM_OFFSET_TRAIL(%s)(U+%04lx, U+%04lx): 0x%lx instead of 0x%lx\n",
                        testName, c, c2, value, values[i]);
            }
        }
        if(c2!=0) {
            value=0x44;
            if(trie->data32==NULL) {
                UTRIE_GET16_FROM_PAIR(trie, c, c2, value);
            } else {
                UTRIE_GET32_FROM_PAIR(trie, c, c2, value);
            }
            if(value!=values[i]) {
                log_err("error: wrong value from UTRIE_GETXX_FROM_PAIR(%s)(U+%04lx, U+%04lx): 0x%lx instead of 0x%lx\n",
                        testName, c, c2, value, values[i]);
            }
        }
        ++i;
    }

    /* try backward */
    p=limit;
    i=countValues;
    while(s<p) {
        --i;
        c=c2=0x33;
        if(trie->data32!=NULL) {
            UTRIE_PREVIOUS32(trie, s, p, c, c2, value);
        } else {
            UTRIE_PREVIOUS16(trie, s, p, c, c2, value);
        }
        if(value!=values[i]) {
            log_err("error: wrong value from UTRIE_PREVIOUS(%s)(U+%04lx, U+%04lx): 0x%lx instead of 0x%lx\n",
                    testName, c, c2, value, values[i]);
        }
        if(
            c2==0 ?
                c!=*p:
                !UTF_IS_LEAD(c) || !UTF_IS_TRAIL(c2) || c!=*p || c2!=*(p+1)
        ) {
            log_err("error: wrong (c, c2) from UTRIE_PREVIOUS(%s): (U+%04lx, U+%04lx)\n",
                    testName, c, c2);
        }
    }
}

static void
testTrieRanges(const char *testName,
               const SetRange setRanges[], int32_t countSetRanges,
               const CheckRange checkRanges[], int32_t countCheckRanges,
               UBool dataIs32, UBool latin1Linear) {
    UTrieGetFoldingOffset *getFoldingOffset;
    const CheckRange *enumRanges;
    UNewTrie *newTrie;
    UTrie trie={ 0 };
    uint32_t value, value2;
    UChar32 start, limit;
    int32_t i, length;
    UErrorCode errorCode;
    UBool overwrite, ok;

    log_verbose("\ntesting Trie '%s'\n", testName);
    newTrie=utrie_open(NULL, NULL, 2000, latin1Linear);

    /* set values from setRanges[] */
    ok=TRUE;
    for(i=0; i<countSetRanges; ++i) {
        start=setRanges[i].start;
        limit=setRanges[i].limit;
        value=setRanges[i].value;
        overwrite=setRanges[i].overwrite;
        if((limit-start)==1 && overwrite) {
            ok&=utrie_set32(newTrie, start, value);
        } else {
            ok&=utrie_setRange32(newTrie, start, limit, value, overwrite);
        }
    }
    if(!ok) {
        log_err("error: setting values into a trie failed (%s)\n", testName);
        return;
    }

    /* verify that all these values are in the new Trie */
    start=0;
    for(i=0; i<countCheckRanges; ++i) {
        limit=checkRanges[i].limit;
        value=checkRanges[i].value;

        while(start<limit) {
            if(value!=utrie_get32(newTrie, start, NULL)) {
                log_err("error: newTrie(%s)[U+%04lx]==0x%lx instead of 0x%lx\n",
                        testName, start, utrie_get32(newTrie, start, NULL), value);
            }
            ++start;
        }
    }

    if(dataIs32) {
        getFoldingOffset=_testFoldingOffset32;
    } else {
        getFoldingOffset=_testFoldingOffset16;
    }

    errorCode=U_ZERO_ERROR;
    length=utrie_serialize(newTrie, storage, sizeof(storage),
                           dataIs32 ? _testFoldedValue32 : _testFoldedValue16,
                           (UBool)!dataIs32,
                           &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("error: utrie_serialize(%s) failed: %s\n", testName, u_errorName(errorCode));
        utrie_close(newTrie);
        return;
    }

    /* test linear Latin-1 range from utrie_getData() */
    if(latin1Linear) {
        uint32_t *data;
        int32_t dataLength;

        data=utrie_getData(newTrie, &dataLength);
        start=0;
        for(i=0; i<countCheckRanges && start<=0xff; ++i) {
            limit=checkRanges[i].limit;
            value=checkRanges[i].value;

            while(start<limit && start<=0xff) {
                if(value!=data[UTRIE_DATA_BLOCK_LENGTH+start]) {
                    log_err("error: newTrie(%s).latin1Data[U+%04lx]==0x%lx instead of 0x%lx\n",
                            testName, start, data[UTRIE_DATA_BLOCK_LENGTH+start], value);
                }
                ++start;
            }
        }
    }

    utrie_close(newTrie);

    errorCode=U_ZERO_ERROR;
    if(!utrie_unserialize(&trie, storage, length, &errorCode)) {
        log_err("error: utrie_unserialize() failed, %s\n", u_errorName(errorCode));
        return;
    }
    trie.getFoldingOffset=getFoldingOffset;

    if(dataIs32!=(trie.data32!=NULL)) {
        log_err("error: trie serialization (%s) did not preserve 32-bitness\n", testName);
    }
    if(latin1Linear!=trie.isLatin1Linear) {
        log_err("error: trie serialization (%s) did not preserve Latin-1-linearity\n", testName);
    }

    /* verify that all these values are in the unserialized Trie */
    start=0;
    for(i=0; i<countCheckRanges; ++i) {
        limit=checkRanges[i].limit;
        value=checkRanges[i].value;

        if(start==0xd800) {
            /* skip surrogates */
            start=limit;
            continue;
        }

        while(start<limit) {
            if(start<=0xffff) {
                if(dataIs32) {
                    value2=UTRIE_GET32_FROM_BMP(&trie, start);
                } else {
                    value2=UTRIE_GET16_FROM_BMP(&trie, start);
                }
                if(value!=value2) {
                    log_err("error: unserialized trie(%s).fromBMP(U+%04lx)==0x%lx instead of 0x%lx\n",
                            testName, start, value2, value);
                }
                if(!UTF_IS_LEAD(start)) {
                    if(dataIs32) {
                        value2=UTRIE_GET32_FROM_LEAD(&trie, start);
                    } else {
                        value2=UTRIE_GET16_FROM_LEAD(&trie, start);
                    }
                    if(value!=value2) {
                        log_err("error: unserialized trie(%s).fromLead(U+%04lx)==0x%lx instead of 0x%lx\n",
                                testName, start, value2, value);
                    }
                }
            }
            if(dataIs32) {
                UTRIE_GET32(&trie, start, value2);
            } else {
                UTRIE_GET16(&trie, start, value2);
            }
            if(value!=value2) {
                log_err("error: unserialized trie(%s).get(U+%04lx)==0x%lx instead of 0x%lx\n",
                        testName, start, value2, value);
            }
            ++start;
        }
    }

    /* enumerate and verify all ranges */
    enumRanges=checkRanges+1;
    utrie_enum(&trie, _testEnumValue, _testEnumRange, &enumRanges);

    /* test linear Latin-1 range */
    if(trie.isLatin1Linear) {
        if(trie.data32!=NULL) {
            const uint32_t *latin1=UTRIE_GET32_LATIN1(&trie);

            for(start=0; start<0x100; ++start) {
                if(latin1[start]!=UTRIE_GET32_FROM_LEAD(&trie, start)) {
                    log_err("error: (%s) trie.latin1[U+%04lx]=0x%lx!=0x%lx=trie.get32(U+%04lx)\n",
                            testName, start, latin1[start], UTRIE_GET32_FROM_LEAD(&trie, start), start);
                }
            }
        } else {
            const uint16_t *latin1=UTRIE_GET16_LATIN1(&trie);

            for(start=0; start<0x100; ++start) {
                if(latin1[start]!=UTRIE_GET16_FROM_LEAD(&trie, start)) {
                    log_err("error: (%s) trie.latin1[U+%04lx]=0x%lx!=0x%lx=trie.get16(U+%04lx)\n",
                            testName, start, latin1[start], UTRIE_GET16_FROM_LEAD(&trie, start), start);
                }
            }
        }
    }

    testTrieIteration(testName, &trie, checkRanges, countCheckRanges);
}

static void
testTrieRanges2(const char *testName,
                const SetRange setRanges[], int32_t countSetRanges,
                const CheckRange checkRanges[], int32_t countCheckRanges,
                UBool dataIs32) {
    char name[40];

    testTrieRanges(testName,
                   setRanges, countSetRanges,
                   checkRanges, countCheckRanges,
                   dataIs32, FALSE);

    uprv_strcpy(name, testName);
    uprv_strcat(name, "-latin1Linear");
    testTrieRanges(name,
                   setRanges, countSetRanges,
                   checkRanges, countCheckRanges,
                   dataIs32, TRUE);
}

static void
testTrieRanges4(const char *testName,
                const SetRange setRanges[], int32_t countSetRanges,
                const CheckRange checkRanges[], int32_t countCheckRanges) {
    char name[40];

    uprv_strcpy(name, testName);
    uprv_strcat(name, ".32");
    testTrieRanges2(name,
                    setRanges, countSetRanges,
                    checkRanges, countCheckRanges,
                    TRUE);

    uprv_strcpy(name, testName);
    uprv_strcat(name, ".16");
    testTrieRanges2(name,
                    setRanges, countSetRanges,
                    checkRanges, countCheckRanges,
                    FALSE);
}

/* test data ----------------------------------------------------------------*/

/* set consecutive ranges, even with value 0 */
static const SetRange
setRanges1[]={
    0,      0x20,       0,      FALSE,
    0x20,   0xa7,       0x1234, FALSE,
    0xa7,   0x3400,     0,      FALSE,
    0x3400, 0x9fa6,     0x6162, FALSE,
    0x9fa6, 0xdada,     0x3132, FALSE,
    0xdada, 0xeeee,     0x27,   FALSE,
    0xeeee, 0x11111,    1,      FALSE,
    0x11111, 0x44444,   0x6162, FALSE,
    0x44444, 0xf0003,   0,      FALSE,
    0xf0003, 0xf0004,   0xf,    FALSE,
    0xf0004, 0xf0006,   0x10,   FALSE,
    0xf0006, 0xf0007,   0x11,   FALSE,
    0xf0007, 0xf0020,   0x12,   FALSE,
    0xf0020, 0x110000,  0,      FALSE
};

static const CheckRange
checkRanges1[]={
    0,      0,      /* dummy start range to make _testEnumRange() simpler */
    0x20,   0,
    0xa7,   0x1234,
    0x3400, 0,
    0x9fa6, 0x6162,
    0xdada, 0x3132,
    0xeeee, 0x27,
    0x11111,1,
    0x44444,0x6162,
    0xf0003,0,
    0xf0004,0xf,
    0xf0006,0x10,
    0xf0007,0x11,
    0xf0020,0x12,
    0x110000, 0
};

/* set some interesting overlapping ranges */
static const SetRange
setRanges2[]={
    0x21,   0x7f,       0x5555, TRUE,
    0x2f800,0x2fedc,    0x7a,   TRUE,
    0x72,   0xdd,       3,      TRUE,
    0xdd,   0xde,       4,      FALSE,
    0x2f987,0x2fa98,    5,      TRUE,
    0x2f777,0x2f833,    0,      TRUE,
    0x2f900,0x2ffee,    1,      FALSE,
    0x2ffee,0x2ffef,    2,      TRUE
};

static const CheckRange
checkRanges2[]={
    0,      0,      /* dummy start range to make _testEnumRange() simpler */
    0x21,   0,
    0x72,   0x5555,
    0xdd,   3,
    0xde,   4,
    0x2f833,0,
    0x2f987,0x7a,
    0x2fa98,5,
    0x2fedc,0x7a,
    0x2ffee,1,
    0x2ffef,2,
    0x110000, 0
};

static void
TrieTest() {
    testTrieRanges4("set1",
        setRanges1, ARRAY_LENGTH(setRanges1),
        checkRanges1, ARRAY_LENGTH(checkRanges1));
    testTrieRanges4("set2",
        setRanges2, ARRAY_LENGTH(setRanges2),
        checkRanges2, ARRAY_LENGTH(checkRanges2));
}

#if 1
void
addTrieTest(TestNode** root) {
    addTest(root, &TrieTest, "tsutil/TrieTest");
}
#else
/* standalone utrie development */
int main(int argc, const char *argv[]) {
    TrieTest();
    return 0;
}
#endif
