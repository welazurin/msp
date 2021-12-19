//
// Created by programowanie on 19.12.2021.
//

#include "msp_matrix_complex.h"

//ALLOCATING
msp_matrix_complex* msp_matrix_complex_allocate(size_t n, size_t m) {
    //DECLARING NEW MATRIX
    msp_matrix_complex * mat;
    //ALLOCATING
    mat = malloc(sizeof(*mat));
    if(mat == NULL) {
        perror("Bad allocation memory in msp_matrix_allocate\n");
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_allocate", "ERROR in allocating memory for matrix");
        return NULL;
    }
    else {
        mat->data = malloc(sizeof(*(mat->data))*n);
        if(mat->data == NULL) {
            perror("Bad allocation memory in msp_matrix_allocate\n");
            msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_allocate", "ERROR in allocating memory for matrix->data");

            free(mat->data);
            return NULL;
        }
        for(unsigned i = 0 ; i < n; i++) {
            mat->data[i] = malloc(sizeof (*(mat->data[i]))*m);
            if(mat->data[i] == NULL) {
                for(unsigned j = i; j > -1; j--) {
                    free(mat->data[j]);
                }
                free(mat->data);
                perror("Bad allocation memory\n");
                msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_allocate", "ERROR in allocating memory for matrix->data[i]");
                return NULL;
            }
        }
        //END OF ALLOCATING
        mat->n = n;
        mat->m = m;
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_allocate", "Success allocating matrix");
        return mat;
    }
}
void msp_matrix_complex_free(msp_matrix_complex* mat) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_free", "Matrix is null-pointer");
        return;
    }
    else {
        for(int i = 0; i < mat->n; i++) {
            free(mat->data[i]);
        }
        free(mat->data);
        mat = NULL;
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_free", "Success free matrix");
    }
}
//ACCESSING
msp_complex msp_matrix_complex_get(const msp_matrix_complex* mat, size_t i, size_t j) {
    if(i > mat->n-1 || j >  mat->m-1) {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_get", "ERROR out of range i > mat->n-1 or j > mat->m-1 i - %d,mat->n-1, j-%d, mat->m-1", i, mat->n-1, j, mat->m-1);
        perror("Error in access to un allocating memory : OUT OF RANGE\n");
        abort();
    }
    else {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_get", "Success returned value %f", mat->data[i][j]);
        return mat->data[i][j];
    }
}
void msp_matrix_complex_set(msp_matrix_complex* mat, size_t i, size_t j, msp_complex x) {
    if(i > mat->n-1 || j >  mat->m-1) {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_set", "ERROR out of range i > mat->n-1 or j > mat->m-1 i - %d,mat->n-1, j-%d, mat->m-1", i, mat->n-1, j, mat->m-1);
        perror("Error in access to un allocating memory : OUT OF RANGE\n");
        return;
    }
    else {
        mat->data[i][j] = x;
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_set", "Success seting value %f", mat->data[i][j]);
    }
}
msp_complex* msp_matrix_complex_get_ptr(msp_matrix_complex* mat, size_t i, size_t j) {
    if(i > mat->n-1 || j >  mat->m-1) {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_get_ptr", "ERROR out of range i > mat->n-1 or j > mat->m-1 i - %d,mat->n-1, j-%d, mat->m-1", i, mat->n-1, j, mat->m-1);
        perror("Error in access to un allocating memory : OUT OF RANGE\n");
        abort();
    }
    else {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_get_ptr", "Success getting pointer %p", &(mat->data[i][j]));
        return &(mat->data[i][j]);
    }
}
//INIT
void msp_matrix_complex_set_all(msp_matrix_complex* mat, msp_complex x) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_set_all", "ERROR matrix is null-pointer");
        perror("mat is Null-pointer\n");
        abort();
    }
    else {
        if(mat->n == 0 || mat->m == 0) {
            perror("mat is empty\n");
        }
        else {
            for(int i = 0; i < mat->n; i++) {
                for(int j = 0; j < mat->m; j++) {
                    mat->data[i][j] = x;
                }
            }
        }
    }
}
void msp_matrix_complex_set_ones(msp_matrix_complex* mat) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_set_ones", "ERROR matrix is null-pointer");
        perror("mat is Null-pointer\n");
        abort();
    }
    else {
        if(mat->n == 0 || mat->m == 0) {
            perror("mat is empty\n");
        }
        else {
            msp_matrix_complex_set_zero(mat);
            if(mat->n > mat->m) {
                for(int i = 0; i < mat->m; i++) {
                    mat->data[i][i] = msp_complex_create(1, 0);
                }
            }
            else {
                for(int i = 0; i < mat->n; i++) {
                    mat->data[i][i] = msp_complex_create(1, 0);
                }
            }

        }
    }
}
void msp_matrix_complex_set_zero(msp_matrix_complex* mat) {
    msp_matrix_complex_set_all(mat, msp_complex_create(0,0));
}
//READING WRITING
void msp_matrix_complex_fprintf(FILE* stream, char* format, const msp_matrix_complex* mat) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX_COMPLEX, "msp_matrix_fprintf", "ERROR matrix is null-pointer");
        perror("matrix is null pointer");
        return;
    }
    char* format_complex = strcat(format, " " );
    format_complex = strcat(format_complex, format);
    format_complex = strcat(format_complex, "i");
    for(int i = 0; i < mat->n; i++) {
        for(int j = 0; j < mat->m; j++) {
            fprintf(stream, format_complex, mat->data[i][j].real, mat->data[i][j].imag);
            fprintf(stream, ", ");
        }
        fprintf(stream, "\n");
    }
}
void msp_matrix_complex_fscanf(FILE* stream, msp_matrix_complex* mat) {
    for(int i = 0; i < mat->n; i++) {
        for(int j = 0; j < mat->m; j++) {
            fscanf(stream, "%f %f", &(mat->data[i][j].real), &(mat->data[i][j].imag));
        }
    }
}
void msp_matrix_complex_fprintf_with_size(FILE* stream, char* format, const msp_matrix_complex* mat) {
    fprintf(stream, "%d, %d\n", mat->n, mat->m);
    msp_matrix_complex_fprintf(stream, format, mat);
}
void msp_matrix_complex_fscanf_with_size(FILE* stream, msp_matrix_complex* mat) {
    size_t n,m;

    fscanf(stream, "%d, %d", &n, &m);
    if(mat==NULL) {
        mat = msp_matrix_complex_allocate(n,m);
    }
    else {
        if(n != mat->n || m != mat->m) {
            msp_matrix_complex* temp;
            temp = msp_matrix_complex_allocate(n, m);
            msp_matrix_complex_free(mat);
            mat = temp;
        }
    }
    msp_matrix_complex_fscanf(stream, mat);
}
//COPY
void msp_matrix_complex_memcpy(msp_matrix_complex* dest, const msp_matrix_complex* src) {
    free(dest);
    dest = msp_matrix_complex_allocate(src->n, src->m);
    dest->n = src->n;
    dest->m = src->m;
    for(int i = 0; i < dest->n; i++) {
        for(int j = 0; j < dest->m; j++) {
            dest->data[i][j] = src->data[i][j];
        }
    }
}
void msp_matrix_complex_swap(msp_matrix_complex* a, msp_matrix_complex* b) {
    size_t n, m;
    msp_complex** data;
    data = a->data;
    b->data = a->data;
    a->data = data;
    n = a->n;
    m = a->m;
    b->n = a->n;
    b->m = a->m;
    a->n = n;
    a->m = m;
}
//ROWS AND COLUMNS
void msp_matrix_complex_get_row(msp_matrix_complex * mat, msp_vector_complex * vec, size_t i){
    if(mat == NULL) {
        perror("msp_matrix is Null-pointer\n");
        abort();
    }
    if(vec == NULL) {
        msp_vector_allocate(mat->m);
    }
    else {
        if(vec->size != mat->m) {
            free(vec);
            vec = msp_vector_complex_allocate(mat->m);
            if(vec == NULL) {
                abort();
            }
        }
    }
    for(int j = 0; i < mat->m; i++) {
        vec->data[i] = mat->data[i][j];
    }
}
void msp_matrix_complex_get_col(const msp_matrix_complex* mat, msp_vector_complex * vec, size_t i) {
    if(mat == NULL) {
        perror("msp_matrix is Null-pointer\n");
        abort();
    }
    if(vec == NULL) {
        msp_vector_allocate(mat->n);
    }
    else {
        if(vec->size != mat->n) {
            free(vec);
            vec = msp_vector_complex_allocate(mat->n);
            if(vec == NULL) {
                abort();
            }
        }
    }
    for(int j = 0; i < mat->n; i++) {
        vec->data[i] = mat->data[j][i];
    }
}
void msp_matrix_complex_set_row(msp_matrix_complex* mat, const msp_vector_complex * vec, size_t i) {
    if(mat == NULL) {
        perror("mat is empty\n");
        abort();
    }
    else if( vec == NULL) {
        perror("vec is empty\n");
        abort();
    }
    else {
        if(vec->size == mat->m) {
            for(int j = 0; j < vec->size; j++) {
                mat->data[i][j] = vec->data[j];
            }
        }
        else {
            perror("mat and msp_vector is not the same lenght");
        }
    }
}
void msp_matrix_complex_set_col(msp_matrix_complex* mat, const msp_vector_complex * vec, size_t i) {
    if(mat == NULL) {
        perror("mat is empty\n");
        abort();
    }
    else if( vec == NULL) {
        perror("vec is empty\n");
        abort();
    }
    else {
        if(vec->size == mat->n) {
            for(int j = 0; j < vec->size; j++) {
                mat->data[j][i] = vec->data[j];
            }
        }
        else {
            perror("mat and msp_vector is not the same lenght");
        }
    }
}

//EXCHANING
void msp_matrix_complex_swap_rows(msp_matrix_complex* mat, size_t i, size_t j) {
        if(mat == NULL) {
            perror("Matrix is null pointer\n");
            return;
        }
        else {
            if(mat->n == 0 || mat->m == 0) {
                perror("Matrix is empty");
                return;
            }
            else if( mat->n >= i || mat->n >= j) {
                perror("Out of range\n");
                return;
            }
            else {
                for(int k = 0; k < mat->m; k++) {
                    msp_complex temp = mat->data[i][k];
                    mat->data[i][k] = mat->data[j][k];
                    mat->data[j][k] = temp;
                }
            }
        }
}
void msp_matrix_complex_swap_columns(msp_matrix_complex* mat, size_t i , size_t j) {
    if(mat == NULL) {
        perror("Matrix is null pointer\n");
        return;
    }
    else {
        if(mat->n == 0 || mat->m == 0) {
            perror("Matrix is empty");
            return;
        }
        else if( mat->m >= i || mat->m >= j) {
            perror("Out of range\n");
            return;
        }
        else {
            for(int k = 0; k < mat->n; k++) {
                msp_complex temp = mat->data[k][i];
                mat->data[k][i] = mat->data[k][j];
                mat->data[k][j] = temp;
            }
        }
    }
}
void msp_matrix_complex_transpose(msp_matrix_complex* dest, const msp_matrix_complex* src) {
    if(dest == NULL) {
        dest = msp_matrix_complex_allocate(src->m, src->n);
    }
    else if(dest->n != src->m || dest->m != src->n) {
        free(dest);
        dest = msp_matrix_complex_allocate(src->m, src->n);
    }
    for(int i = 0; i < src->n; i++){
        for(int j = 0; j < src->m ; j++) {
            dest->data[j][i] = src->data[i][j]; //TODO sprawdzic
        }
    }
}

//OPERATIONS
void msp_matrix_complex_add(msp_matrix_complex* a, const msp_matrix_complex* b) {
    if(a == NULL || b == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n != b->n || a->m != b->m) {
            perror("a and b is not the same lenght\n");
            return;
        }
        else {
            for(int i = 0; i < b->n; i++) {
                for(int j = 0; j < b->m; j++) {
                    a->data[i][j] = msp_complex_add(a->data[i][j], b->data[i][j]);
                }
            }
        }
    }
}
void msp_matrix_complex_sub(msp_matrix_complex* a, const msp_matrix_complex* b) {
    if(a == NULL || b == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n != b->n || a->m != b->m) {
            perror("a and b is not the same lenght\n");
            return;
        }
        else {
            for(int i = 0; i < b->n; i++) {
                for(int j = 0; j < b->m; j++) {
                    a->data[i][j] = msp_complex_sub(a->data[i][j], b->data[i][j]);
                }
            }
        }
    }
}
void msp_matrix_complex_mul_elements(msp_matrix_complex* a, const msp_matrix_complex* b) {
    if(a == NULL || b == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n != b->n || a->m != b->m) {
            perror("a and b is not the same lenght\n");
            return;
        }
        else {
            for(int i = 0; i < b->n; i++) {
                for(int j = 0; j < b->m; j++) {
                    a->data[i][j] = msp_complex_mul(a->data[i][j], b->data[i][j]);

                }
            }
        }
    }
}
msp_matrix_complex* msp_matrix_complex_mul(const msp_matrix_complex* a, const msp_matrix_complex* b) {
    if(a == NULL || b==NULL) {
        perror("mat is nullpoiner\n");
        return NULL;
    }
    else if(a->n == 0 || a->m == 0 || b->n == 0 || b->m == 0) {
        perror("msp_matrix is empty\n");
        return NULL;
    }
    else {
        if(a->n != a->m) {
            perror("cant mul msp_matrix when a->m != b->n\n");
            return NULL;
        }
        else {
            msp_matrix_complex* mat = msp_matrix_complex_allocate(a->n, b->m);
            for(int i = 0; i < mat->n; i++) {
                for(int j = 0; j < mat->m; j++) {
                    mat->data[i][j] = msp_complex_create(0, 0);
                    for(int k = 0; k < b->n; k++) {
                        mat->data[i][k] = msp_complex_add(mat->data[i][k],msp_complex_mul(a->data[i][k],b->data[k][j]));
                    }
                }
            }
            return mat;
        }
    }
}
void msp_matrix_complex_div_elements(msp_matrix_complex* a, const msp_matrix_complex* b) {
    if(a == NULL || b == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n != b->n || a->m != b->m) {
            perror("a and b is not the same lenght\n");
            return;
        }
        else {
            for(int i = 0; i < b->n; i++) {
                for(int j = 0; j < b->m; j++) {
                    if(msp_complex_iszero(b->data[i][j])) {
                        perror("Cant div by 0\n");
                        return;
                    }
                }
            }
            for(int i = 0; i < b->n; i++) {
                for(int j = 0; j < b->m; j++) {
                    a->data[i][j] = msp_complex_div(a->data[i][j], b->data[i][j]);
                }
            }
        }
    }
}
void msp_matrix_complex_scale(msp_matrix_complex* a, const msp_complex x) {
    if(a == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n == 0 || a->m == 0) {
            perror("a is empty msp_matrix\n");
            return;
        }
        else {
            for(int i = 0; i < a->n; i++) {
                for(int j = 0; j < a->m; j++) {
                    a->data[i][j] = msp_complex_mul(a->data[i][j], x);

                }
            }
        }
    }
}
void msp_matrix_complex_scale_columns(msp_matrix_complex* a, const msp_vector_complex * b) {
    if(a == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n == 0 || a->m == 0) {
            perror("a is empty msp_matrix\n");
            return;
        }
        else if(a->n != b->size) {
            perror("a->n and msp_vector b is not the same lenght");
            return;

        }
        else{
            for(int i = 0; i < a->n; i++) {
                for(int j = 0; j < a->m; j++) {
                    a->data[i][j] = msp_complex_mul(a->data[i][j], b->data[i]);
                }
            }
        }
    }
}
void msp_matrix_complex_scale_rows(msp_matrix_complex* a, const msp_vector_complex * b) {
    if(a == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n == 0 || a->m == 0) {
            perror("a is empty msp_matrix\n");
            return;
        }
        else if(a->m != b->size) {
            perror("a->n and msp_vector b is not the same lenght");
            return;

        }
        else{
            for(int i = 0; i < a->n; i++) {
                for(int j = 0; j < a->m; j++) {
                    a->data[j][i] = msp_complex_mul(a->data[j][i], b->data[i]);
                }
            }
        }
    }
}
void msp_matrix_complex_add_constant(msp_matrix_complex* a, const msp_complex x) {
    if(a == NULL) {
        perror("msp_matrix is NULL pointer\n");
        return;
    }
    else {
        if(a->n == 0 || a->m == 0) {
            perror("a is empty msp_matrix\n");
            return;
        }
        else {
            for(int i = 0; i < a->n; i++) {
                for(int j = 0; j < a->m; j++) {
                    a->data[i][j] = msp_complex_add(a->data[i][j], x);
                }
            }
        }
    }
}

//?
int msp_matrix_complex_isnull(const msp_matrix_complex* mat) {
    if(mat == NULL) {
        return -1;
    }
    else if( mat->n ==0 || mat->m == 0) {
        return 0;
    }
    else {
        return 1;
    }
}
