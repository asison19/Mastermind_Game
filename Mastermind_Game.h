#ifndef MASTERMIND_GAME
#define MASTERMIND_GAME

/*
file: Mastermind_Game.h
header for Mastermind_Game.cpp
*/

class Mastermind_Game
{
private:
	int getChoice();
	int askToPlayAgain();
public:
	Mastermind_Game();  //constructor
	~Mastermind_Game(); //destructor
	void playGame();
};

#endif