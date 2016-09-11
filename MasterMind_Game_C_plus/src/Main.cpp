//============================================================================
// Name        : Main.cpp
// Author      : Thang Le 
// Site: 	   :http://letrungthang.blogspot.com
// Version     : 1.0
// Copyright   : No need lal
// Description : MasterMind game
//============================================================================

#include <iostream>

#include "Common.h"
#include "CodePeg.h"
#include "KeyPeg.h"
#include "InputValidator.h"
#include "Configurator.h"
#include "CodePegCalculator.h"

using namespace std;

CodePeg 	*pArrCodePegFactory ;  			// CodePeg is generated randomly by machine
CodePeg 	*pArrCodePegGuess ; 			// CodePeg user guesses
KeyPeg		*pKeyPeg ; 						// keep the result after user guess
InputValidator 		*pInputValidator; 		// validate user's input
Configurator 		*pConfigurator; 		// setup game before playing
CodePegCalculator 	*pCodePegCalculator ; 	// calculate result from user input


// init resource
void AppInit()
{
	pArrCodePegFactory 		= new CodePeg[4] ; // we support only 4 holes per row
	pArrCodePegGuess		= new CodePeg[4];
	pKeyPeg 				= new KeyPeg();

	pConfigurator 			= new Configurator(pArrCodePegFactory, pKeyPeg);
	pCodePegCalculator 		= new CodePegCalculator(pArrCodePegFactory, pArrCodePegGuess, pKeyPeg);

	pInputValidator 		= new InputValidator(pConfigurator, pCodePegCalculator);
}

// cleanup resource
void AppDeInit()
{
	if(pArrCodePegFactory !=NULL) 	delete[] pArrCodePegFactory ;
	if(pArrCodePegGuess !=NULL) 	delete[] pArrCodePegGuess	;
	if(pKeyPeg !=NULL) 				delete pKeyPeg 				;

	if(pConfigurator !=NULL) 		delete pConfigurator 		;
	if(pCodePegCalculator !=NULL) 	delete pCodePegCalculator 	;
	if(pInputValidator !=NULL) 		delete pInputValidator 		;
}

int main() {

	AppInit(); // initialize application

	pInputValidator->GameSart(); // start game

	AppDeInit(); // Deinitialize application

	return 0;
}
