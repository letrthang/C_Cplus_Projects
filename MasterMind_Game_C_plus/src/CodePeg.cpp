/*
 * CodePeg.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
 * Site: http://letrungthang.blogspot.com
 */

#include "Common.h"
#include "CodePeg.h"

// init static var
int CodePeg::PegMaxColor = 0; // maximum number color of code peg


CodePeg::CodePeg() {
	// TODO Auto-generated constructor stub
	PegColor = NONE_COLOR;
	PegPosition = NONE_POSITION ;
	IsChecked = false;

}

CodePeg::~CodePeg() {
	// TODO Auto-generated destructor stub
}

// set CodePegColor
void CodePeg::setCodePegColor(PEG_COLOR pegColor)
{
	PegColor = pegColor;
}

// get CodePegColor
PEG_COLOR CodePeg::getCodePegColor( )
{
	return PegColor;

}

//set CodePegPosition
void CodePeg::setCodePegPosition(PEG_POSITION pegPosition)
{
	PegPosition = pegPosition;
}

//get CodePegPosition
PEG_POSITION CodePeg::getCodePegPosition()
{
	return PegPosition;
}

void CodePeg::setPegMaxColor(int pegMaxColor)
{
	PegMaxColor = pegMaxColor;
}

int CodePeg::getPegMaxColor()
{
	return PegMaxColor ;
}



