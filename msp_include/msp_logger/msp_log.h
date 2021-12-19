//
// Created by programowanie on 19.12.2021.
//

#ifndef MSP_LOG_H
#define MSP_LOG_H
#include <stdio.h>
#include <time.h>
#include "../msp_poly/msp_poly.h"
void msp_log_activate();
void msp_logger(const char* file, const char* fun, const char* text, ...);


#endif //MSP_LOG_H
