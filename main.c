#include <stdio.h>
#include "vector.h"
#include "matrix.h"
int main() {
    msp_matrix* mat = msp_matrix_allocate(4, 5);
    for(int i = 0; i < 4; i ++) {
        for(int j = 0 ; j < 5; j++) {
            mat->data[i][j] = i*5 + j;
        }
    }
    FILE* file;
    file = fopen("test.txt", "w");
    msp_matrix_fprintf_with_size(file, "%f", mat);


    return 0;
}
