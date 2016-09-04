#include "Kinect.h"

//�R���X�g���N�^
Kinect::Kinect() {
	if (KINECT_FLAG) {
		userFlag = new boolean();
		HRESULT hr;

		hr = GetDefaultKinectSensor(&m_pKinectSensor);
		if (FAILED(hr))
			exit(-1);

		if (m_pKinectSensor)
		{
			IBodyFrameSource* pBodyFrameSource = NULL;

			hr = m_pKinectSensor->Open();

			if (SUCCEEDED(hr))
			{
				hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
			}

			if (SUCCEEDED(hr))
			{
				hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
			}

			if (SUCCEEDED(hr))
			{
				hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
			}

			SafeRelease(pBodyFrameSource);
		}

		if (!m_pKinectSensor || FAILED(hr))
			exit(-1);
	}
}

void Kinect::Update() {
	if (KINECT_FLAG) {
		static boolean updateFlag = TRUE; //�X�V�p�̃t���O�A2��Ɉ�񂵂����������Ȃ�
		if (updateFlag) {
			*userFlag = FALSE;
			userJoints[0].Position.Z = 100;

			if (!m_pBodyFrameReader)
			{
				return;
			}

			IBodyFrame* pBodyFrame = NULL;

			HRESULT hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);

			if (SUCCEEDED(hr))
			{
				INT64 nTime = 0;

				hr = pBodyFrame->get_RelativeTime(&nTime);

				IBody* ppBodies[BODY_COUNT] = { 0 };

				if (SUCCEEDED(hr))
				{
					hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
				}
				if (SUCCEEDED(hr))
				{
					hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
				}

				if (SUCCEEDED(hr))
				{
					for (int i = 0; i < BODY_COUNT; ++i) {
						IBody* pBody = ppBodies[i];
						if (pBody)
						{
							BOOLEAN bTracked = false;
							hr = pBody->get_IsTracked(&bTracked);

							if (SUCCEEDED(hr) && bTracked) {
								Joint joints[JointType_Count];
								hr = pBody->GetJoints(_countof(joints), joints);
								if (SUCCEEDED(hr))
								{
									if (joints[0].Position.Z >= min && joints[0].Position.Z < userJoints[0].Position.Z) {
										*userFlag = TRUE;
										for (int i = 0; i < JointType_Count; i++)
											userJoints[i] = joints[i];
									}
								}
							}
						}
					}
				}

				for (int i = 0; i < _countof(ppBodies); ++i)
				{
					SafeRelease(ppBodies[i]);
				}
			}
			SafeRelease(pBodyFrame);
			updateFlag = FALSE;
		}
		else {
			updateFlag = TRUE;
		}
	}
}

//�����𑪒�
boolean Kinect::CheckDistance() {
	if (KINECT_FLAG) {
		if (*userFlag)
			return TRUE;
	}
	else {
		if (CheckHitKey(KEY_INPUT_N) == 1)
			return TRUE;
	}
	return FALSE;
}

//�f�X�g���N�^
Kinect::~Kinect()
{
	if (KINECT_FLAG) {
		SafeRelease(m_pBodyFrameReader);

		// done with coordinate mapper
		SafeRelease(m_pCoordinateMapper);

		// close the Kinect Sensor
		if (m_pKinectSensor)
			m_pKinectSensor->Close();

		SafeRelease(m_pKinectSensor);
	}
}