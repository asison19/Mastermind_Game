/*

*/

#include "Mastermind_Breaker.h"

Mastermind_Breaker::Mastermind_Breaker()
{

}

Mastermind_Breaker::~Mastermind_Breaker()
{

}

void Mastermind_Breaker::play()
{
	createPegs();
	collectPlayerPegs();
}

void Mastermind_Breaker::createPegs()
{
	srand(time(NULL));
	for (int i = 0; i < pegHoleAmount; i++)
		this->pegVector.push_back(rand() % pegAmount);	//gives vector single digit numbers
	createTempPegVector();
}
void Mastermind_Breaker::collectPlayerPegs()
{
	//TODO, add way for player to quit
	bool isGameComplete;

	do{
		//check if the user input exceeds the digit amount
		//error checking fails after pegHoleAmount is greater than 9
		bool isCorrectInput;
		do
		{
			std::cout << "Enter the " << pegHoleAmount << " digit number you think it is: ";
			std::cin >> pegGuess;
			
			//
			reZero();
			amountCorrectPosition = 0;
			amountCorrect = 0;

			if (pegGuess >= pow(10, pegHoleAmount))
			{
				isCorrectInput = false;
				std::cout << "Improper input. ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{
				isCorrectInput = true;
			}
		} while (!isCorrectInput);

		createPegGuessVectors(pegGuess);
		displayUserInput();	//display user's input

		//actual checking of the user's answer
		if (checkAnswer())
		{
			std::cout << "\nYou Win! ";
			displayAnswer();
			isGameComplete = true;
		}
		else
		{
			std::cout << "\nAmount in the correct position: " << amountCorrectPosition
				<< "\nAmount correct, but wrong position:  " << amountCorrect << "\n\n";
			std::cout << "Try Again\n\n";
			//flush buffer an reset stream state
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			isGameComplete = false;
		}
	} while (!isGameComplete);
}
void Mastermind_Breaker::createTempPegVector()
{
	for (int i = 0; i < pegHoleAmount; i++)
	{
		tempPegVector.push_back(pegVector.at(i));
	}
}

void Mastermind_Breaker::reZero()
{
	while (!pegGuessVector.empty())
		pegGuessVector.pop_back();
	while (!tempPegGuessVector.empty())
		tempPegGuessVector.pop_back();
	while (!tempPegVector.empty())
		tempPegVector.pop_back();

	createTempPegVector();
}
void Mastermind_Breaker::createPegGuessVectors(int val)
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
void Mastermind_Breaker::displayUserInput()
{
	std::cout << "Entered: ";
	for (int i = 0; i < pegHoleAmount; i++)
		std::cout << " " << pegGuessVector.at(i);
}

bool Mastermind_Breaker::checkAnswer()
{
	//check for amount of digits that are correct and in the proper position
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

	//check for amount of digits that are correct but in the wrong position
	for (int i = 0; i < pegHoleAmount; i++)
	{
		checkNumber(i);
	}

	return (amountCorrectPosition == pegHoleAmount);
}
void Mastermind_Breaker::checkNumber(int i)
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

void Mastermind_Breaker::displayAnswer()
{
	std::cout << "The correct answer was ";
	for (int i = 0; i < pegHoleAmount; i++)
		std::cout << this->pegVector.at(i) << " ";
	std::cout << "\n\n";
}