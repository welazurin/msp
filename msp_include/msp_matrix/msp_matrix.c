//
// Created by programowanie on 06.12.2021.
//

#include "msp_matrix.h"
//ALLOCATING
msp_matrix* msp_matrix_allocate(size_t n, size_t m) {
    //DECLARING NEW MATRIX
    msp_matrix* mat;
    //ALLOCATING
    mat = malloc(sizeof(*mat));
    if(mat == NULL) {
        perror("Bad allocation memory in msp_matrix_allocate\n");
        msp_logger(MSP_MATRIX, "msp_matrix_allocate", "ERROR in allocating memory for matrix");
        return NULL;
    }
    else {
        mat->data = malloc(sizeof(*(mat->data))*n);
        if(mat->data == NULL) {
            perror("Bad allocation memory in msp_matrix_allocate\n");
            msp_logger(MSP_MATRIX, "msp_matrix_allocate", "ERROR in allocating memory for matrix->data");

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
                msp_logger(MSP_MATRIX, "msp_matrix_allocate", "ERROR in allocating memory for matrix->data[i]");
                return NULL;
            }
        }
        //END OF ALLOCATING
        mat->n = n;
        mat->m = m;
        msp_logger(MSP_MATRIX, "msp_matrix_allocate", "Success allocating matrix");
        return mat;
    }
}

void msp_matrix_free(msp_matrix* mat) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX, "msp_matrix_free", "Matrix is null-pointer");
        return;
    }
    else {
        for(int i = 0; i < mat->n; i++) {
            free(mat->data[i]);
        }
        free(mat->data);
        mat = NULL;
        msp_logger(MSP_MATRIX, "msp_matrix_free", "Success free matrix");
    }
}

//ACCESSING
double msp_matrix_get(const msp_matrix* mat, size_t i, size_t j) {
    if(i > mat->n-1 || j >  mat->m-1) {
        msp_logger(MSP_MATRIX, "msp_matrix_get", "ERROR out of range i > mat->n-1 or j > mat->m-1 i - %d,mat->n-1, j-%d, mat->m-1", i, mat->n-1, j, mat->m-1);
        perror("Error in access to un allocating memory : OUT OF RANGE\n");
        abort();
    }
    else {
        msp_logger(MSP_MATRIX, "msp_matrix_get", "Success returned value %f", mat->data[i][j]);
        return mat->data[i][j];
    }
}

void msp_matrix_set(msp_matrix* mat, size_t i, size_t j, double x) {
    if(i > mat->n-1 || j >  mat->m-1) {
        msp_logger(MSP_MATRIX, "msp_matrix_set", "ERROR out of range i > mat->n-1 or j > mat->m-1 i - %d,mat->n-1, j-%d, mat->m-1", i, mat->n-1, j, mat->m-1);
        perror("Error in access to un allocating memory : OUT OF RANGE\n");
        return;
    }
    else {
        mat->data[i][j] = x;
        msp_logger(MSP_MATRIX, "msp_matrix_set", "Success seting value %f", mat->data[i][j]);
    }
}

double* msp_matrix_get_ptr(msp_matrix* mat, size_t i, size_t j) {
    if(i > mat->n-1 || j >  mat->m-1) {
        msp_logger(MSP_MATRIX, "msp_matrix_get_ptr", "ERROR out of range i > mat->n-1 or j > mat->m-1 i - %d,mat->n-1, j-%d, mat->m-1", i, mat->n-1, j, mat->m-1);
        perror("Error in access to un allocating memory : OUT OF RANGE\n");
        abort();
    }
    else {
        msp_logger(MSP_MATRIX, "msp_matrix_get_ptr", "Success getting pointer %p", &(mat->data[i][j]));
        return &(mat->data[i][j]);
    }
}

//INIT

void msp_matrix_set_all(msp_matrix* mat, double x) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX, "msp_matrix_set_all", "ERROR matrix is null-pointer");
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

void msp_matrix_set_ones(msp_matrix* mat) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX, "msp_matrix_set_ones", "ERROR matrix is null-pointer");
        perror("mat is Null-pointer\n");
        abort();
    }
    else {
        if(mat->n == 0 || mat->m == 0) {
            perror("mat is empty\n");
        }
        else {
            msp_matrix_set_zero(mat);
            if(mat->n > mat->m) {
                for(int i = 0; i < mat->m; i++) {
                    mat->data[i][i] = 1;
                }
            }
            else {
                for(int i = 0; i < mat->n; i++) {
                    mat->data[i][i] = 1;
                }
            }

        }
    }
}

void msp_matrix_set_zero(msp_matrix* mat) {
    msp_matrix_set_all(mat, 0);
}
//READING WRITING
void msp_matrix_fprintf(FILE* stream, const char* format, const msp_matrix* mat) {
    if(mat == NULL) {
        msp_logger(MSP_MATRIX, "msp_matrix_fprintf", "ERROR matrix is null-pointer");
        perror("matrix is null pointer");
        return;
    }
    for(int i = 0; i < mat->n; i++) {
        for(int j = 0; j < mat->m; j++) {
            fprintf(stream, format, mat->data[i][j]);
            fprintf(stream, " ");
        }
        fprintf(stream, "\n");
    }
}
void msp_matrix_fscanf(FILE* stream, msp_matrix* mat) {
    for(int i = 0; i < mat->n; i++) {
        for(int j = 0; j < mat->m; j++) {
            fscanf(stream, "%f", &(mat->data[i][j]));
        }
    }
}
void msp_matrix_fprintf_with_size(FILE* stream, const char* format, const msp_matrix* mat) {
    fprintf(stream, "%d, %d\n", mat->n, mat->m);
    msp_matrix_fprintf(stream, format, mat);
}
void msp_matrix_fscanf_with_size(FILE* stream, msp_matrix* mat) {
    size_t n,m;

    int x = fscanf(stream, "%d, %d", &n, &m);
    if(mat==NULL) {
        mat = msp_matrix_allocate(n,m);
    }
    else {
        if(n != mat->n || m != mat->m) {
            msp_matrix* temp;
            temp = msp_matrix_allocate(n, m);
            msp_matrix_free(mat);
            mat = temp;
        }
    }
    msp_matrix_fscanf(stream, mat);
}
//COPY
void msp_matrix_memcpy(msp_matrix* dest, const msp_matrix* src) {
    free(dest);
    dest = msp_matrix_allocate(src->n, src->m);
    dest->n = src->n;
    dest->m = src->m;
    for(int i = 0; i < dest->n; i++) {
        for(int j = 0; j < dest->m; j++) {
            dest->data[i][j] = src->data[i][j];
        }
    }
}
void msp_matrix_swap(msp_matrix* a, msp_matrix* b) {
    size_t n, m;
    double** data;
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
void msp_matrix_get_row(msp_matrix * mat, msp_vector* vec, size_t i) {
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
            vec = msp_vector_allocate(mat->m);
            if(vec == NULL) {
                abort();
            }
        }
    }
    for(int j = 0; i < mat->m; i++) {
        vec->data[i] = mat->data[i][j];
    }

}
void msp_matrix_get_col(const msp_matrix* mat, msp_vector* vec, size_t i) {
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
            vec = msp_vector_allocate(mat->n);
            if(vec == NULL) {
                abort();
            }
        }
    }
    for(int j = 0; i < mat->n; i++) {
        vec->data[i] = mat->data[j][i];
    }
}

void msp_matrix_set_row(msp_matrix* mat, const msp_vector* vec, size_t i) {
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
void msp_matrix_set_col(msp_matrix* mat, const msp_vector* vec, size_t i) {
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
void msp_matrix_swap_rows(msp_matrix* mat, size_t i, size_t j) {
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
                double temp = 0;
                mat->data[i][k] = temp;
                mat->data[i][k] = mat->data[j][k];
                mat->data[j][k] = temp;
            }
        }
    }
}
void msp_matrix_swap_columns(msp_matrix* mat, size_t i , size_t j){
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
                    double temp = 0;
                    mat->data[k][i] = temp;
                    mat->data[k][i] = mat->data[k][j];
                    mat->data[k][j] = temp;
                }
            }
        }
}

void msp_matrix_transpose(msp_matrix* dest, const msp_matrix* src) {
    if(dest == NULL) {
        dest = msp_matrix_allocate(src->m, src->n);
    }
    else if(dest->n != src->m || dest->m != src->n) {
        free(dest);
        dest = msp_matrix_allocate(src->m, src->n);
    }
    for(int i = 0; i < src->n; i++){
        for(int j = 0; j < src->m ; j++) {
            dest->data[j][i] = src->data[i][j]; //TODO sprawdzic
        }
    }
}

//OPERATIONS
void msp_matrix_add(msp_matrix* a, const msp_matrix* b) {
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
                    a->data[i][j] += b->data[i][j];
                }
            }
        }
    }


}
void msp_matrix_sub(msp_matrix* a, const msp_matrix* b) {
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
                    a->data[i][j] -= b->data[i][j];
                }
            }
        }
    }
}
void msp_matrix_mul_elements(msp_matrix* a, const msp_matrix* b) {
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
                    a->data[i][j] *= b->data[i][j];
                }
            }
        }
    }
}
msp_matrix* msp_matrix_mul(const msp_matrix* a, const msp_matrix* b) {
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
            msp_matrix* mat = msp_matrix_allocate(a->n, b->m);
            for(int i = 0; i < mat->n; i++) {
                for(int j = 0; j < mat->m; j++) {
                    mat->data[i][j] = 0;
                    for(int k = 0; k < b->n; k++) {
                        mat->data[i][k] += (a->data[i][k]*b->data[k][j]);
                    }
                }
            }
            return mat;
        }
    }


}
void msp_matrix_div_elements(msp_matrix* a, const msp_matrix* b) {
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
                    if(b->data[i][j] == 0) {
                        perror("Cant div by 0\n");
                        return;
                    }
                }
            }
            for(int i = 0; i < b->n; i++) {
                for(int j = 0; j < b->m; j++) {
                    a->data[i][j] += b->data[i][j];
                }
            }
        }
    }
}
void msp_matrix_scale(msp_matrix* a, const double x) {
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
                    a->data[i][j] *= x;
                }
            }
        }
    }
}
void msp_matrix_scale_columns(msp_matrix* a, const msp_vector* b) {
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
                    a->data[i][j] *= b->data[i];
                }
            }
        }
    }
}
void msp_matrix_scale_rows(msp_matrix* a, const msp_vector* b) {
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
                    a->data[j][i] *= b->data[i];
                }
            }
        }
    }
}
void msp_matrix_add_constant(msp_matrix* a, const double x) {
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
                    a->data[i][j] += x;
                }
            }
        }
    }
}
double msp_matrix_det(const msp_matrix* a) {
    if(a == NULL) {
        perror("a is NULL pointer\n");
        return 0;
    }
    else {
        if(a->n == 0 || a->m == 0) {
            perror("a is empty\n");
            return 0;
        }
        else if(a->n != a->m) {
            perror("det is only for quadratic msp_matrix\n");
            return 0;
        }
        else {
            int* temp;
            temp = malloc(sizeof(int) * a->n);
            for(int i = 0; i < a->n ;i++) {
                temp[i] = i;
            }
            double result = det(a->n, 0, temp, a->data);
            free(temp);
            return result;
        }
    }
}

//?
int msp_matrix_isnull(const msp_matrix* mat) {
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
int msp_matrix_ispos(const msp_matrix* mat) {
    if(mat == NULL) {
        return -1;
    }
    else {
        for(int i = 0; i < mat->n; i++) {
            for(int j = 0; j < mat->m; j++) {
                if(mat->data[i][j] <= 0 ) {
                    return 0;
                }
            }
        }
        return 1;
    }
}
int msp_matrix_isneg(const msp_matrix* mat) {
    if(mat == NULL) {
        return -1;
    }
    else {
        for(int i = 0; i < mat->n; i++) {
            for(int j = 0; j < mat->m; j++) {
                if(mat->data[i][j] >= 0 ) {
                    return 0;
                }
            }
        }
        return 1;
    }
}


double det ( int n, int w, const int * WK, double ** A )
{
    int    i, j, k, m, * KK;
    double s;

    if( n == 1 )   {
        return A [ w ][ WK [ 0 ] ];
    }                  // sprawdzamy warunek zakończenia rekurencji
    else
        {
            KK = malloc(sizeof (int) * (n-1));        // tworzymy dynamiczny wektor kolumn

            s = 0;                         // zerujemy wartość rozwinięcia
            m = 1;                         // początkowy mnożnik

            for( i = 0; i < n; i++ )       // pętla obliczająca rozwinięcie
                {

                k = 0;                       // tworzymy wektor kolumn dla rekurencji

                for( j = 0; j < n - 1; j++ ) // ma on o 1 kolumnę mniej niż WK
                    {
                    if( k == i ) k++;          // pomijamy bieżącą kolumnę
                    KK [ j ] = WK [ k++ ];     // pozostałe kolumny przenosimy do KK
                    }

                s += m * A [ w ][ WK [ i ] ] * det ( n - 1, w  + 1, KK, A );

                m = -m;                      // kolejny mnożnik

                }

            free(KK);                 // usuwamy zbędną już tablicę dynamiczną

            return s;                      // ustalamy wartość funkcji

        }
}