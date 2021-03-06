#ifndef __PLAYSCREEN_H_INCLUDED__
#define __PLAYSCREEN_H_INCLUDED__

#include "DxLib.h"
#include "Songs.h"
#include "DrawText.h"
#include "DrawObject.h"
#include "Button.h"
#include "SeetingPop.h"
#include "Scene.h"
#include "Touch.h"
#include "Kinect.h"
#include "PlayScreenObject.h"

//通し練習画面
class PlayScreen : public SubScene {
public:
	PlayScreen(DecorationItem *decorationItem, Songs *songs, Touch *touch, Kinect *kinect, const int startScene, const int countDownScene, const int playScene, const int finishScene);
	void Load();
	int Switch(const int scene);
	~PlayScreen();
private:
	void ContentUpdate();
	void ContentView();
	int startScene, countDownScene, playScene, finishScene;
	Kinect *kinect;
	Songs *songs;
	Song *song;
	PlayBar *playBar; //進捗バー
	CountDown *countDown; //カウントダウン画面
};

#endif