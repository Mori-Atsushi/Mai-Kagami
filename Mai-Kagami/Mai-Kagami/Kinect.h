#ifndef __KINECT_H_INCLUDED__
#define __KINECT_H_INCLUDED__


#include "stdafx.h"
#include <strsafe.h>
#include "DxLib.h"
#include "Main.h"

class Kinect
{
	static const int        cDepthWidth = 512;
	static const int        cDepthHeight = 424;

public:
	Kinect(); //�R���X�g���N�^
	void Update(); //�X�V
	~Kinect(); //�f�X�g���N�^
private:
	Joint userJoints[JointType_Count]; //�֐ߍ��W���
	boolean userFlag; //���[�U�[�̏��(TRUE:�F������Ă��� / FALSE:�F������Ă��Ȃ�)

	// Current Kinect
	IKinectSensor*          m_pKinectSensor;
	ICoordinateMapper*      m_pCoordinateMapper;

	// Body reader
	IBodyFrameReader*       m_pBodyFrameReader;
};

#endif