//
// Created by programowanie on 06.12.2021.
//

#ifndef MSP_MSP_VECTOR_H
#define MSP_MSP_VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
typedef struct msp_vector{
    double* data;
    size_t size;
}msp_vector, msp_vector_double;

msp_vector* msp_vector_allocate(size_t size);
void msp_vector_free(msp_vector* vector);
//ACCESSING
double msp_vector_get(const msp_vector* vec, const size_t i);
void msp_vector_set(msp_vector* vec, const size_t i, double x);

double* msp_vector_get_ptr(const msp_vector* vec, const size_t i);
void msp_vector_set_tab(msp_vector* vec, double* data, size_t size);
void msp_vector_set_xy(msp_vector* vec, double xmin, double max, size_t i);
void msp_vector_set_xi(msp_vector* vec, double xmin, double sep, size_t i);
void msp_vector_set_all(msp_vector* vec, double x);
void msp_vector_set_zero(msp_vector* vec);
void msp_vector_set_basis(msp_vector* vec, size_t i);

//READING AND WRITING
void msp_vector_fscanf(FILE* stream, msp_vector* vec);
void msp_vector_fprintf(FILE* stream, const char* format, const msp_vector* vec);
void msp_vector_fprintf_with_size(FILE* stream, const char* format, const msp_vector* vec);
void msp_vector_fscanf_with_size(FILE* stream, msp_vector* vec);

//COPY
void msp_vector_memcpy(msp_vector* dest, msp_vector* src);
void msp_vector_swap(msp_vector* v, msp_vector* q);

void msp_vector_swap_elements(msp_vector* vector, size_t i, size_t j);
void msp_vector_reverse(msp_vector* v);

//OPERATIONS
void msp_vector_add(msp_vector* vec, const msp_vector* b);
void msp_vector_sub(msp_vector* vec, const msp_vector* b);
void msp_vector_mul(msp_vector* vec, const msp_vector* b);
void msp_vector_div(msp_vector* vec, const msp_vector* b);
void msp_vector_scale(msp_vector* vec, const double x);
void msp_vector_add_constant(msp_vector* vec, const double x);
double msp_vector_sum(const msp_vector* vec);

int msp_vector_isnull(const msp_vector* vec);
int msp_vector_ispositive(const msp_vector* vec);
int msp_vector_isngeative(const msp_vector* vec);


#endif //MSP_MSP_VECTOR_H
