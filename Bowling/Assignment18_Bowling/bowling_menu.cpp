#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <memory>

#include "bowling_menu.h"
#include "bowling_arena.h"
#include "bowling_game.h"

CGameMenu::CGameMenu()
{
	m_arrowPosition = 0;
	m_optionSelected = EOption::START;
	m_close = false;
	m_options.push_back("Start");
	m_options.push_back("Options");
	m_options.push_back("How To Play");
	m_options.push_back("Close");

	m_settings.push_back("Number Of Players");
	m_settings.push_back("Automatic Bowl Rolling");

	m_settingsValuesRange.push_back({ 1,2,3,4,5,6,7,8,9,10 });
	m_settingsValuesRange.push_back({0, 1});

	// default value is given : index 1
	for (int i = 0; i < m_settings.size(); i++)
	{
		m_settingsValues.push_back(m_settingsValuesRange[i][1]);
	}


	m_settingSelected = false;
}

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

void CGameMenu::DisplayMenu()
{
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "------------|        WELCOME TO BOWLING ARENA       |----------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";

	std::cout << "\tNavigate menu with Up and Down key.\n";
	std::cout << "\tPress Enter to select.\n\n\n";

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
}

void CGameMenu::DisplaySettings()
{
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "-------------------|        SETTINGS        |-------------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";

	std::cout << "\tNavigate menu with UP and DOWN key.\n";
	std::cout << "\tUse RIGHT and LEFT key to change the values.\n\n\n";

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

void CGameMenu::Start()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "---------------------|        GAME        |---------------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";
	
	int numberOfPlayers = m_settingsValues[0];
	int autoRoll = m_settingsValues[1];

	std::cout << "\tSetting Up The Bowling Arena";
	for (int i = 1; i <= 5; i++)
	{
		std::cout << ".";
		Sleep(1000);
	}

	std::shared_ptr<CGame> game = std::make_unique<CGame>(numberOfPlayers, autoRoll);
	game->Game();

	std::cout << "Press Any Key to return to Main Menu..\n";
	system("pause>nul");
}

void CGameMenu::Options()
{
	bool close1 = false;
	this->m_arrowPosition = 0;
	int index = 1;
	while (!close1)
	{
		system("cls");
		this->DisplaySettings();
		short key1 = 0;
		switch ((key1 = _getch()))
		{
		case KEY_DOWN: // arrow down
			this->m_arrowPosition = (this->m_arrowPosition + 1) % this->m_settings.size();
			break;
		case KEY_UP:// arrow up
			this->m_arrowPosition = (this->m_arrowPosition - 1) % this->m_settings.size();
			break;
		case KEY_RIGHT: // scroll the value at that arrow position
			index = (index + 1) % this->m_settingsValuesRange[this->m_arrowPosition].size();
			this->m_settingsValues[this->m_arrowPosition] = this->m_settingsValuesRange[this->m_arrowPosition][index];
			break;
		case KEY_LEFT:// scroll the value at that arrow position
			index = (index == 0) ? this->m_settingsValuesRange[this->m_arrowPosition].size() - 1 : ((index - 1) % this->m_settingsValuesRange[this->m_arrowPosition].size());
			this->m_settingsValues[this->m_arrowPosition] = this->m_settingsValuesRange[this->m_arrowPosition][index];
			break;
		case KEY_ESC:
			close1 = true;
			break;
		}
	}
	this->m_arrowPosition = 0;
}

void CGameMenu::HowToPLay()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "------------------|        HOW TO PLAY        |-----------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";

	std::cout << "DEFAULTS:\n";
	std::cout << "\t1) Number of Players : 2\n";
	std::cout << "\t2) Automatic Bowl Control : On\n";


	std::cout << "RULES:\n";
	std::cout << "\t1) Its Simple Bowling Game. You have to roll a bowling ball down the board.\n";
	std::cout << "\t2) There are 10 frames in which the game runs. each player gets a turn in 1 frame.\n";
	std::cout << "\t3) If you get all of the pins, its a strike. (10 Points + scores of next two rolls)\n";
	std::cout << "\t4) If you get all of the pins in two rolls, its a spare. (10 Points  + score of next roll).\n";
	std::cout << "\t4) 10th Frame can have 3 rolls according to spare and strike.\n";
	std::cout << "\t5) At the end, scores are calculated and the high scorer wins the game.\n";

	system("pause");
}

void CGameMenu::Close()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "---------------|        Thanks For Playing        |-------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\t";
	this->m_close = true;
	system("pause");
}

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

