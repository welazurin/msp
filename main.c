#include <stdio.h>
#include "msp_include/msp_vector/msp_vector.h"
#include "msp_include/msp_matrix/msp_matrix.h"
#include "msp_include/msp_complex/msp_complex.h"
#include "msp_include/msp_logger/msp_log.h"

int main() {
    msp_log_activate();
    msp_complex z;
    z.real = 3;
    z.imag = 2;
    msp_complex z2;
    z2.real = 4;
    z2.imag = -1;
    msp_complex z3 = msp_complex_pow(z, z2);
    printf("%f %f", z3.real, z3.imag);
    return 0;
}
