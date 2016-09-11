/*
 * Configurator.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Thang Le
 */

#ifndef CONFIGURATOR_H_
#define CONFIGURATOR_H_

class CodePeg;
class KeyPeg;

// this class configured and generated objects

class Configurator {
private:
	CodePeg * pCodePegFactory ;
	KeyPeg  *pKeyPeg;
	unsigned int CreateRandomColor(unsigned int lowEnd, unsigned int highEnd);

public:
	Configurator(CodePeg *codePegFactory, KeyPeg *keyPeg);
	virtual ~Configurator();
	void 	GenerateCodePegKeyPeg(int maxColor, int tryTimes);
};

#endif /* CONFIGURATOR_H_ */
