//
// Created by programowanie on 20.12.2021.
//

#include "msp_command.h"
void command(GtkWidget* widget, msp_interface* entry){
    const gchar* entrytext;
    entrytext = gtk_entry_get_text(GTK_ENTRY(entry->commandLine));

    gtk_text_buffer_set_text(entry->buffer, entrytext, -1);

}