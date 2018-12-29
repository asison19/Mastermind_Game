/*
Player is the maker of the code while the computer is the breaker
*/

#ifndef MASTERMIND_MAKER
#define MASTERMIND_MAKER

#include <vector>
#include <iostream>

class Mastermind_Maker
{
private:
	int pegHoleAmount = 4;
	bool isComputerCodeBreaker;
	std::vector<int> tempPegVector; //contains a temporary version of the answer used for making the clues
	std::vector<int> pegVector; //contains the answer that the player has made
	//TODO change if not needed for player as the code maker
	std::vector<int> pegGuessVector;    //vector used for the player's guess
	std::vector<int> tempPegGuessVector;    //vector used for the player's guess and it's error handling/duplication
	std::vector<int> setVector; //vector to check what gets the same result as pegGuessVector in array, set
	std::vector<int> tempSetVector;	//temporary setVector

	const static int SET_SIZE = 10000;	//size for set, 10^4
	int set[SET_SIZE] = {};	//set for the number of guesses from 0-9999 that is possible

	int amountCorrectPosition = 0;  //the amount of guesses that are in the correct position
	int amountCorrect = 0;  //amount of guesses correct, but in the wrong position
	int computerTries = 1;	//amount of tries computer has made, it will always need to try once

	void displayAnswer();	//display answer
	void createPlayerCode(int);
	void createCode();
	bool computerCheckRecursion(int computerGuess);	//computer guesses for the code based on Donald Knuth's algorithm
	void reZero();	//changes amountCorrect and amountCorrectPostion back to zero, preparing for the next guess

	bool checkComputerSetGuess(int setNumber);	//checks for the right computer guesses that would give the same hints
	void reset();	//empties tempPegGuessVector, tempPegVector, setVector and tempsetVector; calls creteTempPegVector()

	void createTempPegVector();	//creates the temporary peg vector, used in reZero to prepare for the next guess

	void checkSetNumber(int index, int &);	//checks for amount right but wrong position in the set
	bool checkAnswer();	//checks all numbers, used for both playGame and playComputer
	
	void checkNumber(int index);	//checks digit for any correct ones
	void createPegGuessVectors(int val);	//creates and sorts both pegGuess vectors
public:
	void play(); //starts the game with the human as the code maker
};

#endif