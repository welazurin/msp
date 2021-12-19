//
// Created by programowanie on 19.12.2021.
//

#include "msp_poly.h"
#define MSP_POLY "msp_poly.h"
#include <math.h>
//Alocating
msp_poly* msp_poly_allocate(size_t i) {
    msp_poly* poly;
    poly = malloc(sizeof(*poly));
    if(poly == NULL) {
        perror("bad allocating poly");
        msp_logger(MSP_POLY, "msp_poly_allocate", "ERROR in allocating poly");
        return NULL;
    }
    poly->coefficient=msp_vector_allocate(i);
    msp_logger(MSP_POLY, "msp_poly_allocate", "Success allocating poly (%d)", i);
    return poly;
}
void msp_poly_free(msp_poly* poly) {
    if(poly == NULL) {
        return;
    }
    msp_vector_free(poly->coefficient);
    free(poly);
    poly = NULL;
}
//Seting coefficient
void msp_poly_set(msp_poly* poly,double* data, size_t size) {
    if(poly == NULL) {
        msp_vector_free(poly->coefficient);
        poly->coefficient = msp_vector_allocate(size);
        if(poly->coefficient == NULL) {
            msp_logger(MSP_POLY, "msp_poly_set", "ERROR in allocating poly->coefficient");
            return;
        }
    }
    if(poly->coefficient->size != size) {
        msp_vector_free(poly->coefficient);
        poly->coefficient = msp_vector_allocate(size);
        if(poly->coefficient == NULL) {
            msp_logger(MSP_POLY, "msp_poly_set", "ERROR in allocating poly->coefficient");
            return;
        }
    }
    msp_vector_set_tab(poly->coefficient, data, size);
    msp_logger(MSP_POLY, "msp_poly_set", "setting coefficient = %s", poly);
}
//GETTING Value
double msp_poly_get_value(msp_poly* poly, double x) {
    /* f(x) = [0] + [1]x+[2]x^2 + ... + [size-1]x^[n-1] */
    if(poly == NULL) {
        msp_logger(MSP_POLY, "msp_poly_get_value", "ERROR poly is null struct");
        return 0;
    }
    else {
        if(poly->coefficient->size == 0) {
            return 0;
        }
        else {
            double result = 0;
            for(int i = 0; i < poly->coefficient->size; i++) {
                result += poly->coefficient->data[i] * pow(x, i);
            }
            msp_logger(MSP_POLY, "msp_poly_get_value", "f(x) = %s, f(%f) = %f", poly,x, result);
            return result;
        }
    }

}
msp_vector* msp_poly_get(msp_vector* x, msp_poly* poly) {
    if(x == NULL) {
        return NULL;
    }
    else {
        msp_vector* result = msp_vector_allocate(x->size);
        for(int i = 0; i < result->size; i++) {
            result->data[i] = msp_poly_get_value(poly, x->data[i]);
        }
        msp_logger(MSP_POLY, "msp_poly_get", "poly = %s, vec = %v result = %v", poly,x, result);

        return result;
    }


}
msp_poly* msp_poly_derivative(msp_poly* poly) {
    msp_poly* result;
    result = msp_poly_allocate(poly->coefficient->size);
    double* data;
    data= malloc(sizeof(double) * poly->coefficient->size-1);
    for(int i = 1; i < poly->coefficient->size; i++) {
        data[i] = poly->coefficient->data[i] * i;
    }
    msp_poly_set(result, data, poly->coefficient->size);
    msp_logger(MSP_POLY, "msp_poly_derivative", "f(x) = %s, f'(x) = %s", poly,result);
    return result;
}
msp_poly* msp_poly_intergral(msp_poly* poly) {
    msp_poly* result;
    result = msp_poly_allocate(poly->coefficient->size);
    double* data;
    data= malloc(sizeof(double) * poly->coefficient->size+1);
    for(int i = 0; i < poly->coefficient->size; i++) {
        data[i+1] = poly->coefficient->data[i]/(i+1);
    }
    data[0] = 0;
    msp_poly_set(result, data, poly->coefficient->size+1);
    msp_logger(MSP_POLY, "msp_poly_integral", "f(x) = %s, F(x) = %s", poly,result);
    return result;
}

//CONVERTING
msp_vector* msp_poly_to_vector(msp_poly* poly) {
    return poly->coefficient;
}

void msp_poly_fprintf(FILE* stream, msp_poly * poly) {
    for(int i = 0; i < poly->coefficient->size; i++) {
        fprintf(stream, "%f*x^%d", poly->coefficient->data[i], i);
        if(i != poly->coefficient->size-1){
            fprintf(stream, " + ");
        }
    }
    fprintf(stream, "\n");

}