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
        cardList_unshift(hand,cardList_shift(deck));
}

/**
 * @brief Replaces card with top card on deck at zero indexed positon in hand
 * 
 * @param **hand hand to use
 * @param **deck deck to draw from
 * @param pos zero indexed position to replace
 */
void replaceCard(card **hand, card** deck, card** discardPile,int pos) {
    card* prevCard=NULL;
    card* oldCard=*hand;
    for(int i=0; i<pos; i++) {
        prevCard=oldCard;
        oldCard=oldCard->next;
    }

    card* newCard=cardList_shift(deck);

    newCard->next=oldCard->next;
    
    cardList_unshift(discardPile,oldCard);
    
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
 * @return suit type if cards are flush otherwise 0
 */
char hasFlush(card *hand) {
    char cmpFace=hand->face;

    for(int i=0; i<5; i++) {
        if(cmpFace!=hand->face) return 0;
        hand=hand->next;
    }

    return cmpFace;
}

void generateCounts(card *hand, int counts[13]) {
    for(int i=0; i<13; i++) counts[i]=0;

    while(hand!=NULL) {
        counts[hand->value-1]++;
        hand=hand->next;
    }
}

int hasStraight(int counts[13]) {
    int consecCounter=0;
    for(int i=0; i<14; i++) {
        if(counts[i%13]) {
            consecCounter++;
        } else {
            consecCounter=0;
        }
        if(consecCounter==5) return i+1;
    }

    return 0;
}

int hasThreeOfKind(int counts[13]) {
    for(int i=0; i<13; i++)
        if(counts[i]==3) return i+1;

    return 0;
}

int hasFourOfKind(int counts[13]) {
    for(int i=0; i<13; i++)
        if(counts[i]==4) return i+1;

    return 0;
}

int hasTwoPair(int counts[13]) {
    int valueOf2first=0;
    int valueOf2second=0;

    for(int i=0; i<13; i++) {
        if(counts[i]==2) {
            if(valueOf2first) {
                valueOf2second=i+1;
            } else {
                valueOf2first=i+1;
            }
        }
    }

    if(valueOf2first&&valueOf2second) return 1;

    return 0;
}

int hasFullHouse(int counts[13]) {
    int valueOf3=0;
    int valueOf2=0;

    for(int i=0; i<13; i++) {
        if(counts[i]==3) valueOf3=i+1;
        if(counts[i]==2) valueOf2=i+1;
    }

    if(valueOf2&&valueOf3) return 1;

    return 0;
}

const char* rankNames[]={
    "None",
    "Two Pair",
    "Tree of a Kind",
    "Straight",
    "Flush",
    "Full House",
    "Four of a Kind",
    "Straight Flush",
    "Royal Flush"
};

const char* rankExamples[]={
    "  ■  ■  ■  ■  ■",
    " K♠ K♦ 6♦ 6♥  ■",
    " 9♠ 9♣ 9♦  ■  ■",
    " 4■ 5■ 6■ 7■ 8■",
    " ■♣ ■♣ ■♣ ■♣ ■♣",
    " 9♦ 9♥ 9♠ 3♣ 3♥",
    " 9♠ 9♣ 9♦ 9♥  ■",
    " 2♣ 3♣ 4♣ 5♣ 6♣",
    "10♠ J♠ Q♠ K♠ A♠"
};

const int rankRewards[]={
    -1,
    2,
    4,
    5,
    10,
    25,
    50,
    100,
    250
};

int getHandType(card* hand) {
    int counts[13];
    generateCounts(hand,counts);

    int flushValue=hasFlush(hand);
    int straightValue=hasStraight(counts);

    if(straightValue==14 && flushValue) return 8;
    if(straightValue && flushValue) return 7;
    if(hasFourOfKind(counts)) return 6;
    if(hasFullHouse(counts)) return 5;
    if(flushValue) return 4;
    if(straightValue) return 3;
    if(hasThreeOfKind(counts)) return 2;
    if(hasTwoPair(counts)) return 1;
    return 0;
}

int findCardsShouldHold(card *hand, int cardsShouldHold[5]) {
    for(int i=0; i<5; i++) cardsShouldHold[i]=0;
    int cardsHoldAmount=0;

    int counts[13];
    generateCounts(hand,counts);

    if(hasStraight(counts) || hasFlush(hand) || hasFullHouse(counts)) {
        for(int i=0; i<5; i++) cardsShouldHold[i]=1;
        return 5;
    }

    card* tempHand;

    for(int c=0; c<13; c++) {
        if(counts[c]<2) continue;
        tempHand=hand;
        for(int i=0; i<5; i++) {
            if(tempHand->value==c+1) {
                cardsShouldHold[i]=1;
                cardsHoldAmount++;
            }
            tempHand=tempHand->next;
        }
    }

   return cardsHoldAmount;
}

char* createHandSuggestionStr(card *hand) {
    int cardsShouldHold[5];

    int cardsHoldAmount=findCardsShouldHold(hand,cardsShouldHold);

    char suggestionBuffer[100];
    char *buildPointer=suggestionBuffer;

    if(cardsHoldAmount==0) {
        strcpy(suggestionBuffer,"No suggestions");
    } else if(cardsHoldAmount==5) {
        strcpy(suggestionBuffer,"Hold All");
    } else {
        buildPointer+=sprintf(buildPointer,"Hold ");
        for(int i=0; i<5; i++) {
            if(cardsShouldHold[i])
                buildPointer+=sprintf(buildPointer,"%d, ",i+1);
        }
    }
    
    char * outputStr=malloc(sizeof(char)*(strlen(suggestionBuffer)+1));
    strcpy(outputStr,suggestionBuffer);
    return outputStr;
}