#include "MaiKagami.h"

MaiKagami::MaiKagami() {
	touch = new Touch();
	decorationItem = new DecorationItem();
	songs = new Songs(decorationItem); //�Ȉꗗ�쐬
	user = new User();
	kinect = new Kinect(); //�L�l�N�g
	top = new Top(decorationItem, user);
	songSelect = new SongSelect(decorationItem, touch, songs, user);
	throughMain = new ThroughMain(decorationItem, touch, songs, kinect);
	throughResultMain = new ThroughResultMain(decorationItem, touch, songs, user, kinect);
	partMain = new PartMain(decorationItem, touch, songs, kinect);
	partResultMain = new PartResultMain(decorationItem, touch, songs);
	scene = TOP;
}

//�S�̂̎Z�v
void MaiKagami::Update() {
	static int lastScene = TOP;
	touch->Check();
	switch (scene) {
	case TOP:
		scene = top->Switch(scene);
		break;
	case SONG_SELECT:
		scene = songSelect->Switch(scene);
		break;
	case THROUGH:
		scene = throughMain->Switch(scene);
		break;
	case THROUGH_RESULT:
		scene = throughResultMain->Switch(scene);
		break;
	case PART:
		scene = partMain->Switch(scene);
		break;
	case PART_RESULT:
		scene = partResultMain->Switch(scene);
		break;
	}

	if(lastScene != SONG_SELECT && scene == SONG_SELECT)
		songSelect->SetScene(MAIN);
	if (scene == THROUGH_OPTION) {
		songSelect->SetScene(OPTION1);
		scene = SONG_SELECT;
	}
	if (scene == PART_OPTION) {
		songSelect->SetScene(OPTION2);
		scene = SONG_SELECT;
	}

	lastScene = scene;

	kinect->Update();
	top->Update(scene); //�g�b�v��ʌv�Z
	songSelect->Update(scene); //�ȑI����ʌv�Z
	throughMain->Update(scene); //�ʂ����K�v���C��ʌv�Z
	throughResultMain->Update(scene); //�ʂ����K���ʉ�ʌv�Z
	partMain->Update(scene); //�������K�v���C��ʌv�Z
	partResultMain->Update(scene); //�������K���ʉ�ʕ\��
}

//�S�̂̕`��
void MaiKagami::View() {
	top->View(); //�g�b�v��ʕ\��
	songSelect->View(); //�ȑI����ʕ\��
	throughMain->View(); //�ʂ����K�v���C��ʕ\��
	throughResultMain->View(); //�ʂ����K���ʉ�ʕ\��
	partMain->View(); //�������K�v���C��ʕ\��
	partResultMain->View(); //�������K���ʉ�ʕ\��
}

//�f�X�g���N�^
MaiKagami::~MaiKagami() {
	delete top;
	delete songSelect;
	delete throughMain;
	delete throughResultMain;
	delete partMain;
	delete partResultMain;
	delete kinect;
}