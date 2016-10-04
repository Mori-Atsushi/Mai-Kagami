#include "Grading.h"

FlameGrading::FlameGrading(std::map <int, flameData> modelData) {
	this->modelData = modelData;
	modelflame = 0, j = 0;
}

int FlameGrading::Mark(float joints[JointType_Count][3], const int userflame) {
	int x = 0, y;

	while (1) {
		if (modelData.count(userflame + x) != 0) {
			y = userflame + x;
			break;
		}
		if (modelData.count(userflame - x) != 0) {
			y = userflame - x;
			break;
		}
		x++;
	}
	return (int)FlameMark(joints, modelData[y]);
}

int *FlameGrading::MarkPoint(float joints[JointType_Count][3], const int userflame) {
	int x = 0, y;
	int point[4];

	while (1) {
		if (modelData.count(userflame + x) != 0) {
			y = userflame + x;
			break;
		}
		if (modelData.count(userflame - x) != 0) {
			y = userflame - x;
			break;
		}
		x++;
	}

	point[0] = (int)LeftHandMark(joints, modelData[y]);
	point[1] = (int)RightHandMark(joints, modelData[y]);
	point[2] = (int)LeftFootMark(joints, modelData[y]);
	point[3] = (int)RightFootMark(joints, modelData[y]);
	return point;
}

//2�֐ߊԂ̓_���v�Z
float FlameGrading::JointMark(float joints[JointType_Count][3], float model[JointType_Count][3], int x, int y) {
	float userv, modelv;
	float inner = 0, userlen = 0, modellen = 0;
	for (int i = 0; i < 3; i++) {
		userv = joints[x][i] - joints[y][i];
		modelv = model[x][i] - model[y][i];
		inner += userv * modelv;
		userlen += pow(userv, 2);
		modellen += pow(modelv, 2);
	}
	userlen = (float)sqrt(userlen);
	modellen = (float)sqrt(modellen);
	float point = (inner / (userlen * modellen));
	if (point > 1)
		point = 100;
	else if (point > 0)
		point = (1 - acos(point) * 2 / DX_PI) * 100;
	else
		point = 0;
	return point * 1;
}

//1�t���[��������̓_���v�Z
float FlameGrading::FlameMark(float joints[JointType_Count][3], float model[JointType_Count][3]) {
	const int MAX = 24;
	float sum = 0;
	int jointNum[MAX][2] = {
		{ JointType_SpineBase		, JointType_SpineMid },
		{ JointType_SpineBase		, JointType_HipLeft },
		{ JointType_SpineBase		, JointType_HipRight },
		{ JointType_SpineMid		, JointType_SpineShoulder },
		{ JointType_Neck			, JointType_SpineShoulder },
		{ JointType_Neck			, JointType_Head },
		{ JointType_ShoulderLeft	, JointType_ElbowLeft },
		{ JointType_ShoulderLeft	, JointType_SpineShoulder },
		{ JointType_ElbowLeft		, JointType_WristLeft },
		{ JointType_WristLeft		, JointType_HandLeft },
		{ JointType_HandLeft		, JointType_HandTipLeft },
		{ JointType_HandLeft		, JointType_ThumbLeft },
		{ JointType_ShoulderRight	, JointType_ElbowRight },
		{ JointType_ShoulderRight	, JointType_SpineShoulder },
		{ JointType_ElbowRight		, JointType_WristRight },
		{ JointType_WristRight		, JointType_HandRight },
		{ JointType_HandRight		, JointType_HandTipRight },
		{ JointType_HandRight		, JointType_ThumbRight },
		{ JointType_HipLeft			, JointType_KneeLeft },
		{ JointType_KneeLeft		, JointType_AnkleLeft },
		{ JointType_AnkleLeft		, JointType_FootLeft },
		{ JointType_HipRight		, JointType_KneeRight },
		{ JointType_KneeRight		, JointType_AnkleRight },
		{ JointType_AnkleRight		, JointType_FootRight } };
	for (int i = 0; i < MAX; i++)
		sum += JointMark(joints, model, jointNum[i][0], jointNum[i][1]);
	return  sum / MAX;
}

//1�t���[��������̍���_���v�Z
float FlameGrading::LeftHandMark(float joints[JointType_Count][3], float model[JointType_Count][3]) {
	const int MAX = 6;
	float sum = 0;
	int jointNum[MAX][2] = {
		{ JointType_ShoulderLeft	, JointType_ElbowLeft },
		{ JointType_ShoulderLeft	, JointType_SpineShoulder },
		{ JointType_ElbowLeft		, JointType_WristLeft },
		{ JointType_WristLeft		, JointType_HandLeft },
		{ JointType_HandLeft		, JointType_HandTipLeft },
		{ JointType_HandLeft		, JointType_ThumbLeft } };
	for (int i = 0; i < MAX; i++)
		sum += JointMark(joints, model, jointNum[i][0], jointNum[i][1]);
	return  sum / MAX;
}

//1�t���[��������̓_���v�Z
float FlameGrading::RightHandMark(float joints[JointType_Count][3], float model[JointType_Count][3]) {
	const int MAX = 6;
	float sum = 0;
	int jointNum[MAX][2] = {
		{ JointType_ShoulderRight	, JointType_ElbowRight },
		{ JointType_ShoulderRight	, JointType_SpineShoulder },
		{ JointType_ElbowRight		, JointType_WristRight },
		{ JointType_WristRight		, JointType_HandRight },
		{ JointType_HandRight		, JointType_HandTipRight },
		{ JointType_HandRight		, JointType_ThumbRight } };
	for (int i = 0; i < MAX; i++)
		sum += JointMark(joints, model, jointNum[i][0], jointNum[i][1]);
	return  sum / MAX;
}

//1�t���[��������̓_���v�Z
float FlameGrading::LeftFootMark(float joints[JointType_Count][3], float model[JointType_Count][3]) {
	const int MAX = 4;
	float sum = 0;
	int jointNum[MAX][2] = {
		{ JointType_SpineBase		, JointType_HipLeft },
		{ JointType_HipLeft			, JointType_KneeLeft },
		{ JointType_KneeLeft		, JointType_AnkleLeft },
		{ JointType_AnkleLeft		, JointType_FootLeft } };
	for (int i = 0; i < MAX; i++)
		sum += JointMark(joints, model, jointNum[i][0], jointNum[i][1]);
	return  sum / MAX;
}

//1�t���[��������̓_���v�Z
float FlameGrading::RightFootMark(float joints[JointType_Count][3], float model[JointType_Count][3]) {
	const int MAX = 4;
	float sum = 0;
	int jointNum[MAX][2] = {
		{ JointType_SpineBase		, JointType_HipRight },
		{ JointType_HipRight		, JointType_KneeRight },
		{ JointType_KneeRight		, JointType_AnkleRight },
		{ JointType_AnkleRight		, JointType_FootRight } };
	for (int i = 0; i < MAX; i++)
		sum += JointMark(joints, model, jointNum[i][0], jointNum[i][1]);
	return  sum / MAX;
}

Grading::Grading() {
	bezier = new Bezier(1.2, 0, 0.5, 1);
}

void Grading::Mark(const char *model, std::map <int, flameData> userData, const int userflame) {
	const int SCORE_FLAME = 500; //���؂肠����̃t���[��

	const char BAR_NUM = 9; //�^�C�~���O�A�\��̃o�[�̐�
	FILE *modelfp;
	FlameGrading *flameGrading[BAR_NUM];
	const int MAX = 1024;
	char modelline[MAX];
	int i = 0, modelflame = 0, sum = 0, count = 0, scoreCount = 0;
	int timingSum[BAR_NUM] = {}, pointSum[4] = {};
	max = 0;

	if ((modelfp = fopen(model, "r")) == NULL) {
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}

	std::map <int, flameData> modelData;

	while (fgets(modelline, MAX, modelfp) != NULL) {
		float model[JointType_Count][3];
		sscanf(modelline, "%d:", &modelflame);

		int num;
		if (modelflame == 0)
			num = 1;
		else
			num = (int)log10((double)modelflame) + 1;

		char *line = modelline + num + 1;
		for (i = 0; i < JointType_Count; i++) {
			if (sscanf(line, "%f,%f,%f|", &model[i][0], &model[i][1], &model[i][2]) != 3)
				break;
			char str[256];
			line = line + sprintf(str, "%f,%f,%f|", model[i][0], model[i][1], model[i][2]);
		}
		if (i != JointType_Count)
			continue;
		else
			Copy(modelData[modelflame], model);
	}

	for (int i = 0; i < BAR_NUM; i++)
		flameGrading[i] = new FlameGrading(modelData);

	for (int i = 0; i <= userflame; i++) {
		if (userData.count(i) == 0)
			continue;

		for (int k = 0; k < BAR_NUM; k++) {
			int x = k - BAR_NUM / 2;
			int p = flameGrading[k]->Mark(userData[i], i + x * 5);
			timingSum[k] += p;
			if (x == 0) {
				int *temp;
				temp = flameGrading[k]->MarkPoint(userData[i], i);
				for (int l = 0; l < 4; l++)
					pointSum[l] += *(temp + l);
				sum += p;
				score[max] += p;
				if (i >= SCORE_FLAME * (max + 1)) {
					score[max] = (int)(bezier->Calc((double)score[max] / (count - scoreCount) / 100) * 100);
					score[max] = Adjust(score[max]);
					scoreCount = count;
					max++;
				}
			}
		}
		count++;
	}


	score[max] = (int)(bezier->Calc((double)score[max] / (count - scoreCount) / 100) * 100);
	score[max] = Adjust(score[max]);
	max++;
	total = (int)(bezier->Calc((double)sum / count / 100) * 100);
	total = Adjust(total);
	for (int l = 0; l < 4; l++) {
		int x = pointSum[l] / count;
		if (x > 80)
			point[l] = 1;
		else if(x > 40)
			point[l] = 2;
		else
			point[l] = 3;
	}
	timing = 0;
	for (int k = 1; k < BAR_NUM; k++) {
		if (timingSum[timing] < timingSum[k])
			timing = k;
	}
}

int Grading::Adjust(int point) {
	if (point > 100)
		return 100;
	else if (point < 0)
		return 0;
	return point;
}

void Grading::Copy(float dst[JointType_Count][3], float source[JointType_Count][3]) {
	for (int i = 0; i < JointType_Count; i++) {
		for (int j = 0; j < 3; j++)
			dst[i][j] = source[i][j];
	}
}


Grading::~Grading() {
	delete bezier;
}