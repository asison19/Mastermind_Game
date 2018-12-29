/*
Player is the breaker of the code while the computer is the maker
*/
#include <time.h>
#include <random>
#include <iostream>
class Mastermind_Breaker
{
private:
	int pegHoleAmount = 4;
	int pegAmount = 10; //the stuff the player has to guess for
	std::vector<int> pegVector;	//contains the pegs that the player guesses for
	int pegGuess;   //the integer value of what the player guesses
	int amountCorrectPosition = 0;  //the amount of guesses that are in the correct position
	int amountCorrect = 0;  //amount of guesses correct, but in the wrong position
	std::vector<int> pegGuessVector;    //vector used for the player's guess
	std::vector<int> tempPegGuessVector;    //vector used for the player's guess and it's error handling/duplication
	std::vector<int> tempPegVector;	//vector used for the answer and it's error handling/duplication
	bool isComputerCodeBreaker = false;	//to know who's playing what

	void createPegs();
	void collectPlayerPegs();
	void createTempPegVector();
	void reZero();
	void createPegGuessVectors(int val);
	
	void checkNumber(int);

	bool checkAnswer();

	
public:
	Mastermind_Breaker();
	~Mastermind_Breaker();
	void play();
	void displayUserInput();
	void displayAnswer();
};