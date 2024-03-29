#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "utils.c"
#include "card.c"
#include "handutils.c"
#include "player.c"

#define strBuffer_Length 100

void checkStatFile(const char *filename) {
    FILE* fileRead=fopen(filename,"r");
    if(fileRead==NULL) {
        FILE* fileWrite=fopen(filename,"w");

        fprintf(fileWrite,"Game Seed, Player Name, Total Rounds, Rounds Won, Rounds Lost, ");
        for(int i=1; i<9; i++)
            fprintf(fileWrite,"Type %s, ",rankNames[i]);

        fprintf(fileWrite,"\n");

        fclose(fileWrite);
    } else {
        fclose(fileRead);
    }
}

void printPrelude(char* playerName) {
    printRepeatGroup('$',9,5);

    printRepeat(' ',10);
    printRepeatGroup('$',9,3);

    printf("%s,\n",playerName);
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
}

void queryReplacements(int cardsToReplace[5]) {
    for(int i=0; i<5; i++) cardsToReplace[i]=1;
    int cardsRemaining=5;

    int pickedCard;
    while(cardsRemaining) {
        printf("Pick cards (between 1-5) to hold (-1 to stop): ");
        scanf("%d",&pickedCard); clearSTDIN();

        if(pickedCard==-1) break;

        if(pickedCard<1 || pickedCard>5) continue;

        if(!cardsToReplace[pickedCard-1]) {
            cardsToReplace[pickedCard-1]=0;
            cardsRemaining--;
        }
    }
}

//#define AUTOPLAY

int main(int argc, char** argv) {
    const char dataFileName[]="gamestats.csv";

    card* deck=NULL;
    card* discardPile=NULL;

    for(int i=0; i<52; i++)
        cardList_unshift(&deck,card_create(i));

    int randSeed;

    if(argc<2) randSeed=time(0);
    else randSeed=atoi(argv[1]);

    srand(randSeed);

    printf("Enter your name: ");

    char strBuffer[strBuffer_Length];
    scanLine(strBuffer,strBuffer_Length);

    Player* player=Player_create(strBuffer);

    printPrelude(player->name);

    int roundTotalCounts=0;
    int roundRanksCounts[9];
    for(int i=0; i<9; i++) roundRanksCounts[i]=0;

    checkStatFile(dataFileName);

    while(1) {
        cardList_concat(&deck,&discardPile);
        cardList_shuffle(&deck,10000);

        Player_printMoney(player);
        printf("\n");

        #ifdef AUTOPLAY
            int bet=max_ints((player->money/5),min_ints(10,player->money));
        #else
            int bet=Player_queryBet(player);
        #endif

        if(bet==-1) break;

        printf("\nYou bet %d coins\n\n",bet);

        dealCards(&player->hand,&deck,5);

        Player_printHandLarge(player);

        int cardsToHold[5];
        #ifdef AUTOPLAY
            findCardsShouldHold(player->hand,cardsToHold);
        #else
            char* suggestion=createHandSuggestionStr(player->hand);
            printf("::|| %s\n",suggestion);
            free(suggestion);
            queryReplacements(cardsToHold);
        #endif

        printf("\n");
    
        Player_replaceCards(player,&deck,&discardPile,cardsToHold);

        Player_printHandLarge(player);

        int roundRank=getHandType(player->hand);

        roundTotalCounts++;
        roundRanksCounts[roundRank]++;

        long long int coinsToAdd=rankRewards[roundRank]*bet;

        player->money+=coinsToAdd;

        printf(
            "You %s %I64d coins and you now have %I64d coins\n\n",
            (coinsToAdd<0) ? "LOST" : "WON",
            (coinsToAdd<0) ? -coinsToAdd : coinsToAdd,
            player->money
        );

        cardList_concat(&discardPile,&(player->hand));

        if(player->money<=0) {
            printf("You lost all your coins. Game over!\n");
            break;
        }

        printf("Hit Enter key to continue: ");
        #ifndef AUTOPLAY
            clearSTDIN();
        #endif
        printf("\n");
    }

    //Exit procedure
    FILE* statFileAppend=fopen(dataFileName,"a");

    fprintf(statFileAppend,
        "%d, %s, %d, %d, ",
        randSeed,
        player->name,
        roundTotalCounts,
        roundTotalCounts-roundRanksCounts[0]
    );

    for(int i=0; i<9; i++)
        fprintf(statFileAppend,"%d, ",roundRanksCounts[i]);

    fprintf(statFileAppend,"\n");

    fclose(statFileAppend);

    printf("Goodbye %s\n",player->name);

    cardList_teardown(deck);
    cardList_teardown(discardPile);
    Player_destory(player);

    return EXIT_SUCCESS;
}