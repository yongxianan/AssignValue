#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include <ctype.h>
#include "unity.h"
#include "Error.h"
#include "TextParser.h"
#include "Exception.h"
#include "CException.h"
//#include <stdlib.h>

void setUp(void) {}

void tearDown(void) {}


void test_StringCompare_for_first_word_given_a_string(void){
  char *message = " assign mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(1,StringCompare("assign",&message));
  TEST_ASSERT_EQUAL(originalmessage+7,message);
}

void test_StringCompare_for_null(void){
  char *message = NULL;
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(0,StringCompare("assign",&message));
  TEST_ASSERT_EQUAL(originalmessage,message);
}

void test_StringCompare_for_first_word_given_a_string3(void){
  char *message = "assign mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(1,StringCompare("assign",&message));
  TEST_ASSERT_EQUAL(originalmessage+6,message);
}

void test_StringCompare_for_first_word_given_a_string4(void){
  char *message = "sign mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(0,StringCompare("assign",&message));
  TEST_ASSERT_EQUAL(originalmessage,message);
}

void test_StringCompare_for_first_word_given_a_string5(void){
  char *message = "       sign mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(0,StringCompare("assign",&message));
  TEST_ASSERT_EQUAL(originalmessage+7,message);
}

void test_StringCompare_for_first_word_given_a_string6(void){
  char *message = "                   assign mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(1,StringCompare("assign",&message));
  TEST_ASSERT_EQUAL(originalmessage+25,message);
}

void test_StringCompare_for_first_word_given_a_string7(void){
  char *message = "               assign                    mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(1,StringCompare("assign",&message));
  TEST_ASSERT_EQUAL(originalmessage+21,message);
}

void test_extractWord_search_first_word_given_a_string(void){
  char *message = "                   assign mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL_STRING("assign",extractWord(&message));
  TEST_ASSERT_EQUAL(originalmessage+25,message);
}

void test_extractWord_search_second_word_given_a_string(void){
  char *message = "               assign                    mango = 589 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL_STRING("assign",extractWord(&message));
  TEST_ASSERT_EQUAL(originalmessage+21,message);
  TEST_ASSERT_EQUAL_STRING("mango",extractWord(&message));
  TEST_ASSERT_EQUAL(originalmessage+46,message);
}

void test_extractInteger_search_same_number_of_digit_integer_given_a_string(void){
  char *message = "   789   855  741  ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(789,extractInteger(&message));
  TEST_ASSERT_EQUAL(originalmessage+6,message);
  TEST_ASSERT_EQUAL(855,extractInteger(&message));
  TEST_ASSERT_EQUAL(originalmessage+12,message);
  TEST_ASSERT_EQUAL(741,extractInteger(&message));
  TEST_ASSERT_EQUAL(originalmessage+17,message);
}

void test_extractInteger_search_different_number_of_digit_integer_given_a_string(void){
  char *message = "   7895          855 74      8 ";
  char *originalmessage=message;
  TEST_ASSERT_EQUAL(7895,extractInteger(&message));
  TEST_ASSERT_EQUAL(originalmessage+7,message);
  TEST_ASSERT_EQUAL(855,extractInteger(&message));
  TEST_ASSERT_EQUAL(originalmessage+20,message);
  TEST_ASSERT_EQUAL(74,extractInteger(&message));
  TEST_ASSERT_EQUAL(originalmessage+23,message);
  TEST_ASSERT_EQUAL(8,extractInteger(&message));
  TEST_ASSERT_EQUAL(originalmessage+30,message);
}


void test_parseTextAndAssignValues_given_no_table_mapping_should_throw_ERR_TABLE_IS_MISSING(void) {
  CEXCEPTION_T e;
  char *line = " assign mango = 589 ";

  Try {
    parseTextAndAssignValues(line, NULL);
    TEST_FAIL_MESSAGE("Expect ERR_TABLE_IS_MISSING. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_no_command_should_do_nothing(void) {
  CEXCEPTION_T e;
  int tomato = 0;
  VariableMapping varTableMapping[] = {
    {"tomato", &tomato},
    {NULL, NULL},
  };
  char *line = NULL;

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    // Should reach here because no command given
    printf("line = NULL : no problem");
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
    TEST_FAIL_MESSAGE("line = NULL, shouldn't thrown");
  }
}

void test_parseTextAndAssignValues_given_input_command_is_NULL_should_do_nothing(void) {
  CEXCEPTION_T e;
  int kiwi = 0;
  VariableMapping varTableMapping[] = {
    {"kiwi", &kiwi},
    {NULL, NULL},
  };
  char *line = "  ";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    // Should reach here because no command given 
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
    TEST_FAIL_MESSAGE("line = (emply space), shouldn't thrown");
  }
}

// assign orange  = 21346 apple = 1 lemon=10
void test_parseTextAndAssignValues_given_orange_21346_apple_1_lemon_10_should_assigned_correctly(void) {
  CEXCEPTION_T e;
  int orange = 0, apple = 0, lemon = 0;
  VariableMapping varTableMapping[] = {
    {"apple", &apple},
    {"orange", &orange},
    {"lemon", &lemon},
    {NULL, NULL},
  };
  char *line = "assign orange  = 21346 apple = 1 lemon=10";

  Try {
    parseTextAndAssignValues(line, varTableMapping);

    TEST_ASSERT_EQUAL(21346, orange);
    TEST_ASSERT_EQUAL(1, apple);
    TEST_ASSERT_EQUAL(10, lemon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
    TEST_FAIL_MESSAGE("line don't have problem, shouldn't thrown");
  }
}

void test_parseTextAndAssignValues_given_melon_and_value_with_trailing_spaces_should_parse_properly(void) {
  CEXCEPTION_T e;
  int melon = 0;
  VariableMapping varTableMapping[] = {
    {"melon  ", &melon},
    {NULL, NULL},
  };
  char *line = "assign melon = 89   ";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_ASSERT_EQUAL(89, melon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
    TEST_FAIL_MESSAGE("line don't have problem, shouldn't thrown");
  }
}

void test_parseTextAndAssignValues_given_text_without_assign_should_throw_ERR_UNKNOWN_COMMAND(void) {
  CEXCEPTION_T e;
  int papaya = 0;
  VariableMapping varTableMapping[] = {
    {"papaya", &papaya},
    {NULL, NULL},
  };
  char *line = "  papaya = 345 ";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_COMMAND. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_COMMAND, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_guava_23_cucumber_92_should_throw_ERR_UNKNOWN_VARIABLE(void) {
  CEXCEPTION_T e;
  int guava = 0;
  VariableMapping varTableMapping[] = {
    {"guava", &guava},
    {NULL, NULL},
  };
  char *line = "assign guava=23 cucumber=92";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_VARIABLE. But no exception thrown.");
  } Catch(e) {
    TEST_ASSERT_EQUAL(23, guava);
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_VARIABLE, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_malform_pineapple_without_equal_sign_should_throw_ERR_MALFORM_ASSIGN(void) {
  CEXCEPTION_T e;
  int pineapple = 0;
  VariableMapping varTableMapping[] = {
    {"pineapple", &pineapple},
    {NULL, NULL},
  };
  char *line = "assign pineapple 23 ";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORM_ASSIGN. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_MALFORM_ASSIGN, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_malform_ciku_without_number_should_throw_ERR_NOT_A_NUMBER(void) {
  CEXCEPTION_T e;
  int ciku = 0;
  VariableMapping varTableMapping[] = {
    {"ciku", &ciku},
    {NULL, NULL},
  };
  char *line = "assign ciku =  durian = 6";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_NOT_A_NUMBER. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_NOT_A_NUMBER, e->errorCode);
    freeError(e);
  }
}
