#include "KinectBody.h"

//�R���X�g���N�^
KinectBody::KinectBody(IKinectSensor *m_pKinectSensor) {
	userFlag = new boolean();
	HRESULT hr;

	IBodyFrameSource* pBodyFrameSource = NULL;

	hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);

	if (SUCCEEDED(hr))
	{
		hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
	}

	SafeRelease(pBodyFrameSource);

	if ((fp = fopen("FILE/test.txt", "w")) == NULL) {
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}
}

void KinectBody::Update() {
	*userFlag = FALSE;

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
							*userFlag = TRUE;
							for (int i = 0; i < JointType_Count; i++)
								userJoints[i] = joints[i];
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
}

//�ۑ�
void KinectBody::JointSave(const int flame) {
	static boolean flag = TRUE;
	if (flag) {
		fprintf(fp, "%d:", flame);
		if (*userFlag) {
			for (int i = 0; i < JointType_Count; i++)
				fprintf(fp, "%f,%f,%f|", userJoints[i].Position.X, userJoints[i].Position.Y, userJoints[i].Position.Z);
			putc('\n', fp);
		}
		else {
			fprintf(fp, "-1\n");
		}
		flag = FALSE;
	}
	else {
		flag = TRUE;
	}
}

KinectBody::~KinectBody() {
	fclose(fp);
	SafeRelease(m_pBodyFrameReader);
}