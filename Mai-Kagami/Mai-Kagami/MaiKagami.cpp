#include "MaiKagami.h"

MaiKagami::MaiKagami() {
	scene = START; //シーン初期化
	font = new Font();
	loading = new Loading(font);
	top = new Top(font);
	songSelect = new SongSelect(font);
}

//全体の算計
void MaiKagami::Update() {
	int now;

	do {
		now = scene;
		switch (scene) {
		case TOP:
			scene = top->Update(); //トップ画面計算
			break;
		case SONG_SELECT:
			scene = songSelect->Update();
			break;
		}
	} while (now != scene);
}

//全体の描画
void MaiKagami::View() {
	switch (scene) {
	case TOP:
		top->View(); //トップ画面表示
		break;
	case SONG_SELECT:
		songSelect->View(loading);
		break;
	}
}