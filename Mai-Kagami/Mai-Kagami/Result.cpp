#include "Result.h"

Result::Result(Songs *songs, User *user, Kinect *kinect) {
	this->songs = songs;
	this->user = user;
	this->kinect = kinect;
}

void Result::Calc() {
	Song *song = songs->GetSong(songs->GetNowSong());
	if (KINECT_FLAG) {
		char buf[256];
		sprintf(buf, "song/%s/model.txt", song->GetFolder());
		Mark(buf, kinect->kinectBody->GetSave(), kinect->kinectBody->GetNow());
		expression = CalcHappy();
		kinect->kinectBody->DeleteSave();
	}
	strcpy(comment, "B��������T�r�ɓ����Ă���T�r�̏I���ɂ����Ă����\n�̂悤�Ɏv���܂��B�������d�_�I�ɗ��K���܂��傤�B");
}

int Result::CalcHappy() {
	int p = kinect->kinectBody->GetHappy();
	for (int i = 0; i < 8; i++) {
		if(p < 20 + i * 10)
			return i;
	}
	return 8;
}

//���M
void Result::Send() {
	Song *song = songs->GetSong(songs->GetNowSong());
	//��ID�̃��N�G�X�g�쐬
	char songReq[126] = { 0 };
	sprintf_s(songReq, 126, "song=%d", song->GetSongId());
	//���[�U�[ID�̃��N�G�X�g�쐬
	char userReq[32] = { 0 };
	sprintf_s(userReq, 32, "user=%s", user->GetUserId());
	//���ݎ����̎擾
	int temp[5] = { 0 };
	GetNowTime(temp);
	//�N�����̃��N�G�X�g�쐬
	char dateReq[32] = { 0 };
	sprintf_s(dateReq, 32, "date=%02d-%02d-%02d %02d-%02d", temp[0], temp[1], temp[2], temp[3], temp[4]);
	//�������_�̃��N�G�X�g�쐬
	char totalReq[16] = { 0 };
	sprintf_s(totalReq, 16, "total=%d", this->total);
	//��ԕʍ̓_�̃��N�G�X�g�쐬
	char partReq[64] = { 0 };
	sprintf_s(partReq, 64, "part=%d", score[0]);
	for (int i = 1, n = this->max; i < n; i++) {
		sprintf_s(partReq, 64, "%s/%d", partReq, score[i]);
	}
	//�̂̕��ʍ̓_�̃��N�G�X�g�쐬
	char bodyPoint[4] = { 0 };
	for (int i = 0; i < 4; i++) {
		switch (point[i]) {
		case 1:bodyPoint[i] = 'A';	break;
		case 2:bodyPoint[i] = 'B';	break;
		case 3:bodyPoint[i] = 'C';	break;
		}
	}
	char bodyReq[32] = { 0 };
	sprintf_s(bodyReq, 32, "body=%c/%c/%c/%c", bodyPoint[0], bodyPoint[1], bodyPoint[2], bodyPoint[3]);
	//�^�C�~���O�̃��N�G�X�g�쐬
	char timingReq[16] = { 0 };
	sprintf_s(timingReq, 16, "timing=%d", timing);
	//�\��̃��N�G�X�g�쐬
	char expressionReq[16] = { 0 };
	sprintf_s(expressionReq, 16, "expression=%d", expression);
	//�R�����g�̃��N�G�X�g�쐬
	WCHAR w_comment[256] = { 0 };
	mbstowcs(w_comment, comment, 256);
	char commentReq[256] = { 0 };
	sprintf_s(commentReq, 256, "comment=%s", w_comment);

	//url���쐬
	char url[512] = { 0 };
	sprintf_s(url, 512, "http://globalstudios.jp/mai-archive/api_add.php?%s&%s&%s&%s&%s&%s&%s&%s&%s", 
		songReq, userReq, dateReq, totalReq, partReq, bodyReq, timingReq, expressionReq, commentReq);
	Http http;
	if(!http.Send(url))printfDx("http�G���[");
}

void Result::GetNowTime(int nowTime[]) {
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);
	nowTime[0] = pnow->tm_year + 1900;
	nowTime[1] = pnow->tm_mon + 1;
	nowTime[2] = pnow->tm_mday;
	nowTime[3] = pnow->tm_hour;
	nowTime[4] = pnow->tm_min;
}

float Result::GetTotal() {
	return total;
}

//���ʕʓ��_�擾
void Result::GetPoint(int x[4]) {
	for (int i = 0; i < 4; i++)
		x[i] = point[i];
}

//�R�����g�擾
char *Result::GetComment() {
	return comment;
}

//�^�C�~���O�擾
int Result::GetTiming() {
	return timing;
}

//�\��擾
int Result::GetExpression() {
	return expression;
}

//��ԕʓ��_�擾
int Result::GetScore(int x[100]) {
	for (int i = 0; i < max; i++)
		x[i] = score[i];
	return max;
}