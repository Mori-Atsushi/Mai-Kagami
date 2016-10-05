#ifndef __DRAWTEXT_H_INCLUDED__
#define __DRAWTEXT_H_INCLUDED__

#include <string.h>
#include <string>
#include "DxLib.h"
#include "DecorationItem.h"
#include "Draw.h"

enum alignment {ALIGNMENT_LEFT, ALIGNMENT_CENTER, ALIGNMENT_RIGHT};

//�e�L�X�g�֌W
class MyDrawText : public Color, public Draw2{
public:
	MyDrawText(DecorationItem *decorationItem, const char *str, const float x, const float y, const int pos, const int point, const char *colorName = "White"); // pos=����:0 / ������:1 / �E��:2
	void ContentView(); //�`��
	void ChangeText(char *str); //�e�L�X�g�ύX

	void ChangeFont(DecorationItem *decorationItem, const int point); //�t�H���g�T�C�Y�ύX
	void ChangeColor(char *colorName);
	float GetHeight(); //�c�擾
	float GetWidth(); //���擾
protected:
	int decorationItem, point; //�t�H���g���A�|�W�V�������A�t�H���g�T�C�Y
	std::string s; //����
};

//�c�����e�L�X�g
class MyDrawTextV : public MyDrawText {
public:
	MyDrawTextV(DecorationItem *decorationItem, const char *str, const float x, const float y, const int pos, const int point, const char *colorName = "White"); // pos=����:0 / ������:1 / �E��:2
	void ContentView();
private:
	float RotCenterX;
};

//�����s�̃e�L�X�g
class MyDrawTexts : public Color, public Draw {
public:
	MyDrawTexts(DecorationItem *decorationItem, const char *str, const float x, const float y, const int pos, const int point, const float lineInterval, const char *colorName = "White");
	MyDrawTexts(DecorationItem *decorationItem, const char *str, const float x1, const float x2, const float y, const int pos, const int point, const float lineInterval, const char *colorName = "White");

	void ContentView();
	void ChangePos(const float x, const float y);
	void MakeNewLine(std::string s, const float x);	//x�͈̔͂ɕ������܂�悤���s����������	
	void ChangeText(const char *str); //�e�L�X�g�ύX
	float GetWidth(); //���擾
	float GetHeight(); //�����擾
	~MyDrawTexts();
private:
	MyDrawText *myDrawText[256];
	DecorationItem *decorationItem;
	int l = 0, p, inter, point; //�s��, �|�W�V�������, �Ԋu�A�|�C���g��
	char color[100];
};

//�A���_�[���C���t���e�L�X�g
class MyDrawTextLine : public Color, public Draw {
public:
	MyDrawTextLine(DecorationItem *decorationItem, const char *str, const float x, const float y, const int pos, const int point, const float lineLength, const float lineWidth, const char *colorName = "White");
	void ContentView();
	void ChangePos(const float x, const float y);
	void ChangeText(char *str); //�e�L�X�g�ύX
	~MyDrawTextLine();
private:
	MyDrawText *myDrawText;
	int pos;
	float x1, x2, y1, y2, w, l; //���W�A���̑����A���̒���
};

#endif