//
// Created by programowanie on 19.12.2021.
//

#include "msp_poly.h"
#define MSP_POLY "msp_poly.h"
#include <math.h>
//Alocating
msp_poly* msp_poly_allocate(size_t i) { // ALOKACJA PAMIECI NA I WSPOLCZYNNIKOW
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
void msp_poly_free(msp_poly* poly) { //ZWALNIANIE PAMIECI MSP_POLY
    if(poly == NULL) {
        return;
    }
    msp_vector_free(poly->coefficient);
    free(poly);
    poly = NULL;
}
//Seting coefficient
void msp_poly_set(msp_poly* poly, double* data, size_t size) { //MSP POLY PRZYJMUJE WSPOLCZYNNIKI Z DATA
    if(poly == NULL) {
        poly = msp_poly_allocate(size);
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
double msp_poly_get_value(msp_poly* poly, double x) {       // ZWRACAMY WARTOSC FUNKCJI DLA ARGUMENTU X
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
msp_vector* msp_poly_get(msp_vector* x, msp_poly* poly) { // ZWRACAMY WARTOSCI DLA WEKTORA ARGUMENTOW
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

msp_complex msp_poly_get_complex_value(msp_poly* poly, msp_complex z) { // ZWRACA WARTOSC DLA ARGUEMNTU TYPU MSP_COMPLEX
    if(poly == NULL) {
        msp_logger(MSP_POLY, "msp_poly_get_complex_value", "ERROR poly is null struct");
        msp_complex result = msp_complex_create(0,0);
        return result;
    }
    else {
        if(poly->coefficient->size == 0) {
            msp_complex result = msp_complex_create(0,0);
            return result;
        }
        else {
            msp_complex result = msp_complex_create(0,0);
            for(int i = 0; i < poly->coefficient->size; i++) {
                msp_complex coefficient = msp_complex_create(poly->coefficient->data[i], 0);
                msp_complex y = msp_complex_create(i, 0);
                msp_complex pow = msp_complex_pow(z, y);
                result = msp_complex_add(result, msp_complex_mul(coefficient, pow));
            }
            msp_logger(MSP_POLY, "msp_poly_get_value", "f(z) = %s, f(%c) = %c", poly,z, result);
            return result;
        }
    }
}

msp_poly* msp_poly_derivative(msp_poly* poly) { // ZWRACA MSP_POLY KTORE JEST POCHODNA POLY
    msp_poly* result;
    result = msp_poly_allocate(poly->coefficient->size - 1);
    double* data;
    data= malloc(sizeof(double) * poly->coefficient->size-1);
    for(int i = 1; i < poly->coefficient->size-1; i++) {
        data[i] = poly->coefficient->data[i+1] * (i+1);
    }
    data[0] = poly->coefficient->data[1];
    msp_poly_set(result, data, poly->coefficient->size-1);
    msp_logger(MSP_POLY, "msp_poly_derivative", "f(x) = %s, f'(x) = %s", poly,result);
    return result;
}
msp_poly* msp_poly_intergral(msp_poly* poly) { // ZWRACA CALKE Z POLY
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
msp_vector* msp_poly_to_vector(msp_poly* poly) { //ZWRACA WEKTOR WSPOLCZYNNIKOW
    return poly->coefficient;
}

void msp_poly_fprintf(FILE* stream, msp_poly * poly) { // WYPISUJE NA STREAM MSP_POLY
    for(int i = 0; i < poly->coefficient->size; i++) {
        fprintf(stream, "%f*x^%d", poly->coefficient->data[i], i);
        if(i != poly->coefficient->size-1){
            fprintf(stream, " + ");
        }
    }
    fprintf(stream, "\n");

}

msp_vector* msp_poly_real_roots(msp_poly* poly) { // LICZY RZECZYWISTE MIEJSCA ZEROWE FUNKCJI

}
msp_vector_complex* msp_poly_roots(msp_poly* polys) {   //ZWRACA ZESPOLONE MIEJSCA ZEROWE FUNKCJI
    if(polys->coefficient->size < 4) {
        return msp_poly_roots2(polys);
    }
    msp_poly* poly = polys;
    msp_poly* deriv = msp_poly_derivative(poly);
    msp_poly* deriv2 = msp_poly_derivative(deriv);

    msp_vector_complex* result = msp_vector_complex_allocate(poly->coefficient->size-1);
    for(int i = 0; i < poly->coefficient->size-1; i++) {
        msp_complex zero = msp_complex_create(0,0);
        while(1) {
            msp_complex pd = msp_poly_get_complex_value(deriv, zero);
            msp_complex p = msp_poly_get_complex_value(poly, zero);
            if(msp_complex_iszero(p) || msp_complex_get_module(p) < 0.00001) {
                break;
            }
            msp_complex g = msp_complex_div(pd,p);
            msp_complex g2 = msp_complex_pow(g, msp_complex_create(2, 0));
            msp_complex pdd = msp_poly_get_complex_value(deriv2, zero);
            msp_complex h = msp_complex_div(pdd, p);
            h = msp_complex_sub(g2, h);
            msp_complex n = msp_complex_create(poly->coefficient->size-1, 0);
            msp_complex n1 = msp_complex_create(poly->coefficient->size-2, 0);
            msp_complex nh = msp_complex_sub(msp_complex_mul(n,h), g2);
            msp_complex sqrt = msp_complex_sqrt(msp_complex_mul(n1, nh));
            msp_complex g_plus_sqrt = msp_complex_add(g, sqrt);
            msp_complex g_sub_sqrt = msp_complex_sub(g, sqrt);
            msp_complex denom;
            double m1 = msp_complex_get_module(g_plus_sqrt);
            double m2 = msp_complex_get_module(g_sub_sqrt);
            if(m1 > m2) {
                denom = g_plus_sqrt;
            }
            else {
                denom = g_sub_sqrt;
            }
            msp_complex a = msp_complex_div(n, denom);
            zero = msp_complex_sub(zero,a);
        }
        if(zero.imag == 0) {
            result->data[i] = zero;
            poly = msp_poly_horner(poly, zero.real);
        }
        else {
            result->data[i] = zero;
            result->data[i+1] = msp_complex_conjugate(zero);
            i++;
            if(poly->coefficient->size > 3){
                poly = msp_poly_div_2(poly, -2*zero.real, zero.real*zero.real+zero.imag*zero.imag);
            }
        }
    }
    return result;
}

msp_poly* msp_poly_horner(msp_poly* poly, double c) {   //DZIELI FUNCKJE PRZEZ DWUMIAN X-C
    if(poly == NULL) {
        return NULL;
    }
    else if(poly->coefficient->size == 0) {
        return NULL;
    }
    else {
        double* data = malloc((poly->coefficient->size-1) * sizeof(double));
        data[poly->coefficient->size-2] = poly->coefficient->data[poly->coefficient->size-1];
        for(int i = poly->coefficient->size-3; i > -1 ; i--) {
            data[i] = poly->coefficient->data[i+1]*c + data[i+1];
        }
        msp_poly* result = msp_poly_allocate(poly->coefficient->size-1);
        msp_poly_set(result, data, poly->coefficient->size-1);
        return result;
    }


}

msp_poly* msp_poly_div_2(msp_poly* poly, double b, double c) {  //DZIELI POLY PRZEZ X^2 + BX + C
    // A = BQ + R
    // A - poly, B = [1,b,c], Q = result, R = 0
    double eps = 1e-14;
    int deqQ = poly->coefficient->size-3; // deqQ
    int deqR = 1; // deqR
    int deqB = 2;
    int deqA = poly->coefficient->size-1;
    double * data = malloc((deqQ+1)*sizeof(double)); // tablica na Q
    double * denom = malloc(sizeof(double)*3); // B
    denom[0] = c;
    denom[1] = b;
    denom[2] = 1;
    double* R = malloc(sizeof(double) * poly->coefficient->size);
    for (int i = 0; i <= deqA; i++) {
        R[i] = poly->coefficient->data[i];
     }
    for(int j = deqQ; j >= 0; j--) {
        data[deqQ-j] = R[deqA-j]/b;
        for(int i = deqQ-j ; i < deqA-j;i++) {
            R[i] -= data[deqQ-j]*denom[i-deqQ+j];
        }
    }
    msp_poly* result = NULL;
    msp_poly_set(result, data, deqQ);
    return result;


}

msp_vector_complex* msp_poly_roots2(msp_poly* poly) {
    if(poly == NULL) {
        return NULL;
    }
    else if(poly->coefficient == NULL) {
        return NULL;
    }
    else if(poly->coefficient->size > 3) {
        return NULL;
    }
    else if(poly->coefficient->size == 2) {
        double a = poly->coefficient->data[0];
        double b = poly->coefficient->data[1];
        msp_vector_complex* x = msp_vector_complex_allocate(1);
        msp_vector_complex_set_all(x, msp_complex_create(-b/a, 0));
        return x;
    }
    else if(poly->coefficient->size == 1) {
        perror("Funckja liniowa");
        return NULL;
    }
    else {
        double c = poly->coefficient->data[0];
        double b = poly->coefficient->data[1];
        double a = poly->coefficient->data[2];
        double delta = b*b-4*a*c;
        msp_complex sdelta = msp_complex_sqrt_real(delta);
        msp_complex x1 = msp_complex_sub(msp_complex_negativ(msp_complex_create(b, 0)), sdelta);
        x1 = msp_complex_div(x1, msp_complex_create(2*a, 0));
        msp_complex x2 = msp_complex_add(msp_complex_negativ(msp_complex_create(b, 0)), sdelta);
        x2 = msp_complex_div(x2, msp_complex_create(2*a, 0));
        msp_vector_complex* result = msp_vector_complex_allocate(2);
        msp_vector_complex_set(result, 0, x1);
        msp_vector_complex_set(result, 1, x2);
        return result;
    }
}