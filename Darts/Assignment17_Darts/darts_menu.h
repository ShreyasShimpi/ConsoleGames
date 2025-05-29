#pragma once
#include <iostream>
#include <vector>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define KEY_ENTER 13
#define KEY_ESC 27

enum class EOption
{
	START, OPTIONS, HOWTOPLAY, CLOSE
};

class CGameMenu
{
private:
	int m_arrowPosition;

	EOption m_optionSelected;
	std::vector<std::string> m_options;

	std::vector<std::string> m_settings;
	std::vector<std::vector<int>> m_settingsValuesRange;
	std::vector<int> m_settingsValues;

	bool m_settingSelected;
	bool m_close;

public:
	CGameMenu();

	EOption DecodeOption(int arrowPosition);

	void DisplayMenu();

	void DisplaySettings();

	void Start();

	void Options();

	void HowToPLay();

	void Close();

	void GameMenu();
};
