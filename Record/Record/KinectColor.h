#ifndef __KINECTCOLOR_H_INCLUDED__
#define __KINECTCOLOR_H_INCLUDED__

#include "Main.h"
#include <Kinect.h>
#include <opencv2/opencv.hpp>
#include "DxLib.h"
#include "stdafx.h"

class KinectColor
{
public:
	KinectColor(IKinectSensor *m_pKinectSensor); //�R���X�g���N�^
	void Update(); //�X�V
	void View();
	~KinectColor(); //�f�X�g���N�^
private:
	int *width, *height; //�f���̏c���s�N�Z��
	unsigned int *bufferSize; //�f���T�C�Y
	cv::Mat *bufferMat;
	cv::Mat *colorMat;
	int handle; //�O���t�B�b�N�n���h��
	BASEIMAGE baseImage;
	IColorFrameReader* m_pColorFrameReader;
};

#endif