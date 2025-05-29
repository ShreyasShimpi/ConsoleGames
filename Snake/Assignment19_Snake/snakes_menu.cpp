#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <memory>

#include "snakes_menu.h"
#include "snakes_arena.h"

CGameMenu::CGameMenu()
{
	m_arrowPosition = 0;
	m_optionSelected = EOption::START;
	m_close = false;
	m_options.push_back("Start");
	m_options.push_back("Options");
	m_options.push_back("How To Play");
	m_options.push_back("Close");

	// keep no of setting and setting values same
	//m_settings.push_back("Speed");
	m_settings.push_back("Boundary Collision");
	m_settings.push_back("Self Collision");

	m_settingsValuesRange.push_back({ false, true });
	m_settingsValuesRange.push_back({ true, false });

	// default value is given : index 1
	for (int i = 0; i < m_settings.size(); i++)
	{
		m_settingsValues.push_back(m_settingsValuesRange[i][0]);
	}
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
	std::cout << "----------------|        WELCOME TO SNAKES       |--------------\n";
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
		if (i == this->m_arrowPosition)
		{
			std::cout << "\t>   ";
		}
		else
		{
			std::cout << "\t    ";
		}
		printf_s("%-20s :   < %s >\n", this->m_settings[i].c_str(), this->m_settingsValues[i] ? "True" : "False");
	}
}

void CGameMenu::Start()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "---------------------|        GAME        |---------------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\n";
	
	bool boundaryCollision = m_settingsValues[0];
	bool selfCollision = m_settingsValues[1];

	std::cout << "\tLoading the Game";
	for (int i = 1; i <= 5; i++)
	{
		std::cout << ".";
		Sleep(1000);
	}
	system("cls");
	std::unique_ptr<CBoard> game = std::make_unique<CBoard>(boundaryCollision, selfCollision);
	game->UpdateBoard();

	std::cout << "Press Any Key to return to Main Menu..\n";
	system("pause>nul");
}

void CGameMenu::Options()
{
	bool close1 = false;
	this->m_arrowPosition = 0;
	// starting index
	int index = 0;
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
	std::cout << "\t2) Boundary Collision : Off\n";
	std::cout << "\t2) Self Collision : On\n";


	std::cout << "RULES:\n";
	std::cout << "\t1) Move Your Snake with WASD Keys.\n";
	std::cout << "\t2) Game will be over if snake collides with itself.\n";
	std::cout << "\t3) Take the apples to gain points.\n\n\n";

	system("pause");
}

void CGameMenu::Close()
{
	system("cls");
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "---------------|        Thanks For Playing        |-------------\n";
	std::cout << "----------------------------------------------------------------\n\n\n\t";
	this->m_close = true;
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
			this->m_optionSelected = this->DecodeOption(m_arrowPosition);
			break;
		case KEY_UP:
			this->m_arrowPosition = (this->m_arrowPosition - 1) % this->m_options.size();
			this->m_optionSelected = this->DecodeOption(m_arrowPosition);
			break;
		case KEY_ENTER:
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

