/*
 * KeyPeg.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: thangle
  * Site: http://letrungthang.blogspot.com
 */

#include "Common.h"
#include "KeyPeg.h"

// init static
int KeyPeg::MaxTryTime = 0; // maximum number of times user can try
int KeyPeg::CurTryTime = 0; // current number of times tried

KeyPeg::KeyPeg() {

	BlackQuantity = 0;
	WhiteQuantity = 0;
	NoneQuantity  = 0;

}

KeyPeg::~KeyPeg() {
	// TODO Auto-generated destructor stub
}

void KeyPeg::setMaxTryTime(int maxTryTime)
{
	MaxTryTime = maxTryTime;
}

int KeyPeg::getMaxTryTime()
{
	return MaxTryTime ;
}

void KeyPeg::setCurTryTime(int curTryTime)
{
	CurTryTime = curTryTime;
}

int  KeyPeg::getCurTryTime()
{
	return CurTryTime;
}

// add KeyPeg
void KeyPeg::AddKeyPegResult(int blackQuantity, int whiteQuantity)
{
	BlackQuantity = blackQuantity;
	WhiteQuantity = whiteQuantity;
	NoneQuantity  = 4 - (blackQuantity + whiteQuantity);
}

//get result from KeyPeg
KEY_PEG_RESULT KeyPeg::GetKeyPegResult(int *pBlackQuantity, int *pWhiteQuantity, int *pNoneQuantity)
{
	KEY_PEG_RESULT result = CONTINUE ; // continue the game

	*pBlackQuantity = BlackQuantity;
	*pWhiteQuantity = WhiteQuantity;
	*pNoneQuantity  = NoneQuantity;

	if(BlackQuantity == 4)
	{
		result = WIN; // Win
	}
	if((BlackQuantity < 4) && (CurTryTime >= MaxTryTime))
	{
		result = LOSE; // lost
	}

	return result;
}

