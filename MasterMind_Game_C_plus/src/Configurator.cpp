/*
 * Configurator.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
  * Site: http://letrungthang.blogspot.com
 */

#include <math.h>
#include <ctime>
#include <cstdlib>

#include "Common.h"
#include "CodePeg.h"
#include "KeyPeg.h"

#include "Configurator.h"


Configurator::Configurator(CodePeg *codePegFactory, KeyPeg *keyPeg)
{
	pCodePegFactory = codePegFactory;
	pKeyPeg = keyPeg ;
}

Configurator::~Configurator()
{
	// TODO Auto-generated destructor stub
}

unsigned int Configurator::CreateRandomColor(unsigned int lowEnd, unsigned int highEnd)
{
    if(highEnd < lowEnd)
    {
        unsigned int tempForSwap = highEnd;
        highEnd = lowEnd;
        lowEnd = tempForSwap;
    }

    int rangeVal = (highEnd - lowEnd) + 1;
    return (std::rand() % rangeVal) + lowEnd;
}

// we generate CodePeg here based on input data from user
void Configurator::GenerateCodePegKeyPeg(int maxColor, int tryTimes)
{
	PEG_COLOR pegColor;

	//set max color for CodePeg
	pCodePegFactory[0].setPegMaxColor(maxColor);

	for(int i = 0; i<4;i++)
	{
		// generate random color for each CodePeg
		 pegColor = (PEG_COLOR)(CreateRandomColor(1, maxColor));
		 // set random color to each CodePeg
		 pCodePegFactory[i].setCodePegColor(pegColor);
		 //set CodePeg position, because color is random, for simple, we no need random for position
		 pCodePegFactory[i].setCodePegPosition((PEG_POSITION)(i+1));
	}
	// set maxTryTimes for KeyPeg that user want to try
	pKeyPeg->setMaxTryTime(tryTimes);

}

