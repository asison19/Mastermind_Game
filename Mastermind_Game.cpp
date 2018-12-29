/*
file: Mastermind_Game.cpp
cpp for Mastermind_Game.h
*/

#include "Mastermind_Game.h"
#include "Mastermind_Breaker.h"
#include "Mastermind_Maker.h"

Mastermind_Game::Mastermind_Game()
{

}

Mastermind_Game::~Mastermind_Game()
{

}

void Mastermind_Game::playGame()
{
	int choice = 0;
	bool play;
	do
	{
		int choice = getChoice();
		if (choice == 1)
		{
			Mastermind_Breaker breaker;
			breaker.play();
		}
		else if (choice == 2)
		{
			Mastermind_Maker maker;
			maker.play();
		}

		choice = askToPlayAgain();

		if (choice == 1)
		{
			play = true;

		}
		else
		{
			play = false;
		}
	} while (play);
}

int Mastermind_Game::getChoice()
{
	int choice;
	std::cout << "Enter the corresponding number to play Mastermind as the:\n"
		<< "\t1) Code Breaker, and have the Computer create a random number\n"
		<< "\t2) Code Maker, and have the Computer guess the number.\n";
	while (!(std::cin >> choice)
		|| !((choice == 1) || (choice == 2)))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Improper Input. Enter Again:\n";
	}

	return choice;
}

int Mastermind_Game::askToPlayAgain()
{
	std::cout << "Would you like to play again?:\n"
		<< "\t1) Yes.\n"
		<< "\t2) No.\n";
	int choice = 0;	//

	while (!(std::cin >> choice)
		|| !((choice == 1) || (choice == 2)))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Improper Input. Enter Again:\n";
	}
	return choice;
}