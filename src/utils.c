#pragma once

#include <stdio.h>
#include <string.h>

/**
 * @brief returns a random number between min and max
 * 
 * @param min minimum return value (inclusive)
 * @param max maximum return value (exclusive)
 */
int randBetween(int min,int max) {
    return (rand()%(max-min))+min;
}

/**
 * @brief scans a line from stdin and stores in buf without a newline
 * 
 * @param buf the buffer to store the line
 * @param len the maximum size of the buffer
 */
void scanLine(char buf[],int len) {
    fgets(buf,len,stdin);
    if(buf[strlen(buf)-1]=='\n')
        buf[strlen(buf)-1]='\0';
}
/**
 * @brief removes characters from stdin until it reaches a newline
 */
void clearSTDIN() {
    char garbage;
    do scanf("%c",&garbage); while(garbage!='\n');
}

/**
 * @brief prints a character a certain number of times
 * 
 * @param c the character
 * @param num the amount of times to repeat the character
 */
void printRepeat(char c, int num) {
    for(int i=0; i<num; i++) printf("%c",c);
}

/**
 * @brief prints groups of repeated characters seperated by spaces 
 * 
 * @param c the character
 * @param groupsize the size of the groups
 * @param groups the amount of groups
 */
void printRepeatGroup(char c, int groupsize, int groups) {
    for(int i=0; i<groups; i++) {
        printRepeat(c,groupsize);
        printf(" ");
    }
    printf("\n");
}

/**
 * @brief returns the maximum of a and b
 */
int max_ints(int a,int b) {
    return a>b ? a : b;
}

/**
 * @brief returns the minimum of a and b
 */
int min_ints(int a,int b) {
    return a<b ? a : b;
}