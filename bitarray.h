
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint32_t bitarray_element;
typedef uint64_t bitarray_double_element;

typedef struct bitarray {
  bitarray_element *sequence;
  size_t length;
  size_t bitlength;
} bitarray;

typedef struct bitarray_range {
  size_t start;
  size_t end;
} bitarray_range;

#define BITARRAY_BIT_WIDTH (sizeof(bitarray_element) * 8)
#define BITARRAY_REQUIRE_LENGTH(bitlength) (((bitlength) / BITARRAY_BIT_WIDTH) + ((bitlength) % BITARRAY_BIT_WIDTH? 1: 0))

#define MAKE_LOCAL_BITARRAY(varname, bitlength)\
bitarray_element __ ## varname ## _sequence[BITARRAY_REQUIRE_LENGTH(bitlength)] = {};\
bitarray __ ## varname = { __ ## varname ## _sequence, BITARRAY_REQUIRE_LENGTH(bitlength), (bitlength) };\
bitarray *varname = &__ ## varname;

extern size_t bitarray_require_size (size_t);
extern void bitarray_init (bitarray_element*, size_t, size_t, bitarray*);
extern bitarray *make_bitarray (size_t);
extern void free_bitarray (bitarray*);
extern bitarray_range bitarray_slice (size_t, size_t, bitarray*);
extern bitarray_range bitarray_range_slice (size_t, size_t, bitarray_range*);
extern int bitarray_range_set (int, size_t, bitarray_range*, bitarray*);
extern int bitarray_range_get (size_t, bitarray_range*, bitarray*, int*);
extern int bitarray_range_fill (int, size_t, size_t, bitarray_range*, bitarray*);
extern int bitarray_range_fillp (int, size_t, size_t, bitarray_range*, bitarray*, bool*);
extern int bitarray_range_find (int, size_t, bitarray_range*, bitarray*, size_t*);
extern int bitarray_range_read (size_t, size_t, bitarray_range*, bitarray*, bitarray_element*);
extern int bitarray_range_write (bitarray_element, size_t, size_t, bitarray_range*, bitarray*);
extern int bitarray_range_not (bitarray_range*, bitarray*);
extern int bitarray_range_and (bitarray_range*, bitarray*, bitarray_range*, bitarray*);
extern int bitarray_range_or (bitarray_range*, bitarray*, bitarray_range*, bitarray*);
extern int bitarray_range_xor (bitarray_range*, bitarray*, bitarray_range*, bitarray*);
extern size_t bitarray_range_length (bitarray_range*);
extern int bitarray_set (int, size_t, bitarray*);
extern int bitarray_get (size_t, bitarray*, int*);
extern int bitarray_fill (int, size_t, size_t, bitarray*);
extern int bitarray_fillp (int, size_t, size_t, bitarray*, bool*);
extern int bitarray_find (int, size_t, bitarray*, size_t*);
extern int bitarray_read (size_t, size_t, bitarray*, bitarray_element*);
extern int bitarray_write (bitarray_element, size_t, size_t, bitarray*);
extern int bitarray_copy (bitarray*, bitarray*);
extern int bitarray_not (bitarray*);
extern int bitarray_and (bitarray*, bitarray*);
extern int bitarray_or (bitarray*, bitarray*);
extern int bitarray_xor (bitarray*, bitarray*);
extern size_t bitarray_length (bitarray*);
