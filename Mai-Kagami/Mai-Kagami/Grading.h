#ifndef __GRADING_H_INCLUDED__
#define __GRADING_H_INCLUDED__

#include "DxLib.h"
#include <Kinect.h>
#include <map>
#include "Bezier.h"

typedef float flameData[JointType_Count][3];

class FlameGrading {
public:
	FlameGrading(std::map <int, flameData> modelData);
	int Mark(float joints[JointType_Count][3], const int userflame);
	int *MarkPoint(float joints[JointType_Count][3], const int userflame);
private:
	float JointMark(float joints[JointType_Count][3], float model[JointType_Count][3], int x, int y); //2�֐ߊԂ̓_���v�Z
	float FlameMark(float joints[JointType_Count][3], float model[JointType_Count][3]); //1�t���[��������̓_���v�Z
	float LeftHandMark(float joints[JointType_Count][3], float model[JointType_Count][3]); //1�t���[��������̍���_���v�Z
	float RightHandMark(float joints[JointType_Count][3], float model[JointType_Count][3]); //1�t���[��������̉E��_���v�Z
	float LeftFootMark(float joints[JointType_Count][3], float model[JointType_Count][3]); //1�t���[��������̍����_���v�Z
	float RightFootMark(float joints[JointType_Count][3], float model[JointType_Count][3]); //1�t���[��������̉E���_���v�Z
	std::map <int, flameData> modelData;
	int modelflame, j;
	float model[JointType_Count][3];
};

class Grading {
public:
	Grading();
	void Mark(const char *model, std::map <int, flameData> userData, const int userflame);
	~Grading();
protected:
	int total; //�������_
	char comment[1024]; //�R�����g
	int point[4]; //���ʕʓ��_
	int score[100] = {}; //��ԕʓ��_
	int max; //��ԕʓ��_�̓_�̐�
	int timing; //�^�C�~���O
	int expression; //�\��
private:
	int Adjust(int point); //�_����0~100�͈̔͂ɂȂ�悤�ɒ���
	void Copy(float dst[JointType_Count][3], float source[JointType_Count][3]);
	Bezier *bezier;
};

#endif