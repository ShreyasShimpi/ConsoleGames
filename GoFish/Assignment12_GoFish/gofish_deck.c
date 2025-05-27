#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

#include "gofish_deck.h"


// creatiing stack
struct SDeck* CreateDeck()
{
	struct SDeck* temp = (struct SDeck*)malloc(sizeof(struct SDeck));
	if (temp)
	{
		temp->sizeOfDeck = 0;
		temp->topCard = temp->card; // top should point to the first location
		temp->topCard--; // now its at -1 index, when we will push, it comes to 0.
	}
	return temp;
}

void PushInDeck(int val, struct SDeck* temp)
{
	temp->topCard++;
	*(temp->topCard) = val;
	temp->sizeOfDeck++;
}

int PopFromDeck(struct SDeck* temp)
{
	int val = *(temp->topCard);
	temp->topCard--;
	temp->sizeOfDeck--;
	return val;
}


// Swap cards function
void SwapCards(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// function to shuffle the elements in the array which is deck here.
void ShuffleDeck(struct SDeck* temp)
{
	srand(time(NULL));

	// picks the random index from 0 to i and swaps it with current index i
	for (int i = DECKSIZE - 1; i > 0; i--)
	{
		int randomIndex = rand() % (i + 1); // i + 1 to avoid %1 operation when i = 1
		SwapCards(&temp->card[randomIndex], &temp->card[i]);
	}
}

void FillDeck(struct SDeck* temp)
{
	for (int i = 0; i < DECKSIZE; i++)
	{
		PushInDeck(i, temp);
	}
}




