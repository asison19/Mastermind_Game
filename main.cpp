/*
Name: Andrew Sison
Title: Mastermind game ver. 1.3
Description:
Play the Mastermind game as either the code breaker or maker.
https://en.wikipedia.org/wiki/Mastermind_(board_game)

*/
//file: main.cpp
#include "Mastermind_Game.h"
#include <iostream>
void menu();	//used to play the game

int main()
{	
	Mastermind_Game game;
	game.playGame();
	system("pause");

	return 0;
}


