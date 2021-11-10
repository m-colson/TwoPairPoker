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
    printf("%d%c ",c->value,c->face);
}

card* cardList_unshift(card* head, card* new) {
    new->next=head;
    return new;
}

card* cardList_shift(card** head) {
    card* output=*head;
    *head=(*head)->next;
    return output;
}

void cardList_insertAfter(card* head, card* new, int pos) {
    for(int i=0; i<pos; i++) head=head->next;

    new->next=head->next;
    head->next=new;
}

card* cardList_deleteAfter(card* head, int pos) {
    for(int i=0; i<pos; i++) head=head->next;

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
    int count;
    while(list!=NULL) {
        list=list->next;
        count++;
    }
    return count;
}

void cardList_print(card* list) {
    while(list!=NULL) {
        card_print(list);
        list=list->next;
    }
    printf("\n");
}

void cardList_push(card* head,card *new) {
    card* last=cardList_last(head);
    last->next=new;
}

card* cardList_shuffle(card* head, int iters) {
    int head_length=cardList_length(head);
    for(int i=0; i<iters; i++) {
        int randNum=randBetween(0,head_length-1);
        head=cardList_unshift(head,cardList_deleteAfter(head,randNum));
    }
    return head;
}