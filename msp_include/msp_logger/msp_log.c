//
// Created by programowanie on 19.12.2021.
//

//
// Created by programowanie on 16.12.2021.
//

#include "msp_log.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "../msp_matrix/msp_matrix.h"
#include "../msp_complex/msp_complex.h"
#include "../msp_poly/msp_poly.h"
void msp_log_activate() {
    FILE* file;
    file = fopen("logger.txt", "w");
    fclose(file);
}

void msp_logger(const char* namefile, const char* fun, const char* text, ...) {
    FILE* file;
    file = fopen("logger.txt", "a");
    time_t time2;
    time(&time2);
    struct tm *data = localtime(&time2);
    int year = data->tm_year+1900;
    int month = data->tm_mon+1;
    int day = data->tm_mday;
    int hour = data->tm_hour;
    int min = data->tm_min;
    int sec = data->tm_sec;
    fprintf(file, "%0d-%0d-%0d %0d-%0d-%0d: ", year, month, day, hour, min, sec);
    fprintf(file, "In %s: in function %s ", namefile, fun);
    va_list ap;
    va_start(ap, text);
    int i =0;
    while(1) {

        if(text[i] == '\0') {
            fprintf(file, "\n");
            fclose(file);
            return;
        }
        else {
            if(text[i] == '%') {
                i++;
                if(text[i] == 'd') {
                    int x = va_arg(ap, int);
                    fprintf(file, "%d", x);
                }
                else if(text[i] == 'f') {
                    double y = va_arg(ap, double);
                    fprintf(file, "%f", y);
                }
                else if(text[i] == 'm') {
                    msp_matrix* temp = va_arg(ap, msp_matrix*);
                    for(int k = 0; k < temp->n; k++) {
                        for(int l = 0; l < temp->m; l++) {
                            fprintf(file, "%f ", temp->data[k][l]);
                        }
                        fprintf(file, "\n");
                    }
                    //TODO MATRIX

                }
                else if(text[i] == 'v') {
                    msp_vector* temp = va_arg(ap, msp_vector*);
                    for(int k = 0; k < temp->size; k++) {
                        fprintf(file, "%f ", temp->data[k]);
                    }
                    //TODO VECTOR
                }
                else if(text[i] == 'c') {
                    msp_complex z = va_arg(ap, msp_complex);
                    fprintf(file,"(%f)+(%f)i", z.real, z.imag);
                }
                else if(text[i] == 'p') {
                    double* f = va_arg(ap, double*);
                    fprintf(file, "%p", f);
                }
                else if(text[i] == 's') {
                    msp_poly* poly = va_arg(ap, msp_poly*);
                    msp_poly_fprintf(file, poly);
                }
                else{
                    perror("error");
                }
            }
            else {
                fprintf(file, "%c", text[i]);
            }
            i++;

        }
    }



}