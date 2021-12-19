//
// Created by programowanie on 15.12.2021.
//
#ifndef MSP_MSP_COMPLEX_H
#define MSP_MSP_COMPLEX_H
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../msp_logger/msp_log.h"
#define LOG10 2.30258509299404568402
#define PI 3.14159265358979323846

typedef struct msp_complex {
    double real;
    double imag;
} msp_complex;

// CREATING
msp_complex msp_complex_create(double real, double imag);

msp_complex msp_complex_create_polar(double arg, double mod);
//PROPERTIES
int msp_complex_real(msp_complex z);
int msp_complex_imag(msp_complex z);
int msp_complex_zero(msp_complex z);
//GET
double msp_complex_get_module(msp_complex a);

double msp_complex_get_arg(msp_complex b);

double msp_complex_get_real(msp_complex a);

double msp_complex_get_imag(msp_complex a);
//OPERATIONS
msp_complex msp_complex_add(msp_complex a, msp_complex b);

msp_complex msp_complex_div(msp_complex a, msp_complex b);

msp_complex msp_complex_mul(msp_complex a, msp_complex b);

msp_complex msp_complex_sub(msp_complex a, msp_complex b);

msp_complex msp_complex_add_real(msp_complex a, double x);

msp_complex msp_complex_add_imag(msp_complex a, double x);

msp_complex msp_complex_sub_real(msp_complex a, double x);

msp_complex msp_complex_sub_imag(msp_complex a, double x);

msp_complex msp_complex_mul_real(msp_complex a, double x);

msp_complex msp_complex_mul_imag(msp_complex a, double x);

msp_complex msp_complex_div_real(msp_complex a, double x);

msp_complex msp_complex_div_imag(msp_complex a, double x);

msp_complex msp_complex_conjugate(msp_complex a);

msp_complex msp_complex_inverse(msp_complex a);

msp_complex msp_complex_negativ(msp_complex a);

//FUNCTIONS

msp_complex msp_complex_sqrt(msp_complex a);

msp_complex msp_complex_sqrt_real(double x);

msp_complex msp_complex_pow(msp_complex a, msp_complex x);

msp_complex msp_complex_pow_real(msp_complex a, double x);

msp_complex msp_complex_exp(msp_complex z);

msp_complex msp_complex_log(msp_complex z);

msp_complex msp_complex_log10(msp_complex z);

msp_complex msp_complex_log_b(msp_complex z, msp_complex b);

//Trygonometry

msp_complex msp_complex_sin(msp_complex z);

msp_complex msp_complex_cos(msp_complex z);

msp_complex msp_complex_tan(msp_complex z);

msp_complex msp_complex_cot(msp_complex z);

msp_complex msp_complex_sec(msp_complex z);

msp_complex msp_complex_csc(msp_complex z);

#endif //MSP_MSP_COMPLEX_H
