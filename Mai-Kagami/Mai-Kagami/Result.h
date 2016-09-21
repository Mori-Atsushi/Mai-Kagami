#ifndef __RESULT_H_INCLUDED__
#define __RESULT_H_INCLUDED__

#include "DxLib.h"
#include "Songs.h"
#include "User.h"

class Result {
public:
	Result(Songs *songs, User *user);
	void Calc(); //���_�v�Z
	void Send(); //���M
	float GetTotal(); //�������_�擾
	void GetPoint(int x[4]); //���ʕʓ��_�擾
	char *GetComment(); //�R�����g�擾
	int GetTiming(); //�^�C�~���O�擾
	int GetExpression(); //�\��擾
	int GetScore(int x[100]); //��ԕʓ��_�擾
private:
	float total; //�������_
	char comment[1024]; //�R�����g
	int point[4]; //���ʕʓ��_
	int score[100]; //��ԕʓ��_
	int max; //��ԕʓ��_�̓_�̐�
	int timing; //�^�C�~���O
	int expression; //�\��
	Songs *songs;
	User *user;
};

#endif