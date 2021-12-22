//
// Created by programowanie on 20.12.2021.
//

#include "msp_interface.h"
msp_interface* msp_interface_create() {
    msp_interface* interface;
    interface = malloc(sizeof(*interface));
    if(interface == NULL) {
        perror("cant allocate for interface");
        return NULL;
    }
    //Definition on interface
    interface->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    interface->container = gtk_fixed_new();
    interface->commandLine = gtk_entry_new();
    interface->textView = gtk_text_view_new();
    //window options
    gtk_window_set_default_size(GTK_WINDOW(interface->window), 800,600);

    //text view
    gtk_text_view_set_editable(GTK_TEXT_VIEW(interface->textView), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(interface->textView), FALSE);



    gtk_entry_set_max_length (GTK_ENTRY (interface->commandLine), 50);
    interface->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(interface->textView));
    //adding container
    gtk_container_add(GTK_CONTAINER(interface->window), interface->container );
    gtk_fixed_put(GTK_FIXED(interface->container), interface->commandLine, 10, 300);
    gtk_fixed_put(GTK_FIXED(interface->container), interface->textView, 10, 10);
    return interface;

}