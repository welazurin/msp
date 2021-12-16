//
// Created by programowanie on 15.12.2021.
//

#include "complex.h"
#include <math.h>
// CREATING
msp_complex msp_complex_create(double real, double imag) {
    msp_complex z;
    z.real = real;
    z.imag = imag;
    return z;
}

msp_complex msp_complex_create_polar(double arg, double mod) {
    msp_complex z;
    z.real = mod*cos(arg);
    z.imag = mod*sin(arg);
    return z;
}
//PROPERTIES
int msp_complex_real(msp_complex z) {
    if(z.imag == 0 && z.real == 0) {
        return 0;
    }
    else if(z.imag == 0) {
        return 1;
    }
    else {
        return -1;
    }
}
int msp_complex_imag(msp_complex z) {
        if(z.imag == 0 && z.real == 0) {
            return 0;
        }
        else if(z.real == 0) {
            return 1;
        }
        else {
            return -1;
        }
}
int msp_complex_zero(msp_complex z) {
    if(z.imag == 0 && z.real == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
//GET
double msp_complex_get_module(msp_complex a) {
    return sqrt(a.real*a.real + a.imag*a.imag);
}

double msp_complex_get_arg(msp_complex b) {
    double mod = msp_complex_get_module(b);
    return acos(b.real / mod);
}

double msp_complex_get_real(msp_complex a) {
    return a.real;
}

double msp_complex_get_imag(msp_complex a) {
    return a.imag;
}
//OPERATIONS
msp_complex msp_complex_add(msp_complex a, msp_complex b) {
    msp_complex z;
    z.real = a.real + b.real;
    z.imag = a.imag + b.imag;
    return z;
}

msp_complex msp_complex_div(msp_complex a, msp_complex b) {
    msp_complex z;
    if(b.real == 0 && b.imag == 0) {
        perror("cant div by 0");
    }
    double temp = b.real*b.real + b.imag*b.imag;
    z.real = (a.real * b.real + a.imag*b.imag)/temp;
    z.imag =( a.imag * b.real - a.real*b.imag)/temp;
    return z;
}

msp_complex msp_complex_mul(msp_complex a, msp_complex b) {
    msp_complex z;
    z.real = a.real * b.real - a.imag*b.imag;
    z.imag = a.imag * b.real + a.real*b.imag;
    return z;
}

msp_complex msp_complex_sub(msp_complex a, msp_complex b) {
    msp_complex z;
    z.real = a.real - b.real;
    z.imag = a.imag - b.imag;
    return z;
}

msp_complex msp_complex_add_real(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real + x;
    z.imag = a.imag;
    return z;
}

msp_complex msp_complex_add_imag(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real;
    z.imag = a.imag + x;
    return z;
}

msp_complex msp_complex_sub_real(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real - x;
    z.imag = a.imag;
    return z;
}

msp_complex msp_complex_sub_imag(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real;
    z.imag = a.imag - x;
    return z;
}

msp_complex msp_complex_mul_real(msp_complex a, double x){
    msp_complex z;
    z.real = a.real * x;
    z.imag = a.imag;
    return z;
}

msp_complex msp_complex_mul_imag(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real;
    z.imag = a.imag * x;
    return z;
}

msp_complex msp_complex_div_real(msp_complex a, double x) {
    if(x == 0) {
        perror("cant div by 0");
        msp_complex z;
        z.real = 0;
        z.imag = 0;
        return z;
    }
    else {
        msp_complex z;
        z.real = a.real/x;
        z.imag = a.imag;
        return z;
    }
}

msp_complex msp_complex_div_imag(msp_complex a, double x) {
    if(x == 0) {
        perror("cant div by 0");
        msp_complex z;
        z.real = 0;
        z.imag = 0;
        return z;
    }
    else {
        msp_complex z;
        z.real = a.real;
        z.imag = a.imag/x;
        return z;
    }
}

msp_complex msp_complex_conjugate(msp_complex a) {
    msp_complex z;
    z.real = a.real;
    z.imag = -a.imag;
    return z;
}

msp_complex msp_complex_inverse(msp_complex a) {
    msp_complex z;
    if(a.real == 0 && a.imag == 0) {
        perror("cant div by 0");
    }
    double temp = a.real*a.real + a.imag*a.imag;
    z.real = (a.real + a.imag)/temp;
    z.imag =( a.real - a.imag)/temp;
    return z;

}

msp_complex msp_complex_negativ(msp_complex a) {
    msp_complex z;
    z.real = -a.real;
    z.imag = -a.imag;
    return z;
}

//FUNCTIONS

msp_complex msp_complex_sqrt(msp_complex a) {
    double module = msp_complex_get_module(a);
    double arg = msp_complex_get_arg(a);
    msp_complex z;
    module = sqrt(module);
    arg = (arg)/2;
    z.real = module*cos(arg);
    z.imag = module*sin(arg);
    return z;


}

msp_complex msp_complex_sqrt_real(double x) {
    if(x >= 0) {
        msp_complex z;
        z.real = sqrt(x);
        z.imag = 0;
        return z;
    }
    else {
        msp_complex z;
        z.real = 0;
        z.imag = sqrt(-x);
        return z;
    }
}

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

// inverse Trygonometry

msp_complex msp_complex_arcsin(msp_complex z);

msp_complex msp_complex_arccos(msp_complex z);

msp_complex msp_complex_arctan(msp_complex z);

msp_complex msp_complex_arccot(msp_complex z);

msp_complex msp_complex_arcsec(msp_complex z);

msp_complex msp_complex_arccsc(msp_complex z);

//hyberbolic functions

msp_complex msp_complex_sinh(msp_complex z);

msp_complex msp_complex_cosh(msp_complex z);

msp_complex msp_complex_tanh(msp_complex z);

msp_complex msp_complex_coth(msp_complex z);

msp_complex msp_complex_sech(msp_complex z);

msp_complex msp_complex_csch(msp_complex z);

// inverse hyberbolic functions

msp_complex msp_complex_arcsinh(msp_complex z);

msp_complex msp_complex_arccosh(msp_complex z);

msp_complex msp_complex_arctanh(msp_complex z);

msp_complex msp_complex_arccoth(msp_complex z);

msp_complex msp_complex_arcsech(msp_complex z);

msp_complex msp_complex_arccsch(msp_complex z);

