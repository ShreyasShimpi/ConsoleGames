#pragma once

#define NUMBEROFPLAYERS 4

struct SCard
{
	int card;
	struct SCard* nextCard;
};


struct SCard* CreatePlayerHand(int);

void DisplayPlayerHand(struct SCard*);

void InsertAtEnd(struct SCard*, int);

void RemoveFromHand(struct SCard*, int);

int SizeOfHand(struct SCard*);

int PeekAtHand(struct SCard*, int);
