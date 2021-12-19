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
    msp_complex z2 = msp_complex_cos(z);
    printf("%f %f", z2.real, z2.imag);
    return 0;
}
