//
// Created by programowanie on 19.12.2021.
//
#include "msp_vector_complex.h"

msp_vector_complex* msp_vector_complex_allocate(size_t size) {
    msp_vector_complex* vector;
    vector = malloc(sizeof(*vector));
    if(vector == NULL) {
        perror("Bad allocation od msp_vector_complex");
        return NULL;
    }
    vector->size = size;
    vector->data = malloc(sizeof(*vector->data) * size);
    if(vector->data == NULL) {
        perror("Bad allocation od msp_vector->data");
        return NULL;
    }
    return vector;
}
void msp_vector_complex_free(msp_vector_complex* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    free(vector);
}
//ACCESSING
msp_complex msp_vector_complex_get(const msp_vector_complex* vec, const size_t i) {
    if(i > vec->size-1) {
        perror("ERROR IN ACCESSING IN msp_vector_get()");
        return msp_complex_create(0, 0);
    }
    else {
        return vec->data[i];
    }
}
void msp_vector_complex_set(msp_vector_complex* vec, const size_t i, msp_complex x) {
    if(i >= vec->size) {
        perror("Invalid argument: outOfRange");
    }
    else {
        vec->data[i] = x;
    }
}

msp_complex* msp_vector_complex_get_ptr(const msp_vector_complex* vec, const size_t i) {
    if(i >= vec->size) {
        perror("Invalid argument");
        return NULL;
    }
    else {
        return &(vec->data[i]);
    }
}
void msp_vector_complex_set_xy(msp_vector_complex* vec, msp_complex xmin, msp_complex max, size_t i) {
    if(vec->size != i) {
        msp_vector_complex_free(vec);
        vec = msp_vector_complex_allocate(i);
    }
    msp_complex separator = msp_complex_sub(max,xmin);
    separator = msp_complex_div(separator, msp_complex_create(i,0));
    for(int j = 0; j < i; j++) {
        vec->data[j] = msp_complex_sub(xmin,msp_complex_mul(separator, msp_complex_create(j,0)));
    }
}
void msp_vector_complex_set_xi(msp_vector_complex* vec, msp_complex xmin, msp_complex sep, size_t i) {
    if(vec->size != i) {
        msp_vector_complex_free(vec);
        vec = msp_vector_complex_allocate(i);
    }
    for(int j = 0; j < i; j++) {
        vec->data[j] = msp_complex_sub(xmin,msp_complex_mul(sep, msp_complex_create(j,0)));
    }
}
void msp_vector_complex_set_all(msp_vector_complex* vec, msp_complex x) {
    if(vec->size == 0) {
        return;
    }
    else {
        for(int i = 0; i < vec->size; i++) {
            vec->data[i] = x;
        }
    }
}
void msp_vector_complex_set_zero(msp_vector_complex* vec) {
    if(vec->size == 0) {
        return;
    }
    else {
        for(int i = 0; i < vec->size; i++) {
            vec->data[i] = msp_complex_create(0,0);
        }
    }
}
void msp_vector_complex_set_basis(msp_vector_complex* vec, size_t i) {
    if(vec->size == 0) {
        return;
    }
    else {
        for(int j = 0; j < vec->size; j++) {
            vec->data[j] = msp_complex_create(0,0);
        }
        vec->data[i] = msp_complex_create(1,0);
    }
}

//READING AND WRITING
void msp_vector_complex_fscanf(FILE* stream, msp_vector_complex* vec) {
    if(stream == NULL) {
        perror("stream is NULL pointer");
        return;
    }
    else {
        if(vec == NULL) {
            perror("vec is null pointer\n");
            return;
        }
        else {
            for(int i = 0; i < vec->size; i++) {
                fscanf(stream, "%f %f", &(vec->data[i].real), &(vec->data[i].imag));
            }
        }
    }
}
void msp_vector_complex_fprintf(FILE* stream, char* format, const msp_vector_complex* vec) {
    if(stream == NULL) {
        perror("Stream is null-pointer\n");
        return;
    }
    else if(vec == NULL) {
        perror("Vec is null-pointer\n");
        return;
    }
    else {
        for(int i = 0; i < vec->size; i++) {
            fprintf(stream, "%f %fi", vec->data[i].real, vec->data[i].imag);
            fprintf(stream, " ");
        }
    }
}
void msp_vector_complex_fprintf_with_size(FILE* stream, char* format, const msp_vector_complex* vec) {
    if(stream == NULL) {
        perror("Stream is null-pointer\n");
        return;
    }
    else if(vec == NULL) {
        perror("Vec is null-pointer\n");
        return;
    }
    else {
        fprintf(stream, "%d\n", vec->size);
        msp_vector_complex_fprintf(stream, format, vec);
    }
}
void msp_vector_complex_fscanf_with_size(FILE* stream, msp_vector_complex* vec) {
    if(stream == NULL) {
        perror("Stream is null pointer");
        return;
    }
    else {
        int size;
        fscanf(stream, "%d", &size);
        if(vec == NULL) {
            vec = msp_vector_complex_allocate(size);
            if(vec == NULL) {
                return;
            }
        }
        else {
            msp_vector_complex_free(vec);
            vec = msp_vector_complex_allocate(size);
            if(vec == NULL) {
                return;
            }
            msp_vector_complex_fscanf(stream, vec);
        }
    }
}

//COPY
void msp_vector_complex_memcpy(msp_vector_complex* dest, msp_vector_complex* src) {
    if(dest->size != src->size) {
        perror("invalid argument");
        return;
    }
    else {
        for(int i = 0 ; i < dest->size; i++) {
            dest[i] = src[i];
        }
    }
}
void msp_vector_complex_swap(msp_vector_complex* v, msp_vector_complex* q) {
    msp_complex* t = v->data;
    v->data = q->data;
    q->data = t;
    size_t size = v->size;
    v->size = q->size;
    q->size = size;
}

void msp_vector_complex_swap_elements(msp_vector_complex* vector, size_t i, size_t j) {
    if(i >= vector->size || j >= vector->size) {
        perror("invalid argument");
        return;
    }
    else {
        msp_complex t = vector->data[i];
        vector->data[i] = vector->data[j];
        vector->data[j] = t;
    }
}
void msp_vector_complex_reverse(msp_vector_complex* v) {
    if(v->size%2 == 0) {
        for(int i = 0; i < v->size/2; i++) {
            msp_vector_complex_swap_elements(v, i, (v->size-1)-i);
        }
    }
    else {
        for(int i = 0; i < v->size/2; i++) {
            msp_vector_complex_swap_elements(v, i, (v->size-1)-i);
        }
    }
}

//OPERATIONS
void msp_vector_complex_add(msp_vector_complex* vec, const msp_vector_complex* b) {
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            vec->data[i] = msp_complex_add(vec->data[i], b->data[i]);
        }
    }
}
void msp_vector_complex_sub(msp_vector_complex* vec, const msp_vector_complex* b) {
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            vec->data[i] = msp_complex_sub(vec->data[i], b->data[i]);
        }
    }
}
void msp_vector_complex_mul(msp_vector_complex* vec, const msp_vector_complex* b) {
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            vec->data[i] = msp_complex_mul(vec->data[i], b->data[i]);
        }
    }
}
void msp_vector_complex_div(msp_vector_complex* vec, const msp_vector_complex* b) {
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            if(msp_complex_iszero(b->data[i])) {
                errno = EDOM;
                perror("In msp_vector_div() div by 0");

            }
            else {
                vec->data[i] = msp_complex_div(vec->data[i], b->data[i]);
            }

        }
    }
}
void msp_vector_complex_scale(msp_vector_complex* vec, const msp_complex x) {
    for(int i = 0 ; i < vec->size; i++) {
        vec->data[i] = msp_complex_mul(vec->data[i], x);
    }
}
void msp_vector_complex_add_constant(msp_vector_complex* vec, const msp_complex x) {
    for(int i = 0 ; i < vec->size; i++) {
        vec->data[i] = msp_complex_add(vec->data[i], x);
    }
}
msp_complex msp_vector_complex_sum(const msp_vector_complex* vec) {
    msp_complex result = msp_complex_create(0,0);
    for(int i = 0 ; i < vec->size; i++) {
        result = msp_complex_add(result, vec->data[i]);
    }
    return result;
}

int msp_vector_complex_isnull(const msp_vector_complex* vec) {
    if(vec->size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
