#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "solitaire_stack.h"

// to be made
void DisplayConsole(struct STableau* tableau[7], struct SDeck* foundation[4], struct SDeck*, struct SDeck*);

bool AllowedOnFoundation(int, struct SDeck* foundation[4]);

bool AllowedCards(int, struct STableau*);

// check for win
bool CheckForWin(struct SDeck* foundation[4]);


void Game();