#pragma once

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

int randBetween(int min,int max) {
    return (rand()%(max-min))+min;
}

void scanLine(char buf[],int len) {
    fgets(buf,len,stdin);
    if(buf[strlen(buf)-1]=='\n')
        buf[strlen(buf)-1]='\0';
}

void clearSTDIN() {
    char garbage;
    do scanf("%c",&garbage); while(garbage!='\n');
}

void printRepeat(char c, int num) {
    for(int i=0; i<num; i++) printf("%c",c);
}

void printRepeatGroup(char c, int groupsize, int groups) {
    for(int i=0; i<groups; i++) {
        printRepeat(c,groupsize);
        printf(" ");
    }
    printf("\n");
}

int max_ints(int a,int b) {
    return a>b ? a : b;
}

int min_ints(int a,int b) {
    return a<b ? a : b;
}