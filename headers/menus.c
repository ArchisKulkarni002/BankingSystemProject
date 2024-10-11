#include "menus.h"
#include<stdio.h>
#include <ctype.h>

void print_heading(char* heading){
    // make the heading to upper case
    int counter=0;
    printf("|  ");
    for (int i = 0; heading[i] != '\0'; i++) {
        printf("%c", toupper((unsigned char)heading[i]));
        counter++;
    }
    
    printf("  |\n");
    print_underline(counter+6);
}

void print_subheading(char* heading){
    printf("|  %s  |\n", heading);
}


void print_underline(int counter){
    for (int i = 0; i<counter; i++) {
        printf("-");
    }
    
    printf("\n\n");
}