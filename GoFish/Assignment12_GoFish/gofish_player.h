#pragma once
#define NUMBEROFPLAYERS 2

// Idea is to create 13 stacks which will append the cards in respective card value slots between 0 to 12
// so remove from the stack is easier is we are removing from top and not one and all the cards
struct SCardSequence
{
	short card[4];
	short* topCard;
	int sizeOfDeck;
};

struct SHand
{
	struct SCardSequence* stackOfCard[13];
	short score;
	short numberOfCards;
};


struct SCardSequence* CreateCardSequence();

void PushInSequence(int val, struct SCardSequence*);

short PopFromSequnce(struct SCardSequence*);


struct SHand* InitializeHand();

void InsertInHand(struct SHand*, int);

short RemoveFromHand(struct SHand*, int);

bool GameOver(struct SHand* hand[]);

void DisplayCard(int);

void DisplayHand(struct SHand*);

bool HaveCard(struct SHand*, short);

void TransferCards(struct SHand*, struct SHand*, short);

void CheckForCatch(struct SHand*);

void DisplayWinner(struct SHand* hand[]);