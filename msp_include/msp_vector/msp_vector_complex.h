//
// Created by programowanie on 19.12.2021.
//

#ifndef MSP_MSP_VECTOR_COMPLEX_H
#define MSP_MSP_VECTOR_COMPLEX_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../msp_complex/msp_complex.h"

typedef struct msp_vector_complex{
    msp_complex* data;
    size_t size;
}msp_vector_complex;

msp_vector_complex* msp_vector_complex_allocate(size_t size);
void msp_vector_complex_free(msp_vector_complex* vector);
//ACCESSING
msp_complex msp_vector_complex_get(const msp_vector_complex* vec, const size_t i);
void msp_vector_complex_set(msp_vector_complex* vec, const size_t i, msp_complex x);

msp_complex* msp_vector_complex_get_ptr(const msp_vector_complex* vec, const size_t i);
void msp_vector_complex_set_xy(msp_vector_complex* vec, msp_complex xmin, msp_complex max, size_t i);
void msp_vector_complex_set_xi(msp_vector_complex* vec, msp_complex xmin, msp_complex sep, size_t i);
void msp_vector_complex_set_all(msp_vector_complex* vec, msp_complex x);
void msp_vector_complex_set_zero(msp_vector_complex* vec);
void msp_vector_complex_set_basis(msp_vector_complex* vec, size_t i);

//READING AND WRITING
void msp_vector_complex_fscanf(FILE* stream, msp_vector_complex* vec);
void msp_vector_complex_fprintf(FILE* stream, char* format, const msp_vector_complex* vec);
void msp_vector_complex_fprintf_with_size(FILE* stream, char* format, const msp_vector_complex* vec);
void msp_vector_complex_fscanf_with_size(FILE* stream, msp_vector_complex* vec);

//COPY
void msp_vector_complex_memcpy(msp_vector_complex* dest, msp_vector_complex* src);
void msp_vector_complex_swap(msp_vector_complex* v, msp_vector_complex* q);

void msp_vector_complex_swap_elements(msp_vector_complex* vector, size_t i, size_t j);
void msp_vector_complex_reverse(msp_vector_complex* v);

//OPERATIONS
void msp_vector_complex_add(msp_vector_complex* vec, const msp_vector_complex* b);
void msp_vector_complex_sub(msp_vector_complex* vec, const msp_vector_complex* b);
void msp_vector_complex_mul(msp_vector_complex* vec, const msp_vector_complex* b);
void msp_vector_complex_div(msp_vector_complex* vec, const msp_vector_complex* b);
void msp_vector_complex_scale(msp_vector_complex* vec, const msp_complex x);
void msp_vector_complex_add_constant(msp_vector_complex* vec, const msp_complex x);
msp_complex msp_vector_complex_sum(const msp_vector_complex* vec);

int msp_vector_complex_isnull(const msp_vector_complex* vec);


#endif //MSP_MSP_VECTOR_COMPLEX_H
