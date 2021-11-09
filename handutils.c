#pragma once
#include "card.c"

/**
 * @brief Deals a certain amount of cards to hand from top of deck
 * 
 * @param **hand hand to use
 * @param **deck deck to draw from
 * @param num number of cards to deal
 */
void dealCards(card** hand, card** deck, int num) {
    for(int i=0; i<num; i++) 
        *hand=cardList_unshift(*hand,cardList_shift(deck));
}

/**
 * @brief Replaces card with top card on deck at zero indexed positon in hand
 * 
 * @param **hand hand to use
 * @param **deck deck to draw from
 * @param pos zero indexed position to replace
 */
void replaceCard(card **hand, card** deck, int pos) {
    card* prevCard=NULL;
    card* oldCard=*hand;
    for(int i=0; i<pos; i++) {
        prevCard=oldCard;
        oldCard=oldCard->next;
    }

    card* newCard=cardList_shift(deck);

    newCard->next=oldCard->next;
    
    if(pos==0) {
        *hand=newCard;
    } else {
        prevCard->next=newCard;   
    }
}

/**
 * @brief Tests the first 5 cards of a card list for a flush
 * 
 * @param hand the hand to test
 * @return char if cards are flush returns the suit type otherwise 0
 */
char isFlush(card *hand) {
    char cmpFace=hand->face;

    for(int i=1; i<5; i++) {
        if(cmpFace!=hand->face) return 0;
        hand=hand->next;
    }

    return cmpFace;
}

int isStraight(card *hand) {
    
}

int isThreeOfKind(card *hand) {

}

int isTwoPair(card *hand) {

}

int isFullHouse(card* hand) {

}