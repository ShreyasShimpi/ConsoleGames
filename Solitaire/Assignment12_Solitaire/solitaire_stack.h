#pragma once

#define DECKSIZE 52


// Stack declaration
struct SDeck
{
	int* card;
	int* topCard;
	int sizeOfDeck;
};

struct STableau
{
	struct SDeck* deck;
	// start and end are used for keeping track of which card in tableau we can move
	int startIndex;
	int endIndex;
};

// normal deck functions
struct SDeck* CreateDeck(int);

void PushInDeck(int, struct SDeck*);

int PopFromDeck(struct SDeck*);

int PeekDeck(struct SDeck*);

void ShuffleDeck(struct SDeck*);

void SwapCards(int*, int*);

void FillDeck(struct SDeck*);

void DisplayCard(int);



// tableau deck functions
struct STableau* CreateTableauDeck(int);