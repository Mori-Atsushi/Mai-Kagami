#ifndef __THROUGHPAUSE_H_INCLUDED__
#define __THROUGHPAUSE_H_INCLUDED__

#include "DxLib.h"
#include "Button.h"
#include "DecorationItem.h"
#include "Songs.h"
#include "ThroughDefine.h"
#include "SeetingPop.h"
#include "PauseScreen.h"
#include "Touch.h"
#include "Scene.h"

//�|�[�Y�{�^�����
class ThroughPauseButton : public SubScene {
public:
	ThroughPauseButton(Touch *touch, DecorationItem* decorationItem);
	void Load();
	int Switch(const int scene);
	void Delete();
	~ThroughPauseButton();
private:
	void ContentUpdate();
	void ContentView();
	DecorationItem *decorationItem;
	CircleGraphButton *pauseButton; //�ꎞ��~�p�{�^��
};

//�|�[�Y���
class ThroughPauseScreen : public PauseScreen {
public:
	ThroughPauseScreen(DecorationItem *decorationItem, Songs *songs, Touch *touch);
private:
};

//���x�ύX���
class ThroughPauseSetting : public SpeedPop {
public:
	ThroughPauseSetting::ThroughPauseSetting(DecorationItem *decorationItem, Songs *songs, Touch *touch) : SpeedPop(decorationItem, songs, touch) { this->decorationItem = decorationItem; };
	int Switch(const int scene);
	void ContentUpdate();
private:
	DecorationItem *decorationItem;
};

//�|�[�Y�֌W
class ThroughPause : public SubScene {
public:
	ThroughPause(DecorationItem *decorationItem, Songs *songs, Touch *touch);
	void Load();
	int Switch(const int scene);
	void Delete();
	~ThroughPause();
private:
	void ContentUpdate();
	void ContentView();
	Songs *songs;
	boolean flag; //�|�[�Y�����ǂ����̃t���O
	ThroughPauseButton *throughPauseButton; //�|�[�Y�{�^�����
	ThroughPauseScreen *throughPauseScreen; //�|�[�Y���
	ThroughPauseSetting *throughPauseSetting; //���x�ύX���
};

#endif