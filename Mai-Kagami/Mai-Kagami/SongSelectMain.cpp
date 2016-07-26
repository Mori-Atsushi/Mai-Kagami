#include "SongSelectMain.h"

SongSelect::SongSelect(Font *font) {
	f = font;
	loadFlag = 0;
}

//曲選択画面ロード
void SongSelect::Load() {
	if (loadFlag == 2)
		return;

	if (loadFlag == 0) {
		songSelectTitle = new SongSelectTitle(f); //曲選択画面タイトル初期化
		songSelectButton = new SongSelectButton(f);
		songSelectCover = new SongSelectCover(f); //選択中の曲初期化
		songSelectPop = new SongSelectPop(f);
		touch = new Touch();
		loadFlag = 1;
		scene = MAIN;
	}

	if (loadFlag == 1 && GetASyncLoadNum() == 0)
		loadFlag = 2;
}

//曲選択画面計算
int SongSelect::Update() {
	Load();
	if (loadFlag == 2) {
		touch->Check();
		switch (scene)
		{
		case BACK:
			if (touch->Get(1) == 1)
				scene = BACK_TOP;
			if (touch->Get(2) == 1)
				scene = MAIN;
			break;
		case MAIN:
			if (touch->Get(4) == 1)
				scene = BACK;
			if (touch->Get(1) == 1)
				scene = MODE;
			songSelectCover->Update(touch);
			break;
		case MODE:
			if (touch->Get(4) == 1)
				scene = MAIN;
		}

		if (scene == BACK_TOP) {
			Delete();
			return TOP;
		}

		songSelectTitle->Update(scene);

	}
	return SONG_SELECT;
}

//曲選択画面表示
void SongSelect::View(Loading *loading) {
	if (loadFlag == 2) {
		songSelectCover->View(); //カバー表示
		songSelectTitle->View(); //タイトル表示

		switch (scene)
		{
		case BACK:
			songSelectPop->View();
			break;
		case MAIN:
			songSelectButton->View(); //ボタン表示
			break;
		}
	}
	else {
		loading->View();
	}
}

void SongSelect::Delete() {
	loadFlag = 0;
	delete songSelectCover;
	delete songSelectButton;
	delete songSelectTitle;
	delete songSelectPop;
	delete touch;
}