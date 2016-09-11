/*
 * CodePeg.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
 */

#ifndef CODEPEG_H_
#define CODEPEG_H_

class CodePeg {

private:
	PEG_COLOR 		PegColor ; // color of code peg
	PEG_POSITION 	PegPosition; // position of code peg
	static int 		PegMaxColor; // maximum number color of code peg


public:
	bool IsChecked; // was this object checked

	CodePeg();
	virtual ~CodePeg();

	void setCodePegColor(PEG_COLOR pegColor);
	PEG_COLOR getCodePegColor( );

	void setCodePegPosition(PEG_POSITION pegPosition);
	PEG_POSITION getCodePegPosition();

	void setPegMaxColor(int pegMaxColor);
	int  getPegMaxColor();


};

#endif /* CODEPEG_H_ */
