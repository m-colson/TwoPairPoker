#include <stdio.h>
#include <stdlib.h>

#include "../src/handutils.c"

#define assert(c,msg) if(!(c)) {printf(msg" failed\n");exit(EXIT_FAILURE);} else {printf(msg" passed\n");}
 
card* createHand(const int arr[5]) {
    card* output=NULL;

    for(int i=0; i<5; i++)
        output=cardList_unshift(output,card_create(arr[i]-1));

    return output;
}

void destroyHand(card* c) {
    while(c!=NULL) {
        card* temp=c->next;
        card_destroy(c);
        c=temp;
    }
}

int main() {
    {
        const int cardFrom[5]={3,4,5,6,7};
        card* temp=createHand(cardFrom);
        
        assert(hasFlush(temp)=='c',"Simple flush positive");

        destroyHand(temp);
    }
    {
        const int cardFrom[5]={3,15,5,6,7};
        card* temp=createHand(cardFrom);

        assert(hasFlush(temp)==0,"Simple flush negative");

        destroyHand(temp);
    }
    {
        const int cardFrom[5]={3,3+13,5,7,3+(3*13)};
        card* temp=createHand(cardFrom);
        int counts[13];
        generateCounts(temp,counts);

        assert(hasThreeOfKind(counts),"Three of kind positive");

        destroyHand(temp);
    }
    {
        const int cardFrom[5]={3,17,5,7,3+(3*13)};
        card* temp=createHand(cardFrom);
        int counts[13];
        generateCounts(temp,counts);

        assert(hasThreeOfKind(counts)==0,"Three of kind negative");

        destroyHand(temp);
    }
    {
        const int cardFrom[5]={6,5,7+13,3+26,4+(3*13)};
        card* temp=createHand(cardFrom);
        int counts[13];
        generateCounts(temp,counts);

        assert(hasStraight(counts)==7,"Straight positive");

        destroyHand(temp);
    }
    {
        const int cardFrom[5]={9,5,7+13,4+26,4+(3*13)};
        card* temp=createHand(cardFrom);
        int counts[13];
        generateCounts(temp,counts);

        assert(hasStraight(counts)==0,"Straight negative");

        destroyHand(temp);
    }


    printf("\nAll tests passed\n");
}

