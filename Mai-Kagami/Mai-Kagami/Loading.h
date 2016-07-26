#ifndef __LOGIN_H_INCLUDED__
#define __LOGIN_H_INCLUDED__

#include "Main.h"
#include "DxLib.h"
#include "Draw.h"
#include "Font.h"

//���O�C����ʊ֌W
class Loading {
public:
	Loading(Font *font); //���[�h
	void Update(); //�v�Z
	void View(); //�\��
	~Loading();
private:
	MyDrawText *myDrawText;
};

#endif