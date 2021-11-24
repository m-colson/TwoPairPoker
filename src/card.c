#pragma once
#include <stdlib.h>
#include "utils.c"

const char cardSuits[]="cshd";

typedef struct card_s {
    char face;
    int value;
    struct card_s* next;
} card;

card* card_create(int cardValue) {
    card* output=(card*)malloc(sizeof(card));

    output->value=cardValue%13+1;
    output->face=cardSuits[cardValue/13];
    output->next=NULL;
    return output;
}

void card_destroy(card* c) {
    free(c);
}

/**
 * @brief prints a card formatted like a poker card
 * 
 * @param c the card to print 
 */
void card_print(card* c) {
    switch(c->value) {
        case 13:
            printf("K");
            break;
        case 12:
            printf("Q");
            break;
        case 11:
            printf("J");
            break;
        case 1:
            printf("A");
            break;
        default:
            printf("%d",c->value);
            break;
    }
    switch(c->face) {
        #ifdef SUITS
            case 's': printf("♠"); break;
            case 'c': printf("♣"); break;
            case 'h': printf("♥"); break;
            case 'd': printf("♦"); break;
        #else
            case 's': printf("s"); break;
            case 'c': printf("c"); break;
            case 'h': printf("h"); break;
            case 'd': printf("d"); break;
        #endif
        default:
            fprintf(stderr,"Invalid card face\n");
            exit(EXIT_FAILURE);
    }
}

/**
 * @brief destroys all the cards in a card list
 * 
 * @param head the start of the list
 */
void cardList_teardown(card *head) {
    card *next;
    while(head!=NULL) {
        next=head->next;
        card_destroy(head);
        head=next;
    }
}

/**
 * @brief returns a pointer to the numth element in the card list
 * 
 * @param head the start of the list
 * @param num the position to get the card
 */
card *cardList_get(card* head, int num) {
    for(int i=0; i<num; i++) head=head->next;
    return head;
}

/**
 * @brief adds a new element to the front of the card list
 * 
 * @param head a pointer to the start of the list
 * @param new the new element to add
 */
void cardList_unshift(card** head, card* new) {
    new->next=*head;
    *head=new;
}

/**
 * @brief removes and return the first element from a card list
 * 
 * @param head a pointer to the start of the list
 */
card* cardList_shift(card** head) {
    card* output=*head;
    *head=(*head)->next;
    return output;
}

/**
 * @brief removes and returns an element from the array after the position
 * 
 * @param head the start of the list 
 * @param pos the position of the element before the element to remove
 */
card* cardList_removeAfter(card* head, int pos) {
    head=cardList_get(head,pos);

    card* output=head->next;
    head->next=head->next->next;

    return output;
}

/**
 * @brief returns a pointer to the last element in the card list
 * 
 * @param head the start of the card list
 */
card* cardList_last(card* head) {
    while(head->next!=NULL) {
        head=head->next;
    }
    return head; 
}

/**
 * @brief returns the number of elements in the card list
 * 
 * @param list the start of the card list
 */
int cardList_length(card* list) {
    int count=0;
    while(list!=NULL) {
        list=list->next;
        count++;
    }
    return count;
}

/**
 * @brief prints the elements of a card list with a newline
 * 
 * @param list the start of the card list
 */
void cardList_print(card* list) {
    while(list!=NULL) {
        card_print(list);
        printf(" ");
        list=list->next;
    }
    printf("\n");
}

/**
 * @brief shuffles a card list by removing random elements from list add adding them to the front
 * 
 * @param head a pointer to the start of the list
 * @param iters the amount of times to repeat the procedure
 */
void cardList_shuffle(card** head, int iters) {
    int head_length=cardList_length(*head);
    for(int i=0; i<iters; i++) {
        int randNum=randBetween(0,head_length-1);
        cardList_unshift(head,cardList_removeAfter(*head,randNum));
    }
}

/**
 * @brief adds tail to the end of head and makes tail null
 */
void cardList_concat(card** head, card** tail) {
    if(*head==NULL) {
        *head=*tail;
    } else {
        cardList_last(*head)->next=*tail;
    }
    *tail=NULL;
}