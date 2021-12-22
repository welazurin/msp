//
// Created by programowanie on 21.12.2021.
//

#ifndef MSP_MSP_TAB_MATRIX_H
#define MSP_MSP_TAB_MATRIX_H
#include "../msp_matrix/msp_matrix.h"

typedef struct msp_tab_matrix{
    msp_matrix** data;
    size_t size;
}msp_tab_matrix;
#endif //MSP_MSP_TAB_MATRIX_H
