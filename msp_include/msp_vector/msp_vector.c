//
// Created by programowanie on 06.12.2021.
//
#include "msp_vector.h"

msp_vector* msp_vector_allocate(size_t size) {
    msp_vector* vector;
    vector = malloc(sizeof(*vector));
    if(vector == NULL) {
        perror("Bad allocation od msp_vector");
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
void msp_vector_free(msp_vector* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    free(vector);
}
double msp_vector_get(const msp_vector* vec, const size_t i) {
    if(i > vec->size-1) {
        perror("ERROR IN ACCESSING IN msp_vector_get()");
        return 0;
    }
    else {
        return vec->data[i];
    }
}
void msp_vector_set(msp_vector* vec, const size_t i, double x) {
    if(i >= vec->size) {
        perror("Invalid argument: outOfRange");
    }
    else {
        vec->data[i] = x;
    }
}
double* msp_vector_get_ptr(const msp_vector* vec, const size_t i) {
    if(i >= vec->size) {
        perror("Invalid argument");
        return NULL;
    }
    else {
        return &(vec->data[i]);
    }
}
void msp_vector_set_tab(msp_vector* vec, double* data, size_t size) {
    if(vec == NULL) {
        return;
    }
    else {
        if(vec->size != size) {
            free(vec);
            vec = msp_vector_allocate(size);
        }
        for(int i = 0; i < size; i++) {
            vec->data[i] = data[i];
        }
    }
}
void msp_vector_set_xy(msp_vector* vec, double xmin, double max, size_t i) {
    if(vec->size != i) {
        msp_vector_free(vec);
        vec = msp_vector_allocate(i);
    }
    double separator = (max-xmin)/(double)i;
    for(int j = 0; j < i; j++) {
        vec->data[j] = xmin+separator*j;
    }
}
void msp_vector_set_xi(msp_vector* vec, double xmin, double sep, size_t i) {
    if(vec->size != i) {
        msp_vector_free(vec);
        vec = msp_vector_allocate(i);
    }
    for(int j = 0; j < i; j++) {
        vec->data[j] = xmin+sep*j;
    }
}

void msp_vector_set_all(msp_vector* vec, double x) {
    if(vec->size == 0) {
        return;
    }
    else {
        for(int i = 0; i < vec->size; i++) {
            vec->data[i] = x;
        }
    }
}
void msp_vector_set_zero(msp_vector* vec) {
    if(vec->size == 0) {
        return;
    }
    else {
        for(int i = 0; i < vec->size; i++) {
            vec->data[i] = 0;
        }
    }
}
void msp_vector_set_basis(msp_vector* vec, size_t i){
    if(vec->size == 0) {
        return;
    }
    else {
        for(int j = 0; j < vec->size; j++) {
            vec->data[j] = 0;
        }
        vec->data[i] = 1;
    }
}

//READING AND WRITING
void msp_vector_fscanf(FILE* stream, msp_vector* vec) {
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
                fscanf(stream, "%f", &(vec->data[i]));
            }
        }
    }
}
void msp_vector_fprintf(FILE* stream, const char* format, const msp_vector* vec) {
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
            fprintf(stream, format, vec->data[i]);
            fprintf(stream, " ");
        }
    }
}
void msp_vector_fprintf_with_size(FILE* stream, const char* format, const msp_vector* vec) {
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
        msp_vector_fprintf(stream, format, vec);
    }
}
void msp_vector_fscanf_with_size(FILE* stream, msp_vector* vec) {
    if(stream == NULL) {
        perror("Stream is null pointer");
        return;
    }
    else {
        int size;
        fscanf(stream, "%d", &size);
        if(vec == NULL) {
            vec = msp_vector_allocate(size);
            if(vec == NULL) {
                return;
            }
        }
        else {
            msp_vector_free(vec);
            vec = msp_vector_allocate(size);
            if(vec == NULL) {
                return;
            }
            msp_vector_fscanf(stream, vec);
        }
    }
}

//COPY
void msp_vector_memcpy(msp_vector* dest, msp_vector* src) {
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
void msp_vector_swap(msp_vector* v, msp_vector* q) {
    double* t = v->data;
    v->data = q->data;
    q->data = t;
    size_t size = v->size;
    v->size = q->size;
    q->size = size;
}
void msp_vector_swap_elements(msp_vector* vector, size_t i, size_t j) {
    if(i >= vector->size || j >= vector->size) {
        perror("invalid argument");
        return;
    }
    else {
        double t = vector->data[i];
        vector->data[i] = vector->data[j];
        vector->data[j] = t;
    }

}
void msp_vector_reverse(msp_vector* v) {
    if(v->size%2 == 0) {
        for(int i = 0; i < v->size/2; i++) {
            msp_vector_swap_elements(v, i, (v->size-1)-i);
        }
    }
    else {
        for(int i = 0; i < v->size/2; i++) {
            msp_vector_swap_elements(v, i, (v->size-1)-i);
        }
    }
}

//OPERATIONS
void msp_vector_add(msp_vector* vec, const msp_vector* b) {
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            vec->data[i] += b->data[i];
        }
    }
}
void msp_vector_sub(msp_vector* vec, const msp_vector* b){
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            vec->data[i] -= b->data[i];
        }
    }
}
void msp_vector_mul(msp_vector* vec, const msp_vector* b){
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            vec->data[i] *= b->data[i];
        }
    }
}
void msp_vector_div(msp_vector* vec, const msp_vector* b){
    if(vec->size != b->size) {
        perror("INVALID ARGUMENT");
        return;
    }
    else {
        for(int i = 0 ; i< vec->size; i ++) {
            if(b->data[i] == 0) {
                errno = EDOM;
                perror("In msp_vector_div() div by 0");

            }
            else {
                vec->data[i] /= b->data[i];
            }

        }
    }
}
void msp_vector_scale(msp_vector* vec, const double x) {
    for(int i = 0 ; i < vec->size; i++) {
        vec->data[i] *= x;
    }

}
void msp_vector_add_constant(msp_vector* vec, const double x) {
    for(int i = 0 ; i < vec->size; i++) {
        vec->data[i] += x;
    }

}
double msp_vector_sum(const msp_vector* vec) {
    double result = 0;
    for(int i = 0 ; i < vec->size; i++) {
        result += vec->data[i];
    }
    return result;
}

int msp_vector_isnull(const msp_vector* vec) {
    if(vec->size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
int msp_vector_ispositive(const msp_vector* vec) {
    for(int i = 0 ; i < vec->size; i++) {
        if(vec->data[i] <= 0) {
            return 0;
        }
    }
    return 1;
}
int msp_vector_isngeative(const msp_vector* vec) {
    for(int i = 0 ; i < vec->size; i++) {
        if(vec->data[i] >= 0) {
            return 0;
        }
    }
    return 1;
}
