#ifndef __TOPMAIN_H_INCLUDED__
#define __TOPMAIN_H_INCLUDED__

#include "Nfc.h"
#include "DxLib.h"
#include "Main.h"
#include "DecorationItem.h"
#include "Top.h"
#include "Scene.h"
#include "User.h"

//�g�b�v��ʊ֌W
class Top : public Scene {
public:
	Top(DecorationItem *decorationItem, User *user);
	MainScene Switch(const MainScene scene);
	~Top();
private:
	DecorationItem *decoItem;	//�t�H���g&���ʉ�
	TopLogo *topLogo; //�g�b�v���S
	TopTouchMessage *topTouchMessage; //NFC�^�b�`���b�Z�[�W
	TopTouchButton *topTouchButton; //NFC�^�b�`�{�^��
	Nfc nfc; //NFC�Ď�
	User *user;
	int bgmHandle; //bgm
	void ContentUpdate(); //�v�Z
	void ContentView(); //�\��
	void ContentLoad();
	void ContentDelete();
};

#endif