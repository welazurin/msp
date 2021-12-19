//
// Created by programowanie on 19.12.2021.
//

#ifndef MSP_MSP_VECTOR_COMPLEX_H
#define MSP_MSP_VECTOR_COMPLEX_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct msp_vector_complex{
    double* data;
    size_t size;
}msp_vector_complex;

msp_vector* msp_vector_complex_allocate(size_t size);
void msp_vector_complex_free(msp_vector* vector);
//ACCESSING
double msp_vector_complex_get(const msp_vector* vec, const size_t i);
void msp_vector_complex_set(msp_vector* vec, const size_t i, double x);

double* msp_vector_complex_get_ptr(const msp_vector* vec, const size_t i);

void msp_vector_complex_set_all(msp_vector* vec, double x);
void msp_vector_complex_set_zero(msp_vector* vec);
void msp_vector_complex_set_basis(msp_vector* vec, size_t i);

//READING AND WRITING
void msp_vector_complex_fscanf(FILE* stream, msp_vector* vec);
void msp_vector_complex_fprintf(FILE* stream, const char* format, const msp_vector* vec);
void msp_vector_complex_fprintf_with_size(FILE* stream, const char* format, const msp_vector* vec);
void msp_vector_complex_fscanf_with_size(FILE* stream, msp_vector* vec);

//COPY
void msp_vector_complex_memcpy(msp_vector* dest, msp_vector* src);
void msp_vector_complex_swap(msp_vector* v, msp_vector* q);

void msp_vector_complex__swap_elements(msp_vector* vector, size_t i, size_t j);
void msp_vector_complex_reverse(msp_vector* v);

//OPERATIONS
void msp_vector_complex_add(msp_vector* vec, const msp_vector* b);
void msp_vector_complex_sub(msp_vector* vec, const msp_vector* b);
void msp_vector_complex_mul(msp_vector* vec, const msp_vector* b);
void msp_vector_complex_div(msp_vector* vec, const msp_vector* b);
void msp_vector_complex_scale(msp_vector* vec, const double x);
void msp_vector_complex_add_constant(msp_vector* vec, const double x);
double msp_vector_complex_sum(const msp_vector* vec);

int msp_vector_complex_isnull(const msp_vector* vec);
int msp_vector_complex_ispositive(const msp_vector* vec);
int msp_vector_complex_isngeative(const msp_vector* vec);


#endif //MSP_MSP_VECTOR_H



#endif //MSP_MSP_VECTOR_COMPLEX_H
