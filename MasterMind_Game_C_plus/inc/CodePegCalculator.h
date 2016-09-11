/*
 * CodePegCalculator.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
 */

#ifndef CODEPEGCALCULATOR_H_
#define CODEPEGCALCULATOR_H_

class CodePeg;
class KeyPeg;

class CodePegCalculator {
private:
	CodePeg *pCodePegFactory ;
	CodePeg *pCodePegGuess ;
	KeyPeg  *pKeyPeg ;
public:
	CodePegCalculator(CodePeg *codePegFactory, CodePeg *codePegGuess, KeyPeg *keyPeg);
	virtual ~CodePegCalculator();
	void CalculatorResult(int userGuess[]);
	KEY_PEG_RESULT GetResult(int *pBlackQuantity,int *pWhiteQuantity, int *pNoneQuantity);
};

#endif /* CODEPEGCALCULATOR_H_ */
