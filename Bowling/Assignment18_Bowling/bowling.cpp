#include "bowling_menu.h"

int main()
{
	CGameMenu* gameMenu = new CGameMenu;
	gameMenu->GameMenu();
	delete gameMenu;
}
