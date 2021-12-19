//
// Created by programowanie on 19.12.2021.
//

#ifndef MSP_MSP_POLY_H
#define MSP_MSP_POLY_H
#include "../msp_vector/msp_vector.h"
#include "../msp_logger/msp_log.h"
typedef struct msp_poly{
    msp_vector* coefficient;
}msp_poly;
//Alocating
msp_poly* msp_poly_allocate(size_t i);
void msp_poly_free(msp_poly* poly);
//Seting coefficient
void msp_poly_set(msp_poly * poly,double* data , size_t size);
//GETTING Value
double msp_poly_get_value(msp_poly* poly,double x);
msp_vector* msp_poly_get(msp_vector* x, msp_poly* poly);
msp_poly* msp_poly_derivative(msp_poly* poly);
msp_poly* msp_poly_intergral(msp_poly* poly);
void msp_poly_fprintf(FILE* stream, msp_poly * poly);
//CONVERTING
msp_vector* msp_poly_to_vector(msp_poly* poly);
#endif //MSP_MSP_POLY_H
