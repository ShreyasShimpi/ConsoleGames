#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "uno_player.h"
#include "uno_deck.h"



struct SCard* CreatePlayerHand(int val)
{
	//create a struct on heap. Addign card, set next to NULL, return struct pointer

	struct SCard* temp = (struct SCard*)malloc(sizeof(struct SCard));
	if (temp) {
		temp->card = val;
		temp->nextCard = NULL;
	}
	return temp;
}


void InsertAtEnd(struct SCard* head, int val)
{


	/*
		start from head node. iterate through to the end. once we reach end,
		create a new node with card and attach it to the list
	*/


	struct SCard* itr = head;
	while (1) {
		if (itr->nextCard == NULL) {
			itr->nextCard = CreatePlayerHand(val);
			break;
		}
		else {
			itr = itr->nextCard;
		}
	}
}

void RemoveFromHand(struct SCard* ptr, int index)
{

	int p = -1;//This is used for going to the position pointed by the index
	struct SCard* temp = ptr;
	//if (temp->nextCard == NULL)
	//{
	//	printf("Your Hand is empty");
	//	return;
	//}
	while (p != index - 1)
	{
		temp = temp->nextCard;
		p++;
	}
	struct SCard* temp2 = temp->nextCard;
	temp->nextCard = temp->nextCard->nextCard;
	temp2->nextCard = NULL;
	free(temp2);
}

void DisplayPlayerHand(struct SCard* ptr)
{
	/*
		start by attaching temp to head node. Till we reach the last node,
		print the data of current node and proceed to the next node
	*/
	struct SCard* temp = ptr->nextCard;
	int i = 1;
	while (temp != NULL)
	{
		printf("\t%d. ", i);
		DisplayCard(temp->card);
		temp = temp->nextCard;
		i++;
	}
	printf("\n");
}

int SizeOfHand(struct SCard* ptr)
{
	int size = 0;
	struct SCard* temp = ptr->nextCard;
	while (temp != NULL)
	{
		temp = temp->nextCard;
		size++;
	}

	return size;
}

int PeekAtHand(struct SCard* ptr, int index)
{
	int p = -1;//This is used for going to the position pointed by the index
	struct SCard* temp = ptr;
	while (p != index)
	{
		temp = temp->nextCard;
		p++;
	}

	return temp->card;
}
