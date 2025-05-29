#include "darts_menu.h"

// main game
int main()
{
	CGameMenu* gameMenu = new CGameMenu;
	gameMenu->GameMenu();
	delete gameMenu;
}
