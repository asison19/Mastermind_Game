/*

*/

#include "Mastermind_Maker.h"

void Mastermind_Maker::play()
{
	std::cout << "Playing as the code creator.\n";
	createCode();
	//creates a set of numbers from 0000 to 9999
	for (int i = 0; i < SET_SIZE; i++)
		this->set[i] = i;
	//calls itself until it finds the player's code

	if (!computerCheckRecursion(1122))
	{
		computerCheckRecursion(set[0]);	//we do this because the computer skips set[0]
	}
}

void Mastermind_Maker::displayAnswer()
{
	std::cout << "The correct answer was ";
	for (int i = 0; i < pegHoleAmount; i++)
		std::cout << this->pegVector.at(i) << " ";
	std::cout << "\n\n";
}

void Mastermind_Maker::createPlayerCode(int inputCode)
{
	//separate the pegGuess into digits in reverse order
	int temp = inputCode;

	for (int i = 0; i < pegHoleAmount; i++)
	{
		if (temp == 0)
		{
			this->tempPegVector.push_back(0);
		}
		else
		{
			this->tempPegVector.push_back(temp % 10);
		}
		temp = temp / 10;
	}

	//creates pegVector and puts tempPegVector in proper order
	while (!tempPegVector.empty())
	{
		pegVector.push_back(tempPegVector.back());
		tempPegVector.pop_back();
	}
	for (int i = 0; i < pegHoleAmount; i++)
	{
		tempPegVector.push_back(pegVector.at(i));
	}
}
void Mastermind_Maker::createCode()
{
	int inputCode = 0;
	std::cout << "Enter a " << pegHoleAmount << " digit number for the Computer to guess:\t";
	std::cin >> inputCode;
	int val = 10000;
	if (inputCode >= val)
	{
		std::cout << "Too many Digits.\n";
		createCode();
	}
	else if (inputCode < 0)
	{
		std::cout << "Invalid Entry. Number was negative\n";
		createCode();
	}
	else
	{
		isComputerCodeBreaker = true;
		//has proper input code
		createPlayerCode(inputCode);
		std::cout << "You entered:\t";
		for (int i = 0; i < pegHoleAmount; i++)
			std::cout << pegVector.at(i) << " ";
		std::cout << "\n";
	}
}

bool Mastermind_Maker::computerCheckRecursion(int computerGuess)
{
	reZero();
	createPegGuessVectors(computerGuess);
	std::cout << "The computer Guesses: ";
	for (int i = 0; i < pegHoleAmount; i++)
	{
		std::cout << pegGuessVector.at(i) << " ";
	}
	std::cout << "\n";

	//actual checking of the computer's answer
	if (!checkAnswer())
	{
		//computer hasn't won and continues here
		set[computerGuess] = NULL;	//this was the wrong guess leading it here
		computerTries++;
		//remove from set all the values that won't give you the same hints
		for (int i : set)
		{
			if (!checkComputerSetGuess(set[i]))
			{
				set[i] = NULL;
			}
		}
		for (int j : set)
		{
			//computer skips set[0], which is 0 because it believes it is equal to NULL
			if (set[j] != NULL)
			{
				//because the computer haasn't won, it will make another guess
				//the next guess will be the next available possible solution
				return computerCheckRecursion(set[j]);
			}
		}
		return false;
	}
	else
	{
		//computer has won and continues here
		displayAnswer();
		std::cout << "Computer Wins in " << computerTries << " tries.\n";

		return true;
	}
}

void Mastermind_Maker::reZero()
{
	this->amountCorrectPosition = 0;
	this->amountCorrect = 0;
	while (!pegGuessVector.empty())
		pegGuessVector.pop_back();
	while (!tempPegGuessVector.empty())
		tempPegGuessVector.pop_back();
	while (!tempPegVector.empty())
		tempPegVector.pop_back();

	createTempPegVector();
}

void Mastermind_Maker::reset()
{
	while (!tempPegGuessVector.empty())
		tempPegGuessVector.pop_back();
	while (!tempPegVector.empty())
		tempPegVector.pop_back();
	while (!setVector.empty())
		setVector.pop_back();
	while (!tempSetVector.empty())
		tempSetVector.pop_back();

	createTempPegVector();
}

bool Mastermind_Maker::checkComputerSetGuess(int setNumber)
{
	int tempAmountCorrectPosition = 0;
	int tempAmountCorrect = 0;

	reset();

	//separate the tempSetVector into digits in reverse order
	int temp = setNumber;
	for (int i = 0; i < pegHoleAmount; i++)
	{
		if (temp == 0)
		{
			this->tempSetVector.push_back(0);
		}
		else
		{
			this->tempSetVector.push_back(temp % 10);
		}
		temp = temp / 10;
	}

	//creates setVector with it and puts tempSetVector in proper order
	while (!tempSetVector.empty())
	{
		setVector.push_back(tempSetVector.back());
		tempSetVector.pop_back();
	}
	for (int i = 0; i < pegHoleAmount; i++)
	{
		tempSetVector.push_back(setVector.at(i));
	}

	//check for amount of digits that are proper
	for (int i = 0; i < pegHoleAmount; i++)
	{
		if (setVector.at(i) == pegGuessVector.at(i))
		{
			tempAmountCorrectPosition++;

			tempSetVector.at(i) = 10;
		}
	}
	for (int i = 0; i < pegHoleAmount; i++)
	{
		checkSetNumber(i, tempAmountCorrect);
	}
	if ((tempAmountCorrect == amountCorrect) && (tempAmountCorrectPosition == amountCorrectPosition))
	{
		return true;
	}
	else return false;
}



void Mastermind_Maker::createTempPegVector()
{
	for (int i = 0; i < pegHoleAmount; i++)
	{
		tempPegVector.push_back(pegVector.at(i));
	}
}

void Mastermind_Maker::checkSetNumber(int i, int &tempAmountCorrect)
{
	for (int j = 0; j < pegHoleAmount; j++)
	{
		if (tempSetVector.at(j) == pegGuessVector.at(i)
			&& !(i == j))
		{
			tempAmountCorrect++;
			tempSetVector.at(j) = 100;
			return;
		}
	}
}

/*
Checks if the answer is correct and 
makes the clues for the digits necessary.
*/
bool Mastermind_Maker::checkAnswer()
{
	//check for amount of digits that are proper
	for (int i = 0; i < pegHoleAmount; i++)
	{
		if (tempPegVector.at(i) == pegGuessVector.at(i))
		{
			amountCorrectPosition++;
			tempPegVector.at(i) = 10;
			if (!isComputerCodeBreaker)
				pegGuessVector.at(i) = 11; //so it won't find the same one twice
		}
	}
	//check for amount of digits that are right but wrong position
	for (int i = 0; i < pegHoleAmount; i++)
	{
		checkNumber(i);
	}

	return (amountCorrectPosition == pegHoleAmount);
}

void Mastermind_Maker::checkNumber(int i)
{
	for (int j = 0; j < pegHoleAmount; j++)
	{
		if (tempPegVector.at(j) == pegGuessVector.at(i)
			&& !(i == j))
		{
			amountCorrect++;
			tempPegVector.at(j) = 100;
			return;
		}
	}
}

void Mastermind_Maker::createPegGuessVectors(int val)
{
	//separate the answer variable into seperate digits to the tempPegGuessVector
	//in reverse order
	int temp = val;
	for (int i = 0; i < pegHoleAmount; i++)
	{
		if (temp == 0)
		{
			this->tempPegGuessVector.push_back(0);
		}
		else
		{
			this->tempPegGuessVector.push_back(temp % 10);
		}
		temp = temp / 10;
	}

	//put pegGuessVector and tempPegGuessVector in proper order
	while (!tempPegGuessVector.empty())
	{
		pegGuessVector.push_back(tempPegGuessVector.back());
		tempPegGuessVector.pop_back();
	}
	for (int i = 0; i < pegHoleAmount; i++)
	{
		tempPegGuessVector.push_back(pegGuessVector.at(i));
	}
}