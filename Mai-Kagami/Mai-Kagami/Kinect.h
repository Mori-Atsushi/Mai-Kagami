#ifndef __KINECT_H_INCLUDED__
#define __KINECT_H_INCLUDED__


#include "stdafx.h"
#include <strsafe.h>
#include "DxLib.h"
#include "Main.h"

class Kinect
{
public:
	Kinect(); //�R���X�g���N�^
	void Update(); //�X�V
	boolean CheckDistance(); //�����𑪒�
	~Kinect(); //�f�X�g���N�^
private:
	const float min = 2.0; //�ŒZ����
	Joint userJoints[JointType_Count]; //�֐ߍ��W���
	boolean *userFlag; //���[�U�[�̏��(TRUE:�F������Ă��� / FALSE:�F������Ă��Ȃ�)
	int x;

	// Current Kinect
	IKinectSensor*          m_pKinectSensor;
	ICoordinateMapper*      m_pCoordinateMapper;

	// Body reader
	IBodyFrameReader*       m_pBodyFrameReader;
};

#endif