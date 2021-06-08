
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bitarray.h"

#ifndef MIN
#define MIN(a, b) ((a)<(b)? (a): (b))
#endif 

#ifndef MAX
#define MAX(a, b) ((a)<(b)? (b): (a))
#endif 

#define BIT_FULL ((bitarray_element)~0)
#define MASK_LEFT(index) (index < BITARRAY_BIT_WIDTH? (BIT_FULL << (index) & BIT_FULL): 0)
#define MASK_RIGHT(index) (index < BITARRAY_BIT_WIDTH? ~MASK_LEFT(index): BIT_FULL)
#define FILL_BY_MASK(value, bits, mask) ((value)? (bits)|(mask): (bits)&~(mask))
#define FILLP_BY_MASK(value, bits, mask) ((value)? ((bits)&(mask))==(mask): ((bits)&(mask))==0)
#define BIT_NTH(bits, index) ((bits)&(1 << (index)))
#define BIT_NTH_EQ(value, bits, index) ((value)? BIT_NTH(bits, index): !BIT_NTH(bits, index))

size_t bitarray_require_length (size_t bitlength){
  return BITARRAY_REQUIRE_LENGTH(bitlength);
}

static void clear_bitarray_sequence (bitarray_element *sequence, size_t length){
  for (size_t index = 0; index < length; index++){
    sequence[index] = 0;
  }
}

void bitarray_init (bitarray_element *sequence, size_t length, size_t bitlength, bitarray *barray){
  clear_bitarray_sequence(sequence, length);
  barray->sequence = sequence;
  barray->length = length;
  barray->bitlength = bitlength;
}

bitarray *make_bitarray (size_t bitlength){
  size_t requirelength = bitarray_require_length(bitlength);
  bitarray *barray = malloc(sizeof(bitarray));
  if (barray == NULL){
    return NULL;
  }
  bitarray_element *barrayseq = malloc(requirelength * sizeof(bitarray_element));
  if (barrayseq == NULL){
    free(barray);
    return NULL;
  }
  bitarray_init(barrayseq, requirelength, bitlength, barray);
  return barray;
}

void free_bitarray (bitarray *barray){
  free(barray->sequence);
  free(barray);
}

static inline bitarray_range bitarray_full_slice (bitarray *barray){
  bitarray_range newrange = { 
    0, 
    bitarray_length(barray)
  };
  return newrange;
}

bitarray_range bitarray_slice (size_t start, size_t end, bitarray *barray){
  size_t min = MIN(start, end);
  size_t max = MAX(start, end);
  bitarray_range newrange = {
    MIN(min, bitarray_length(barray)),
    MIN(max, bitarray_length(barray))
  };
  return newrange;
}

bitarray_range bitarray_range_slice (size_t start, size_t end, bitarray_range *range){
  size_t min = MIN(range->start + start, range->start + end);
  size_t max = MAX(range->start + start, range->start + end);
  bitarray_range newrange = {
    MIN(min, range->end),
    MIN(max, range->end),
  };
  return newrange;
}

static inline void bitarray_range_position (size_t index, bitarray_range *range, size_t *indexdivp, size_t *indexmodp){
  *indexdivp = (range->start + index) / BITARRAY_BIT_WIDTH;
  *indexmodp = (range->start + index) % BITARRAY_BIT_WIDTH;
}

static inline void bitarray_range_range (size_t start, size_t end, bitarray_range *range, size_t *mindivp, size_t *minmodp, size_t *maxdivp, size_t *maxmodp){
  size_t min = MIN(range->start + start, range->start + end);
  size_t max = MAX(range->start + start, range->start + end);
  *mindivp = min / BITARRAY_BIT_WIDTH;
  *minmodp = min % BITARRAY_BIT_WIDTH;
  *maxdivp = (min < max? max -1: max) / BITARRAY_BIT_WIDTH;
  *maxmodp = (min < max? max -1: max) % BITARRAY_BIT_WIDTH + (min < max? 1: 0);
}

static inline bitarray_double_element bitarray_read_double (size_t index, bitarray *barray){
  if (index +1 < barray->length){
    bitarray_double_element first = barray->sequence[index];
    bitarray_double_element second = barray->sequence[index +1];
    return first | (second << BITARRAY_BIT_WIDTH);
  }
  else 
  if (index < barray->length){
    bitarray_double_element first = barray->sequence[index];
    return first;
  }
  else {
    return 0;
  }
}

static inline void bitarray_write_double (bitarray_double_element value, size_t index, bitarray *barray){
  if (index +1 < barray->length){
    barray->sequence[index] = value;
    barray->sequence[index +1] = value >> BITARRAY_BIT_WIDTH;
  }
  else 
  if (index < barray->length){
    barray->sequence[index] = value;
  }
}

int bitarray_range_set (int value, size_t index, bitarray_range *range, bitarray *barray){
  if (range->start + index < range->end){
    size_t inddiv;
    size_t indmod;
    bitarray_range_position(index, range, &inddiv, &indmod);
    barray->sequence[inddiv] = (barray->sequence[inddiv] & ~(1 << indmod)) | ((value? 1: 0) << indmod);
    return 0;
  }
  else {
    return 1; 
  }
}

int bitarray_range_get (size_t index, bitarray_range *range, bitarray *barray, int *valuep){
  if (range->start + index < range->end){
    size_t inddiv;
    size_t indmod;
    bitarray_range_position(index, range, &inddiv, &indmod);
    *valuep = barray->sequence[inddiv] & (1 << indmod);
    return 0;
  }
  else {
    return 1; 
  }
}

int bitarray_range_fill (int value, size_t start, size_t end, bitarray_range *range, bitarray *barray){
  if (range->start + start <= range->end && range->start + end <= range->end){
    size_t mindiv;
    size_t minmod;
    size_t maxdiv;
    size_t maxmod;
    bitarray_range_range(start, end, range, &mindiv, &minmod, &maxdiv, &maxmod);
    if (mindiv == maxdiv){
      barray->sequence[mindiv] = FILL_BY_MASK(value, barray->sequence[mindiv], MASK_LEFT(minmod) & MASK_RIGHT(maxmod));
      return 0;
    }
    else {
      barray->sequence[mindiv] = FILL_BY_MASK(value, barray->sequence[mindiv], MASK_LEFT(minmod));
      for (size_t index = mindiv +1; index < maxdiv; index++){
        barray->sequence[index] = value? BIT_FULL: 0x00;
      }
      barray->sequence[maxdiv] = FILL_BY_MASK(value, barray->sequence[maxdiv], MASK_RIGHT(maxmod));
      return 0;
    }
  }
  else {
    return 1; 
  }
}

int bitarray_range_fillp (int value, size_t start, size_t end, bitarray_range *range, bitarray *barray, bool *fillp){
  if (range->start + start <= range->end && range->start + end <= range->end){
    size_t mindiv;
    size_t minmod;
    size_t maxdiv;
    size_t maxmod;
    bitarray_range_range(start, end, range, &mindiv, &minmod, &maxdiv, &maxmod);
    if (mindiv == maxdiv){
      *fillp = FILLP_BY_MASK(value, barray->sequence[mindiv], MASK_LEFT(minmod) & MASK_RIGHT(maxmod));
      return 0;
    }
    else {
      if (!FILLP_BY_MASK(value, barray->sequence[mindiv], MASK_LEFT(minmod))){
        *fillp = false;
        return 0;
      }
      for (size_t index = mindiv +1; index < maxdiv; index++){
        if (barray->sequence[index] != (value? BIT_FULL: 0x00)){
          *fillp = false;
          return 0;
        }
      }
      if (!FILLP_BY_MASK(value, barray->sequence[maxdiv], MASK_RIGHT(maxmod))){
        *fillp = false;
        return 0;
      }
      *fillp = true;
      return 0;
    }
  }
  else {
    return 1; 
  }
}

static inline int bitarray_range_find_at (int value, size_t size, size_t offset, bitarray_range *range, bitarray *barray, size_t *nextoffsetp){
  if (range->start + offset + size <= range->end){
    size_t offsetdiv;
    size_t offsetmod;
    bitarray_range_position(offset, range, &offsetdiv, &offsetmod);
    size_t indexprefix = 0;
    for (; indexprefix < size && offsetmod + indexprefix < BITARRAY_BIT_WIDTH; indexprefix++){
      if (!BIT_NTH_EQ(value, barray->sequence[offsetdiv], offsetmod + indexprefix)){
        *nextoffsetp = offset + indexprefix +1;
        return 1;
      }
    }
    size_t index = 1;
    for (; indexprefix + index * BITARRAY_BIT_WIDTH < size; index++){
      if (barray->sequence[offsetdiv + index] != (value? BIT_FULL: 0x00)){
        *nextoffsetp = offset + indexprefix + index * BITARRAY_BIT_WIDTH +1;
        return 1;
      }
    }
    size_t indexsuffix = 0;
    for (; indexprefix + index * BITARRAY_BIT_WIDTH + indexsuffix < size && indexsuffix < BITARRAY_BIT_WIDTH; indexsuffix++){
      if (!BIT_NTH_EQ(value, barray->sequence[offsetdiv + index], indexsuffix)){
        *nextoffsetp = offset + indexprefix + index * BITARRAY_BIT_WIDTH + indexsuffix +1;
        return 1;
      }
    }
    return 0;
  }
  else {
    *nextoffsetp = bitarray_range_length(range);
    return 1;
  }
}

int bitarray_range_find (int value, size_t size, bitarray_range *range, bitarray *barray, size_t *foundindexp){
  size_t offset = 0;
  while (range->start + offset < range->end){
    size_t nextoffset;
    if (bitarray_range_find_at(value, size, offset, range, barray, &nextoffset) == 0){
      *foundindexp = offset;
      return 0;
    }
    else {
      offset = nextoffset;
    }
  }
  return 1;
}

inline int bitarray_range_read (size_t size, size_t offset, bitarray_range *range, bitarray *barray, bitarray_element *valuep){
  if (range->start + offset + size <= range->end && size <= BITARRAY_BIT_WIDTH){
    size_t offsetdiv;
    size_t offsetmod;
    bitarray_range_position(offset, range, &offsetdiv, &offsetmod);
    bitarray_double_element dvalue = bitarray_read_double(offsetdiv, barray);
    *valuep = (dvalue >> offsetmod) & MASK_RIGHT(size);
    return 0;
  }
  else {
    return 1; 
  }
}

inline int bitarray_range_write (bitarray_element value, size_t size, size_t offset, bitarray_range *range, bitarray *barray){
  if (range->start + offset + size <= range->end && size <= BITARRAY_BIT_WIDTH){
    size_t offsetdiv;
    size_t offsetmod;
    bitarray_range_position(offset, range, &offsetdiv, &offsetmod);
    bitarray_double_element dvalue = bitarray_read_double(offsetdiv, barray);
    bitarray_double_element dresult = (dvalue & ~((bitarray_double_element)MASK_RIGHT(size) << offsetmod)) | ((value & MASK_RIGHT(size)) << offsetmod);
    bitarray_write_double(dresult, offsetdiv, barray);
    return 0;
  }
  else {
    return 1; 
  }
}

int bitarray_range_copy (bitarray_range *range, bitarray *barray, bitarray_range *rangeto, bitarray *barrayto){
  if (bitarray_range_length(range) == bitarray_range_length(rangeto)){
    for (size_t index = 0; index + BITARRAY_BIT_WIDTH <= bitarray_range_length(range); index += BITARRAY_BIT_WIDTH){
      bitarray_element value;
      if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, range, barray, &value) != 0){ return 1; }
      if (bitarray_range_write(value, BITARRAY_BIT_WIDTH, index, rangeto, barrayto) != 0){ return 1; }
    }
    bitarray_element value;
    if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, range, barray, &value) != 0){ return 1; }
    if (bitarray_range_write(value, bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, rangeto, barrayto) != 0){ return 1; }
    return 0;
  }
  else {
    return 1;
  }
}

int bitarray_range_not (bitarray_range *range, bitarray *barray){
  for (size_t index = 0; index + BITARRAY_BIT_WIDTH <= bitarray_range_length(range); index += BITARRAY_BIT_WIDTH){
    bitarray_element value;
    if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, range, barray, &value) != 0){ return 1; }
    if (bitarray_range_write(~value, BITARRAY_BIT_WIDTH, index, range, barray) != 0){ return 1; }
  }
  bitarray_element value;
  if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, range, barray, &value) != 0){ return 1; }
  if (bitarray_range_write(~value, bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, range, barray) != 0){ return 1; }
  return 0;
}

int bitarray_range_and (bitarray_range *range, bitarray *barray, bitarray_range *rangeto, bitarray *barrayto){
  if (bitarray_range_length(range) == bitarray_range_length(rangeto)){
    for (size_t index = 0; index + BITARRAY_BIT_WIDTH <= bitarray_range_length(range); index += BITARRAY_BIT_WIDTH){
      bitarray_element value;
      bitarray_element valueto;
      if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, range, barray, &value) != 0){ return 1; }
      if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, rangeto, barrayto, &valueto) != 0){ return 1; }
      if (bitarray_range_write(value & valueto, BITARRAY_BIT_WIDTH, index, rangeto, barrayto) != 0){ return 1; }
    }
    bitarray_element value;
    bitarray_element valueto;
    if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, range, barray, &value) != 0){ return 1; }
    if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, rangeto, barrayto, &valueto) != 0){ return 1; }
    if (bitarray_range_write(value & valueto, bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, rangeto, barrayto) != 0){ return 1; }
    return 0;
  }
  else {
    return 1;
  }
}

int bitarray_range_or (bitarray_range *range, bitarray *barray, bitarray_range *rangeto, bitarray *barrayto){
  if (bitarray_range_length(range) == bitarray_range_length(rangeto)){
    for (size_t index = 0; index + BITARRAY_BIT_WIDTH <= bitarray_range_length(range); index += BITARRAY_BIT_WIDTH){
      bitarray_element value;
      bitarray_element valueto;
      if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, range, barray, &value) != 0){ return 1; }
      if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, rangeto, barrayto, &valueto) != 0){ return 1; }
      if (bitarray_range_write(value | valueto, BITARRAY_BIT_WIDTH, index, rangeto, barrayto) != 0){ return 1; }
    }
    bitarray_element value;
    bitarray_element valueto;
    if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, range, barray, &value) != 0){ return 1; }
    if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, rangeto, barrayto, &valueto) != 0){ return 1; }
    if (bitarray_range_write(value | valueto, bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, rangeto, barrayto) != 0){ return 1; }
    return 0;
  }
  else {
    return 1;
  }
}

int bitarray_range_xor (bitarray_range *range, bitarray *barray, bitarray_range *rangeto, bitarray *barrayto){
  if (bitarray_range_length(range) == bitarray_range_length(rangeto)){
    for (size_t index = 0; index + BITARRAY_BIT_WIDTH <= bitarray_range_length(range); index += BITARRAY_BIT_WIDTH){
      bitarray_element value;
      bitarray_element valueto;
      if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, range, barray, &value) != 0){ return 1; }
      if (bitarray_range_read(BITARRAY_BIT_WIDTH, index, rangeto, barrayto, &valueto) != 0){ return 1; }
      if (bitarray_range_write(value ^ valueto, BITARRAY_BIT_WIDTH, index, rangeto, barrayto) != 0){ return 1; }
    }
    bitarray_element value;
    bitarray_element valueto;
    if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, range, barray, &value) != 0){ return 1; }
    if (bitarray_range_read(bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, rangeto, barrayto, &valueto) != 0){ return 1; }
    if (bitarray_range_write(value ^ valueto, bitarray_range_length(range) % BITARRAY_BIT_WIDTH, bitarray_range_length(range) - bitarray_range_length(range) % BITARRAY_BIT_WIDTH, rangeto, barrayto) != 0){ return 1; }
    return 0;
  }
  else {
    return 1;
  }
}

size_t bitarray_range_length (bitarray_range *range){
  return range->end - range->start;
}

int bitarray_set (int value, size_t index, bitarray *barray){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_set(value, index, &fullrange, barray);
}

int bitarray_get (size_t index, bitarray *barray, int *valuep){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_get(index, &fullrange, barray, valuep);
}

int bitarray_fill (int value, size_t start, size_t end, bitarray *barray){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_fill(value, start, end, &fullrange, barray);
}

int bitarray_fillp (int value, size_t start, size_t end, bitarray *barray, bool *fillp){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_fillp(value, start, end, &fullrange, barray, fillp);
}

int bitarray_find (int value, size_t size, bitarray *barray, size_t *foundindexp){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_find(value, size, &fullrange, barray, foundindexp);
}

int bitarray_read (size_t size, size_t offset, bitarray *barray, bitarray_element *valuep){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_read(size, offset, &fullrange, barray, valuep);
}

int bitarray_write (bitarray_element value, size_t size, size_t offset, bitarray *barray){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_write(value, size, offset, &fullrange, barray);
}

int bitarray_copy (bitarray *barray, bitarray *barrayto){
  bitarray_range fullrange = bitarray_full_slice(barray);
  bitarray_range fullrangeto = bitarray_full_slice(barrayto);
  return bitarray_range_copy(&fullrange, barray, &fullrangeto, barrayto);
}

int bitarray_not (bitarray *barray){
  bitarray_range fullrange = bitarray_full_slice(barray);
  return bitarray_range_not(&fullrange, barray);
}

int bitarray_and (bitarray *barray, bitarray *barrayto){
  bitarray_range fullrange = bitarray_full_slice(barray);
  bitarray_range fullrangeto = bitarray_full_slice(barrayto);
  return bitarray_range_and(&fullrange, barray, &fullrangeto, barrayto);
}

int bitarray_or (bitarray *barray, bitarray *barrayto){
  bitarray_range fullrange = bitarray_full_slice(barray);
  bitarray_range fullrangeto = bitarray_full_slice(barrayto);
  return bitarray_range_or(&fullrange, barray, &fullrangeto, barrayto);
}

int bitarray_xor (bitarray *barray, bitarray *barrayto){
  bitarray_range fullrange = bitarray_full_slice(barray);
  bitarray_range fullrangeto = bitarray_full_slice(barrayto);
  return bitarray_range_xor(&fullrange, barray, &fullrangeto, barrayto);
}

size_t bitarray_length (bitarray *barray){
  return barray->bitlength;
}
