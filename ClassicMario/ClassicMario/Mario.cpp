#include<iostream>
#include "CGame.h"
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

#define WIDTH 640
#define HEIGHT 480

int main()
{
	CGame game(WIDTH, HEIGHT, " Mario "); 

	game.Run();

}