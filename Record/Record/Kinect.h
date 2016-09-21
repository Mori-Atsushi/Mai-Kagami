#ifndef __KINECT_H_INCLUDED__
#define __KINECT_H_INCLUDED__

#include "stdafx.h"
#include <strsafe.h>
#include "DxLib.h"
#include "KinectBody.h"
#include "KinectColor.h"

class Kinect
{
public:
	Kinect(); //�R���X�g���N�^
	void Update(); //�X�V
	void View(); //�`��
	~Kinect(); //�f�X�g���N�^
	KinectBody *kinectBody;
	KinectColor *kinectColor;
private:
	// Current Kinect
	IKinectSensor *m_pKinectSensor;
};

#endif