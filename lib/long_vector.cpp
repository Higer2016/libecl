/*
   Copyright (C) 2011  Equinor ASA, Norway.

   The file 'vector_template.c' is part of ERT - Ensemble based Reservoir Tool.

   ERT is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   ERT is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.

   See the GNU General Public License at <http://www.gnu.org/licenses/gpl.html>
   for more details.
*/

/**
   This file implements a very simple vector functionality. The vector
   is charactereized by the following:

    o The content is only fundamental scalar types, like double, int
      or bool. If you want a vector of compositie types use the
      vector_type implementation.

    o The vector will grow as needed. You can safely set any index in
      the vector, and it will automatically grow. However - this might
      lead to 'holes' - these will be filled with the default value.

    o The implementation is in terms of a long, the following sed
      one-liners will then produce proper source and header files:

        sed -e's/long/int/g' vector_template.c > int_vector.c
        sed -e's/long/int/g' vector_template.h > int_vector.h


   Illustration of the interplay of size, alloc_size and default value.


   1. int_vector_type * vector = int_vector_alloc(2 , 77);
   2. int_vector_append(vector , 1);
   3. int_vector_append(vector , 0);
   4. int_vector_append(vector , 12);
   5. int_vector_iset(vector , 6 , 78);
   6. int_vector_set_default( vector , 99 );

   ------------------------------------

    �-----�-----�
1.  | 77  | 77  |                                                                                     size = 0, alloc_size = 2
    �-----�-----�

    �-----�-----�
2.  |  1  | 77  |                                                                                     size = 1, alloc_size = 2
    �-----�-----�

    �-----�-----�
3.  |  1  |  0  |                                                                                     size = 2, alloc_size = 2
    �-----�-----�

    �-----�-----�-----�-----�
4.  |  1  |  0  |  12 | 77  |                                                                         size = 3, alloc_size = 4
    �-----�-----�-----�-----�

    �-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�
5.  |  1  |  0  |  12 |  77 |  77 | 77  |  78 | 77  | 77  |  77 | 77  | 77  | 77  | 77  | 77  | 77  | size = 7, alloc_size = 12, default = 77
    �-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�

    �-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�
6.  |  1  |  0  |  12 |  77 |  77 | 77  |  78 | 99  | 99  |  99 | 99  | 99  | 99  | 99  | 99  | 99  | size = 7, alloc_size = 12, default = 99
    �-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�-----�

       0     1      2    3     4     5     6     7     8     9    10    11    12    13    14   15


    1. In point 4. above - if you ask the vector for it's size you
       will get 3, and int_vector_iget(vector, 3) will fail because
       that is beyound the end of the vector.

    2. The size of the vector is the index (+1) of the last validly
       set element in the vector.

    3. In point 5 above we have grown the vector quite a lot to be
       able to write in index 6, as a results there are now many slots
       in the vector which contain the default value - i.e. 77 in this
       case.

    4. In point 6 we change the default value 77 -> 99, then all the
       77 values from position 7 and onwards are changed to 99; the 77
       values in positions 3,4 & 5 are not touched.


*/

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <ert/util/type_macros.hpp>
#include <ert/util/util.h>
#include <ert/util/long_vector.hpp>

#ifdef __cplusplus
extern "C" {
#endif

static const char * string_type = "long";
#define TYPE_VECTOR_ID ((int *) string_type )[0]

struct long_vector_struct {
  UTIL_TYPE_ID_DECLARATION;
  int      alloc_size;    /* The allocated size of data. */
  int      size;          /* The index of the last valid - i.e. actively set - element in the vector. */
  long   default_value; /* The data vector is initialized with this value. */
  long * data;          /* The actual data. */
  bool     data_owner;    /* Is the vector owner of the the actual storage data?
                             If this is false the vector can not be resized. */
  bool     read_only;
};


/**
   This datatype is used when allocating a permutation list
   corresponding to a sorted a xxx_vector instance. This permutation
   list can then be used to reorder several xxx_vector instances.
*/

typedef struct {
  int    index;
  long value;
} sort_node_type;


UTIL_SAFE_CAST_FUNCTION(long_vector , TYPE_VECTOR_ID);
UTIL_IS_INSTANCE_FUNCTION(long_vector , TYPE_VECTOR_ID);


static void long_vector_realloc_data__(long_vector_type * vector , int new_alloc_size, long default_value) {
  if (new_alloc_size != vector->alloc_size) {
    if (vector->data_owner) {
      if (new_alloc_size > 0) {
        int i;
        vector->data = (long*)util_realloc(vector->data , new_alloc_size * sizeof * vector->data );
        for (i=vector->alloc_size;  i < new_alloc_size; i++)
          vector->data[i] = default_value;
      } else {
        if (vector->alloc_size > 0) {
          free(vector->data);
          vector->data = NULL;
        }
      }
      vector->alloc_size = new_alloc_size;
    } else
      util_abort("%s: tried to change the storage are for a shared data segment \n",__func__);
  }
}


static void long_vector_memmove(long_vector_type * vector , int offset , int shift) {
  if ((shift + offset) < 0)
    util_abort("%s: offset:%d  left_shift:%d - invalid \n",__func__ , offset , -shift);

  if ((shift + vector->size > vector->alloc_size))
    long_vector_realloc_data__( vector , util_int_min( 2*vector->alloc_size , shift + vector->size ), vector->default_value);

  {
    size_t move_size   = (vector->size - offset) * sizeof(long);
    long * target    = &vector->data[offset + shift];
    const long * src = &vector->data[offset];
    memmove( target , src , move_size );

    vector->size += shift;
  }
}



static void long_vector_assert_index(const long_vector_type * vector , int index) {
  if ((index < 0) || (index >= vector->size))
    util_abort("%s: index:%d invalid. Valid interval: [0,%d>.\n",__func__ , index , vector->size);
}




static long_vector_type * long_vector_alloc__(int init_size , long default_value, long * data, int alloc_size , bool data_owner ) {
  long_vector_type * vector = (long_vector_type*)util_malloc( sizeof * vector );
  UTIL_TYPE_ID_INIT( vector , TYPE_VECTOR_ID);
  vector->default_value       = default_value;

  /**
     Not all combinations of (data, alloc_size, data_owner) are valid:

     1. Creating a new vector instance with fresh storage allocation
        from long_vector_alloc():

          data       == NULL
          alloc_size == 0
          data_owner == true


     2. Creating a shared wrapper from the long_vector_alloc_shared_wrapper():

          data       != NULL
          data_size   > 0
          data_owner == false


     3. Creating a private wrapper which steals the input data from
        long_vector_alloc_private_wrapper():

          data       != NULL
          data_size   > 0
          data_owner == true

  */

  if (data == NULL) {  /* Case 1: */
    vector->data              = NULL;
    vector->data_owner        = true;     /* The input values alloc_size and */
    vector->alloc_size        = 0;        /* data_owner are not even consulted. */
  } else {             /* Case 2 & 3 */
    vector->data              = data;
    vector->data_owner        = data_owner;
    vector->alloc_size        = alloc_size;
  }
  vector->size                = 0;

  long_vector_set_read_only( vector , false );
  if (init_size > 0)
    long_vector_resize( vector , init_size , default_value );  /* Filling up the init size elements with the default value */

  return vector;
}


/**
   The alloc_size argument is just a hint - the vector will grow as
   needed.
*/

long_vector_type * long_vector_alloc(int init_size , long default_value) {
  long_vector_type * vector = long_vector_alloc__( init_size , default_value , NULL , 0 , true );
  return vector;
}


/**
   new_size < current_size: The trailing elements will be lost

   new_size > current_size: The vector will grow by adding default elements at the end.
*/

void long_vector_resize( long_vector_type * vector , int new_size, long default_value ) {
  if (new_size > vector->size) {
    if (new_size > vector->alloc_size) {
      for (int i = vector->size; i < vector->alloc_size; i++)
        vector->data[i] = default_value;
      long_vector_realloc_data__( vector, 2 * new_size, default_value);
    }
    else
      for (int i = vector->size; i < new_size; i++)
        vector->data[i] = default_value;
  }
  vector->size = new_size;
}


void long_vector_set_read_only( long_vector_type * vector , bool read_only) {
  vector->read_only = read_only;
}

bool long_vector_get_read_only( const long_vector_type * vector ) {
  return vector->read_only;
}


static void long_vector_assert_writable( const long_vector_type * vector ) {
  if (vector->read_only)
    util_abort("%s: Sorry - tried to modify a read_only vector instance.\n",__func__);
}

/**
   This function will allocate a shared wrapper around the input
   pointer data. The vector implementation will work transparently
   with the input data, but the data will not be reallocated, and also
   not freed when exiting, this implies that it is safe (memory wise)
   to work with the memory location pointed to by data from somewhere
   else as well.

   Vector wrappers allocated this way can NOT grow, and will fail HARD
   if a resize beyond alloc_size is attempted - check with
   long_vector_growable()
*/


long_vector_type * long_vector_alloc_shared_wrapper(int init_size, long default_value , long * data , int alloc_size) {
  return long_vector_alloc__( init_size , default_value , data , alloc_size , false );
}


/**
   This function will allocate a vector wrapper around the input
   pointer data. The input data will be hijacked by the vector
   implementation, and the vector will continue like a 100% normal
   vector instance, that includes the capability to resize the data
   area, and the data are will also be freed when the vector is freed.

   Observe that it is (in general) NOT safe to continue to use the
   data pointer from an external scope.
*/


long_vector_type * long_vector_alloc_private_wrapper(int init_size, long default_value , long * data , int alloc_size) {
  return long_vector_alloc__( init_size , default_value , data , alloc_size , false );
}



/**
   This function will copy a block starting at index @src_offset in
   the src vector to a block starting at @target_offset in the target
   vector. The target vector will be resized and initialized with
   default values as required.

   If len goes beyond the length of the src vector the function will
   fail hard.
*/
void long_vector_memcpy_data_block( long_vector_type * target , const long_vector_type * src , int target_offset , int src_offset , int len) {
  if ((src_offset + len) > src->size)
    util_abort("%s: offset:%d  blocksize:%d  vector_size:%d - invalid \n",__func__ , src_offset , len , src->size);

  /* Force a resize + default initialisation of the target. */
  if (target->alloc_size < (target_offset + len))
    long_vector_iset( target , target_offset + len - 1 , target->default_value) ;

  /* Copy the content. */
  memcpy( &target->data[target_offset] , &src->data[src_offset] , len * sizeof * src->data );

  /* Update size of target. */
  if (target->size < (target_offset + len))
    target->size = target_offset + len;
}



void long_vector_memcpy_from_data( long_vector_type * target , const long * src , int src_size ) {
  long_vector_reset( target );
  //long_vector_iset( target , src_size - 1 , 0 );
  long_vector_resize( target, src_size, 0);
  memcpy( target->data , src , src_size * sizeof * target->data );
}


void long_vector_memcpy_data( long * target, const long_vector_type * src ) {
  memcpy( target , src->data , src->size * sizeof * src->data );
}


/**
   This function will copy all the content (both header and data) from
   the src vector to the target vector. If the the current allocation
   size of the target vector is sufficiently large, it will not be
   touched.

   Observe that also the default value will be copied.
*/


void long_vector_memcpy( long_vector_type * target, const long_vector_type * src ) {
  long_vector_reset( target );
  target->default_value = src->default_value;

  long_vector_memcpy_data_block( target  , src , 0 , 0 , src->size );
}






/**
   Should essentially implement Python sliced index lookup.
*/
long_vector_type * long_vector_alloc_strided_copy( const long_vector_type * src , int start , int stop , int stride ) {
  long_vector_type * copy = long_vector_alloc( 0 , src->default_value );
  if (start < 0)
    start = src->size - start;

  if (stop < 0)
    stop = src->size - stop;

  {
    int src_index = start;
    while (src_index < stop) {
      long_vector_append( copy , long_vector_iget( src , src_index ));
      src_index += stride;
    }
  }
  return copy;
}


long_vector_type * long_vector_alloc_copy( const long_vector_type * src) {
  long_vector_type * copy = long_vector_alloc( src->size , src->default_value );
  long_vector_realloc_data__( copy , src->alloc_size, src->default_value );
  copy->size = src->size;
  memcpy(copy->data , src->data , src->alloc_size * sizeof * src->data );
  return copy;
}

bool long_vector_growable( const long_vector_type * vector) {
  return vector->data_owner;
}


long long_vector_get_default(const long_vector_type * vector) {
  return vector->default_value;
}


/**
   This will set the default value. This implies that everything
   following the current length of the vector will be set to the new
   default value, whereas values not explicitly set in the interior of
   the vector will retain the old default value.
*/


void long_vector_set_default(long_vector_type * vector, long default_value) {
  long_vector_assert_writable( vector );
  {
    int i;
    vector->default_value = default_value;
    for (i=vector->size; i < vector->alloc_size; i++)
      vector->data[i] = default_value;
  }
}

/**
   This function will append the value @default_value to the vector,
   and then subsequently set this value as the new default.
*/

void long_vector_append_default(long_vector_type * vector , long default_value) {
  long_vector_append( vector , default_value );
  long_vector_set_default( vector , default_value );
}


/**
   This function will iset the value @default_value into the vector,
   and then subsequently set this value as the new default.

   1.    V = [1 , 2 , 3 , 4 ], default = 77


   2.  _iset_default(v , 10 , 66)

         V = [1 ,2 , 3 ,  4 , 77, 77, 77, 77, 77, 77, 66]

       I.e. before setting the 66 value all values up to @index are
       filled with the current default.

   3. If @index is inside the current data region, there will be no
      effect of the current default, i.e. _iset_default(v , 2 , 66)
      will just give:

         V = [1 ,2 , 66 ,  4 ]

      and 66 as the new default value.
*/

void long_vector_iset_default(long_vector_type * vector , int index , long default_value) {
  long_vector_iset( vector , index , default_value );
  long_vector_set_default( vector , default_value );
}




long long_vector_iget(const long_vector_type * vector , int index) {
  long_vector_assert_index(vector , index);
  return vector->data[index];
}

/* Will start counting from the reverse end, as negative indexing in python:

   vector_reverse_iget( v , -1 ) => The last element
   vector_reverse_iget( v , -2 ) => The second to last element

*/
long long_vector_reverse_iget(const long_vector_type * vector , int index) {
  return long_vector_iget( vector , index + vector->size );
}



/**
   This might very well operate on a default value.
*/
void long_vector_imul(long_vector_type * vector, int index, long factor) {
  long_vector_assert_index(vector , index);
  vector->data[index] *= factor;
}


/* Vector * scalar */
void long_vector_scale(long_vector_type * vector, long factor) {
  int i;
  for (i=0; i < vector->size; i++)
    vector->data[i] *= factor;
}


/* Vector / scalar; seperate _div function to ensure correct integer division. */
void long_vector_div(long_vector_type * vector, long divisor) {
  int i;
  for (i=0; i < vector->size; i++)
    vector->data[i] /= divisor;
}


/* vector + scalar */
void long_vector_shift(long_vector_type * vector, long delta) {
  int i;
  for (i=0; i < vector->size; i++)
    vector->data[i] += delta;
}

/* vector + vector */
void long_vector_inplace_add( long_vector_type * vector , const long_vector_type * delta) {
  if (vector->size != delta->size)
    util_abort("%s: combining vectors with different size: %d and %d \n",__func__ , vector->size , delta->size);
  {
    int i;
    for (i=0; i < vector->size; i++)
      vector->data[i] += delta->data[i];
  }
}

/* vector - vector */
void long_vector_inplace_sub( long_vector_type * vector , const long_vector_type * delta) {
  if (vector->size != delta->size)
    util_abort("%s: combining vectors with different size: %d and %d \n",__func__ , vector->size , delta->size);
  {
    int i;
    for (i=0; i < vector->size; i++)
      vector->data[i] -= delta->data[i];
  }
}


/* vector * vector (elementwise) */
void long_vector_inplace_mul( long_vector_type * vector , const long_vector_type * factor) {
  if (vector->size != factor->size)
    util_abort("%s: combining vectors with different size: %d and %d \n",__func__ , vector->size , factor->size);
  {
    int i;
    for (i=0; i < vector->size; i++)
      vector->data[i] *= factor->data[i];
  }
}


/* vector / vector (elementwise) */
void long_vector_inplace_div( long_vector_type * vector , const long_vector_type * inv_factor) {
  if (vector->size != inv_factor->size)
    util_abort("%s: combining vectors with different size: %d and %d \n",__func__ , vector->size , inv_factor->size);
  {
    int i;
    for (i=0; i < vector->size; i++)
      vector->data[i] /= inv_factor->data[i];
  }
}

/* Will return default value if index > size. Will fail HARD on negative indices (not that safe) ....*/

long long_vector_safe_iget(const long_vector_type * vector, int index) {
  if (index >= vector->size)
    return vector->default_value;
  else {
    if (index >= 0)
      return vector->data[index];
    else {
      util_abort("%s: index:%d is invalid - only accepts positive indices.\n",__func__ , index);
      return -1;
    }
  }
}

/** Will abort is size == 0 */
long long_vector_get_last(const long_vector_type * vector) {
  return long_vector_iget(vector , vector->size - 1);
}


/** Will abort is size == 0 */
long long_vector_get_first(const long_vector_type * vector) {
  return long_vector_iget(vector , 0);
}

/**
   Observe that this function will grow the vector if necessary. If
   index > size - i.e. leaving holes in the vector, these are
   explicitly set to the default value. If a reallocation is needed it
   is done in the realloc routine, otherwise it is done here.
*/

void long_vector_iset(long_vector_type * vector , int index , long value) {
  long_vector_assert_writable( vector );
  {
    if (index < 0)
      util_abort("%s: Sorry - can NOT set negative indices. called with index:%d \n",__func__ , index);
    {
      if (vector->alloc_size <= index)
        long_vector_realloc_data__(vector , 2 * (index + 1), vector->default_value);  /* Must have ( + 1) here to ensure we are not doing 2*0 */
      vector->data[index] = value;
      if (index >= vector->size) {
        int i;
        for (i=vector->size; i < index; i++)
          vector->data[i] = vector->default_value;
        vector->size = index + 1;
      }
    }
  }
}

/*
  The block_size can be negative, in which case the loop will walk to
  the left in the vector.
*/

void long_vector_iset_block(long_vector_type * vector , int index , int block_size , long value) {
  int sign = (block_size > 0) ? 1 : -1 ;
  int c;
  for (c=0; c < abs(block_size); c++)
    long_vector_iset( vector , index + c * sign , value);
}


/**
   This function invokes _iset - i.e. growing the vector if needed. If
   the index is not currently set, the default value will be used.
*/

long long_vector_iadd( long_vector_type * vector , int index , long delta) {
  long new_value     = long_vector_safe_iget(vector , index ) + delta;
  long_vector_iset( vector , index , new_value );
  return new_value;
}

/**
   Will remove a block of length @block_size elements, starting at
   @index from the vector. The @block_size might very well extend beyond
   the length of the vector.

   V = [ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9]

   vector_idel_block( vector , 4 , 2 ) =>  V = [ 0 , 1 , 2 , 3 , 6 , 7 , 8 , 9]

   The function is based on memmove() and probably not a high
   performance player....
*/


void long_vector_idel_block( long_vector_type * vector , int index , int block_size) {
  long_vector_assert_writable( vector );
  {
    if ((index >= 0) && (index < vector->size) && (block_size >= 0)) {
      if (index + block_size > vector->size)
        block_size = vector->size - index;

      index += block_size;
      long_vector_memmove( vector , index , -block_size );
    } else
      util_abort("%s: invalid input \n",__func__);
  }
}

/**
   Removes element @index from the vector, shifting all elements to
   the right of @index one element to the left and shrinking the total
   vector. The return value is the value which is removed.
*/


long long_vector_idel( long_vector_type * vector , int index) {
  long del_value = long_vector_iget( vector , index );
  long_vector_idel_block( vector , index , 1 );
  return del_value;
}



/**
   Removes all occurences of @value from the vector, thereby shrinking
   the vector. The return value is the number of elements removed from
   the vector.
*/

long long_vector_del_value( long_vector_type * vector , long del_value) {
  int index = 0;
  int del_count = 0;
  while (true) {
    if (index == vector->size)
      break;

    if (long_vector_iget( vector , index) == del_value) {
      long_vector_idel( vector , index);
      del_count++;
    } else
      index++;
  }
  return del_count;
}


void long_vector_insert( long_vector_type * vector , int index , long value) {
  if (index >= vector->size)
    long_vector_iset( vector , index , value );
  else {
    long_vector_memmove( vector , index , 1 );
    long_vector_iset( vector , index , value );
  }
}


void long_vector_append(long_vector_type * vector , long value) {
  //long_vector_iset(vector , vector->size , value);
  int size = vector->size;
  long_vector_resize(vector, size+1, 0);
  vector->data[size] = value;
}


void long_vector_reset(long_vector_type * vector) {
  long_vector_assert_writable( vector );
  vector->size = 0;
}


void long_vector_free_container(long_vector_type * vector) {
  free( vector );
}


void long_vector_free_data(long_vector_type * vector) {
  long_vector_reset(vector);
  long_vector_realloc_data__(vector , 0, vector->default_value);
}


void long_vector_free(long_vector_type * vector) {
  if (vector->data_owner)
    free( vector->data );
  long_vector_free_container( vector );
}


void long_vector_free__(void * __vector) {
  long_vector_type * vector = (long_vector_type *) __vector;
  long_vector_free( vector );
}


void long_vector_reset__(void * __vector) {
  long_vector_type * vector = long_vector_safe_cast( __vector );
  long_vector_reset( vector );
}


int long_vector_size(const long_vector_type * vector) {
  return vector->size;
}


/**
   The pop function will remove the last element from the vector and
   return it. If the vector is empty - it will abort.
*/

long long_vector_pop(long_vector_type * vector) {
  long_vector_assert_writable( vector );
  {
    if (vector->size > 0) {
      long value = vector->data[vector->size - 1];
      vector->size--;
      return value;
    } else {
      util_abort("%s: trying to pop from empty vector \n",__func__);
      return -1;   /* Compiler shut up. */
    }
  }
}


void long_vector_rshift(long_vector_type * vector , int shift) {
  if (shift < 0)
    long_vector_memmove( vector , -shift , shift);
  else {
    int i;
    long_vector_memmove( vector , 0 , shift);
    for (i=0; i < shift; i++)
      vector->data[i] = vector->default_value;
  }
}

void long_vector_lshift(long_vector_type * vector , int shift) {
  long_vector_rshift( vector , -shift);
}


long * long_vector_get_ptr(const long_vector_type * vector) {
  long_vector_assert_writable( vector );
  return vector->data;
}



const long * long_vector_get_const_ptr(const long_vector_type * vector) {
  return vector->data;
}


/**
   Observe that there is a principle difference between the get_ptr()
   functions and alloc_data_copy() when the vector has zero size. The
   former functions will always return valid (long *) pointer,
   altough possibly none of the elements have been set by the vector
   instance, whereas the alloc_data_copy() function will return NULL
   in that case.
*/

long * long_vector_alloc_data_copy( const long_vector_type * vector ) {
  int      size = vector->size * sizeof ( long );
  long * copy = (long*)util_calloc(vector->size , sizeof * copy );
  if (copy != NULL)
    memcpy( copy , vector->data , size);
  return copy;
}

int long_vector_element_size( const long_vector_type * vector ) {
  return sizeof( long );
}

void long_vector_set_many(long_vector_type * vector , int index , const long * data , int length) {
  long_vector_assert_writable( vector );
  {
    int min_size = index + length;
    if (min_size > vector->alloc_size)
      long_vector_realloc_data__(vector , 2 * min_size, vector->default_value);
    memcpy( &vector->data[index] , data , length * sizeof * data);
    if (min_size > vector->size)
      vector->size = min_size;
  }
}

void long_vector_set_all(long_vector_type * vector , long value) {
  long_vector_assert_writable( vector );
  {
    int i;
    for (i=0; i< vector->size; i++)
      vector->data[i] = value;
  }
}


/**
   The bahviour of this function should closely follow the semantics
   of the Python range() function.
*/
void long_vector_init_range(long_vector_type * vector , long value1 , long value2 , long delta) {
  long_vector_reset( vector );
  if (delta != 0) {
    bool valid_range = delta > 0 && value2 > value1;
    #if true
    valid_range |= delta < 0 && value2 < value1;
    #endif

    if (valid_range) {
      long current_value = value1;
      while (true) {
	    long_vector_append( vector , current_value );
	    current_value += delta;

        if (delta > 0 && current_value >= value2)
	      break;

        #if true
        if (delta < 0 && current_value <= value2)
	      break;
        #endif
      }
    }
  }
}



bool long_vector_init_linear(long_vector_type * vector , long start_value, long end_value, int num_values) {
  if (num_values < 2)
    return false;

  long_vector_reset( vector );
  long_vector_iset( vector, 0 , start_value);
  {
    double slope = (end_value - start_value) / (num_values - 1);

    for (int i=1; i < num_values - 1; i++) {
      long value = (long) start_value + slope*i;
      long_vector_iset(vector, i, value);
    }
  }
  long_vector_iset( vector, num_values - 1, end_value);
  return true;
}


void long_vector_append_many(long_vector_type * vector , const long * data , int length) {
  long_vector_set_many( vector , long_vector_size( vector ) , data , length);
}

void long_vector_append_vector(long_vector_type * vector , const long_vector_type * other) {
  long_vector_append_many( vector , long_vector_get_const_ptr( other ), long_vector_size( other ));
}


/**
   This will realloc the vector so that alloc_size exactly matches
   size.
*/

void long_vector_shrink(long_vector_type * vector) {
  long_vector_realloc_data__(vector , vector->size, vector->default_value);
}


int long_vector_get_max_index(const long_vector_type * vector, bool reverse) {
  if (vector->size == 0)
    util_abort("%s: can not look for max_index in an empty vector \n",__func__);
  {
    int max_index;
    int i;
    if (reverse) {
      long max_value;
      max_index = vector->size - 1;
      max_value = vector->data[max_index];

      for (i=vector->size - 1; i >= 0; i--) {
        if (vector->data[i] > max_value) {
          max_value = vector->data[i];
          max_index = i;
        }
      }
    } else {
      long max_value;
      max_index = 0;
      max_value = vector->data[max_index];

      for (i=0; i < vector->size; i++) {
        if (vector->data[i] > max_value) {
          max_value = vector->data[i];
          max_index = i;
        }
      }
    }
    return max_index;
  }
}


long long_vector_get_max(const long_vector_type * vector) {
  int max_index = long_vector_get_max_index( vector , false );
  return vector->data[ max_index ];
}


int long_vector_get_min_index(const long_vector_type * vector, bool reverse) {
  if (vector->size == 0)
    util_abort("%s: can not look for min_index in an empty vector \n",__func__);
  {
    int min_index;
    int i;
    if (reverse) {
      long min_value;
      min_index = vector->size - 1;

      min_value = vector->data[min_index];
      for (i=vector->size - 1; i >= 0; i--) {
        if (vector->data[i] < min_value) {
          min_value = vector->data[i];
          min_index = i;
        }
      }
    } else {
      long min_value;
      min_index = 0;

      min_value = vector->data[min_index];
      for (i=0; i < vector->size; i++) {
        if (vector->data[i] < min_value) {
          min_value = vector->data[i];
          min_index = i;
        }
      }
    }
    return min_index;
  }
}




long long_vector_get_min(const long_vector_type * vector) {
  int min_index = long_vector_get_min_index( vector , false );
  return vector->data[ min_index ];
}





long long_vector_sum(const long_vector_type * vector) {
  int i;
  long sum = 0;
  for (i=0; i < vector->size; i++)
    sum += vector->data[i];
  return sum;
}


/**
   Checks if the vector contains the value @value. The comparison is
   done with ==; i.e. it is only suitable for integer-like types.

   The implementation does a linear search through the vector and
   returns the index of the @value, or -1 if @value is not found. If
   the vector is known to be sorted you should use the
   long_vector_index_sorted() instead.
*/

int long_vector_index(const long_vector_type * vector , long value) {
  if (vector->size) {
    int index = 0;
    while (true) {
      if (vector->data[index] == value)
        break;

      index++;
      if (index == vector->size) {
        index = -1;  /* Not found */
        break;
      }
    }

    return index;
  } else
    return -1;
}

bool long_vector_contains(const long_vector_type * vector , long value) {
  if (long_vector_index( vector , value) >= 0)
    return true;
  else
    return false;
}


bool long_vector_contains_sorted(const long_vector_type * vector , long value) {
  if (long_vector_index_sorted( vector , value) >= 0)
    return true;
  else
    return false;
}


/*
  Should be reimplemented with util_sorted_contains_xxx().
*/

int long_vector_index_sorted(const long_vector_type * vector , long value) {
  if (vector->size) {

    if (value < vector->data[0])
      return -1;
    if (value == vector->data[ 0 ])
      return 0;

    {
      int last_index = vector->size - 1;
      if (value > vector->data[ last_index ])
        return -1;
      if (value == vector->data[ last_index])
        return last_index;
    }


    {
      int lower_index = 0;
      int upper_index = vector->size - 1;

      while (true) {
        if ((upper_index - lower_index) <= 1)
          /* Not found */
          return -1;

        {
          int center_index = (lower_index + upper_index) / 2;
          long center_value = vector->data[ center_index ];

          if (center_value == value)
            /* Found it */
            return center_index;
          else {
            if (center_value > value)
              upper_index = center_index;
            else
              lower_index = center_index;
          }
        }
      }
    }
  } else
    return -1;
}

static int long_vector_cmp(const void *_a, const void *_b) {
  long a = *((long *) _a);
  long b = *((long *) _b);

  if (a > b)
    return 1;

  if (a < b)
    return -1;

  return 0;
}

/* Reverse compare function. */

static int long_vector_rcmp(const void *a, const void *b) {
  return long_vector_cmp( b , a );
}


/**
   The input vector will be altered in place, so that the vector only
   contains every numerical value __once__. On exit the values will be
   sorted in increasing order.

   vector = <7 , 0 , 1 , 7 , 1 , 0 , 7 , 1> => <0,1,7>
*/

void long_vector_select_unique(long_vector_type * vector) {
  long_vector_assert_writable( vector );
  if (vector->size > 0) {
    long_vector_type * copy = long_vector_alloc_copy( vector );
    long_vector_sort( copy );
    long_vector_reset( vector );
    {
      int i;
      long previous_value = long_vector_iget( copy , 0);
      long_vector_append( vector , previous_value);

      for (i=1; i <  copy->size; i++) {
        long value = long_vector_iget( copy , i );
        if (value != previous_value)
          long_vector_append( vector , value);
        previous_value = value;
      }
    }
    long_vector_free( copy );
  }
}

/**
   Inplace numerical sort of the vector; sorted in increasing order.
*/
void long_vector_sort(long_vector_type * vector) {
  long_vector_assert_writable( vector );
  qsort(vector->data , vector->size , sizeof * vector->data ,  long_vector_cmp);
}


void long_vector_rsort(long_vector_type * vector) {
  long_vector_assert_writable( vector );
  qsort(vector->data , vector->size , sizeof * vector->data ,  long_vector_rcmp);
}



static int long_vector_cmp_node(const void *_a, const void *_b) {
  sort_node_type a = *((sort_node_type *) _a);
  sort_node_type b = *((sort_node_type *) _b);

  if (a.value < b.value)
    return -1;

  if (a.value > b.value)
    return 1;

  return 0;
}


static int long_vector_rcmp_node(const void *a, const void *b) {
  return long_vector_cmp_node( b , a );
}

/**
   This function will allocate a (int *) pointer of indices,
   corresponding to the permutations of the elements in the vector to
   get it into sorted order. This permutation can then be used to sort
   several vectors identically:

   int_vector_type    * v1;
   bool_vector_type   * v2;
   double_vector_type * v2;
   .....
   .....

   {
      int * sort_perm = int_vector_alloc_sort_perm( v1 );
      int_vector_permute( v1 , sort_perm );
      bool_vector_permute( v2 , sort_perm );
      double_vector_permute( v3 , sort_perm );
      free(sort_perm);
   }

*/




static perm_vector_type * long_vector_alloc_sort_perm__(const long_vector_type * vector, bool reverse) {
  int * perm = (int*)util_calloc( vector->size , sizeof * perm ); // The perm_vector return value will take ownership of this array.
  sort_node_type * sort_nodes = (sort_node_type*)util_calloc( vector->size , sizeof * sort_nodes );
  int i;
  for (i=0; i < vector->size; i++) {
    sort_nodes[i].index = i;
    sort_nodes[i].value = vector->data[i];
  }
  if (reverse)
    qsort(sort_nodes , vector->size , sizeof * sort_nodes ,  long_vector_rcmp_node);
  else
    qsort(sort_nodes , vector->size , sizeof * sort_nodes ,  long_vector_cmp_node);

  for (i=0; i < vector->size; i++)
    perm[i] = sort_nodes[i].index;

  free( sort_nodes );
  return perm_vector_alloc( perm , vector->size );
}


perm_vector_type * long_vector_alloc_sort_perm(const long_vector_type * vector) {
  return long_vector_alloc_sort_perm__( vector , false );
}


perm_vector_type *  long_vector_alloc_rsort_perm(const long_vector_type * vector) {
  return long_vector_alloc_sort_perm__( vector , true );
}


void long_vector_permute(long_vector_type * vector , const perm_vector_type * perm) {
  long_vector_assert_writable( vector );
  {
    int i;
    long * tmp = (long*)util_alloc_copy( vector->data , sizeof * tmp * vector->size );
    for (i=0; i < vector->size; i++)
      vector->data[i] = tmp[perm_vector_iget( perm , i )];
    free( tmp );
  }
}

/**
   Looks through the vector and checks if it is in sorted form. If the
   @reverse argument is true it will check for descending values,
   otherwise for ascending values.
*/

bool long_vector_is_sorted( const long_vector_type * vector , bool reverse) {
  bool sorted = true;
  int start_index, delta,stop_index;

  if (reverse) {
    start_index = vector->size - 1;
    stop_index = 0;
    delta = -1;
  } else {
    start_index = 0;
    stop_index = vector->size - 1;
    delta = 1;
  }
  {
    int index = start_index;

    while (true) {
      if (vector->data[index] > vector->data[index + delta]) {
        sorted = false;
        break;
      }
      index = index + delta;
      if (index == stop_index)
        break;
    }

    return sorted;
  }
}

/**
   This function can be used to implement lookup tables of various
   types. The input vector @limits is supposed to contain container
   limits, e.g.

       limits = [0 , 1 , 2 , 3 , 4]

   The @limits vector must be sorted. The function will then look up
   in which bin @value fits and return the bin index. If the test

         limit[i] <= value < limit[i+1]

   succeeds the function will return i. If value is less than
   limits[0] the function will return -1, if value is greater than
   max( limit ) the function will return -1 * limit->size.

   The parameter @guess can be used to speed up the process, a value
   of @guess < 0 is interpreted as "no guess". When all input has been
   validated the final search will be binary search.
*/



int long_vector_lookup_bin( const long_vector_type * limits , long value , int guess) {
  if (value < limits->data[0])
    return -1;

  if (value > limits->data[ limits->size - 1])
    return -1 * limits->size;

  if (guess >= limits->size)
    guess = -1;  /* No guess */

  return long_vector_lookup_bin__( limits , value , guess );
}



/*
  This is the fast path and assumes that @value is within the limits,
  and that guess < limits->size. See long_vector_lookup_bin() for
  further documentation.x
*/

int long_vector_lookup_bin__( const long_vector_type * limits , long value , int guess) {
  if (guess >= 0) {
    if ((limits->data[ guess ] <= value) && (limits->data[guess + 1] > value))
      return guess;  /* The guess was a hit. */
  }
  /* We did not have a guess - or it did not pay off. Start with a
     binary search. */
  {
    int index;
    int lower_index = 0;
    int upper_index = limits->size - 1;
    while (true) {
      if ((upper_index - lower_index) == 1) {
        /* We have found it. */
        index = lower_index;
        break;
      }

      {
        int central_index = (lower_index + upper_index) / 2;
        long central_value = limits->data[ central_index ];

        if (central_value > value)
          upper_index = central_index;
        else
          lower_index = central_index;
      }
    }
    return index;
  }
}

void long_vector_fprintf(const long_vector_type * vector , FILE * stream , const char * name , const char * fmt) {
  int i;
  if (name != NULL)
    fprintf(stream , "%s = [" , name);
  else
    fprintf(stream , "[");

  for (i = 0; i < vector->size; i++) {
    fprintf(stream , fmt , vector->data[i]);
    if (i < (vector->size - 1))
      fprintf(stream , ", ");
  }

  fprintf(stream , "]\n");
}


/*
  This function does not consider the default value; it does a
  vector_resize based on the input size.
*/
void long_vector_fread_data( long_vector_type * vector , int size, FILE * stream) {
  long_vector_realloc_data__( vector , size, vector->default_value );
  util_fread( vector->data , sizeof * vector->data , size , stream , __func__);
  vector->size = size;
}



void long_vector_fwrite_data( const long_vector_type * vector , FILE * stream ) {
  util_fwrite(  vector->data , sizeof * vector->data , vector->size , stream , __func__);
}



/**
   Writing:
   1. Size
   2. default value
   3. Values
*/

void long_vector_fwrite(const long_vector_type * vector , FILE * stream) {
  util_fwrite_int( vector->size , stream );
  util_fwrite( &vector->default_value , sizeof vector->default_value , 1 , stream , __func__);
  long_vector_fwrite_data( vector , stream );
}



/*
  Observe that this function will reset the default value.
*/
void long_vector_fread( long_vector_type * vector , FILE * stream ) {
  long     default_value;
  int size = util_fread_int( stream );
  util_fread( &default_value , sizeof default_value , 1 , stream , __func__);
  {
    long_vector_set_default( vector , default_value );
    long_vector_fread_data( vector , size , stream );
  }
}



long_vector_type * long_vector_fread_alloc( FILE * stream ) {
  long_vector_type * vector = long_vector_alloc( 0,0 );
  long_vector_fread( vector , stream );
  return vector;
}

bool long_vector_equal(const long_vector_type * vector1 , const long_vector_type * vector2) {
  if (vector1->size == vector2->size) {
    if (memcmp(vector1->data , vector2->data , sizeof * vector1->data * vector1->size) == 0)
      return true;
    else
      return false;
  } else
    return false;
}


int long_vector_first_equal(const long_vector_type * vector1, const long_vector_type * vector2, int offset) {
  if (offset >= vector1->size)
    return -2;

  if (offset >= vector2->size)
    return -2;

  int index = offset;
  while (vector1->data[index] != vector2->data[index]) {
    index++;

    if (index == vector1->size)
      return -1;

    if (index == vector2->size)
      return -1;
  }

  return index;
}



int long_vector_first_not_equal(const long_vector_type * vector1, const long_vector_type * vector2, int offset) {
  if (offset >= vector1->size)
    return -2;

  if (offset >= vector2->size)
    return -2;

  int index = offset;
  while (vector1->data[index] == vector2->data[index]) {
    index++;

    if (index == vector1->size)
      return -1;

    if (index == vector2->size)
      return -1;
  }

  return index;
}



void  long_vector_apply(long_vector_type * vector , long_ftype * func) {
  long_vector_assert_writable( vector );
  {
    int i;
    for (i=0; i < vector->size; i++)
      vector->data[i] = func( vector->data[i] );
  }
}

int long_vector_count_equal( const long_vector_type * vector , long cmp_value) {
  int count = 0;
  int i;
  for (i=0; i < vector->size; i++)
    if (vector->data[i] == cmp_value)
      count += 1;

  return count;

}

/*
  The upper limit is inclusive - if it is commensurable with the
  delta.
*/

void long_vector_range_fill(long_vector_type * vector , long limit1 , long delta , long limit2) {
  long current_value = limit1;

  if (delta == 0)
    util_abort("%s: sorry can not have delta == 0 \n",__func__);

  long_vector_reset( vector );
  while (true) {
    long_vector_append( vector , current_value );
    current_value += delta;
    if (delta > 0 && current_value > limit2)
      break;

    #if true
    if (delta < 0 && current_value < limit2)
      break;
    #endif
  }
}

#ifdef __cplusplus
}
#endif
