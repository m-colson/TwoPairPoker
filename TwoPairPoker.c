#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * @brief names of all ranks in two pair or better poker based on rank number
 */
const char* rankNames[] = {
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

/**
 * @brief examples of all ranks in two pair or better poker based on rank number
 */
const char* rankExamples[] = {
    "  \xfe  \xfe  \xfe  \xfe  \xfe",
    " K\x06 K\x04 6\x04 6\x03  \xfe",
    " 9\x06 9\x05 9\x04  \xfe  \xfe",
    " 4\xfe 5\xfe 6\xfe 7\xfe 8\xfe",
    " \xfe\x05 \xfe\x05 \xfe\x05 \xfe\x05 \xfe\x05",
    " 9\x04 9\x03 9\x06 3\x05 3\x03",
    " 9\x06 9\x05 9\x04 9\x03  \xfe",
    " 2\x05 3\x05 4\x05 5\x05 6\x05",
    "10\x06 J\x06 Q\x06 K\x06 A\x06"
};

/**
 * @brief rewards of all ranks in two pair or better poker based on rank number
 */
const int rankRewards[] = {
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

/**
 * @brief returns a random number between min and max
 *
 * @param min minimum return value (inclusive)
 * @param max maximum return value (exclusive)
 */
int randBetween(int min, int max) {
    return (rand() % (max - min)) + min;
}

/**
 * @brief scans a line from stdin and stores in buf without a newline
 *
 * @param buf the buffer to store the line
 * @param len the maximum size of the buffer
 */
void scanLine(char buf[], int len) {
    fgets(buf, len, stdin);
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
}
/**
 * @brief removes characters from stdin until it reaches a newline
 */
void clearSTDIN() {
    char garbage;
    do scanf("%c", &garbage); while (garbage != '\n');
}

/**
 * @brief prints a character a certain number of times
 *
 * @param c the character
 * @param num the amount of times to repeat the character
 */
void printRepeat(char c, int num) {
    for (int i = 0; i < num; i++) printf("%c", c);
}

/**
 * @brief prints groups of repeated characters seperated by spaces
 *
 * @param c the character
 * @param groupsize the size of the groups
 * @param groups the amount of groups
 */
void printRepeatGroup(char c, int groupsize, int groups) {
    for (int i = 0; i < groups; i++) {
        printRepeat(c, groupsize);
        printf(" ");
    }
    printf("\n");
}

/**
 * @brief returns the maximum of a and b
 */
int max_ints(int a, int b) {
    return a > b ? a : b;
}

/**
 * @brief returns the minimum of a and b
 */
int min_ints(int a, int b) {
    return a < b ? a : b;
}

void* xmalloc(int bytes) {
    void* output = malloc(bytes);
    if (output == NULL) {
        fprintf(stderr, "FATAL: Out of memory");
        exit(EXIT_FAILURE);
    }
    return output;
}

const char cardSuits[] = "cshd";

typedef struct card_s {
    char face;
    int value;
    struct card_s* next;
} card;

card* card_create(int cardValue) {
    card* output = (card*)xmalloc(sizeof(card));

    output->value = cardValue % 13 + 1;
    output->face = cardSuits[cardValue / 13];
    output->next = NULL;
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
    switch (c->value) {
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
        printf("%d", c->value);
        break;
    }
    switch (c->face) {
#ifdef SUITS
    case 's': printf("\x06"); break;
    case 'c': printf("\x05"); break;
    case 'h': printf("\x03"); break;
    case 'd': printf("\x04"); break;
#else
    case 's': printf("s"); break;
    case 'c': printf("c"); break;
    case 'h': printf("h"); break;
    case 'd': printf("d"); break;
#endif
    default:
        fprintf(stderr, "Invalid card face\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief destroys all the cards in a card list
 *
 * @param head the start of the list
 */
void cardList_teardown(card* head) {
    card* next;
    while (head != NULL) {
        next = head->next;
        card_destroy(head);
        head = next;
    }
}

/**
 * @brief returns a pointer to the numth element in the card list
 *
 * @param head the start of the list
 * @param num the position to get the card
 */
card* cardList_get(card* head, int num) {
    for (int i = 0; i < num; i++) head = head->next;
    return head;
}

/**
 * @brief adds a new element to the front of the card list
 *
 * @param head a pointer to the start of the list
 * @param new the new element to add
 */
void cardList_unshift(card** head, card* new) {
    new->next = *head;
    *head = new;
}

/**
 * @brief removes and return the first element from a card list
 *
 * @param head a pointer to the start of the list
 */
card* cardList_shift(card** head) {
    card* output = *head;
    *head = (*head)->next;
    return output;
}

/**
 * @brief removes and returns an element from the array after the position
 *
 * @param head the start of the list
 * @param pos the position of the element before the element to remove
 */
card* cardList_removeAfter(card* head, int pos) {
    head = cardList_get(head, pos);

    card* output = head->next;
    head->next = head->next->next;

    return output;
}

/**
 * @brief returns a pointer to the last element in the card list
 *
 * @param head the start of the card list
 */
card* cardList_last(card* head) {
    while (head->next != NULL) {
        head = head->next;
    }
    return head;
}

/**
 * @brief returns the number of elements in the card list
 *
 * @param list the start of the card list
 */
int cardList_length(card* list) {
    int count = 0;
    while (list != NULL) {
        list = list->next;
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
    while (list != NULL) {
        card_print(list);
        printf(" ");
        list = list->next;
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
    int head_length = cardList_length(*head);
    for (int i = 0; i < iters; i++) {
        int randNum = randBetween(0, head_length - 1);
        cardList_unshift(head, cardList_removeAfter(*head, randNum));
    }
}

/**
 * @brief adds tail to the end of head and makes tail null
 */
void cardList_concat(card** head, card** tail) {
    if (*head == NULL) {
        *head = *tail;
    }
    else {
        cardList_last(*head)->next = *tail;
    }
    *tail = NULL;
}

/**
 * @brief Deals a certain amount of cards to hand from top of deck
 *
 * @param **hand hand to use
 * @param **deck deck to draw from
 * @param num number of cards to deal
 */
void dealCards(card** hand, card** deck, int num) {
    for (int i = 0; i < num; i++)
        cardList_unshift(hand, cardList_shift(deck));
}

/**
 * @brief Replaces card with top card on deck at zero indexed positon in hand
 *
 * @param **hand hand to use
 * @param **deck deck to draw from
 * @param pos zero indexed position to replace
 */
void replaceCard(card** hand, card** deck, card** discardPile, int pos) {
    card* prevCard = NULL;
    card* oldCard = *hand;
    for (int i = 0; i < pos; i++) {
        prevCard = oldCard;
        oldCard = oldCard->next;
    }

    card* newCard = cardList_shift(deck);

    newCard->next = oldCard->next;

    cardList_unshift(discardPile, oldCard);

    if (pos == 0) {
        *hand = newCard;
    }
    else {
        prevCard->next = newCard;
    }
}

/**
 * @brief Tests the first 5 cards of a card list for a flush
 *
 * @param hand the hand to test
 * @return suit type if cards are flush otherwise 0
 */
char hasFlush(card* hand) {
    char cmpFace = hand->face;

    for (int i = 0; i < 5; i++) {
        if (cmpFace != hand->face) return 0;
        hand = hand->next;
    }

    return cmpFace;
}

/**
 * @brief Generates a array with the counts of the card values in the hand
 *
 * @param hand hand to count the card values in
 * @param counts array to write to
 */
void generateCounts(card* hand, int counts[13]) {
    for (int i = 0; i < 13; i++) counts[i] = 0;

    while (hand != NULL) {
        counts[hand->value - 1]++;
        hand = hand->next;
    }
}

/**
 * @brief checks a count array for a straight
 *
 * @param counts array from generateCounts()
 * @return the value of the highest card in the straight or zero
 */
int hasStraight(int counts[13]) {
    int consecCounter = 0;
    for (int i = 0; i < 14; i++) {
        if (counts[i % 13]) {
            consecCounter++;
        }
        else {
            consecCounter = 0;
        }
        if (consecCounter == 5) return i + 1;
    }

    return 0;
}

/**
 * @brief checks a count array for three of a kind
 *
 * @param counts array from generateCounts()
 * @return the value of the card used in the three of a kind or zero
 */
int hasThreeOfKind(int counts[13]) {
    for (int i = 0; i < 13; i++)
        if (counts[i] == 3) return i + 1;

    return 0;
}

/**
 * @brief checks a count array for four of a kind
 *
 * @param counts array from generateCounts()
 * @return the value of the card used in the four of a kind or zero
 */
int hasFourOfKind(int counts[13]) {
    for (int i = 0; i < 13; i++)
        if (counts[i] == 4) return i + 1;

    return 0;
}

/**
 * @brief checks a count array for two pair
 *
 * @param counts array from generateCounts()
 * @return 1 if has two pair otherwise 0
 */
int hasTwoPair(int counts[13]) {
    int valueOf2first = 0;
    int valueOf2second = 0;

    for (int i = 0; i < 13; i++) {
        if (counts[i] == 2) {
            if (valueOf2first) {
                valueOf2second = i + 1;
            }
            else {
                valueOf2first = i + 1;
            }
        }
    }

    if (valueOf2first && valueOf2second) return 1;

    return 0;
}

/**
 * @brief checks a count array for a full house
 *
 * @param counts array from generateCounts()
 * @return 1 if has a full house otherwise 0
 */
int hasFullHouse(int counts[13]) {
    int valueOf3 = 0;
    int valueOf2 = 0;

    for (int i = 0; i < 13; i++) {
        if (counts[i] == 3) valueOf3 = i + 1;
        if (counts[i] == 2) valueOf2 = i + 1;
    }

    if (valueOf2 && valueOf3) return 1;

    return 0;
}

/**
 * @brief determines the rank number of a hand
 *
 * @param hand the hand to test
 * @return the rank number of the hand
 */
int getHandType(card* hand) {
    int counts[13];
    generateCounts(hand, counts);

    int flushValue = hasFlush(hand);
    int straightValue = hasStraight(counts);

    if (straightValue == 14 && flushValue) return 8;
    if (straightValue && flushValue) return 7;
    if (hasFourOfKind(counts)) return 6;
    if (hasFullHouse(counts)) return 5;
    if (flushValue) return 4;
    if (straightValue) return 3;
    if (hasThreeOfKind(counts)) return 2;
    if (hasTwoPair(counts)) return 1;
    return 0;
}

/**
 * @brief determines what cards the player should hold
 *
 * @param hand the hand to use
 * @param cardsShouldHold an array to store if the position should be held
 * @return the amount of cards that were held
 */
int findCardsShouldHold(card* hand, int cardsShouldHold[5]) {
    for (int i = 0; i < 5; i++) cardsShouldHold[i] = 0;
    int cardsHoldAmount = 0;

    int counts[13];
    generateCounts(hand, counts);

    if (hasStraight(counts) || hasFlush(hand)) {
        for (int i = 0; i < 5; i++) cardsShouldHold[i] = 1;
        return 5;
    }

    card* tempHand;

    for (int c = 0; c < 13; c++) {
        if (counts[c] < 2) continue;
        tempHand = hand;
        for (int i = 0; i < 5; i++) {
            if (tempHand->value == c + 1) {
                cardsShouldHold[i] = 1;
                cardsHoldAmount++;
            }
            tempHand = tempHand->next;
        }
    }

    return cardsHoldAmount;
}

/**
 * @brief Creates a suggestion string based on findCardsShouldHold()
 *
 * @param hand the hand to use
 * @return the string created (with )
 */
char* createHandSuggestionStr(card* hand) {
    int cardsShouldHold[5];
    int cardsHoldAmount = findCardsShouldHold(hand, cardsShouldHold);

    char suggestionBuffer[100];
    char* buildPointer = suggestionBuffer;

    if (cardsHoldAmount == 0) {
        strcpy(suggestionBuffer, "No suggestions");
    }
    else if (cardsHoldAmount == 5) {
        strcpy(suggestionBuffer, "Hold All");
    }
    else {
        buildPointer += sprintf(buildPointer, "Hold");
        for (int i = 0; i < 5; i++) {
            if (cardsShouldHold[i])
                buildPointer += sprintf(buildPointer, " %d", i + 1);
        }
    }

    char* outputStr = xmalloc(sizeof(char) * (strlen(suggestionBuffer) + 1));
    strcpy(outputStr, suggestionBuffer);

    return outputStr;
}

typedef struct Player_struct {
    char* name;
    long long int money;
    card* hand;
} Player;

/**
 * @brief returns a new player with a new
 *
 * @param nameBuf
 */

Player* Player_create(char nameBuf[]) {
    Player* output = (Player*)xmalloc(sizeof(Player));
    output->hand = NULL;

    output->name = (char*)xmalloc(sizeof(char) * (strlen(nameBuf) + 1));
    strcpy(output->name, nameBuf);

    output->money = 100;
    
    return output;
}

void Player_destory(Player* p) {
    free(p->name);
    cardList_teardown(p->hand);
    free(p);
}

void Player_printMoney(Player* p) {
    printRepeatGroup('*', 9, 5);
    printRepeat('*', 5);
    printf(" %s, you have %I64d coins\t    ", p->name, p->money);
    printRepeat('*', 5);
    printf("\n");
    printRepeatGroup('*', 9, 5);
}

int Player_queryBet(Player* p) {
    int output;
    do {
        printf("Place your bet (1-%I64d) coins (-1 to quit playing): ", p->money);
        scanf("%d", &output); clearSTDIN();
        if (output == -1) break;
    } while (output<1 || output>p->money);

    return output;
}

void Player_printHand(Player* p) {
    printf("%s's hand: (%s)\n", p->name, rankNames[getHandType(p->hand)]);
    cardList_print(p->hand);
}

void Player_printHandLarge(Player* p) {
    int cards_length = cardList_length(p->hand);

    printf("%s's hand: (%s)\n", p->name, rankNames[getHandType(p->hand)]);

    for (int i = 0; i < cards_length; i++) {
        printRepeat('-', 7);
        printRepeat(' ', 5);
    }
    printf("\n");

    card* temp = p->hand;

    for (int i = 0; i < cards_length; i++) {
        printf("|");
        card_print(temp);
        printRepeat(' ', temp->value == 10 ? 2 : 3);
        printf("|");
        printRepeat(' ', 5);
        temp = temp->next;
    }
    printf("\n");

    for (int i = 0; i < cards_length; i++) {
        printf("|");
        printRepeat(' ', 5);
        printf("|");
        printRepeat(' ', 5);
    }
    printf("\n");

    temp = p->hand;

    for (int i = 0; i < cards_length; i++) {
        printf("|");
        printRepeat(' ', temp->value == 10 ? 2 : 3);
        card_print(temp);
        printf("|");
        printRepeat(' ', 5);
        temp = temp->next;
    }
    printf("\n");

    for (int i = 0; i < cards_length; i++) {
        printRepeat('-', 7);
        printRepeat(' ', 5);
    }
    printf("\n");

}

void Player_replaceCards(Player* p, card** deck, card** discardPile, int cardToHold[5]) {
    for (int i = 0; i < 5; i++)
        if (!cardToHold[i]) replaceCard(&p->hand, deck, discardPile, i);
}

#define strBuffer_Length 100

void checkStatFile(const char* filename) {
    FILE* fileRead = fopen(filename, "r");
    if (fileRead == NULL) {
        FILE* fileWrite = fopen(filename, "w");

        fprintf(fileWrite, "Game Seed, Player Name, Total Rounds, Rounds Won, Rounds Lost, ");
        for (int i = 1; i < 9; i++)
            fprintf(fileWrite, "Type %s, ", rankNames[i]);

        fprintf(fileWrite, "\n");

        fclose(fileWrite);
    }
    else {
        fclose(fileRead);
    }
}

void printPrelude(char* playerName) {
    printRepeatGroup('$', 9, 5);

    printRepeat(' ', 10);
    printRepeatGroup('$', 9, 3);

    printf("%s,\n", playerName);
    printf("\tLet's player Two pairs or Better\n");

    printRepeat(' ', 10);
    printRepeatGroup('$', 9, 3);

    printRepeatGroup('$', 9, 5);

    printRepeat('$', 9);
    printRepeat(' ', 5);
    printf("Rank of winning");
    printRepeat(' ', 11);
    printRepeat('$', 9);
    printf("\n");
    printRepeat('\t', 5);
    printf("Pay\n");

    for (int i = 8; i > 0; i--) {
        printf("%s", rankNames[i]);
        int stringPadding = 2 - (strlen(rankNames[i])) / 8;
        for (int t = 0; t < stringPadding; t++) printf("\t");

        printf("%s", rankExamples[i]);

        printf("\t\t%d*bet\n", rankRewards[i]);
    }

    printf("\n");
}

void queryReplacements(int cardsToHold[5]) {
    for (int i = 0; i < 5; i++) cardsToHold[i] = 0;
    int cardsRemaining = 5;

    int pickedCard;
    while (cardsRemaining) {
        printf("Pick cards (between 1-5) to hold (-1 to stop): ");
        scanf("%d", &pickedCard); clearSTDIN();

        if (pickedCard == -1) break;

        if (pickedCard < 1 || pickedCard>5) continue;

        if (!cardsToHold[pickedCard - 1]) {
            cardsToHold[pickedCard - 1] = 1;
            cardsRemaining--;
        }
    }
}

//#define AUTOPLAY

int main(int argc, char** argv) {
    const char dataFileName[] = "gamestats.csv";

    card* deck = NULL;
    card* discardPile = NULL;

    for (int i = 0; i < 52; i++)
        cardList_unshift(&deck, card_create(i));

    int randSeed;

    if (argc < 2) randSeed = time(0);
    else randSeed = atoi(argv[1]);

    srand(randSeed);

    printf("Enter your name: ");

    char strBuffer[strBuffer_Length];
    scanLine(strBuffer, strBuffer_Length);

    Player* player = Player_create(strBuffer);

    printPrelude(player->name);

    int roundTotalCounts = 0;
    int roundRanksCounts[9];
    for (int i = 0; i < 9; i++) roundRanksCounts[i] = 0;

    checkStatFile(dataFileName);

    while (1) {
        cardList_concat(&deck, &discardPile);
        cardList_shuffle(&deck, 10000);

        Player_printMoney(player);
        printf("\n");

#ifdef AUTOPLAY
        int bet = max_ints((player->money / 5), min_ints(10, player->money));
#else
        int bet = Player_queryBet(player);
#endif

        if (bet == -1) break;

        printf("\nYou bet %d coins\n\n", bet);

        dealCards(&player->hand, &deck, 5);

        Player_printHandLarge(player);

        int cardsToHold[5];
#ifdef AUTOPLAY
        findCardsShouldHold(player->hand, cardsToHold);
#else
        char* suggestion = createHandSuggestionStr(player->hand);
        printf("::|| %s\n", suggestion);
        free(suggestion);
        queryReplacements(cardsToHold);
#endif

        printf("\n");

        Player_replaceCards(player, &deck, &discardPile, cardsToHold);

        Player_printHandLarge(player);

        int roundRank = getHandType(player->hand);

        roundTotalCounts++;
        roundRanksCounts[roundRank]++;

        long long int coinsToAdd = rankRewards[roundRank] * (long long int)bet;

        player->money += coinsToAdd;

        printf(
            "You %s %I64d coins and you now have %I64d coins\n\n",
            (coinsToAdd < 0) ? "LOST" : "WON",
            (coinsToAdd < 0) ? -coinsToAdd : coinsToAdd,
            player->money
        );

        cardList_concat(&discardPile, &(player->hand));

        if (player->money <= 0) {
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
    FILE* statFileAppend = fopen(dataFileName, "a");

    fprintf(statFileAppend,
        "%d, %s, %d, %d, ",
        randSeed,
        player->name,
        roundTotalCounts,
        roundTotalCounts - roundRanksCounts[0]
    );

    for (int i = 0; i < 9; i++)
        fprintf(statFileAppend, "%d, ", roundRanksCounts[i]);

    fprintf(statFileAppend, "\n");

    fclose(statFileAppend);

    printf("Goodbye %s\n", player->name);

    cardList_teardown(deck);
    cardList_teardown(discardPile);
    Player_destory(player);

    return EXIT_SUCCESS;
}