#include "Movie.h"

//���揉����
Movie::Movie(const float x, const float y, const char *filename) {
	this->x = x;
	this->y = y;
	handle = LoadGraph(filename); // �摜�̃��[�h
}

//����\��
void Movie::View() {
	if (!CheckHandleASyncLoad(handle)) {
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraphF(x, y, 1, 0, handle, TRUE); //�`��
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}

//�Đ�
void Movie::Start() {
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && GetMovieStateToGraph(handle) == 0)
		PlayMovieToGraph(handle);
}

//���݂̃t���[�����擾
int Movie::GetNowFlame() {
	return TellMovieToGraphToFrame(handle);
}

Movie::~Movie() {
	DeleteGraph(handle);
}