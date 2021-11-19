#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "utils.c"
#include "card.c"
#include "handutils.c"
#include "player.c"

#define strBuffer_Length 100

int main(int argc, char** argv) {
    card* deck=NULL;
    card* discardPile=NULL;

    for(int i=0; i<52; i++)
        cardList_unshift(&deck,card_create(i));

    if(argc<2) srand(time(0));
    else srand(atoi(argv[1]));

    cardList_shuffle(&deck,10000);

    printf("Enter your name: ");

    char strBuffer[strBuffer_Length];
    scanLine(strBuffer,strBuffer_Length);

    Player* player=Player_create(strBuffer);

    printRepeatGroup('$',9,5);

    printRepeat(' ',10);
    printRepeatGroup('$',9,3);

    printf("%s,\n",player->name);
    printf("\tLet's player Two pairs or Better\n");

    printRepeat(' ',10);
    printRepeatGroup('$',9,3);

    printRepeatGroup('$',9,5);

    printRepeat('$',9);
    printRepeat(' ',5);
    printf("Rank of winning");
    printRepeat(' ',11);
    printRepeat('$',9);
    printf("\n");
    printRepeat('\t',5);
    printf("Pay\n");

    for(int i=8; i>0; i--) {
        printf("%s",rankNames[i]);
        int stringPadding=2-(strlen(rankNames[i]))/8;
        for(int t=0; t<stringPadding; t++) printf("\t");

        printf("%s",rankExamples[i]);

        printf("\t\t%d*bet\n",rankRewards[i]);
    }

    printf("\n");

    while(player->money>0) {
        if(cardList_length(deck)<=5) {
            cardList_shuffle(&discardPile,10000);
            cardList_concat(&deck,discardPile);
        }

        Player_printMoney(player);
        printf("\n");

        int bet=Player_queryBet(player);

        printf("\nYou bet %d coins\n\n",bet);

        dealCards(&player->hand,&deck,5);

        Player_printHandLarge(player);

        Player_queryAndReplaceCards(player,&deck);
        printf("\n");

        Player_printHandLarge(player);

        Player_updateMoneyAndPrint(player,bet);

        cardList_concat(&discardPile,player->hand);
        player->hand=NULL;

        printf("Hit Enter key to continue: ");
        scanf(""); clearSTDIN();
        printf("\n");         
    }

    Player_destory(player);
    return EXIT_SUCCESS;
}