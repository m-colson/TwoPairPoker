#include <stdio.h>
#include <stdlib.h>

#include "utils.c"
#include "card.c"
#include "handutils.c"

int main(void) {
    card* deck=NULL;

    for(int i=0; i<52; i++) {
        deck=cardList_unshift(deck,card_create(i));
    }

    srand(0);
    deck=cardList_shuffle(deck,1000);

    cardList_print(deck);

    card* hand=NULL;

    dealCards(&hand,&deck,5);

    cardList_print(hand);

    cardList_print(deck);

    replaceCard(&hand,&deck,0);

    cardList_print(hand);

    cardList_print(deck);


    return EXIT_SUCCESS;
}