//
// Created by programowanie on 06.12.2021.
//

#ifndef MSP_MSP_MATRIX_H
#define MSP_MSP_MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../msp_vector/msp_vector.h"
typedef struct msp_matrix {
    double **data;
    size_t n;
    size_t m;
}msp_matrix, msp_matrix_double;

//ALLOCATING
msp_matrix* msp_matrix_allocate(size_t n, size_t m);
void msp_matrix_free(msp_matrix* mat);
//ACCESSING
double msp_matrix_get(const msp_matrix* mat, size_t i, size_t j);
void msp_matrix_set(msp_matrix* mat, size_t i, size_t j, double x);
double* msp_matrix_get_ptr(msp_matrix* mat, size_t i, size_t j);
//INIT
void msp_matrix_set_all(msp_matrix* mat, double x);
void msp_matrix_set_ones(msp_matrix* mat);
void msp_matrix_set_zero(msp_matrix* mat);
//READING WRITING
void msp_matrix_fprintf(FILE* stream, const char* format, const msp_matrix* mat);
void msp_matrix_fscanf(FILE* stream, msp_matrix* mat);
void msp_matrix_fprintf_with_size(FILE* stream, const char* format, const msp_matrix* mat);
void msp_matrix_fscanf_with_size(FILE* stream, msp_matrix* mat);
//COPY
void msp_matrix_memcpy(msp_matrix* dest, const msp_matrix* src);
void msp_matrix_swap(msp_matrix* a, msp_matrix* b);
//ROWS AND COLUMNS
void msp_matrix_get_row(msp_matrix * mat, msp_vector* vec, size_t i);
void msp_matrix_get_col(const msp_matrix* mat, msp_vector* vec, size_t i);
void msp_matrix_set_row(msp_matrix* mat, const msp_vector* vec, size_t i);
void msp_matrix_set_col(msp_matrix* mat, const msp_vector* vec, size_t i);

//EXCHANING
void msp_matrix_swap_rows(msp_matrix* mat, size_t i, size_t j);
void msp_matrix_swap_columns(msp_matrix* mat, size_t i , size_t j);
void msp_matrix_transpose(msp_matrix* dest, const msp_matrix* src);

//OPERATIONS
void msp_matrix_add(msp_matrix* a, const msp_matrix* b);
void msp_matrix_sub(msp_matrix* a, const msp_matrix* b);
void msp_matrix_mul_elements(msp_matrix* a, const msp_matrix* b);
msp_matrix* msp_matrix_mul(const msp_matrix* a, const msp_matrix* b);
void msp_matrix_div_elements(msp_matrix* a, const msp_matrix* b);
void msp_matrix_scale(msp_matrix* a, const double x);
void msp_matrix_scale_columns(msp_matrix* a, const msp_vector* b);
void msp_matrix_scale_rows(msp_matrix* a, const msp_vector* b);
void msp_matrix_add_constant(msp_matrix* a, const double x);
double msp_matrix_det(const msp_matrix* a);

//?
int msp_matrix_isnull(const msp_matrix* mat);
int msp_matrix_ispos(const msp_matrix* mat);
int msp_matrix_isneg(const msp_matrix* mat);

double det ( int n, int w, const int * WK, double ** A );
#endif //MSP_MSP_MATRIX_H
