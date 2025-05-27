
#pragma once

#define DECKSIZE 52


// Stack declaration
struct SDeck
{
	int card[DECKSIZE];
	int* topCard;
	int sizeOfDeck;
};

void PushInDeck(int, struct SDeck*);

int PopFromDeck(struct SDeck*);

struct SDeck* CreateDeck();

void ShuffleDeck(struct SDeck*);

void SwapCards(int*, int*);

void FillDeck(struct SDeck*);

