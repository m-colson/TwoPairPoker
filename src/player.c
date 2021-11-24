#pragma once

#include <stdio.h>
#include <string.h>

#include "card.c"
#include "utils.c"
#include "handutils.c"

typedef struct Player_struct {
    char *name;
    long long int money;
    card *hand;
} Player;

/**
 * @brief returns a new player with a new 
 * 
 * @param nameBuf 
 */

Player* Player_create(char nameBuf[]) {
    Player* output=(Player*)malloc(sizeof(Player));

    output->name=(char*)malloc(sizeof(char)*(strlen(nameBuf)+1));
    strcpy(output->name,nameBuf);

    output->money=100;

    return output;
}

void Player_destory(Player *p) {
    free(p->name);
    cardList_teardown(p->hand);
    free(p);
}

void Player_printMoney(Player *p) {
    printRepeatGroup('*',9,5);
    printRepeat('*',5);
    printf(" %s, you have %I64d coins\t    ",p->name,p->money);
    printRepeat('*',5);
    printf("\n");
    printRepeatGroup('*',9,5);
}

int Player_queryBet(Player *p) {
    int output;
    do {
        printf("Place your bet (1-%I64d) coins (-1 to quit playing): ",p->money);
        scanf("%d",&output); clearSTDIN();
        if(output==-1) break;
    } while(output<1 || output>p->money);

    return output;
}

void Player_printHand(Player *p) {
    printf("%s's hand: (%s)\n",p->name,rankNames[getHandType(p->hand)]);
    cardList_print(p->hand);
}

void Player_printHandLarge(Player *p) {
    printf("%s's hand: (%s)\n",p->name,rankNames[getHandType(p->hand)]);

    int cards_length=cardList_length(p->hand);

    for(int i=0; i<cards_length; i++) {
        printRepeat('-',7);
        printRepeat(' ',5);
    }
    printf("\n");

    card *temp=p->hand;

    for(int i=0; i<cards_length; i++) {
        printf("|");
        card_print(temp);
        printRepeat(' ',temp->value==10 ? 2 : 3);
        printf("|");
        printRepeat(' ',5);
        temp=temp->next;
    }
    printf("\n");

    for(int i=0; i<cards_length; i++) {
        printf("|");
        printRepeat(' ',5);
        printf("|");
        printRepeat(' ',5);
    }
    printf("\n");

    temp=p->hand;

    for(int i=0; i<cards_length; i++) {
        printf("|");
        printRepeat(' ',temp->value==10 ? 2 : 3);
        card_print(temp);
        printf("|");
        printRepeat(' ',5);
        temp=temp->next;
    }
    printf("\n");

    for(int i=0; i<cards_length; i++) {
        printRepeat('-',7);
        printRepeat(' ',5);
    }
    printf("\n");

}

void Player_replaceCards(Player *p,card **deck,card **discardPile,int cardToHold[5]) {
    for(int i=0; i<5; i++)
        if(!cardToHold[i]) replaceCard(&p->hand,deck,discardPile,i);
}