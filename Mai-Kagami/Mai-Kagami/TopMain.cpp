#include "TopMain.h"

//�g�b�v��ʃR���X�g���N�^
Top::Top(DecorationItem *decorationItem, User *user) {
	this->user = user;
	decoItem = decorationItem;
	topLogo = new TopLogo(HEIGHT / 3); //���S������
	topTouchMessage = new TopTouchMessage(decoItem, HEIGHT * 0.42); //NFC�^�b�`���b�Z�[�W������
	topTouchButton = new TopTouchButton(decoItem); //NFC�^�b�`�{�^��������
}

//�g�b�v��ʏ�����
void Top::ContentLoad() {
	topLogo->Load();
	topTouchMessage->Init();
	bgmHandle = LoadSoundMem("SE/bgm.wav");
	nfc.Init();
}

//��ʂ̐؂�ւ�
MainScene Top::Switch(const MainScene scene) {
	char* id = nfc.GetId();
	if (id[0] != '\0') {
		user->SetUserId(id);
		nfc.reset_calledCont();
		Delete();
		return SONG_SELECT;
	}
	return TOP;
}

//�g�b�v��ʌv�Z
void Top::ContentUpdate() {
	if (nowScene == TOP) {
		Load();
		topTouchMessage->Update(); //NFC�^�b�`���b�Z�[�W�v�Z
	}
}

//�g�b�v��ʕ\��
void Top::ContentView() {
	if (CheckSoundMem(bgmHandle) == 0)
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK);
	topLogo->View(); //���S�\��
	topTouchMessage->View(); //NFC�^�b�`���b�Z�[�W�\��
	topTouchButton->View(); //NFC�^�b�`�{�^���\��
}

void Top::ContentDelete() {
	DeleteSoundMem(bgmHandle);
	topLogo->Release();
}

Top::~Top() {
	delete topLogo;
	delete topTouchButton;
	delete topTouchMessage;
}