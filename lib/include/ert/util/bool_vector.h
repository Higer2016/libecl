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

#ifndef ERT_bool_VECTOR_H
#define ERT_bool_VECTOR_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdbool.h>

#include <ert/util/type_macros.h>
#include <ert/util/perm_vector.h>

typedef struct bool_vector_struct bool_vector_type;
typedef bool (bool_ftype) (bool);


  int                  bool_vector_lookup_bin( const bool_vector_type * limits , bool value , int guess);
  int                  bool_vector_lookup_bin__( const bool_vector_type * limits , bool value , int guess);
  void                 bool_vector_inplace_div( bool_vector_type * vector , const bool_vector_type * inv_factor);
  void                 bool_vector_inplace_mul( bool_vector_type * vector , const bool_vector_type * factor);
  void                 bool_vector_inplace_add( bool_vector_type * vector , const bool_vector_type * delta);
  void                 bool_vector_inplace_sub( bool_vector_type * vector , const bool_vector_type * delta);
  void                 bool_vector_set_read_only( bool_vector_type * vector , bool read_only);
  bool                 bool_vector_get_read_only( const bool_vector_type * vector );
  void                 bool_vector_memcpy_data( bool * target, const bool_vector_type * src );
  void                 bool_vector_memcpy_from_data( bool_vector_type * target , const bool * src , int src_size );
  void                 bool_vector_memcpy(  bool_vector_type * target , const bool_vector_type * src);
  void                 bool_vector_memcpy_data_block( bool_vector_type * target , const bool_vector_type * src , int target_offset , int src_offset , int len);
  bool                 bool_vector_growable( const bool_vector_type * vector);
  void                 bool_vector_select_unique(bool_vector_type * vector);
  bool_vector_type * bool_vector_alloc( int init_size , bool );
  bool_vector_type * bool_vector_alloc_private_wrapper(int init_size, bool default_value , bool * data , int alloc_size);
  bool_vector_type * bool_vector_alloc_shared_wrapper(int init_size, bool default_value , bool * data , int alloc_size);
  bool_vector_type * bool_vector_alloc_strided_copy( const bool_vector_type * src , int start , int stop , int stride );
  bool_vector_type * bool_vector_alloc_copy( const bool_vector_type * src);
  void                 bool_vector_imul(bool_vector_type * vector, int index, bool factor);
  void                 bool_vector_scale(bool_vector_type * vector, bool factor);
  void                 bool_vector_div(bool_vector_type * vector, bool divisor);
  bool               bool_vector_reverse_iget(const bool_vector_type * vector , int index);
  bool               bool_vector_iget(const bool_vector_type * , int);
  bool               bool_vector_safe_iget(const bool_vector_type * , int);
  bool               bool_vector_get_min(const bool_vector_type * vector);
  bool               bool_vector_get_max(const bool_vector_type * vector);
  int                  bool_vector_get_min_index(const bool_vector_type * vector, bool reverse);
  int                  bool_vector_get_max_index(const bool_vector_type * vector, bool reverse);
  bool               bool_vector_iadd( bool_vector_type * vector , int index , bool delta);
  void                 bool_vector_resize( bool_vector_type * vector , int new_size , bool default_value );
  void                 bool_vector_iset(bool_vector_type *       , int , bool);
  void                 bool_vector_iset_block(bool_vector_type * vector , int index , int block_size , bool value);
  void                 bool_vector_idel_block( bool_vector_type * vector , int index , int block_size);
  bool               bool_vector_idel( bool_vector_type * vector , int index);
  bool               bool_vector_del_value( bool_vector_type * vector , bool del_value);
  void                 bool_vector_insert( bool_vector_type * vector , int index , bool value);
  void                 bool_vector_append(bool_vector_type *     , bool);
  void                 bool_vector_free_container(bool_vector_type * vector);
  void                 bool_vector_free(bool_vector_type *);
  void                 bool_vector_free__(void *);
  void                 bool_vector_free_data(bool_vector_type *);
  void                 bool_vector_reset(bool_vector_type *);
  void                 bool_vector_reset__(void * __vector);
  int                  bool_vector_size(const bool_vector_type * );
  void                 bool_vector_lshift(bool_vector_type * vector , int shift);
  void                 bool_vector_rshift(bool_vector_type * vector , int shift);
  bool               bool_vector_pop(bool_vector_type * vector);
  bool               bool_vector_get_first(const bool_vector_type * vector);
  bool               bool_vector_get_last(const bool_vector_type * );
  bool *             bool_vector_get_ptr(const bool_vector_type * );
  bool *             bool_vector_alloc_data_copy( const bool_vector_type * vector );
  const bool *       bool_vector_get_const_ptr(const bool_vector_type * );
  bool bool_vector_init_linear(bool_vector_type * vector , bool start_value, bool end_value, int num_values);
  void                 bool_vector_init_range(bool_vector_type * vector , bool value1 , bool value2 , bool delta);
  void                 bool_vector_set_many(bool_vector_type *  , int  , const bool *  , int );
  void                 bool_vector_set_all(bool_vector_type * vector , bool value);
  void                 bool_vector_append_many(bool_vector_type * vector , const bool * data , int length);
  void                 bool_vector_append_vector(bool_vector_type * vector , const bool_vector_type * other);
  void                 bool_vector_shrink(bool_vector_type * );
  bool               bool_vector_sum(const bool_vector_type * );
  bool               bool_vector_get_default(const bool_vector_type * );
  void                 bool_vector_set_default(bool_vector_type * vector, bool default_value);
  void                 bool_vector_append_default(bool_vector_type * vector , bool default_value);
  void                 bool_vector_iset_default(bool_vector_type * vector , int index , bool default_value);
  bool                 bool_vector_is_sorted( const bool_vector_type * vector , bool reverse);
  bool                 bool_vector_contains(const bool_vector_type * vector , bool value);
  bool                 bool_vector_contains_sorted(const bool_vector_type * vector , bool value);
  int                  bool_vector_index(const bool_vector_type * vector , bool value);
  int                  bool_vector_index_sorted(const bool_vector_type * vector , bool value);
  void                 bool_vector_sort(bool_vector_type * vector);
  void                 bool_vector_rsort(bool_vector_type * vector);
  void                 bool_vector_permute(bool_vector_type * vector , const perm_vector_type * perm);
  perm_vector_type *   bool_vector_alloc_sort_perm(const bool_vector_type * vector);
  perm_vector_type *   bool_vector_alloc_rsort_perm(const bool_vector_type * vector);
  void                 bool_vector_fprintf(const bool_vector_type * vector , FILE * stream , const char * name , const char * fmt);
  void                 bool_vector_fwrite(const bool_vector_type * vector , FILE * stream);
  bool_vector_type * bool_vector_fread_alloc( FILE * stream );
  void                 bool_vector_fread( bool_vector_type * vector , FILE * stream );
  void                 bool_vector_fwrite_data( const bool_vector_type * vector , FILE * stream );
  void                 bool_vector_fread_data( bool_vector_type * vector , int size, FILE * stream);
  bool                 bool_vector_equal(const bool_vector_type * vector1 , const bool_vector_type * vector2);
  int                  bool_vector_first_equal(const bool_vector_type * vector1, const bool_vector_type * vector2, int offset);
  int                  bool_vector_first_not_equal(const bool_vector_type * vector1, const bool_vector_type * vector2, int offset);
  void                 bool_vector_apply(bool_vector_type * vector , bool_ftype *func);
  int                  bool_vector_count_equal( const bool_vector_type * vector , bool cmp_value);
  int                  bool_vector_element_size( const bool_vector_type * vector );
  void                 bool_vector_range_fill(bool_vector_type * vector , bool limit1 , bool delta , bool limit2);
  void                 bool_vector_shift(bool_vector_type * vector, bool delta);

  UTIL_SAFE_CAST_HEADER( bool_vector );
  UTIL_IS_INSTANCE_HEADER( bool_vector );

#ifdef __cplusplus
}
#endif
#endif
//




