
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "bitarray.h"

#define TEST(form)\
if (form){\
printf("success: %s at %s:%d\n", #form, __FILE__, __LINE__);\
}\
else {\
printf("error: %s at %s:%d\n", #form, __FILE__, __LINE__); abort();\
}

static void bitarray_print (bitarray *barray, size_t separateby){
  for (size_t index = 0; index < bitarray_length(barray); index++){
    if (0 < index && index % separateby == 0){
      putchar(' ');
    }
    int value;
    bitarray_get(index, barray, &value);
    putchar('0' + (value? 1: 0));
  }
}

static void bitarray_println (bitarray *barray, size_t separateby){
  bitarray_print(barray, separateby);
  putchar('\n');
}

static void test_bitarray_set (){
  MAKE_LOCAL_BITARRAY(barray, 128);
  TEST(bitarray_length(barray) == 128);
  // set 1
  {
    TEST(bitarray_set(1, 2 + 0, barray) == 0);
    TEST(bitarray_set(1, 3 + 0, barray) == 0);
    TEST(bitarray_set(1, 4 + 0, barray) == 0);
    TEST(bitarray_set(1, 5 + 0, barray) == 0);
    TEST(bitarray_set(1, 2 + 64, barray) == 0);
    TEST(bitarray_set(1, 3 + 64, barray) == 0);
    TEST(bitarray_set(1, 4 + 64, barray) == 0);
    TEST(bitarray_set(1, 5 + 64, barray) == 0);
  }
  // get 1
  {
    int value;
    TEST(bitarray_get(2 + 0, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(3 + 0, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(4 + 0, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(5 + 0, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(2 + 64, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(3 + 64, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(4 + 64, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(5 + 64, barray, &value) == 0);
    TEST(value != 0);
  }
  // set 0
  {
    TEST(bitarray_set(0, 2 + 0, barray) == 0);
    TEST(bitarray_set(0, 3 + 0, barray) == 0);
    TEST(bitarray_set(0, 4 + 0, barray) == 0);
    TEST(bitarray_set(0, 5 + 0, barray) == 0);
    TEST(bitarray_set(0, 2 + 64, barray) == 0);
    TEST(bitarray_set(0, 3 + 64, barray) == 0);
    TEST(bitarray_set(0, 4 + 64, barray) == 0);
    TEST(bitarray_set(0, 5 + 64, barray) == 0);
  }
  // get 0
  {
    int value;
    TEST(bitarray_get(2 + 0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(3 + 0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(4 + 0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(5 + 0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(3 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(4 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(5 + 64, barray, &value) == 0);
    TEST(value == 0);
  }
  // set out of range (always error!)
  TEST(bitarray_set(1, 129, barray) != 0);
  // get out of range (always error!)
  int value;
  TEST(bitarray_get(129, barray, &value) != 0);
}

static void test_bitarray_fill (){
  // fill 1 between 0 ~ 0
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 0, 0, barray) == 0);
    int value;
    TEST(bitarray_get(0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(1, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(3, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(4, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(5, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(6, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(7, barray, &value) == 0);
    TEST(value == 0);
  }
  // fill 1 between 4 ~ 4
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 4, 4, barray) == 0);
    int value;
    TEST(bitarray_get(0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(1, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(3, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(4, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(5, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(6, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(7, barray, &value) == 0);
    TEST(value == 0);
  }
  // fill 1 between 2 ~ 6
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 2, 6, barray) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 2, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 2, 6, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(0, 6, 8, barray, &fillp) == 0);
    TEST(fillp == true);
    int value;
    TEST(bitarray_get(0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(1, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(3, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(4, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(5, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(6, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(7, barray, &value) == 0);
    TEST(value == 0);
  }
  // fill 1 between 2 ~ 14 (00111111 11111100)
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 2, 14, barray) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 2, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 2, 14, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(0, 14, 16, barray, &fillp) == 0);
    TEST(fillp == true);
    // get 0 ~ 7
    {
      int value;
      TEST(bitarray_get(0, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(1, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(2, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(3, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(4, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(5, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(6, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(7, barray, &value) == 0);
      TEST(value != 0);
    }
    // get 8 ~ 15
    {
      int value;
      TEST(bitarray_get(8, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(9, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(10, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(11, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(12, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(13, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(14, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(15, barray, &value) == 0);
      TEST(value == 0);
    }
  }
  // fill 1 between 2 ~ 22
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 2, 22, barray) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 2, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 2, 22, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(0, 22, 24, barray, &fillp) == 0);
    TEST(fillp == true);
    // get 0 ~ 7
    {
      int value;
      TEST(bitarray_get(0, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(1, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(2, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(3, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(4, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(5, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(6, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(7, barray, &value) == 0);
      TEST(value != 0);
    }
    // get 8 ~ 15
    {
      int value;
      TEST(bitarray_get(8, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(9, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(10, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(11, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(12, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(13, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(14, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(15, barray, &value) == 0);
      TEST(value != 0);
    }
    // get 16 ~ 25
    {
      int value;
      TEST(bitarray_get(16, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(17, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(18, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(19, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(20, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(21, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(22, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(23, barray, &value) == 0);
      TEST(value == 0);
    }
  }
  // fill 0 ~ 24 
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 0, 24, barray) == 0);
    bool fillp;
    TEST(bitarray_fillp(1, 0, 24, barray, &fillp) == 0);
    TEST(fillp == true);
    // get 0 ~ 7
    {
      int value;
      TEST(bitarray_get(0, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(1, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(2, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(3, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(4, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(5, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(6, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(7, barray, &value) == 0);
      TEST(value != 0);
    }
    // get 8 ~ 15
    {
      int value;
      TEST(bitarray_get(8, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(9, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(10, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(11, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(12, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(13, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(14, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(15, barray, &value) == 0);
      TEST(value != 0);
    }
    // get 16 ~ 25
    {
      int value;
      TEST(bitarray_get(16, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(17, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(18, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(19, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(20, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(21, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(22, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(23, barray, &value) == 0);
      TEST(value != 0);
    }
  }
  // fill 1 between 64 ~ 64
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    TEST(bitarray_length(barray) == 128);
    TEST(bitarray_fill(1, 64, 64, barray) == 0);
    int value;
    TEST(bitarray_get(0 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(1 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(3 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(4 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(5 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(6 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(7 + 64, barray, &value) == 0);
    TEST(value == 0);
  }
  // fill 1 between 66 ~ 70
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    TEST(bitarray_length(barray) == 128);
    TEST(bitarray_fill(1, 66, 70, barray) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 66, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 66, 70, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(0, 70, 128, barray, &fillp) == 0);
    TEST(fillp == true);
    int value;
    TEST(bitarray_get(0 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(1 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2 + 64, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(3 + 64, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(4 + 64, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(5 + 64, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(6 + 64, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(7 + 64, barray, &value) == 0);
    TEST(value == 0);
  }
  // fill 1 between 66 ~ 78 (00111111 11111100)
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    TEST(bitarray_length(barray) == 128);
    TEST(bitarray_fill(1, 66, 78, barray) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 66, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 66, 78, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(0, 78, 128, barray, &fillp) == 0);
    TEST(fillp == true);
    // get 0 ~ 7
    {
      int value;
      TEST(bitarray_get(0 + 64, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(1 + 64, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(2 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(3 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(4 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(5 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(6 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(7 + 64, barray, &value) == 0);
      TEST(value != 0);
    }
    // get 8 ~ 15
    {
      int value;
      TEST(bitarray_get(8 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(9 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(10 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(11 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(12 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(13 + 64, barray, &value) == 0);
      TEST(value != 0);
      TEST(bitarray_get(14 + 64, barray, &value) == 0);
      TEST(value == 0);
      TEST(bitarray_get(15 + 64, barray, &value) == 0);
      TEST(value == 0);
    }
  }
  // fill 0 ~ 4, 4 ~ 8, 8 ~ 12
  {
    MAKE_LOCAL_BITARRAY(barray, 12);
    TEST(bitarray_length(barray) == 12);
    bool fillp;
    TEST(bitarray_fill(1, 0, 4, barray) == 0);
    TEST(bitarray_fillp(1, 0, 4, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fill(1, 4, 8, barray) == 0);
    TEST(bitarray_fillp(1, 4, 8, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fill(1, 8, 12, barray) == 0);
    TEST(bitarray_fillp(1, 8, 12, barray, &fillp) == 0);
    TEST(fillp == true);
  }
  // fill out of range (always error!)
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 0, 25, barray) != 0);
  }
  // fillp out of range (always error!)
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 25, barray, &fillp) != 0);
  }
}

static void test_bitarray_find (){
  // find 1 between 2 ~ 6 into 00111100
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 2, 6, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(1, 4, barray, &foundindex) == 0);
    TEST(foundindex == 2);
  }
  // find 1 between 2 ~ 14 into 00111111 11111100
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 2, 14, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(1, 12, barray, &foundindex) == 0);
    TEST(foundindex == 2);
  }
  // find 1 between 2 ~ 22 into 00111111 11111111 11111100
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 2, 22, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(1, 20, barray, &foundindex) == 0);
    TEST(foundindex == 2);
  }
  // find 0 between 2 ~ 6 into 11000011
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 0, 2, barray) == 0);
    TEST(bitarray_fill(1, 6, 8, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(0, 4, barray, &foundindex) == 0);
    TEST(foundindex == 2);
  }
  // find 0 between 2 ~ 14 into 11000000 00000011
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 0, 2, barray) == 0);
    TEST(bitarray_fill(1, 14, 16, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(0, 12, barray, &foundindex) == 0);
    TEST(foundindex == 2);
  }
  // find 0 between 2 ~ 22 into 11000000 00000000 00000011
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 0, 2, barray) == 0);
    TEST(bitarray_fill(1, 22, 24, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(0, 20, barray, &foundindex) == 0);
    TEST(foundindex == 2);
  }
  // found 1 sizeof 4 into 00000000 11000000 11110000
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 8, 10, barray) == 0);
    TEST(bitarray_fill(1, 16, 20, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(1, 4, barray, &foundindex) == 0);
    TEST(foundindex == 16);
  }
  // found 0 sizeof 4 into 11111111 00111111 00001111
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    TEST(bitarray_fill(1, 0, 24, barray) == 0);
    TEST(bitarray_fill(0, 8, 10, barray) == 0);
    TEST(bitarray_fill(0, 16, 20, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(0, 4, barray, &foundindex) == 0);
    TEST(foundindex == 16);
  }
  // found 1 sizeof 4 into 00000000 ~ 11000000 11110000
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    TEST(bitarray_length(barray) == 128);
    TEST(bitarray_fill(1, 64, 66, barray) == 0);
    TEST(bitarray_fill(1, 96, 100, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(1, 4, barray, &foundindex) == 0);
    TEST(foundindex == 96);
  }
  // found 0 sizeof 4 into 11111111 ~ 00111111 00001111
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    TEST(bitarray_length(barray) == 128);
    TEST(bitarray_fill(1, 0, 128, barray) == 0);
    TEST(bitarray_fill(0, 64, 66, barray) == 0);
    TEST(bitarray_fill(0, 96, 100, barray) == 0);
    size_t foundindex;
    TEST(bitarray_find(0, 4, barray, &foundindex) == 0);
    TEST(foundindex == 96);
  }
  // find 0 sizeof 4 into 00000000 0000 third
  {
    MAKE_LOCAL_BITARRAY(barray, 12);
    TEST(bitarray_length(barray) == 12);
    size_t foundindex;
    TEST(bitarray_find(0, 4, barray, &foundindex) == 0);
    TEST(foundindex == 0);
    TEST(bitarray_fill(1, 0, 4, barray) == 0);
    TEST(bitarray_find(0, 4, barray, &foundindex) == 0);
    TEST(foundindex == 4);
    TEST(bitarray_fill(1, 4, 8, barray) == 0);
    TEST(bitarray_find(0, 4, barray, &foundindex) == 0);
    TEST(foundindex == 8);
    TEST(bitarray_fill(1, 8, 12, barray) == 0);
  }
  // find out of range (always error!)
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    size_t foundindex;
    TEST(bitarray_find(0, 32, barray, &foundindex) != 0);
  }
  // find out of range (always error!)
  {
    MAKE_LOCAL_BITARRAY(barray, 24);
    TEST(bitarray_length(barray) == 24);
    size_t foundindex;
    TEST(bitarray_find(1, 32, barray, &foundindex) != 0);
  }
}

static void test_bitarray_write (){
  // write bits (11111111 00000000)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    TEST(bitarray_length(barray) == 16);
    TEST(bitarray_write(0xff, 8, 0, barray) == 0);
    int value;
    TEST(bitarray_get(0, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(1, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(2, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(3, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(4, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(5, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(6, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(7, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(8, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(9, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(10, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(11, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(12, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(13, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(14, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(15, barray, &value) == 0);
    TEST(value == 0);
  }
  // write bits (00111111 11000000)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    TEST(bitarray_length(barray) == 16);
    TEST(bitarray_write(0xff, 8, 2, barray) == 0);
    int value;
    TEST(bitarray_get(0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(1, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(3, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(4, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(5, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(6, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(7, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(8, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(9, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(10, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(11, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(12, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(13, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(14, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(15, barray, &value) == 0);
    TEST(value == 0);
  }
  // write bits (00001111 11110000)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    TEST(bitarray_length(barray) == 16);
    TEST(bitarray_write(0xff, 8, 4, barray) == 0);
    int value;
    TEST(bitarray_get(0, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(1, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(2, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(3, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(4, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(5, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(6, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(7, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(8, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(9, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(10, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(11, barray, &value) == 0);
    TEST(value != 0);
    TEST(bitarray_get(12, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(13, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(14, barray, &value) == 0);
    TEST(value == 0);
    TEST(bitarray_get(15, barray, &value) == 0);
    TEST(value == 0);
  }
  // write out of range (always error!)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    TEST(bitarray_length(barray) == 16);
    TEST(bitarray_write(0xff, 8, 0, barray) == 0);
    TEST(bitarray_write(0xff, 8, 8, barray) == 0);
    TEST(bitarray_write(0xff, 8, 16, barray) != 0);
  }
  // read bits from (11111111 00000000)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    TEST(bitarray_length(barray) == 16);
    TEST(bitarray_fill(1, 0, 8, barray) == 0);
    bitarray_element value;
    TEST(bitarray_read(8, 0, barray, &value) == 0);
    TEST(value == 0xff);
    TEST(bitarray_read(8, 8, barray, &value) == 0);
    TEST(value == 0x00);
    TEST(bitarray_read(8, 2, barray, &value) == 0);
    TEST(value == 0b00111111);
    TEST(bitarray_read(6, 10, barray, &value) == 0);
    TEST(value == 0b00000000);
    TEST(bitarray_read(8, 4, barray, &value) == 0);
    TEST(value == 0x0f);
    TEST(bitarray_read(4, 12, barray, &value) == 0);
    TEST(value == 0x00);
  }
  // read out of range (always error!)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    TEST(bitarray_length(barray) == 16);
    bitarray_element value;
    TEST(bitarray_read(8, 0, barray, &value) == 0);
    TEST(bitarray_read(8, 8, barray, &value) == 0);
    TEST(bitarray_read(8, 16, barray, &value) != 0);
  }
}

static void test_bitarray_copy (){
  // copy (11111111 00000000)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    MAKE_LOCAL_BITARRAY(barray2, 16);
    TEST(bitarray_length(barray) == 16);
    TEST(bitarray_length(barray2) == 16);
    TEST(bitarray_fill(1, 0, 8, barray) == 0);
    TEST(bitarray_copy(barray, barray2) == 0);
    bool fillp;
    TEST(bitarray_fillp(1, 0, 8, barray2, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(0, 8, 16, barray2, &fillp) == 0);
    TEST(fillp == true);
  }
  // copy (11111111 ~ 00000000)
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    MAKE_LOCAL_BITARRAY(barray2, 128);
    TEST(bitarray_length(barray) == 128);
    TEST(bitarray_length(barray2) == 128);
    TEST(bitarray_fill(1, 0, 64, barray) == 0);
    TEST(bitarray_copy(barray, barray2) == 0);
    bool fillp;
    TEST(bitarray_fillp(1, 0, 64, barray2, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(0, 64, 128, barray2, &fillp) == 0);
    TEST(fillp == true);
  }
  // copy 0 size arrays
  {
    MAKE_LOCAL_BITARRAY(barray, 0);
    MAKE_LOCAL_BITARRAY(barray2, 0);
    TEST(bitarray_length(barray) == 0);
    TEST(bitarray_length(barray2) == 0);
    TEST(bitarray_copy(barray, barray2) == 0);
  }
  // copy different size arrays (always error!)
  {
    MAKE_LOCAL_BITARRAY(barray, 16);
    MAKE_LOCAL_BITARRAY(barray2, 8);
    TEST(bitarray_length(barray) == 16);
    TEST(bitarray_length(barray2) == 8);
    TEST(bitarray_fill(1, 0, 8, barray) == 0);
    TEST(bitarray_copy(barray, barray2) != 0); // different size (always error!)
  }
}

static void test_bitarray_strange_length (){
  // set and get
  {
    MAKE_LOCAL_BITARRAY(barray, 11);
    TEST(bitarray_length(barray) == 11);
    TEST(bitarray_set(1, 0, barray) == 0);
    TEST(bitarray_set(1, 1, barray) == 0);
    TEST(bitarray_set(1, 2, barray) == 0);
    TEST(bitarray_set(1, 3, barray) == 0);
    TEST(bitarray_set(1, 4, barray) == 0);
    TEST(bitarray_set(1, 5, barray) == 0);
    TEST(bitarray_set(1, 6, barray) == 0);
    TEST(bitarray_set(1, 7, barray) == 0);
    TEST(bitarray_set(1, 8, barray) == 0);
    TEST(bitarray_set(1, 9, barray) == 0);
    TEST(bitarray_set(1, 10, barray) == 0);
    TEST(bitarray_set(1, 11, barray) != 0); //always error!
    int value;
    TEST(bitarray_get(0, barray, &value) == 0);
    TEST(bitarray_get(1, barray, &value) == 0);
    TEST(bitarray_get(2, barray, &value) == 0);
    TEST(bitarray_get(3, barray, &value) == 0);
    TEST(bitarray_get(4, barray, &value) == 0);
    TEST(bitarray_get(5, barray, &value) == 0);
    TEST(bitarray_get(6, barray, &value) == 0);
    TEST(bitarray_get(7, barray, &value) == 0);
    TEST(bitarray_get(8, barray, &value) == 0);
    TEST(bitarray_get(9, barray, &value) == 0);
    TEST(bitarray_get(10, barray, &value) == 0);
    TEST(bitarray_get(11, barray, &value) != 0); //always error!
  }
  // fill and fillp
  {
    MAKE_LOCAL_BITARRAY(barray, 11);
    TEST(bitarray_length(barray) == 11);
    TEST(bitarray_fill(1, 0, 11, barray) == 0);
    TEST(bitarray_fill(1, 0, 12, barray) != 0); //always error!
    bool fillp;
    TEST(bitarray_fillp(1, 0, 11, barray, &fillp) == 0); 
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 0, 12, barray, &fillp) != 0); //always error! 
  }
  // write and read 
  {
    MAKE_LOCAL_BITARRAY(barray, 11);
    TEST(bitarray_length(barray) == 11);
    TEST(bitarray_write(0xff, 8, 0, barray) == 0);
    TEST(bitarray_write(0xff, 3, 8, barray) == 0);
    TEST(bitarray_write(0xff, 8, 8, barray) != 0); //always error!
    bitarray_element value;
    TEST(bitarray_read(8, 0, barray, &value) == 0);
    TEST(value == 0xff);
    TEST(bitarray_read(3, 8, barray, &value) == 0);
    TEST(value == 0b111);
    TEST(bitarray_read(8, 8, barray, &value) != 0); //always error!
  }
}

static void test_bitarray_not (){
  // not 00000000 ~ 00000000 
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    TEST(bitarray_length(barray) == 128);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 128, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_not(barray) == 0);
    TEST(bitarray_fillp(1, 0, 128, barray, &fillp) == 0);
    TEST(fillp == true);
  }
}

static void test_bitarray_and (){
  // and 00000000 ~ 11111111 & 00000000 ~ 00000000 
  {
    MAKE_LOCAL_BITARRAY(barray1, 128);
    MAKE_LOCAL_BITARRAY(barray2, 128);
    TEST(bitarray_length(barray1) == 128);
    TEST(bitarray_length(barray2) == 128);
    TEST(bitarray_fill(1, 64, 128, barray1) == 0);
    TEST(bitarray_and(barray1, barray2) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 128, barray2, &fillp) == 0);
    TEST(fillp == true);
  }
  // and 00000000 ~ 11111111 & 00000000 ~ 11111111
  {
    MAKE_LOCAL_BITARRAY(barray1, 128);
    MAKE_LOCAL_BITARRAY(barray2, 128);
    TEST(bitarray_length(barray1) == 128);
    TEST(bitarray_length(barray2) == 128);
    TEST(bitarray_fill(1, 64, 128, barray1) == 0);
    TEST(bitarray_fill(1, 64, 128, barray2) == 0);
    TEST(bitarray_and(barray1, barray2) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 64, barray2, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 64, 128, barray2, &fillp) == 0);
    TEST(fillp == true);
  }
}

static void test_bitarray_or (){
  // and 00000000 ~ 11111111 & 00000000 ~ 00000000 
  {
    MAKE_LOCAL_BITARRAY(barray1, 128);
    MAKE_LOCAL_BITARRAY(barray2, 128);
    TEST(bitarray_length(barray1) == 128);
    TEST(bitarray_length(barray2) == 128);
    TEST(bitarray_fill(1, 64, 128, barray1) == 0);
    TEST(bitarray_or(barray1, barray2) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 64, barray2, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 64, 128, barray2, &fillp) == 0);
    TEST(fillp == true);
  }
}

static void test_bitarray_xor (){
  // and 00000000 ~ 00000000 & 00000000 ~ 00000000 
  {
    MAKE_LOCAL_BITARRAY(barray1, 128);
    MAKE_LOCAL_BITARRAY(barray2, 128);
    TEST(bitarray_length(barray1) == 128);
    TEST(bitarray_length(barray2) == 128);
    TEST(bitarray_xor(barray1, barray2) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 128, barray2, &fillp) == 0);
    TEST(fillp == true);
  }
  // and 00000000 ~ 11111111 & 00000000 ~ 00000000 
  {
    MAKE_LOCAL_BITARRAY(barray1, 128);
    MAKE_LOCAL_BITARRAY(barray2, 128);
    TEST(bitarray_length(barray1) == 128);
    TEST(bitarray_length(barray2) == 128);
    TEST(bitarray_fill(1, 64, 128, barray1) == 0);
    TEST(bitarray_xor(barray1, barray2) == 0);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 64, barray2, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fillp(1, 64, 128, barray2, &fillp) == 0);
    TEST(fillp == true);
  }
}

static void test_make_bitarray (){
  {
    bitarray *barray = make_bitarray(128);
    TEST(barray != NULL);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 128, barray, &fillp) == 0);
    TEST(fillp == true);
    TEST(bitarray_fill(1, 0, 128, barray) == 0);
    TEST(bitarray_fillp(1, 0, 128, barray, &fillp) == 0);
    TEST(fillp == true);
    free_bitarray(barray);
  }
}

static void test_bitarray_find2 (){
  {
    bitarray *barray = make_bitarray(256);
    TEST(barray != NULL);
    // fill 0 ~ 40
    {
      size_t foundindex;
      TEST(bitarray_find(0, 40, barray, &foundindex) == 0);
      TEST(foundindex == 0);
      bool fillp;
      TEST(bitarray_fillp(0, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
      TEST(bitarray_fill(1, foundindex, foundindex +40, barray) == 0);
      TEST(bitarray_fillp(1, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
    }
    // fill 40 ~ 80
    {
      size_t foundindex;
      TEST(bitarray_find(0, 40, barray, &foundindex) == 0);
      TEST(foundindex == 40);
      bool fillp;
      TEST(bitarray_fillp(0, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
      TEST(bitarray_fill(1, foundindex, foundindex +40, barray) == 0);
      TEST(bitarray_fillp(1, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
    }
    // fill 80 ~ 120
    {
      size_t foundindex;
      TEST(bitarray_find(0, 40, barray, &foundindex) == 0);
      TEST(foundindex == 80);
      bool fillp;
      TEST(bitarray_fillp(0, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
      TEST(bitarray_fill(1, foundindex, foundindex +40, barray) == 0);
      TEST(bitarray_fillp(1, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
    }
    // fill 120 ~ 160
    {
      size_t foundindex;
      TEST(bitarray_find(0, 40, barray, &foundindex) == 0);
      TEST(foundindex == 120);
      bool fillp;
      TEST(bitarray_fillp(0, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
      TEST(bitarray_fill(1, foundindex, foundindex +40, barray) == 0);
      TEST(bitarray_fillp(1, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
    }
    // fill 160 ~ 200
    {
      size_t foundindex;
      TEST(bitarray_find(0, 40, barray, &foundindex) == 0);
      TEST(foundindex == 160);
      bool fillp;
      TEST(bitarray_fillp(0, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
      TEST(bitarray_fill(1, foundindex, foundindex +40, barray) == 0);
      TEST(bitarray_fillp(1, foundindex, foundindex +40, barray, &fillp) == 0);
      TEST(fillp == true);
    }
    free_bitarray(barray);
  }
}

static void test_bitarray_write2 (){
  {
    MAKE_LOCAL_BITARRAY(barray, 128);
    bool fillp;
    TEST(bitarray_fillp(0, 0, 128, barray, &fillp) == 0);
    bitarray_element value;
    TEST(bitarray_write(0xff, 4, 0, barray) == 0); // 0x0f
    TEST(bitarray_read(4, 0, barray, &value) == 0);
    TEST(value == 0x0f);
    TEST(bitarray_read(4, 4, barray, &value) == 0);
    TEST(value == 0x00);
    TEST(bitarray_read(8, 0, barray, &value) == 0);
    TEST(value == 0x0f);
    TEST(bitarray_read(8, 4, barray, &value) == 0);
    TEST(value == 0x00);
  }
}

int main (){
  test_bitarray_set();
  test_bitarray_fill();
  test_bitarray_find();
  test_bitarray_write();
  test_bitarray_copy();
  test_bitarray_strange_length();
  test_bitarray_not();
  test_bitarray_and();
  test_bitarray_or();
  test_bitarray_xor();
  test_make_bitarray();
  test_bitarray_find2();
  test_bitarray_write2();
  return 0;
}
