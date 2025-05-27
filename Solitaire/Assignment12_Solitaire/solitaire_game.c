#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

#include "solitaire_stack.h"

void DisplayConsole(struct STableau* tableau[7], struct SDeck* foundation[4], struct SDeck* stockPile, struct SDeck* wastePile)
{
	printf("<------------------------------------------------------------- Welcome To Solitaire ------------------------------------------------------------->\n\n\n\n");

	printf("                                                                                                       Foundation \n");
	printf("      Stock Pile            Waste Pile                                 Hearts Pile          Diamonds Pile           Spades Pile          Clubs Pile     \n");
	printf("[|||||||||||||||||||] ");
	DisplayCard(PeekDeck(wastePile));
	printf("                      ");
	DisplayCard(PeekDeck(foundation[0]));
	DisplayCard(PeekDeck(foundation[1]));
	DisplayCard(PeekDeck(foundation[2]));
	DisplayCard(PeekDeck(foundation[3]));
	printf("\n\n\n\n");


	printf("                                                        TABLEAU                                                                             \n");
	printf("       1st Pile              2nd Pile              3rd Pile              4th Pile              5th Pile              6th Pile              7th Pile     \n");

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (tableau[j]->startIndex == 0)
			{
				printf("[                   ] ");
			}

			else if (tableau[j]->startIndex <= i + 1)
			{
				DisplayCard(tableau[j]->deck->card[i]);
			}

			else
			{
				printf("[|||||||||||||||||||] ");
			}
		}
		printf("\n");
	}
	printf("\n\n\n");
}

// check if the card is allowed on foundation by checking the type and card
bool AllowedOnFoundation(int card, struct SDeck* foundation[4])
{
	int cardValue = (card - 1) % 13 + 1; // 1 to 13
	int cardType = (card - 1) / 13 + 1; // 1 to 4

	if (foundation[cardType - 1]->sizeOfDeck == 0 && cardValue == 1)
	{
		return true;
	}
	else if (foundation[cardType - 1]->sizeOfDeck > 0 && foundation[cardType - 1]->sizeOfDeck <= 13)
	{
		
		int foundationCard = PeekDeck(foundation[cardType - 1]) ;
		if (foundationCard + 1 == card)
		{
			return true;
		}
	}
	return false;
}

// check
bool AllowedOnTableau(int card, struct STableau* tableau)
{
	int cardValue = (card - 1) % 13 + 1; // 1 to 13
	int cardColor = (card - 1) / 26 + 1; //  1 red - 2 black

	if (tableau->deck->sizeOfDeck != 0)
	{
		int tableauCard = PeekDeck(tableau->deck);

		int tableauCardValue = (tableauCard - 1) % 13 + 1; // 1 to 13
		int tableauCardColor = (tableauCard - 1) / 26 + 1; //  1 red - 2 black

		// if color is different and the numbers are consecutive
		if (tableauCardColor != cardColor && tableauCardValue == cardValue + 1)
		{
			return true;
		}
	}
	else
	{
		// if its a king, then allow on empty pile
		if (cardValue == 13)
		{
			return true;
		}
	}
	return false;
}


bool AllowedCards(int choiceNumberOfCards, struct STableau* tableau)
{
	if (choiceNumberOfCards <= tableau->endIndex - tableau->startIndex + 1)
	{
		return true;
	}
	return false;
}

// check for win
bool CheckForWin(struct SDeck* foundation[4])
{
	int total = 0;
	for (int i = 0; i < 4; i++)
	{
		total += foundation[i]->sizeOfDeck;
	}

	// all cards in foundation
	if (total == 52)
	{
		printf("\n\n<----------------------------| You Managed to Get all the Cards to the Foundation |---------------------------->\n\n");
		printf("\n\n<----------------------------------------------| YOU WIN! |---------------------------------------------------> \n\n");
		Sleep(5000);
		return true;
	}
	return false;
}



void Game()
{
	// linked list approach
	// array of linked lists to store the heads of 7 front decks
	//struct SCard* tableau[7];
	//for (int i = 0; i < 7; i++)
	//{
	//	tableau[i] = CreatePlayerHand(-1); // front cards is referring to the head of the 7 front decks(linked list)
	//}

	// stack approach
	//struct STableau* tableau[7];
	struct STableau** tableau = (struct STableau**)malloc(7 * sizeof(struct STableau*));
	if (tableau)
	{
		for (int i = 0; i < 7; i++)
		{
			tableau[i] = CreateTableauDeck(19); // front cards is referring to the head of the 7 front decks(linked list)

		}
	}

	// creating decks
	struct SDeck* stockPile = CreateDeck(52);

	// stockPile filling
	FillDeck(stockPile);

	// shuffle stockPile
	ShuffleDeck(stockPile);

	// creating waste pile
	struct SDeck* wastePile = CreateDeck(52);

	// creating foundation piles
	//struct SDeck* foundation[4]; //
	struct SDeck** foundation = (struct SDeck**)malloc(4 * sizeof(struct SDeck*));

	if (foundation)
	{
		for (int i = 0; i < 4; i++)
		{
			foundation[i] = CreateDeck(13); // 4 piles of foundation
		}
	}

	// to close the game, can be used if no move is possible
	bool close = false;

	// Initialize Tableau
	for (int i = 0; i < 7; i++)
	{
		for (int j = i; j < 7; j++)
		{
			PushInDeck(PopFromDeck(stockPile), tableau[j]->deck);
			tableau[j]->startIndex += 1;
			tableau[j]->endIndex += 1;
		}
	}

	for (int i = 5; i > 0; i--)
	{

		system("cls");
		printf("<------------------------------------------------------------- Welcome To Solitaire ------------------------------------------------------------->\n\n\n\n");
		printf("How to Play:\n");
		printf("\t1. The goal of the game is to sort out cards into sequences based on their suits and rank, and this is done through moving cards around.\n\t  The initially shuffled deck will eventually be sorted into cards in the order of K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2, A, from high to low,\n\t   with no mixed suits. At the end of a game of solitaire, the deck will be sorted neatly. \n");
		printf("\t2. The Foundations are the 4 main piles where a suit is built up. \n\t  Each Foundation will be of a certain suit, be it hearts, diamonds, spades and clubs. \n\t  clearing the board of that suit. Each Foundation begins with an Ace, and builds towards a King. Foundations begin \n");
		printf("\t3. Sometimes known as the stock or hand, the draw pile is the remaining cards after all cards are dealt onto the Table.\n");
		printf("\t4. The focus of the game is to move cards individually from the table to the Foundations. \n\t  This means carefully unveiling and drawing cards, as certain cards may be blocked, and you can only begin a Foundation with an Ace. \n\t  If an Ace is available on the beginning board, they should be moved onto the Foundations.\n\t  If a card is removed from the Table, and a pile is left with the last card unrevealed, the card is unveiled.\n");
		printf("\t5. The goal of Classic Solitaire is to transfer all cards from the Table to the Foundation.\n\t   The game will end if either no more moves are possible, or if all cards are cleared and sorted out.\n");

		printf("\n\nGame will begin in %d....", i);
		Sleep(1000);
	}

	while (!close)
	{
		system("cls");
		// display the console
		DisplayConsole(tableau, foundation, stockPile, wastePile);

		// Menu
		short choice = 0;
		printf("Choices: \n");
		printf("\t1. Tableau-to-Tableau    : Take card/cards from one pile of Tableau and displace them to different pile in Tableau.\n");
		printf("\t2. Waste-to-Tableau      : Take Card from waste pile and put it in Tableau.\n");
		printf("\t3. Waste-to-Foundation   : Take Card from waste pile and put it in one of the foundation pile.\n");
		printf("\t4. Tableau-to-Foundation : Take a card from tableau and put it in the of the foundation pile.\n");
		printf("\t5. Stock-to-Waste        : Draw a Card From Stock and Put it over waste pile.\n");
		printf("\t6. Close                 : Close the game if you want to when there are no moves can be made.\n");
		printf("Your Choice: ");
		scanf_s("%hi", &choice);
		printf("\n");

		switch (choice)
		{
		case 1:

			printf("\n<-----------Tableau-to-Tableau------------>\n");

			short choiceTableauFrom;
			short choiceTableauTo;
			short choiceNumberOfCards;


			printf("\nSelect the Tableau Deck you want the card/cards From (1 - 7): ");
			scanf_s("%hi", &choiceTableauFrom);

			printf("\nSelect the Number of Cards you want to place (1 - 13): ");
			scanf_s("%hi", &choiceNumberOfCards);

			printf("\nSelect the Tableau Deck you want the card/cards placed To (1 - 7): ");
			scanf_s("%hi", &choiceTableauTo);

			if (tableau[choiceTableauFrom - 1]->deck->sizeOfDeck == 0)
			{
				printf("\nThe Tableau deck you selected has No cards in it. Try Again!\n");
				Sleep(1000);
			}
			else if (!AllowedCards(choiceNumberOfCards, tableau[choiceTableauFrom - 1]))
			{
				printf("\nNumber of card selected is Invalid. Try Again!\n");
				Sleep(1000);
			}
			else
			{
				int indexToCheck = tableau[choiceTableauFrom - 1]->endIndex - choiceNumberOfCards;
				int cardToCheck = tableau[choiceTableauFrom - 1]->deck->card[indexToCheck];

				// adding elements
				if (AllowedOnTableau(cardToCheck, tableau[choiceTableauTo - 1]))
				{
					struct SDeck* temp = CreateDeck(choiceNumberOfCards);
					for (int i = 0; i < choiceNumberOfCards; i++)
					{
						PushInDeck(PopFromDeck(tableau[choiceTableauFrom - 1]->deck), temp);
						tableau[choiceTableauFrom - 1]->endIndex -= 1;
					}

					// edge : if we move all the visible cards , then we have to reveal the next card
					// so if endIndex becomes less than startIndex, then decrement the startIndex
					if (tableau[choiceTableauFrom - 1]->endIndex < tableau[choiceTableauFrom - 1]->startIndex)
					{
						tableau[choiceTableauFrom - 1]->startIndex -= 1;
					}

					for (int i = 0; i < choiceNumberOfCards; i++)
					{
						PushInDeck(PopFromDeck(temp), tableau[choiceTableauTo - 1]->deck);
						tableau[choiceTableauTo - 1]->endIndex += 1;
					}

					//edge: if we add on empty slot with king, then start should be incremented
					// so if startIndex is 0 and if we add, then start should be incremented
					if (tableau[choiceTableauTo - 1]->startIndex == 0)
					{
						tableau[choiceTableauTo - 1]->startIndex += 1;
					}

				}
				else
				{
					printf("\nThe card/sequence is not allowed to the tableau you selected. Try again!\n");
					Sleep(1000);
				}
			}


			break;

		case 2:

			printf("\n<-----------Waste-to-Tableau------------>\n");

			if (wastePile->sizeOfDeck == 0)
			{
				printf("\nThe Waste Pile has No cards in it. Try Again!\n");
				Sleep(1000);
			}
			else
			{
				int wasteCard = PeekDeck(wastePile);
				short choiceTableau;

				printf("Select the Tableau Deck you want the card to be placed (1 - 7): ");
				scanf_s("%hi", &choiceTableau);

				if (AllowedOnTableau(wasteCard, tableau[choiceTableau - 1]))
				{
					// removed from waste pile
					PopFromDeck(wastePile);

					// adding to the tableau
					PushInDeck(wasteCard, tableau[choiceTableau - 1]->deck);
					tableau[choiceTableau - 1]->endIndex += 1;

					//edge: if we add on empty slot with king, then start should be incremented
					// so if startIndex is 0 and if we add, then start should be incremented
					if (tableau[choiceTableau - 1]->startIndex == 0)
					{
						tableau[choiceTableau - 1]->startIndex += 1;
					}
				}
				else
				{
					printf("The card is not allowed to the tableau you selected. Try again!\n");
					Sleep(1000);
				}
			}
			break;

		case 3:

			printf("\n<-----------Waste-to-Foundation------------>\n");

			if (wastePile->sizeOfDeck == 0)
			{
				printf("\nThe Waste Pile has No cards in it. Try Again!\n");
				Sleep(1000);
			}
			else
			{
				int wasteCard = PeekDeck(wastePile);

				//short choiceColor;
				//printf("Select the Type of Card (1: hearts, 2: diamonds, 3: spades, 4: clubs): ");
				//scanf_s("%hi", &choiceColor);

				if (AllowedOnFoundation(wasteCard, foundation))
				{
					PopFromDeck(wastePile);
					PushInDeck(wasteCard, foundation[(wasteCard - 1) / 13]);
					printf("The card has been added to the foundation.\n");
					Sleep(1000);
				}
				else
				{
					printf("The card is not allowed to the foundation. Try again!\n");
					Sleep(1000);
				}
			}

			break;

		case 4:

			printf("\n<-----------Tableau-to-Foundation------------>\n");
			short choiceTableau;

			printf("Select the Tableau Deck you want the card from (1 - 7): ");
			scanf_s("%hi", &choiceTableau);
			if (tableau[choiceTableau - 1]->deck->sizeOfDeck == 0)
			{
				printf("\nThe Deck has No cards in it. Try Again!\n");
				Sleep(1000);
			}
			else
			{
				int card = PeekDeck(tableau[choiceTableau - 1]->deck);
				//short choiceType;
				//printf("Select the Type of Card (1: hearts, 2: diamonds, 3: spades, 4: clubs): ");
				//scanf_s("%hi", &choiceType);

				if (AllowedOnFoundation(card, foundation))
				{
					// adding to foundation
					PushInDeck(card, foundation[(card - 1) / 13]);

					// remove from tableau
					PopFromDeck(tableau[choiceTableau - 1]->deck);
					tableau[choiceTableau - 1]->endIndex -= 1;

					// edge : if we move all the visible cards , then we have to reveal the next card
					// so if endIndex becomes less than startIndex, then decrement the startIndex
					if (tableau[choiceTableau - 1]->endIndex < tableau[choiceTableau - 1]->startIndex)
					{
						tableau[choiceTableau - 1]->startIndex -= 1;
					}

					printf("The card has been added to the foundation.\n");
					Sleep(1000);
				}
				else
				{
					printf("The card is not allowed to the foundation. Try again!\n");
					Sleep(1000);
				}
			}

			break;

		case 5:
			printf("\n<-----------Stock-to-Waste------------>\n");
			if (stockPile->sizeOfDeck == 0)
			{
				printf("\nThe stock pile has no more cards!!\n");
				Sleep(1000);
			}
			else
			{
				printf("Taking card from Stock pile...\n");
				Sleep(1000);
				PushInDeck(PopFromDeck(stockPile), wastePile);
				printf("Placing that card on Waste Pile...\n");
				Sleep(1000);
			}
			break;

		case 6:
			printf("\n<-----------Close------------>\n");
			close = true;
			printf("\nThanks for Playing!\n");
			system("pause");
			break;

		default:
			break;
		}

		// winner
		if (CheckForWin(foundation))
		{
			close = true;
		}
	}


	// Freeing the memory
	if (foundation)
	{
		for (int i = 0; i < 4; i++)
		{
			free(foundation[i]); // 4 piles of foundation
		}
	}
	free(foundation);
	free(wastePile);
	free(stockPile);
	for (int i = 0; i < 7; i++)
	{
		free(tableau[i]); // 4 piles of foundation
	}
	free(tableau);
}