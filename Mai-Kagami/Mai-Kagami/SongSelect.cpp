#include "SongSelect.h"

//�ȑI����ʃ{�^��������
SongSelectButton::SongSelectButton(DecorationItem *decorationItem, Touch *touch) {
	this->decorationItem = decorationItem;
	button[0] = new TriangleButton(decorationItem, touch, "�O�̋Ȃ�", 0, 0);
	button[1] = new CircleButton(decorationItem, touch, "����", 1);
	button[2] = new TriangleButton(decorationItem, touch, "���̋Ȃ�", 1, 2);
	button[3] = new CircleButton2(decorationItem, touch, "�I��", 4);
}

//�ȑI����ʃ{�^����ʐ؂�ւ�
int SongSelectButton::Switch(const int scene) {
	if (button[1]->GetTouch() == 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_DECIDE);
		return MODE;
	}
	if (button[3]->GetTouch() == 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_DECIDE);
		return BACK;
	}
	return scene;
}

//�ȑI����ʃ{�^���v�Z
void SongSelectButton::ContentUpdate() {
	if (nowScene == MAIN)
		viewFlag = TRUE;
	else
		viewFlag = FALSE;
}

//�ȑI����ʃ{�^���\��
void SongSelectButton::ContentView() {
	for (int i = 0; i < 4; i++)
		button[i]->View();
}

SongSelectButton::~SongSelectButton() {
	for (int i = 0; i < 4; i++)
		delete button[i];
}

//�I���p�|�b�v�A�b�v
SongSelectPop::SongSelectPop(DecorationItem *decorationItem, Touch *touch) {
	this->decorationItem = decorationItem;
	this->touch = touch;
	blackBox = new BlackBox();
	title = new MyDrawText(decorationItem, "- �I�� -", WIDTH * 0.75, HEIGHT * 0.4, 1, 40, "Blue");
	message = new MyDrawText(decorationItem, "�{���ɏI��\n���܂����H", WIDTH * 0.75, HEIGHT * 0.45, 1, 30);
	button[0] = new CircleButton(decorationItem, touch, "�͂�", 1, WIDTH * 0.75, "White");
	button[1] = new CircleButton(decorationItem, touch, "������", 2, WIDTH * 0.75, "White");
}

int SongSelectPop::Switch(const int scene) {
	if (touch->Get(1) == 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_DECIDE);
		return BACK_TOP;
	}
	if (touch->Get(2) == 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_DECIDE);
		return MAIN;
	}
	return scene;
}

void SongSelectPop::ContentUpdate() {
	if (nowScene == BACK)
		viewFlag = TRUE;
	else
		viewFlag = FALSE;
}

void SongSelectPop::ContentView() {
	blackBox->View();
	title->View();
	message->View();
	for (int i = 0; i < 2; i++)
		button[i]->View();
}

SongSelectPop::~SongSelectPop() {
	delete blackBox;
	delete title;
	delete message;
	for (int i = 0; i < 2; i++)
		delete button[i];
}