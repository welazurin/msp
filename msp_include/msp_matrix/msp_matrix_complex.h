//
// Created by programowanie on 19.12.2021.
//

#ifndef MSP_MATRIX_COMPLEX_H
#define MSP_MATRIX_COMPLEX_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../msp_vector/msp_vector.h"
#include "../msp_logger/msp_log.h"
#include "../msp_complex/msp_complex.h"
#include "../msp_vector/msp_vector_complex.h"
#define MSP_MATRIX_COMPLEX "msp_matrix_complex.h"

typedef struct msp_matrix_complex {
    msp_complex **data;
    size_t n;
    size_t m;
}msp_matrix_complex;

//ALLOCATING
msp_matrix_complex* msp_matrix_complex_allocate(size_t n, size_t m);
void msp_matrix_complex_free(msp_matrix_complex* mat);
//ACCESSING
msp_complex msp_matrix_complex_get(const msp_matrix_complex* mat, size_t i, size_t j);
void msp_matrix_complex_set(msp_matrix_complex* mat, size_t i, size_t j, msp_complex x);
msp_complex* msp_matrix_complex_get_ptr(msp_matrix_complex* mat, size_t i, size_t j);
//INIT
void msp_matrix_complex_set_all(msp_matrix_complex* mat, msp_complex x);
void msp_matrix_complex_set_ones(msp_matrix_complex* mat);
void msp_matrix_complex_set_zero(msp_matrix_complex* mat);
//READING WRITING
void msp_matrix_complex_fprintf(FILE* stream, char* format, const msp_matrix_complex* mat);
void msp_matrix_complex_fscanf(FILE* stream, msp_matrix_complex* mat);
void msp_matrix_complex_fprintf_with_size(FILE* stream, char* format, const msp_matrix_complex* mat);
void msp_matrix_complex_fscanf_with_size(FILE* stream, msp_matrix_complex* mat);
//COPY
void msp_matrix_complex_memcpy(msp_matrix_complex* dest, const msp_matrix_complex* src);
void msp_matrix_complex_swap(msp_matrix_complex* a, msp_matrix_complex* b);
//ROWS AND COLUMNS
void msp_matrix_complex_get_row(msp_matrix_complex * mat, msp_vector_complex * vec, size_t i);
void msp_matrix_complex_get_col(const msp_matrix_complex* mat, msp_vector_complex * vec, size_t i);
void msp_matrix_complex_set_row(msp_matrix_complex* mat, const msp_vector_complex * vec, size_t i);
void msp_matrix_complex_set_col(msp_matrix_complex* mat, const msp_vector_complex * vec, size_t i);

//EXCHANING
void msp_matrix_complex_swap_rows(msp_matrix_complex* mat, size_t i, size_t j);
void msp_matrix_complex_swap_columns(msp_matrix_complex* mat, size_t i , size_t j);
void msp_matrix_complex_transpose(msp_matrix_complex* dest, const msp_matrix_complex* src);

//OPERATIONS
void msp_matrix_complex_add(msp_matrix_complex* a, const msp_matrix_complex* b);
void msp_matrix_complex_sub(msp_matrix_complex* a, const msp_matrix_complex* b);
void msp_matrix_complex_mul_elements(msp_matrix_complex* a, const msp_matrix_complex* b);
msp_matrix_complex* msp_matrix_complex_mul(const msp_matrix_complex* a, const msp_matrix_complex* b);
void msp_matrix_complex_div_elements(msp_matrix_complex* a, const msp_matrix_complex* b);
void msp_matrix_complex_scale(msp_matrix_complex* a, const msp_complex x);
void msp_matrix_complex_scale_columns(msp_matrix_complex* a, const msp_vector_complex* b);
void msp_matrix_complex_scale_rows(msp_matrix_complex* a, const msp_vector_complex* b);
void msp_matrix_complex_add_constant(msp_matrix_complex* a, const msp_complex x);

//?
int msp_matrix_complex_isnull(const msp_matrix_complex* mat);

#endif //MSP_MATRIX_COMPLEX_H
