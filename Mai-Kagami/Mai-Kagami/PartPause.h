#ifndef __PARTPAUSE_H_INCLUDED__
#define __PARTPAUSE_H_INCLUDED__

#include "DxLib.h"
#include "Button.h"
#include "DecorationItem.h"
#include "Songs.h"
#include "PartDefine.h"
#include "SeetingPop.h"
#include "PauseScreen.h"
#include "Touch.h"
#include "Scene.h"
#include "PartOptionPop.h"
#include "Kinect.h"

//�|�[�Y�{�^�����
class PartPauseButton : public SubScene {
public:
	PartPauseButton(DecorationItem *decorationItem, Touch *touch, Songs *songs, Kinect *kinect);
	void Load();
	int Switch(const int scene);
	void Delete();
	~PartPauseButton();
private:
	void ContentUpdate();
	void ContentView();
	DecorationItem *decorationItem;
	Songs *songs;
	Kinect *kinect;
	CircleGraphButton *button[2]; //�{�^��
};

//�|�[�Y���
class PartPauseScreen : public PauseScreen {
public:
	PartPauseScreen(DecorationItem *decorationItem, Songs *songs, Touch *touch);
};

class PartOptionPreview3 : public PartOptionPreview {
public:
	PartOptionPreview3(DecorationItem *decorationItem, Songs *songs, Touch *touch);
	int Switch(const int scene);
	~PartOptionPreview3();
private:
	DecorationItem *decorationItem;
	BlackBox *blackBox;
	void ContentView();
	Button *button;
};

//�ݒ�ύX���
class PartPauseSetting : public PartOptionPop {
public:
	PartPauseSetting(DecorationItem *decorationItem, Songs *songs, Touch *touch);
};

//�|�[�Y�֌W
class PartPause : public SubScene {
public:
	PartPause(DecorationItem *decorationItem, Songs *songs, Touch *touch, Kinect *kinect);
	void Load();
	int Switch(const int scene);
	void Delete();
	~PartPause();
private:
	void ContentUpdate();
	void ContentView();
	Songs *songs;
	boolean flag; //�|�[�Y�����ǂ����̃t���O
	PartPauseButton *partPauseButton; //�|�[�Y�{�^�����
	PartPauseScreen *partPauseScreen; //�|�[�Y���
	PartPauseSetting *partPauseSetting; //�ݒ�ύX���
};

#endif