#pragma once

#define DECKSIZE 108


// Stack declaration
struct SDeck
{
	int card[DECKSIZE];
	int* topCard;
	int sizeOfDeck;
};

void PushInDeck(int, struct SDeck*);

int PopFromDeck(struct SDeck*);

int PeekDeck(struct SDeck*);

struct SDeck* CreateDeck();

void ShuffleDeck(struct SDeck*);

void SwapCards(int*, int*);

void FillDeck(struct SDeck*);

void DisplayCard(int);
