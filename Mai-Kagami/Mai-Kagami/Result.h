#ifndef __RESULT_H_INCLUDED__
#define __RESULT_H_INCLUDED__

#include "DxLib.h"

class Result {
public:
	void Calc();
	float GetTotal(); //総合得点取得
private:
	float total; //総合得点
};

#endif