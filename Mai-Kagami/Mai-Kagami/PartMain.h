#ifndef __PARTMAIN_H_INCLUDED__
#define __PARTMAIN_H_INCLUDED__

#include "DxLib.h"
#include "Scene.h"
#include "Main.h"
#include "DecorationItem.h"
#include "Songs.h"
#include "Touch.h"
#include "PartDefine.h"
#include "PartPlay.h"
#include "PartPause.h"

class PartMain : public Scene {
public:
	PartMain(DecorationItem *decorationItem, Touch *touch, Songs *songs, Kinect *kinect);
	MainScene Switch(const MainScene scene);
	~PartMain();
private:
	void ContentLoad();
	void ContentUpdate();
	void ContentView();
	void ContentDelete();
	DecorationItem *decorationItem;
	PartStart *partStart;
	PartPlay *partPlay;
	PartPause *partPause;
	int scene;
};

#endif