#include "DxLib.h"

//����֌W
class Movie {
public:
	Movie(const float x, const float y, const char *filename); //������
	void View();
	void Start(); //�Đ�
	int GetNowFlame(); //���݂̃t���[�����擾

	~Movie();
private:
	double speed, sp;
	float x, y;
	int handle; //�摜�p�n���h��
};