#include "Main.h"
#include "Kinect.h"
#include "Movie.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(WIDTH, HEIGHT, 32); //�E�B���h�E�T�C�Y�ݒ�
	SetBackgroundColor(0, 0, 0); //�w�i�F�ݒ�
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetAlwaysRunFlag(TRUE); //�o�b�N�O���E���h�ł����������s

	Kinect *kinect = new Kinect();
	Movie *movie = new Movie(WIDTH / 2, HEIGHT / 2, "FILE/test.ogv");

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		movie->Start();
		kinect->Update();
//		kinect->View();
		movie->View();
		kinect->kinectBody->JointSave(movie->GetNowFlame()); //�ۑ�
	}

	DxLib_End(); // DX���C�u�����I������

	return 0;
}