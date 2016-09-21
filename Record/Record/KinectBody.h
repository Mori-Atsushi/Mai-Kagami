#ifndef __KINECTBODY_H_INCLUDED__
#define __KINECTBODY_H_INCLUDED__

#include <Kinect.h>
#include "DxLib.h"
#include "stdafx.h"

class KinectBody
{
public:
	KinectBody(IKinectSensor *m_pKinectSensor); //�R���X�g���N�^
	void Update(); //�X�V
	void JointSave(const int flame); //�ۑ�
	~KinectBody(); //�f�X�g���N�^
private:
	boolean *userFlag; //���[�U�[�̏��(TRUE:�F������Ă��� / FALSE:�F������Ă��Ȃ�)
	Joint userJoints[JointType_Count];

	// Body reader
	IBodyFrameReader*       m_pBodyFrameReader;

	FILE *fp;
};

#endif