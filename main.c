#include <stdio.h>
//#include /<gtk/gtk.h>
#include "msp_include/msp_vector/msp_vector.h"
#include "msp_include/msp_matrix/msp_matrix.h"
#include "msp_include/msp_complex/msp_complex.h"
#include "msp_include/msp_logger/msp_log.h"
#include "msp_include/msp_poly/msp_poly.h"
#include "msp_include/msp_interface/msp_interface.h"
#include "msp_include/msp_interface/msp_command.h"
#include "msp_include/msp_data/msp_tab_vector.h"

int main(int argc, char* argv[]) {
    /*gtk_init(&argc, &argv);
    msp_interface * interface = msp_interface_create();
    gtk_widget_show_all(interface->window);
    g_signal_connect(G_OBJECT(interface->commandLine), "activate", G_CALLBACK(command), interface);
    gtk_main();*/
    double data[3];
    msp_poly* poly = msp_poly_allocate(3);
    for(int i = 0; i < 3;i ++) {
        data[i] = i+3;
    }
    data[2] = -data[2];
    msp_poly_set(poly, data , 3);
    msp_vector_complex* result = msp_poly_roots(poly);
    msp_poly_fprintf(stdout, poly);
    msp_vector_complex_fprintf(stdout, "%f", result);


    return 0;
}
