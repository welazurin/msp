//
// Created by programowanie on 21.12.2021.
//

#ifndef MSP_MSP_TAB_VECTOR_H
#define MSP_MSP_TAB_VECTOR_H
#include "../msp_vector/msp_vector.h"
typedef struct msp_tab_vector{
    msp_vector** data;      // table of pointer to msp_vector
    size_t size;
}msp_tab_vector;

msp_tab_vector* msp_tab_vector_create();
msp_tab_vector* msp_tab_vector_create_with_size(size_t size);
void msp_tab_vector_realloc(msp_tab_vector* tab, size_t size);
void msp_tab_vector_push_back(msp_tab_vector* tab, msp_vector* vector);
msp_vector* msp_tab_vector_pop(msp_tab_vector* tab);
msp_vector* msp_tab_vector_get(msp_tab_vector* tab, size_t i);

#endif //MSP_MSP_TAB_VECTOR_H
