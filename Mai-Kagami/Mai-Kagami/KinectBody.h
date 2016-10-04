#ifndef __KINECTBODY_H_INCLUDED__
#define __KINECTBODY_H_INCLUDED__

#include <Kinect.h>
#include "DxLib.h"
#include "stdafx.h"
#include "Main.h"
#include "Grading.h"
#include <map>

class KinectBody
{
public:
	KinectBody(IKinectSensor *m_pKinectSensor); //�R���X�g���N�^
	void Update(); //�X�V
	boolean CheckDistance(); //�����𑪒�
	void JointSave(const int flame); //�ۑ�
	std::map <int, flameData> GetSave();
	int GetNow();
	~KinectBody(); //�f�X�g���N�^
private:
	std::map <int, flameData> userData;
	Joint userJoints[JointType_Count]; //�֐ߍ��W���
	boolean *userFlag; //���[�U�[�̏��(TRUE:�F������Ă��� / FALSE:�F������Ă��Ȃ�)
	int now = 0;

	// Body reader
	IBodyFrameReader*       m_pBodyFrameReader;
};

#endif