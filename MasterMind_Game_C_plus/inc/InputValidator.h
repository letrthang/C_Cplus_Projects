/*
 * InputValidator.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
 */

#ifndef INPUTVALIDATOR_H_
#define INPUTVALIDATOR_H_

class Configurator;
class CodePegCalculator;

class InputValidator {
private:
	Configurator 		*pConfigurator;
	CodePegCalculator 	*pCodePegCalculator;
public:
	InputValidator(Configurator *configurator, CodePegCalculator *codePegCalculator);
	virtual ~InputValidator();
	void GameSart(); // start game, ask user input data
};

#endif /* INPUTVALIDATOR_H_ */
