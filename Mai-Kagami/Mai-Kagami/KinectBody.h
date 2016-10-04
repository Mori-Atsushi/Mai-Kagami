#ifndef __KINECTBODY_H_INCLUDED__
#define __KINECTBODY_H_INCLUDED__

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
	void DeleteSave(const int flame = 0); //�w�肵��flame�܂ł̃f�[�^���폜
	std::map <int, flameData> GetSave();
	int GetHappy();
	int GetNow();
	~KinectBody(); //�f�X�g���N�^
private:
	std::map <int, flameData> userData;
	Joint userJoints[JointType_Count]; //�֐ߍ��W���
	boolean *userFlag; //���[�U�[�̏��(TRUE:�F������Ă��� / FALSE:�F������Ă��Ȃ�)
	int happyFace, happySum, happyNum;
	int now = 0;

	// Body reader
	IBodyFrameReader*       m_pBodyFrameReader;

	// Face readers
	IFaceFrameReader*	   m_pFaceFrameReaders[BODY_COUNT];
	// Face sources
	IFaceFrameSource*	   m_pFaceFrameSources[BODY_COUNT];
};

#endif