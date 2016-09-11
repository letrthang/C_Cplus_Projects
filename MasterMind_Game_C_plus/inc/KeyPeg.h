/*
 * KeyPeg.h
 *
 *  Created on: Jan 24, 2015
 *      Author: thangle
 */

#ifndef KEYPEG_H_
#define KEYPEG_H_

class KeyPeg {
private:
	static int 			MaxTryTime ; // maximum number of times user can try
	static int 			CurTryTime ; // current number of times tried
	int 				BlackQuantity ;
	int 				WhiteQuantity ;
	int 				NoneQuantity ;

public:

	KeyPeg();
	virtual ~KeyPeg();

	void setMaxTryTime(int maxTryTime);
	int  getMaxTryTime();

	void setCurTryTime(int curTryTime);
	int  getCurTryTime();


	void AddKeyPegResult(int blackQuantity, int whiteQuantity);
	KEY_PEG_RESULT GetKeyPegResult(int *pBlackQuantity,int *pWhiteQuantity, int *pNoneQuantity);

};

#endif /* KEYPEG_H_ */
