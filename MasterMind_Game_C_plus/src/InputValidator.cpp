/*
 * InputValidator.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
  * Site: http://letrungthang.blogspot.com
 */

#include <iostream>
#include "Common.h"
#include "Configurator.h"
#include "CodePegCalculator.h"

#include "InputValidator.h"

using namespace std;

InputValidator::InputValidator(Configurator *configurator, CodePegCalculator *codePegCalculator)
{
	pConfigurator = configurator;
	pCodePegCalculator = codePegCalculator;

}

InputValidator::~InputValidator() {
	// TODO Auto-generated destructor stub
}

void InputValidator::GameSart()
{
	int maxColor;
	int maxTryTimes;

	char userInput[12];
	int userGuess[8];

	KEY_PEG_RESULT result ;
	int blackQuantity, whiteQuantity, noneQuantity ;

	bool isInputOK = true;

	//1. start getting user's input for setting up the game
	cout << "====== MasterMind @Thang Le ======" << endl;
	do
	{
		cout << "Please set number of color (Min = 1, Max = 6):" << endl; // user input color max
		cin >> maxColor ;
		// validate input
		if((maxColor >= MAX_COLOR) || (maxColor <= 0))
		{
			cout << "Wrong input. Please try again. Range = 1 -> 6 color." << endl;
			isInputOK = false;
		}
		else
		{
			isInputOK = true;
		}
	} while (isInputOK == false);

	do
	{
		cout << "Please set number of time trying to guess:" << endl; // max times want play
		cin >> maxTryTimes ;
		// validate input
		if(maxTryTimes <= 0)
		{
			cout << "Wrong input. Must be not zero. Please try again." << endl ;
			isInputOK = false;
		}
		else
		{
			isInputOK = true;
		}
	}while(isInputOK == false);

	cout << "---------------------------------"<< endl ;
	cout << "You set: number color = "<< maxColor << ", Try times = " << maxTryTimes << endl ;
	cout << "color mapping:    1-> RED,   2-> GREEN,  3-> BLUE,  4-> YELLOW, 5-> PINK, 6-> GREY." << endl ;
	cout << "Position mapping: 1-> FIRST, 2-> SECOND, 3-> THIRD, 4-> FOURTH." << endl ;
	cout << "Input format is: ColorPosition-ColorPosition-ColorPosition-ColorPosition." << endl ;
	cout << "Example: 11-22-33-44." << endl ;
	cout << "KeyPeg mapping: BLACK -> Right Both Color and Position, WHITE-> Only Right Color, NONE -> All wrong." << endl ;


	// 2. setup game: set CodePeg and KeyPeg
	pConfigurator->GenerateCodePegKeyPeg(maxColor, maxTryTimes);

	cout << "----------Game Start------------"<< endl ;
	cout << "Please input your guess. Example: 11-22-33-44."<< endl ;

	// 3. get user's guess. for simple, we ignore validate input from user here
GameContinue:
	cin >> userInput ;

	userGuess[0] = userInput[0] - '0'; // do a simple convert here and to remove dash "-" digit
	userGuess[1] = userInput[1] - '0';
	userGuess[2] = userInput[3] - '0';
	userGuess[3] = userInput[4] - '0';
	userGuess[4] = userInput[6] - '0';
	userGuess[5] = userInput[7] - '0';
	userGuess[6] = userInput[9] - '0';
	userGuess[7] = userInput[10]- '0';

	// 4. process user's input
	pCodePegCalculator->CalculatorResult(userGuess);

	// 5. get result after calculation
	result = pCodePegCalculator->GetResult(&blackQuantity, &whiteQuantity, & noneQuantity);
	cout << "=> BLACK = "<< blackQuantity << ", WHITE = " << whiteQuantity << ", NONE = " << noneQuantity << endl ;

	if(result == WIN)
	{
		cout << "You are victory!!!"<< endl ;
	}
	else if (result == LOSE)
	{
		cout << "Game Over...."<< endl ;
	}
	else
	{
		cout << "Please input your guess again." << endl ;
		goto GameContinue ; // a simple way to repeat the game. should not do in product code ;)
	}

}

