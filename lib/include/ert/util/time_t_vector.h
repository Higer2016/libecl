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

#ifndef ERT_time_t_VECTOR_H
#define ERT_time_t_VECTOR_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdbool.h>

#include <ert/util/type_macros.h>
#include <ert/util/perm_vector.h>

typedef struct time_t_vector_struct time_t_vector_type;
typedef time_t (time_t_ftype) (time_t);


  int                  time_t_vector_lookup_bin( const time_t_vector_type * limits , time_t value , int guess);
  int                  time_t_vector_lookup_bin__( const time_t_vector_type * limits , time_t value , int guess);
  void                 time_t_vector_inplace_div( time_t_vector_type * vector , const time_t_vector_type * inv_factor);
  void                 time_t_vector_inplace_mul( time_t_vector_type * vector , const time_t_vector_type * factor);
  void                 time_t_vector_inplace_add( time_t_vector_type * vector , const time_t_vector_type * delta);
  void                 time_t_vector_inplace_sub( time_t_vector_type * vector , const time_t_vector_type * delta);
  void                 time_t_vector_set_read_only( time_t_vector_type * vector , bool read_only);
  bool                 time_t_vector_get_read_only( const time_t_vector_type * vector );
  void                 time_t_vector_memcpy_data( time_t * target, const time_t_vector_type * src );
  void                 time_t_vector_memcpy_from_data( time_t_vector_type * target , const time_t * src , int src_size );
  void                 time_t_vector_memcpy(  time_t_vector_type * target , const time_t_vector_type * src);
  void                 time_t_vector_memcpy_data_block( time_t_vector_type * target , const time_t_vector_type * src , int target_offset , int src_offset , int len);
  bool                 time_t_vector_growable( const time_t_vector_type * vector);
  void                 time_t_vector_select_unique(time_t_vector_type * vector);
  time_t_vector_type * time_t_vector_alloc( int init_size , time_t );
  time_t_vector_type * time_t_vector_alloc_private_wrapper(int init_size, time_t default_value , time_t * data , int alloc_size);
  time_t_vector_type * time_t_vector_alloc_shared_wrapper(int init_size, time_t default_value , time_t * data , int alloc_size);
  time_t_vector_type * time_t_vector_alloc_strided_copy( const time_t_vector_type * src , int start , int stop , int stride );
  time_t_vector_type * time_t_vector_alloc_copy( const time_t_vector_type * src);
  void                 time_t_vector_imul(time_t_vector_type * vector, int index, time_t factor);
  void                 time_t_vector_scale(time_t_vector_type * vector, time_t factor);
  void                 time_t_vector_div(time_t_vector_type * vector, time_t divisor);
  time_t               time_t_vector_reverse_iget(const time_t_vector_type * vector , int index);
  time_t               time_t_vector_iget(const time_t_vector_type * , int);
  time_t               time_t_vector_safe_iget(const time_t_vector_type * , int);
  time_t               time_t_vector_get_min(const time_t_vector_type * vector);
  time_t               time_t_vector_get_max(const time_t_vector_type * vector);
  int                  time_t_vector_get_min_index(const time_t_vector_type * vector, bool reverse);
  int                  time_t_vector_get_max_index(const time_t_vector_type * vector, bool reverse);
  time_t               time_t_vector_iadd( time_t_vector_type * vector , int index , time_t delta);
  void                 time_t_vector_resize( time_t_vector_type * vector , int new_size , time_t default_value );
  void                 time_t_vector_iset(time_t_vector_type *       , int , time_t);
  void                 time_t_vector_iset_block(time_t_vector_type * vector , int index , int block_size , time_t value);
  void                 time_t_vector_idel_block( time_t_vector_type * vector , int index , int block_size);
  time_t               time_t_vector_idel( time_t_vector_type * vector , int index);
  time_t               time_t_vector_del_value( time_t_vector_type * vector , time_t del_value);
  void                 time_t_vector_insert( time_t_vector_type * vector , int index , time_t value);
  void                 time_t_vector_append(time_t_vector_type *     , time_t);
  void                 time_t_vector_free_container(time_t_vector_type * vector);
  void                 time_t_vector_free(time_t_vector_type *);
  void                 time_t_vector_free__(void *);
  void                 time_t_vector_free_data(time_t_vector_type *);
  void                 time_t_vector_reset(time_t_vector_type *);
  void                 time_t_vector_reset__(void * __vector);
  int                  time_t_vector_size(const time_t_vector_type * );
  void                 time_t_vector_lshift(time_t_vector_type * vector , int shift);
  void                 time_t_vector_rshift(time_t_vector_type * vector , int shift);
  time_t               time_t_vector_pop(time_t_vector_type * vector);
  time_t               time_t_vector_get_first(const time_t_vector_type * vector);
  time_t               time_t_vector_get_last(const time_t_vector_type * );
  time_t *             time_t_vector_get_ptr(const time_t_vector_type * );
  time_t *             time_t_vector_alloc_data_copy( const time_t_vector_type * vector );
  const time_t *       time_t_vector_get_const_ptr(const time_t_vector_type * );
  bool time_t_vector_init_linear(time_t_vector_type * vector , time_t start_value, time_t end_value, int num_values);
  void                 time_t_vector_init_range(time_t_vector_type * vector , time_t value1 , time_t value2 , time_t delta);
  void                 time_t_vector_set_many(time_t_vector_type *  , int  , const time_t *  , int );
  void                 time_t_vector_set_all(time_t_vector_type * vector , time_t value);
  void                 time_t_vector_append_many(time_t_vector_type * vector , const time_t * data , int length);
  void                 time_t_vector_append_vector(time_t_vector_type * vector , const time_t_vector_type * other);
  void                 time_t_vector_shrink(time_t_vector_type * );
  time_t               time_t_vector_sum(const time_t_vector_type * );
  time_t               time_t_vector_get_default(const time_t_vector_type * );
  void                 time_t_vector_set_default(time_t_vector_type * vector, time_t default_value);
  void                 time_t_vector_append_default(time_t_vector_type * vector , time_t default_value);
  void                 time_t_vector_iset_default(time_t_vector_type * vector , int index , time_t default_value);
  bool                 time_t_vector_is_sorted( const time_t_vector_type * vector , bool reverse);
  bool                 time_t_vector_contains(const time_t_vector_type * vector , time_t value);
  bool                 time_t_vector_contains_sorted(const time_t_vector_type * vector , time_t value);
  int                  time_t_vector_index(const time_t_vector_type * vector , time_t value);
  int                  time_t_vector_index_sorted(const time_t_vector_type * vector , time_t value);
  void                 time_t_vector_sort(time_t_vector_type * vector);
  void                 time_t_vector_rsort(time_t_vector_type * vector);
  void                 time_t_vector_permute(time_t_vector_type * vector , const perm_vector_type * perm);
  perm_vector_type *   time_t_vector_alloc_sort_perm(const time_t_vector_type * vector);
  perm_vector_type *   time_t_vector_alloc_rsort_perm(const time_t_vector_type * vector);
  void                 time_t_vector_fprintf(const time_t_vector_type * vector , FILE * stream , const char * name , const char * fmt);
  void                 time_t_vector_fwrite(const time_t_vector_type * vector , FILE * stream);
  time_t_vector_type * time_t_vector_fread_alloc( FILE * stream );
  void                 time_t_vector_fread( time_t_vector_type * vector , FILE * stream );
  void                 time_t_vector_fwrite_data( const time_t_vector_type * vector , FILE * stream );
  void                 time_t_vector_fread_data( time_t_vector_type * vector , int size, FILE * stream);
  bool                 time_t_vector_equal(const time_t_vector_type * vector1 , const time_t_vector_type * vector2);
  int                  time_t_vector_first_equal(const time_t_vector_type * vector1, const time_t_vector_type * vector2, int offset);
  int                  time_t_vector_first_not_equal(const time_t_vector_type * vector1, const time_t_vector_type * vector2, int offset);
  void                 time_t_vector_apply(time_t_vector_type * vector , time_t_ftype *func);
  int                  time_t_vector_count_equal( const time_t_vector_type * vector , time_t cmp_value);
  int                  time_t_vector_element_size( const time_t_vector_type * vector );
  void                 time_t_vector_range_fill(time_t_vector_type * vector , time_t limit1 , time_t delta , time_t limit2);
  void                 time_t_vector_shift(time_t_vector_type * vector, time_t delta);

  UTIL_SAFE_CAST_HEADER( time_t_vector );
  UTIL_IS_INSTANCE_HEADER( time_t_vector );

#ifdef __cplusplus
}
#endif
#endif
//




