/*
 * CodePegCalculator.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
  * Site: http://letrungthang.blogspot.com
 */

#include "Common.h"
#include "CodePeg.h"
#include "KeyPeg.h"

#include "CodePegCalculator.h"


CodePegCalculator::CodePegCalculator(CodePeg *codePegFactory, CodePeg *codePegGuess, KeyPeg *keyPeg)
{
	pCodePegFactory = codePegFactory;
	pCodePegGuess = codePegGuess;
	pKeyPeg = keyPeg;

}

CodePegCalculator::~CodePegCalculator()
{
	// TODO Auto-generated destructor stub
}

void CodePegCalculator::CalculatorResult(int userGuess[])
{
	int blackQuantity = 0;
	int whiteQuantity = 0;
	int actualWhiteQuantity = 0;
	int curTryTimes = 0;

	// fill up user's guess to current CodePeg list
	for(int i=0; i<4; i++)
	{
		pCodePegGuess[i].setCodePegColor((PEG_COLOR)(userGuess[i*2]));
		pCodePegGuess[i].setCodePegPosition((PEG_POSITION)(userGuess[(i*2)+1]));
	}

	//update current tried times
	curTryTimes = pKeyPeg->getCurTryTime();
	curTryTimes++;
	pKeyPeg->setCurTryTime(curTryTimes);

	// reset IsChecked marker of CodePeg
	for(int i=0; i<4; i++)
	{
		pCodePegFactory[i].IsChecked = false;
		pCodePegGuess[i].IsChecked = false ;
	}

	// Now, start comparing current CodePeg list with machine generation CodePeg list
	// 1. We check WHITE condition first, don't care BLACK condition. So only comparing color
	for(int i=0; i<4; i++)
	{
		for(int j =0; j<4; j++)
		{
			if(pCodePegGuess[i].getCodePegColor() == pCodePegFactory[j].getCodePegColor())
			{
				if((pCodePegFactory[j].IsChecked == false) && (pCodePegGuess[i].IsChecked == false))
				{
					pCodePegFactory[j].IsChecked = true; // mark it. we not check it again in next round
					pCodePegGuess[i].IsChecked = true; // mark it. we not check it again in next round
					whiteQuantity ++;
				}
			}

		}

	}
	// 2. Then we check BLACK condition: comparing both color and position
	for(int i=0; i<4; i++)
	{
		if((pCodePegGuess[i].getCodePegColor() == pCodePegFactory[i].getCodePegColor()) &&
		(pCodePegGuess[i].getCodePegPosition() == pCodePegFactory[i].getCodePegPosition()))
		{
			blackQuantity ++ ; // right color and right position
		}
	}

	// 3. calculate actual WHITE quantity
	actualWhiteQuantity = whiteQuantity - blackQuantity ;

	// 4. set result to KeyPeg
	pKeyPeg->AddKeyPegResult(blackQuantity, actualWhiteQuantity);

}

// get result after calculation
KEY_PEG_RESULT CodePegCalculator::GetResult(int *pBlackQuantity,int *pWhiteQuantity, int *pNoneQuantity)
{
	return pKeyPeg->GetKeyPegResult(pBlackQuantity, pWhiteQuantity, pNoneQuantity);
}

