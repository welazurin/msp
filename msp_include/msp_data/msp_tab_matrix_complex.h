//
// Created by programowanie on 21.12.2021.
//

#ifndef MSP_MSP_TAB_MATRIX_COMPLEX_H
#define MSP_MSP_TAB_MATRIX_COMPLEX_H
#include "../msp_matrix/msp_matrix_complex.h"

typedef struct msp_tab_matrix_complex{
    msp_matrix_complex** data;
    size_t size;
}msp_tab_matrix_complex;

#endif //MSP_MSP_TAB_MATRIX_COMPLEX_H
