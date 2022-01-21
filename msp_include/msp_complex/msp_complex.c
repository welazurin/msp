//
// Created by programowanie on 15.12.2021.
//
#include "msp_complex.h"


#define MSP_COMPLEX "msp_complex.h"
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
    double result = sqrt(a.real*a.real + a.imag*a.imag);
    msp_logger(MSP_COMPLEX, "msp_complex_get_module", "result = mod(a), %f = mod(%c)", result, a);
    return result;
}

double msp_complex_get_arg(msp_complex b) {
    if(b.imag == 0 && b.real == 0) {
        return 0;
    }
    double mod = msp_complex_get_module(b);
    double result = atan2(b.imag, b.real);
    msp_logger(MSP_COMPLEX, "msp_complex_get_arg", "result = arg(a), %f = arg(%c)", result, b);
    return result;
}

double msp_complex_get_real(msp_complex a) {
    double result = a.real;
    return a.real;
}

double msp_complex_get_imag(msp_complex a) {
    double result = a.imag;
    return result;
}
//OPERATIONS
msp_complex msp_complex_add(msp_complex a, msp_complex b) {
    msp_complex z;
    z.real = a.real + b.real;
    z.imag = a.imag + b.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_add", "z = a + b, %c = %c + %c", z,a,b);
    return z;
}

msp_complex msp_complex_div(msp_complex a, msp_complex b) {
    msp_complex z;
    if(b.real == 0 && b.imag == 0) {
        perror("cant div by 0");
        msp_logger(MSP_COMPLEX, "msp_complex_div_real", "ERROR try do div by 0");
        return z;
    }
    double temp = b.real*b.real + b.imag*b.imag;
    z.real = (a.real * b.real + a.imag*b.imag)/temp;
    z.imag =( a.imag * b.real - a.real*b.imag)/temp;
    msp_logger(MSP_COMPLEX, "msp_complex_div", "z = a / b, %c = %c / %c", z,a,b);
    return z;
}

msp_complex msp_complex_mul(msp_complex a, msp_complex b) {
    msp_complex z;
    z.real = a.real * b.real - a.imag*b.imag;
    z.imag = a.imag * b.real + a.real*b.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_mul", "z = a * b, %c = %c * %c", z,a,b);
    return z;
}

msp_complex msp_complex_sub(msp_complex a, msp_complex b) {
    msp_complex z;
    z.real = a.real - b.real;
    z.imag = a.imag - b.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_sub", "z = a - b, %c = %c - %c", z,a,b);
    return z;
}

msp_complex msp_complex_add_real(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real + x;
    z.imag = a.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_add_real", "z = a + x, %c = %c + %f", z,a, x);
    return z;
}

msp_complex msp_complex_add_imag(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real;
    z.imag = a.imag + x;
    msp_logger(MSP_COMPLEX, "msp_complex_add_imag", "z = a + x, %c = %c + %fi", z,a, x);
    return z;
}

msp_complex msp_complex_sub_real(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real - x;
    z.imag = a.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_sub_real", "z = a - x, %c = %c - %f", z,a, x);
    return z;
}

msp_complex msp_complex_sub_imag(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real;
    z.imag = a.imag - x;
    msp_logger(MSP_COMPLEX, "msp_complex_add_real", "z = a - x, %c = %c - %fi", z,a, x);
    return z;
}

msp_complex msp_complex_mul_real(msp_complex a, double x){
    msp_complex z;
    z.real = a.real * x;
    z.imag = a.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_mul_real", "z = a * x, %c = (%f*%f + %fi)", z,a.real, x, a.imag);
    return z;
}

msp_complex msp_complex_mul_imag(msp_complex a, double x) {
    msp_complex z;
    z.real = a.real*x;
    z.imag = a.imag * x;
    msp_logger(MSP_COMPLEX, "msp_complex_mul_imag", "z = a * x, %c = (%f + %f*%fi)", z,a.real, x, a.imag);
    return z;
}

msp_complex msp_complex_div_real(msp_complex a, double x) {
    if(x == 0) {
        perror("cant div by 0");
        msp_complex z;
        z.real = 0;
        z.imag = 0;
        msp_logger(MSP_COMPLEX, "msp_complex_div_real", "ERROR try do div by 0");
        return z;
    }
    else {
        msp_complex z;
        z.real = a.real/x;
        z.imag = a.imag;
        msp_logger(MSP_COMPLEX, "msp_complex_div_real", "z = a / x, %c = (%f/%f + %fi)", z,a.real, x, a.imag);
        return z;
    }
}

msp_complex msp_complex_div_imag(msp_complex a, double x) {
    if(x == 0) {
        perror("cant div by 0");
        msp_complex z;
        z.real = 0;
        z.imag = 0;
        msp_logger(MSP_COMPLEX, "msp_complex_div_imag", "ERROR try do div by 0");
        return z;
    }
    else {
        msp_complex z;
        z.real = a.real/x;
        z.imag = a.imag/x;
        msp_logger(MSP_COMPLEX, "msp_complex_div_imag", "z = a / x, %c = (%f + %f*%fi)", z,a.real,  a.imag, x);
        return z;
    }
}

msp_complex msp_complex_conjugate(msp_complex a) {
    msp_complex z;
    z.real = a.real;
    z.imag = -a.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_conjugate", "z = (a - bi), %c = (%f - %fi)", z,a.real,  a.imag);
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
    msp_logger(MSP_COMPLEX, "msp_complex_inverse", "z = 1/a, %c = 1/%c", z,a);
    return z;

}

msp_complex msp_complex_negativ(msp_complex a) {
    msp_complex z;
    z.real = -a.real;
    z.imag = -a.imag;
    msp_logger(MSP_COMPLEX, "msp_complex_negativ", "z = -a, %c = -%c", z, a);
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
    msp_logger(MSP_COMPLEX, "msp_complex_sqrt", "z = sqrt(a), %c = sqrt(%c)", z, a);
    return z;


}

msp_complex msp_complex_sqrt_real(double x) {
    if(x >= 0) {
        msp_complex z;
        z.real = sqrt(x);
        z.imag = 0;
        msp_logger(MSP_COMPLEX, "msp_complex_sqrt_real", "z = sqrt(x), %c = sqrt(%f)", z, x);
        return z;
    }
    else {
        msp_complex z;
        z.real = 0;
        z.imag = sqrt(-x);
        msp_logger(MSP_COMPLEX, "msp_complex_sqrt_real", "z = sqrt(a), %c = sqrt(%f)", z, x);
        return z;
    }
}

msp_complex msp_complex_pow(msp_complex a, msp_complex x) {
    if(msp_complex_iszero(x)) {
        msp_complex result = msp_complex_create(1, 0);
        msp_logger(MSP_COMPLEX, "msp_complex_pow", "z = a^x, %c = %c ^ %c", result,a, x);
        return result;
    }
    if(msp_complex_iszero(a)) {
        msp_complex result = msp_complex_create(0, 0);
        msp_logger(MSP_COMPLEX, "msp_complex_pow", "z = a^x, %c = %c ^ %c", result,a, x);
        return result;
    }
    double arg = msp_complex_get_arg(a);
    double mod = msp_complex_get_module(a);
    msp_complex loga = msp_complex_log(a);
    msp_complex result = msp_complex_exp(msp_complex_mul(loga, x));
    msp_logger(MSP_COMPLEX, "msp_complex_pow", "z = a^x, %c = %c ^ %c", result,a, x);
    return result;
}

msp_complex msp_complex_pow_real(msp_complex a, double x) {
    msp_complex z;
    z.real = x;
    z.imag = 0;
    msp_complex result = msp_complex_pow(a, z);
    msp_logger(MSP_COMPLEX, "msp_complex_pow", "z = a^x, %c = %c ^ %c", result,a, x);
    return result;
}

msp_complex msp_complex_exp(msp_complex z) {
    if(z.real == 0 && z.imag == 0) {
        msp_complex result = msp_complex_create(1,0);
        msp_logger(MSP_COMPLEX, "msp_complex_exp", "z = exp(a), %c = exp(%c)", result, z);
        return result;
    }
    msp_complex result;
    result.real = exp(z.real)*cos(z.imag);
    result.imag = exp(z.real) * sin(z.imag);
    msp_logger(MSP_COMPLEX, "msp_complex_exp", "z = exp(a), %c = exp(%c)", result, z);
    return result;
}

msp_complex msp_complex_log(msp_complex z) {
    msp_complex result;
    double mod = msp_complex_get_module(z);
    double arg = msp_complex_get_arg(z);
    result.real = log(mod);
    result.imag = arg;
    msp_logger(MSP_COMPLEX, "msp_complex_log", "z = log(a), %c = log(%c)", result, z);
    return result;
}

msp_complex msp_complex_log10(msp_complex z) {
    msp_complex result = msp_complex_log(z);
    msp_complex log10;
    log10.imag = 0;
    log10.real = LOG10;
    result = msp_complex_div(result, log10);
    msp_logger(MSP_COMPLEX, "msp_complex_log10", "z = log10(a), %c = log10(%c)", result, z);
    return result;
}

msp_complex msp_complex_log_b(msp_complex z, msp_complex b) {
    if(b.real == 0 && b.imag == 0) {
        perror("cant log when b = 0");
        msp_logger(MSP_COMPLEX, "msp_complex_log10", "error b is equal to 0");
        return msp_complex_create(0,0);
    }
    msp_complex result;
    msp_complex logb;
    logb = msp_complex_log(b);
    result = msp_complex_log(z);
    result = msp_complex_div(result, logb);
    msp_logger(MSP_COMPLEX, "msp_complex_log10", "z = log10(a), %c = log10(%c)", result, z);
    return result;
}

//Trygonometry

msp_complex msp_complex_sin(msp_complex z) {
    msp_complex result;
    msp_complex i;
    i.real = 0;
    i.imag = 1;
    msp_complex e_iz, e_miz;
    e_iz = msp_complex_exp(msp_complex_mul(z,i));
    e_miz = msp_complex_exp(msp_complex_negativ(msp_complex_mul(z,i)));

    i.imag = 2;
    result = msp_complex_div(msp_complex_sub(e_iz, e_miz), i);
    msp_logger(MSP_COMPLEX, "msp_complex_sin", "z = sin(a), %c = sin(%c)", result, z);
    return result;
}

msp_complex msp_complex_cos(msp_complex z) {
    msp_complex result;
    msp_complex i;
    i.real = 0;
    i.imag = 1;
    msp_complex e_iz, e_miz;
    e_iz = msp_complex_exp(msp_complex_mul(z,i));
    e_miz = msp_complex_exp(msp_complex_negativ(msp_complex_mul(z,i)));
    result = msp_complex_div_real(msp_complex_add(e_iz, e_miz), 2);
    msp_logger(MSP_COMPLEX, "msp_complex_cos", "z = cos(a), %c = cos(%c)", result, z);
    return result;
}

msp_complex msp_complex_tan(msp_complex z) {
    msp_complex cos = msp_complex_cos(z);
    if(cos.real == 0 && cos.imag == 0) {
        perror("tan is infinity");
        msp_logger(MSP_COMPLEX, "msp_complex_tan", "tan is infinity");
        return msp_complex_create(0,0);
    }
    msp_complex result = msp_complex_div(msp_complex_sin(z), cos);
    msp_logger(MSP_COMPLEX, "msp_complex_tan", "z = tan(a), %c = tan(%c)", result, z);
    return result;
}

msp_complex msp_complex_cot(msp_complex z) {
    msp_complex sin = msp_complex_sin(z);
    if(sin.real == 0 && sin.imag == 0) {
        perror("ctan is infinity");
        msp_logger(MSP_COMPLEX, "msp_complex_cot", "cot is infinity");
        return msp_complex_create(0,0);
    }
    msp_complex result = msp_complex_div(msp_complex_cos(z), sin);
    msp_logger(MSP_COMPLEX, "msp_complex_cot", "z = cot(a), %c = cot(%c)", result, z);
    return result;
}

msp_complex msp_complex_sec(msp_complex z) {
    msp_complex sin = msp_complex_sin(z);
    if(sin. real == 0 && sin.imag == 0) {
        perror("sin is infinity");
        msp_logger(MSP_COMPLEX, "msp_complex_sin", "sin is infinity");
        return msp_complex_create(0,0);
    }
    else {
        msp_complex result = msp_complex_div(msp_complex_create(1, 0), sin);
        msp_logger(MSP_COMPLEX, "msp_complex_sec", "z = sec(a), %c = sec(%c)", result, z);
        return result;
    }
}

msp_complex msp_complex_csc(msp_complex z) {
    msp_complex csc = msp_complex_cos(z);
    if(csc. real == 0 && csc.imag == 0) {
        perror("csc is infinity");
        msp_logger(MSP_COMPLEX, "msp_complex_csc", "csc is infinity");
        return msp_complex_create(0,0);
    }
    else {
        msp_complex result = msp_complex_div(msp_complex_create(1, 0), csc);
        msp_logger(MSP_COMPLEX, "msp_complex_csc", "z = csc(a), %c = csc(%c)", result, z);
        return result;
    }
}

int msp_complex_iszero (msp_complex z) {
    if(z.imag == 0 && z.real == 0) {
        return 1;
    }
    else {
        return 0;
    }
}