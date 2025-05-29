#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>

#include "darts_menu.h"
#include "darts_board.h"
#include "darts_game.h"

// all menu options are initiated
CGameMenu::CGameMenu()
{
	m_arrowPosition = 0;
	m_optionSelected = EOption::START;
	m_close = false;

	// push the options strings into vector
	m_options.push_back("Start");
	m_options.push_back("Options");
	m_options.push_back("How To Play");
	m_options.push_back("Close");

	// push the settings strings into vector
	m_settings.push_back("Number Of Players");
	m_settings.push_back("Game Mode");
	m_settings.push_back("Random Throw");

	// this is the range of values settings can be given
	m_settingsValuesRange.push_back({ 1,2,3,4,5,6,7,8,9,10 });
	m_settingsValuesRange.push_back({ 301, 501 });
	m_settingsValuesRange.push_back({ 0, 1 });

	// default value is given
	for (int i = 0; i < m_settings.size(); i++)
	{
		m_settingsValues.push_back(m_settingsValuesRange[i][0]);
	}


	m_settingSelected = false;
}

// used for decoding the enum
EOption CGameMenu::DecodeOption(int arrowPosition)
{
	switch (arrowPosition)
	{
	case 0:
		return EOption::START;
		break;
	case 1:
		return EOption::OPTIONS;
		break;
	case 2:
		return EOption::HOWTOPLAY;
		break;
	case 3:
		return EOption::CLOSE;
		break;
	}
}

// Display front menu
void CGameMenu::DisplayMenu()
{
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "----------------|        Welcome To Darts        |--------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";

	std::cout << "\tNavigate menu with UP and DOWN key.\n";
	std::cout << "\tPress ENTER to select.\n\n\n";

	for (int i = 0; i < this->m_options.size(); i++)
	{
		if (i == this->m_arrowPosition)
		{
			std::cout << "\t>";
		}
		else
		{
			std::cout << "\t  ";
		}
		std::cout << this->m_options[i] << "\n";
	}
	std::cout << "\n\n\t* MAKE THE CONSOLE FULLSCREEN FOR BETTER GRAPHIC. *\n";
}

// display settings menu
void CGameMenu::DisplaySettings()
{
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "-------------------|        Settings        |-------------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";

	std::cout << "\tNavigate menu with UP and DOWN key.\n";
	std::cout << "\tPress ENTER to change the value.\n";
	std::cout << "\tUse RIGHT and LEFT key to change the values.\n";
	std::cout << "\tPress ESC if you are don't with changing values.\n\n\n";

	for (int i = 0; i < this->m_settings.size(); i++)
	{
		if (i == this->m_arrowPosition && this->m_settingSelected)
		{
			std::cout << "\t>>  ";
		}
		else if (i == this->m_arrowPosition)
		{
			std::cout << "\t>   ";
		}
		else
		{
			std::cout << "\t    ";
		}
		printf_s("%-20s :   < %d >\n", this->m_settings[i].c_str(), this->m_settingsValues[i]);
	}
}

// Start function : initiate the board class (actual game starts here)
void CGameMenu::Start()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "---------------------|        Game        |---------------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";

	int numberOfPlayers = m_settingsValues[0];
	int gameMode = m_settingsValues[1];
	bool isRandom = m_settingsValues[2];

	std::cout << "Setting Up The Dart Board";
	for (int i = 1; i <= 5; i++)
	{
		std::cout << ".";
		Sleep(1000);
	}
	std::cout << "\n";

	CGame* game = new CGame(numberOfPlayers, gameMode, isRandom);
	game->Game();

	system("pause>nul");
	delete game;
}

// handling values in options
void CGameMenu::Options()
{
	bool close1 = false;
	this->m_arrowPosition = 0;
	while (!close1)
	{
		system("cls");
		this->DisplaySettings();
		short key1 = 0;
		switch ((key1 = _getch()))
		{
		case KEY_DOWN:
			this->m_arrowPosition = (this->m_arrowPosition + 1) % this->m_settings.size();
			break;
		case KEY_UP:
			this->m_arrowPosition = (this->m_arrowPosition - 1) % this->m_settings.size();
			break;
		case KEY_ENTER:
		{
			bool close2 = false;
			this->m_settingSelected = true;
			int index = 0;

			while (!close2)
			{
				system("cls");
				this->DisplaySettings();
				switch ((key1 = _getch()))
				{
				case KEY_RIGHT:
					index = (index + 1) % this->m_settingsValuesRange[this->m_arrowPosition].size();
					this->m_settingsValues[this->m_arrowPosition] = this->m_settingsValuesRange[this->m_arrowPosition][index];
					break;
				case KEY_LEFT:
					index = (index == 0) ? this->m_settingsValuesRange[this->m_arrowPosition].size() - 1 : ((index - 1) % this->m_settingsValuesRange[this->m_arrowPosition].size());
					this->m_settingsValues[this->m_arrowPosition] = this->m_settingsValuesRange[this->m_arrowPosition][index];
					break;
				case KEY_ESC:
					close2 = true;
					break;
				}
			}
			this->m_settingSelected = false;
			break;
		}
		case KEY_ESC:
			close1 = true;
			break;
		}
	}
	this->m_arrowPosition = 0;
}

// How to play instructions
void CGameMenu::HowToPLay()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "------------------|        How To PLay        |-----------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";

	// sample board
	PrintDartBoard(30, 10);

	std::cout << "DEFAULTS:\n";
	std::cout << "\t1) Random Darts are off.\n";
	std::cout << "\t2) Angles are from 0 (starting from right) to 360.\n";
	std::cout << "\t3) Offset for Dart Board is set to 5.\n";
	std::cout << "\t4) Game Mode is set to 301.\n";
	std::cout << "\t5) Game Opens in single player mode.\n";
	std::cout << "\t6) Radius of the dart Board is 40. \n";

	std::cout << "RULES:\n";
	std::cout << "\t1) The play starts with initial points according to the game mode.(301/ 501)\n";
	std::cout << "\t2) The objective is to get this score to 0.\n";
	std::cout << "\t3) For This You need to throw darts on the dart boards with numbers marked on it.\n";
	std::cout << "\t4) There are 20 sections(arcs) and 2 center circles to throw darts in.\n";
	std::cout << "\t5) Each section has 4 sub-sections. Double, Outer Single, Triple and Inner Singles.\n";
	std::cout << "\t6) Your Points are calculated according to where you land a dart. Inner center scores 50, and Outer Center scores 25.\n";
	std::cout << "\t\t For ex. You throw dart in 18 Double section, the score will be 36.\n";
	std::cout << "\t7) Every turn player gets 3 rounds to throw dart. The overall score of darts is calculated and subtracted from the total.\n";
	std::cout << "\t8) The Player has to Double Out. That means you must land on double to make your score exactly 0.\n";
	std::cout << "\t\t For ex. If 36 points are remaining, you must throw dart on 18 double.\n";
	std::cout << "\t9) If Turn Total goes below 0, then that turn is not counted.\n\n";
	system("pause");
}

// close the game
void CGameMenu::Close()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "---------------|        Thanks For Playing        |-------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";
	this->m_close = true;
	system("pause>nul");
}

// key presses are handeled here
void CGameMenu::GameMenu()
{
	while (!this->m_close)
	{
		system("cls");
		this->DisplayMenu();

		short key = 0;
		switch ((key = _getch()))
		{
		case KEY_DOWN: //
			this->m_arrowPosition = (this->m_arrowPosition + 1) % this->m_options.size();
			break;
		case KEY_UP:
			this->m_arrowPosition = (this->m_arrowPosition - 1) % this->m_options.size();
			break;
		case KEY_ENTER:

			this->m_optionSelected = this->DecodeOption(m_arrowPosition);

			switch (this->m_optionSelected)
			{
			case EOption::START:
				this->Start();
				break;
			case EOption::HOWTOPLAY:
				this->HowToPLay();
				break;
			case EOption::OPTIONS:
				this->Options();
				break;
			case EOption::CLOSE:
				this->Close();
				break;
			}
			break;
		}
	}
}

