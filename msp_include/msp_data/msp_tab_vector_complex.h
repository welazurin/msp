//
// Created by programowanie on 21.12.2021.
//

#ifndef MSP_MSP_TAB_VECTOR_COMPLEX_H
#define MSP_MSP_TAB_VECTOR_COMPLEX_H
#include "../msp_vector/msp_vector_complex.h"
typedef struct msp_tab_vector_complex{
    msp_vector_complex** data;
    size_t size;
}msp_tab_vector_complex;


#endif //MSP_MSP_TAB_VECTOR_COMPLEX_H
