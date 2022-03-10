/*
   Copyright (C) 2011  Equinor ASA, Norway.

   The file 'vector_template.h' is part of ERT - Ensemble based Reservoir Tool.

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

#ifndef ERT_int_VECTOR_H
#define ERT_int_VECTOR_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdbool.h>

#include <ert/util/type_macros.h>
#include <ert/util/perm_vector.h>

typedef struct int_vector_struct int_vector_type;
typedef int (int_ftype) (int);


  int                  int_vector_lookup_bin( const int_vector_type * limits , int value , int guess);
  int                  int_vector_lookup_bin__( const int_vector_type * limits , int value , int guess);
  void                 int_vector_inplace_div( int_vector_type * vector , const int_vector_type * inv_factor);
  void                 int_vector_inplace_mul( int_vector_type * vector , const int_vector_type * factor);
  void                 int_vector_inplace_add( int_vector_type * vector , const int_vector_type * delta);
  void                 int_vector_inplace_sub( int_vector_type * vector , const int_vector_type * delta);
  void                 int_vector_set_read_only( int_vector_type * vector , bool read_only);
  bool                 int_vector_get_read_only( const int_vector_type * vector );
  void                 int_vector_memcpy_data( int * target, const int_vector_type * src );
  void                 int_vector_memcpy_from_data( int_vector_type * target , const int * src , int src_size );
  void                 int_vector_memcpy(  int_vector_type * target , const int_vector_type * src);
  void                 int_vector_memcpy_data_block( int_vector_type * target , const int_vector_type * src , int target_offset , int src_offset , int len);
  bool                 int_vector_growable( const int_vector_type * vector);
  void                 int_vector_select_unique(int_vector_type * vector);
  int_vector_type * int_vector_alloc( int init_size , int );
  int_vector_type * int_vector_alloc_private_wrapper(int init_size, int default_value , int * data , int alloc_size);
  int_vector_type * int_vector_alloc_shared_wrapper(int init_size, int default_value , int * data , int alloc_size);
  int_vector_type * int_vector_alloc_strided_copy( const int_vector_type * src , int start , int stop , int stride );
  int_vector_type * int_vector_alloc_copy( const int_vector_type * src);
  void                 int_vector_imul(int_vector_type * vector, int index, int factor);
  void                 int_vector_scale(int_vector_type * vector, int factor);
  void                 int_vector_div(int_vector_type * vector, int divisor);
  int               int_vector_reverse_iget(const int_vector_type * vector , int index);
  int               int_vector_iget(const int_vector_type * , int);
  int               int_vector_safe_iget(const int_vector_type * , int);
  int               int_vector_get_min(const int_vector_type * vector);
  int               int_vector_get_max(const int_vector_type * vector);
  int                  int_vector_get_min_index(const int_vector_type * vector, bool reverse);
  int                  int_vector_get_max_index(const int_vector_type * vector, bool reverse);
  int               int_vector_iadd( int_vector_type * vector , int index , int delta);
  void                 int_vector_resize( int_vector_type * vector , int new_size , int default_value );
  void                 int_vector_iset(int_vector_type *       , int , int);
  void                 int_vector_iset_block(int_vector_type * vector , int index , int block_size , int value);
  void                 int_vector_idel_block( int_vector_type * vector , int index , int block_size);
  int               int_vector_idel( int_vector_type * vector , int index);
  int               int_vector_del_value( int_vector_type * vector , int del_value);
  void                 int_vector_insert( int_vector_type * vector , int index , int value);
  void                 int_vector_append(int_vector_type *     , int);
  void                 int_vector_free_container(int_vector_type * vector);
  void                 int_vector_free(int_vector_type *);
  void                 int_vector_free__(void *);
  void                 int_vector_free_data(int_vector_type *);
  void                 int_vector_reset(int_vector_type *);
  void                 int_vector_reset__(void * __vector);
  int                  int_vector_size(const int_vector_type * );
  void                 int_vector_lshift(int_vector_type * vector , int shift);
  void                 int_vector_rshift(int_vector_type * vector , int shift);
  int               int_vector_pop(int_vector_type * vector);
  int               int_vector_get_first(const int_vector_type * vector);
  int               int_vector_get_last(const int_vector_type * );
  int *             int_vector_get_ptr(const int_vector_type * );
  int *             int_vector_alloc_data_copy( const int_vector_type * vector );
  const int *       int_vector_get_const_ptr(const int_vector_type * );
  bool int_vector_init_linear(int_vector_type * vector , int start_value, int end_value, int num_values);
  void                 int_vector_init_range(int_vector_type * vector , int value1 , int value2 , int delta);
  void                 int_vector_set_many(int_vector_type *  , int  , const int *  , int );
  void                 int_vector_set_all(int_vector_type * vector , int value);
  void                 int_vector_append_many(int_vector_type * vector , const int * data , int length);
  void                 int_vector_append_vector(int_vector_type * vector , const int_vector_type * other);
  void                 int_vector_shrink(int_vector_type * );
  int               int_vector_sum(const int_vector_type * );
  int               int_vector_get_default(const int_vector_type * );
  void                 int_vector_set_default(int_vector_type * vector, int default_value);
  void                 int_vector_append_default(int_vector_type * vector , int default_value);
  void                 int_vector_iset_default(int_vector_type * vector , int index , int default_value);
  bool                 int_vector_is_sorted( const int_vector_type * vector , bool reverse);
  bool                 int_vector_contains(const int_vector_type * vector , int value);
  bool                 int_vector_contains_sorted(const int_vector_type * vector , int value);
  int                  int_vector_index(const int_vector_type * vector , int value);
  int                  int_vector_index_sorted(const int_vector_type * vector , int value);
  void                 int_vector_sort(int_vector_type * vector);
  void                 int_vector_rsort(int_vector_type * vector);
  void                 int_vector_permute(int_vector_type * vector , const perm_vector_type * perm);
  perm_vector_type *   int_vector_alloc_sort_perm(const int_vector_type * vector);
  perm_vector_type *   int_vector_alloc_rsort_perm(const int_vector_type * vector);
  void                 int_vector_fprintf(const int_vector_type * vector , FILE * stream , const char * name , const char * fmt);
  void                 int_vector_fwrite(const int_vector_type * vector , FILE * stream);
  int_vector_type * int_vector_fread_alloc( FILE * stream );
  void                 int_vector_fread( int_vector_type * vector , FILE * stream );
  void                 int_vector_fwrite_data( const int_vector_type * vector , FILE * stream );
  void                 int_vector_fread_data( int_vector_type * vector , int size, FILE * stream);
  bool                 int_vector_equal(const int_vector_type * vector1 , const int_vector_type * vector2);
  int                  int_vector_first_equal(const int_vector_type * vector1, const int_vector_type * vector2, int offset);
  int                  int_vector_first_not_equal(const int_vector_type * vector1, const int_vector_type * vector2, int offset);
  void                 int_vector_apply(int_vector_type * vector , int_ftype *func);
  int                  int_vector_count_equal( const int_vector_type * vector , int cmp_value);
  int                  int_vector_element_size( const int_vector_type * vector );
  void                 int_vector_range_fill(int_vector_type * vector , int limit1 , int delta , int limit2);
  void                 int_vector_shift(int_vector_type * vector, int delta);

  UTIL_SAFE_CAST_HEADER( int_vector );
  UTIL_IS_INSTANCE_HEADER( int_vector );

#ifdef __cplusplus
}
#endif
#endif
//




