#include "PlayScreenObject.h"

//�i���o�[
PlayBar::PlayBar(DecorationItem *decorationItem) {
	barAll = new MyDrawBar(WIDTH * 0.41, HEIGHT * 0.055, WIDTH * 0.56, 10);
	barNow = new MyDrawBar(WIDTH * 0.41, HEIGHT * 0.055, 0, 10, "Blue");
	
	circle[0] = new MyDrawCircle(WIDTH * 0.41, HEIGHT * 0.055, 12);
	circle[1] = new MyDrawCircle(WIDTH * 0.41, HEIGHT * 0.055, 5, "White");
	this->decorationItem = decorationItem;
}

void PlayBar::Load(Song *song) {
	this->song = song;
	song->LoadPart();
}

void PlayBar::Update() {
	int nowFlame = song->danceMovie->GetNowFlame();
	int startFlame = song->danceMovie->GetStartFlame();
	int lastFlame = song->danceMovie->GetEndFlame();

	for (int i = 0; i < song->GetPartNum(); i++) {
		SongPart *songPart = song->GetPart(i);
		float x = WIDTH * 0.41 + WIDTH * 0.56 * (float)(songPart->GetFlame() - startFlame) / (lastFlame - startFlame);
		part[i] = new MyDrawTextV(decorationItem, songPart->GetName(), x, HEIGHT * 0.056, 0, 16);
		if (songPart->GetFlame() >= startFlame && songPart->GetFlame() <= lastFlame)
			part[i]->SetViewFlag(TRUE);
		else
			part[i]->SetViewFlag(FALSE);
	}

	float now = WIDTH * 0.56 * (float)(nowFlame - startFlame) / (lastFlame - startFlame);
	barNow->ChangeSize(now, 10);
	for (int i = 0; i < 2; i++)
		circle[i]->ChangePos(WIDTH * 0.41 + now, HEIGHT * 0.055);
	for (int i = song->GetPartNum() - 1; i >= 0; i--) {
		SongPart *songPart = song->GetPart(i);
		if (nowFlame < lastFlame && nowFlame >= songPart->GetFlame()) {
			part[i]->ChangeColor("Blue");
			part[i]->ChangeFont(decorationItem, 20);
		}
		else {
			part[i]->ChangeColor("White");
			part[i]->ChangeFont(decorationItem, 16);
		}
		lastFlame = songPart->GetFlame();
	}
}

void PlayBar::View() {
	barAll->View();
	barNow->View();
	for (int i = 0; i < 2; i++)
		circle[i]->View();
	for (int i = 0; i < song->GetPartNum(); i++)
		part[i]->View();
}

PlayBar::~PlayBar() {
	delete barAll;
	delete barNow;
	for (int i = 0; i < 2; i++)
		delete circle[i];
}

//�J�E���g�_�E�����
CountDown::CountDown(DecorationItem *decorationItem, const int thisScene, const int playScene) {
	this->thisScene = thisScene;
	this->playScene = playScene;
	const float x = WIDTH * 0.5; //�~�̒��S�ix���W�j
	const float y = HEIGHT * 0.5; //�~�̒��S�iy���W�j
	const float r = WIDTH * 0.2; //�~�̔��a

	text = new MyDrawText(decorationItem, "���������Ă�������", x, y + r + 80, 1, 40);
	circle = new MyDrawCircle(x, y, r, 10, "White"); //�������F�̉~
	countCircle1 = new MyDrawCircleGauge(x, y, r, 0, 5, "Blue");	//�Q�[�W
	countCircle2 = new MyDrawCircle(0, 0, 20, "Blue");	//�Q�[�W�̐�̉~
	countCircle3 = new MyDrawCircle(0, 0, 25, "White");	//�Q�[�W�̐�̉~�̉�
}

int CountDown::Switch(const int scene) {
	if (++count == max)
		return playScene;
	return scene;
}

void CountDown::ContentUpdate() {
	if (nowScene == thisScene) {
		viewFlag = TRUE;
		countCircle1->ChangeDegree((double)count / max * 100);
		countCircle2->ChangePos(countCircle1->GetEndX() * SIZE_RATE, countCircle1->GetEndY() * SIZE_RATE);
		countCircle3->ChangePos(countCircle1->GetEndX() * SIZE_RATE, countCircle1->GetEndY() * SIZE_RATE);
	}
	else {
		count = 0;
		viewFlag = FALSE;
	}
}

void CountDown::ContentView() {
	text->View();
	circle->View();
	countCircle3->View();
	countCircle1->View();
	countCircle2->View();
	
}

CountDown::~CountDown() {
	delete text;
	delete circle;
	delete countCircle1;
	delete countCircle2;
	delete countCircle3;
}