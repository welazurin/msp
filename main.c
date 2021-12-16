#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include "complex.h"
int main() {

    msp_complex z = msp_complex_create(3 ,4);
    msp_complex z2 = msp_complex_sqrt_real(-5);
    printf("%f %f\n", z2.real, z2.imag);
    z2 = msp_complex_mul(z2, z2);
    printf("%f %f", z2.real, z2.imag);





    return 0;
}
