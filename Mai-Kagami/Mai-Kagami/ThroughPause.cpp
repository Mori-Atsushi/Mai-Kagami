#include "ThroughPause.h"

ThroughPauseButton::ThroughPauseButton(Touch *touch, DecorationItem* decorationItem) {
	this->decorationItem = decorationItem;
	pauseButton = new CircleGraphButton(touch, 0, "img/pause.png");
}

void ThroughPauseButton::Load() {
	pauseButton->Load();
}

int ThroughPauseButton::Switch(const int scene) {
	if (pauseButton->GetTouch() == 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_DECIDE);
		return THROUGH_PAUSE;
	}
	return scene;
}

void ThroughPauseButton::ContentUpdate() {
	switch (nowScene)
	{
	case THROUGH_PLAY:
	case THROUGH_COUNTDOWN:
	case THROUGH_START:
		viewFlag = TRUE;
		break;
	default:
		viewFlag = FALSE;
		break;
	}
}

void ThroughPauseButton::ContentView() {
	pauseButton->View();
}

void ThroughPauseButton::Delete() {
	pauseButton->Release();
}

ThroughPauseButton::~ThroughPauseButton() {
	delete pauseButton;
}

ThroughPauseScreen::ThroughPauseScreen(DecorationItem *decorationItem, Songs *songs, Touch *touch) 
	: PauseScreen(decorationItem, songs, touch, THROUGH_PAUSE, THROUGH_START, THROUGH_BACK_SONG_SELECT, THROUGH_SETTING) {}

int ThroughPauseSetting::Switch(const int scene) {
	if (button->GetTouch() == 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_DECIDE);
		song->danceMovie->SetSpeed();
		return THROUGH_PAUSE;
	}
	return scene;
}

void ThroughPauseSetting::ContentUpdate() {
	if (nowScene == THROUGH_SETTING) {
		SpeedPop::ContentUpdate();
		viewFlag = TRUE;
	}
	else {
		viewFlag = FALSE;
	}
}

ThroughPause::ThroughPause(DecorationItem *decorationItem, Songs *songs, Touch *touch) {
	throughPauseButton = new ThroughPauseButton(touch, decorationItem); //�|�[�Y�{�^�����
	throughPauseScreen = new ThroughPauseScreen(decorationItem, songs, touch);
	throughPauseSetting = new ThroughPauseSetting(decorationItem, songs, touch);
	flag = FALSE;
}

void ThroughPause::Load() {
	throughPauseButton->Load();
	throughPauseScreen->Load();
	throughPauseSetting->Load();
}

int ThroughPause::Switch(const int scene) {
	switch (scene)
	{
	case THROUGH_COUNTDOWN:
	case THROUGH_PLAY:
	case THROUGH_START:
		return throughPauseButton->Switch(scene);
	case THROUGH_PAUSE:
		return throughPauseScreen->Switch(scene);
	case THROUGH_SETTING:
		return throughPauseSetting->Switch(scene);
	}
	return scene;
}

void ThroughPause::ContentUpdate() {
	throughPauseButton->Update(nowScene);
	throughPauseScreen->Update(nowScene);
	throughPauseSetting->Update(nowScene);

	switch (nowScene)
	{
	case THROUGH_SETTING:
	case THROUGH_PLAY:
	case THROUGH_PAUSE:
	case THROUGH_COUNTDOWN:
	case THROUGH_START:
		viewFlag = TRUE;
		break;
	default:
		viewFlag = FALSE;
		break;
	}
}

void ThroughPause::ContentView() {
	throughPauseButton->View();
	throughPauseScreen->View();
	throughPauseSetting->View();
}

void ThroughPause::Delete() {
	throughPauseButton->Delete();
	throughPauseScreen->Delete();
	throughPauseSetting->Delete();
}

ThroughPause::~ThroughPause() {
	delete throughPauseButton;
	delete throughPauseScreen;
	delete throughPauseSetting;
}