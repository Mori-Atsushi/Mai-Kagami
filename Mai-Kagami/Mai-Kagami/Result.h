#ifndef __RESULT_H_INCLUDED__
#define __RESULT_H_INCLUDED__

#include <time.h>

#include "DxLib.h"
#include "Songs.h"
#include "User.h"
#include "Grading.h"
#include "Http.h"
#include "Kinect.h"

class Result : public Grading {
public:
	Result(Songs *songs, User *user, Kinect *kinect);
	void Calc(); //���_�v�Z
	void Send(); //���M
	float GetTotal(); //�������_�擾
	void GetPoint(int x[4]); //���ʕʓ��_�擾
	char *GetComment(); //�R�����g�擾
	int GetTiming(); //�^�C�~���O�擾
	int GetExpression(); //�\��擾
	int GetScore(int x[100]); //��ԕʓ��_�擾
private:
	void GetNowTime(int nowTime[]);
	char comment[1024]; //�R�����g
	Songs *songs;
	User *user;
	Kinect *kinect;
};

#endif