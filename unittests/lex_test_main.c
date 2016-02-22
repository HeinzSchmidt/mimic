/*************************************************************************/
/*                                                                       */
/*                  Language Technologies Institute                      */
/*                     Carnegie Mellon University                        */
/*                        Copyright (c) 1999                             */
/*                        All Rights Reserved.                           */
/*                                                                       */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*                                                                       */
/*  CARNEGIE MELLON UNIVERSITY AND THE CONTRIBUTORS TO THIS WORK         */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL CARNEGIE MELLON UNIVERSITY NOR THE CONTRIBUTORS BE LIABLE      */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*             Author:  Alan W Black (awb@cs.cmu.edu)                    */
/*               Date:  December 1999                                    */
/*************************************************************************/
/*                                                                       */
/*  Test of lexicon/lts rules                                            */
/*                                                                       */
/*************************************************************************/
#include <stdio.h>
#include "cst_lexicon.h"

#include "cutest.h"

extern cst_lexicon cmu_lex;
void cmu_lex_init();

static void lookup_and_test(cst_lexicon *l, const char *word, const char *feats,
        const char *expected_lexes)
{
    cst_val *p;
    const cst_val *syl;

    char *tok;
    char * expected_str = malloc(strlen(expected_lexes) + 1);

    p = lex_lookup(l,word, feats, NULL);
    strcpy(expected_str, expected_lexes);
    tok = strtok(expected_str, " ");
    for (syl = p; syl;)
    {
        TEST_CHECK(strcmp(val_string(val_car(syl)), tok) == 0);
        syl = val_cdr(syl);
        if (syl)
            tok = strtok(NULL, " ");
        if (tok == NULL)
            break;
    }
    delete_val(p);
}

void test_sleekit(void)
{
    cmu_lex_init();
    lookup_and_test(&cmu_lex,"sleekit", NULL, "s l iy1 k ih0 t");
}

void test_chair(void)
{
    cmu_lex_init();
    lookup_and_test(&cmu_lex,"chair", NULL, "ch eh1 r");
}

void test_project(void)
{
    cmu_lex_init();
    lookup_and_test(&cmu_lex,"project", "n", "p r aa1 jh eh0 k t");
    lookup_and_test(&cmu_lex,"project", "v", "p r ax0 jh eh1 k t");
    lookup_and_test(&cmu_lex,"project", "j", "p r aa1 jh eh0 k t");
}

void test_bbcc(void)
{
    cmu_lex_init();
    lookup_and_test(&cmu_lex, "bbcc", NULL, "b b k");
}

void test_zzzz(void)
{
    cmu_lex_init();
    lookup_and_test(&cmu_lex, "zzzz", NULL, "z iy1 z");
}


void test_crax(void)
{
    cmu_lex_init();
    lookup_and_test(&cmu_lex,"crax",NULL, "k r ae1 k s");
}
    
void test_a(void)
{
    cmu_lex_init();
    lookup_and_test(&cmu_lex,"a","dt", "ax0");
}

TEST_LIST = {
    {"sleekit", test_sleekit},
    {"chair", test_chair},
    {"project", test_project},
    {"bbcc", test_bbcc},
    {"zzzz", test_zzzz},
    {"crax", test_crax},
    {"a", test_a},
    {0}
};
