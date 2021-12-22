//
// Created by programowanie on 21.12.2021.
//

#include "msp_tab_vector.h"
msp_tab_vector* msp_tab_vector_create() {
    msp_tab_vector* tab = malloc(sizeof(*tab));
    if(tab == NULL) {
        perror("cant allocate;");
        return NULL;
    }
    else {
        tab->size = 0;
    }
    return tab;
}
msp_tab_vector* msp_tab_vector_create_with_size(size_t size) {
    msp_tab_vector* tab = malloc(sizeof(*tab));
    if(tab == NULL) {
        perror("cant allocate;");
        return NULL;
    }
    else {
        tab->size = size;
        tab->data = malloc(sizeof(msp_vector*) * size);
        if(tab->data == NULL) {
            perror("cant allocate");
            return NULL;
        }
    }
    return tab;
}
void msp_tab_vector_realloc(msp_tab_vector* tab, size_t size) {
    msp_vector** temp;
    temp = tab->data;
    temp = realloc(tab->data, sizeof(msp_vector)*size);
    if(temp == NULL) {
        abort();
        return;
    }
    else {
        tab->data = temp;
    }
}
void msp_tab_vector_push_back(msp_tab_vector* tab, msp_vector* vector) {
    msp_tab_vector_realloc(tab, tab->size+1);
    tab->size += 1;
    tab->data[tab->size-1] = vector;
}
msp_vector* msp_tab_vector_pop(msp_tab_vector* tab) {
    msp_vector* result = tab->data[tab->size-1];
    msp_tab_vector_realloc(tab, tab->size-1);
    tab->size -= 1;
    return result;
}
msp_vector* msp_tab_vector_get(msp_tab_vector* tab, size_t i) {
    msp_vector* result = tab->data[i];
    for(int j = i; j < tab->size-2; j++) {
        tab->data[j] = tab->data[j+1];
    }
    msp_tab_vector_realloc(tab, tab->size-1);
    tab->size -=1;
    return result;
}