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

void card_destroy(card* n) {
    free(n);
}

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

void cardList_teardown(card *head) {
    card *next;
    while(head!=NULL) {
        next=head->next;
        card_destroy(head);
        head=next;
    }
}

card *cardList_get(card* head, int num) {
    for(int i=0; i<num; i++) head=head->next;
    return head;
}

void cardList_unshift(card** head, card* new) {
    new->next=*head;
    *head=new;
}

card* cardList_shift(card** head) {
    card* output=*head;
    *head=(*head)->next;
    return output;
}

card* cardList_removeAfter(card* head, int pos) {
    head=cardList_get(head,pos);

    card* output=head->next;
    head->next=head->next->next;

    return output;
}

card* cardList_last(card* head) {
    while(head->next!=NULL) {
        head=head->next;
    }
    return head; 
}

int cardList_length(card* list) {
    int count=0;
    while(list!=NULL) {
        list=list->next;
        count++;
    }
    return count;
}

void cardList_print(card* list) {
    while(list!=NULL) {
        card_print(list);
        printf(" ");
        list=list->next;
    }
    printf("\n");
}

void cardList_shuffle(card** head, int iters) {
    int head_length=cardList_length(*head);
    for(int i=0; i<iters; i++) {
        int randNum=randBetween(0,head_length-1);
        cardList_unshift(head,cardList_removeAfter(*head,randNum));
    }
}

void cardList_concat(card** head, card** tail) {
    if(*head==NULL) {
        *head=*tail;
    } else {
        cardList_last(*head)->next=*tail;
        *tail=NULL;
    }
}