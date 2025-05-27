#pragma once
#define NUMBEROFPLAYERS 4

void Game();

int Winner(struct SCard* [NUMBEROFPLAYERS]);

void RestartDrawPile(struct SDeck*, struct SDeck*);

bool IsAllowed(int, int, int);

int PickCard(struct SCard*, struct SDeck*, struct SDeck*, int);

int SetColor();