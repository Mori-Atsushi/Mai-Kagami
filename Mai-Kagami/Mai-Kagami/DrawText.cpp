﻿#include "DrawText.h"

//テキスト初期化
//MyDrawText（フォントポインタ、表示文字、x座標、y座標、ポジション情報、フォントサイズ、色）　※色は省略可能、省略した場合白色
//ポジション情報（0：左寄せ、1：中央寄せ、2：右寄せ）
MyDrawText::MyDrawText(Font *font, const char *str, const float x, const float y, const int pos, const int point, const char *colorName)
	: Color(colorName) , Draw2(pos) {
	s = str; //文字列
	ChangeFont(font, point);
	MyDrawText::point = point;
	ChangePos(x, y);
}

//テキスト表示
void MyDrawText::ContentView() {
	DrawStringFToHandle(x, y, s.c_str(), Color::Get(), f); //文字表示
}

//テキスト変更
void MyDrawText::ChangeText(char *str) {
	s = str;
	ChangePos();
}

//フォントサイズ変更
void MyDrawText::ChangeFont(Font *font, const int point) {
	f = font->Get(point); //フォント情報
}

//文字色変更
void MyDrawText::ChangeColor(char *colorName) {
	Color::ChangeColor(colorName);
}

//テキストの縦取得
float MyDrawText::GetHeight() {
	int line = 1; //行数
	for (int i = 0; i < strlen(s.c_str()); i++) {
		if (s.c_str()[i] == '\n')
			line++;
	}

	return (float)point * (1 + 1 / 3) * line;
}

//テキストの幅取得
float MyDrawText::GetWidth() {
	return 	(float)GetDrawStringWidthToHandle(s.c_str(), (int)strlen(s.c_str()), f) * SIZE_RATE;
}

//縦書きテキスト初期化
//MyDrawText（フォントポインタ、表示文字、x座標、y座標、ポジション情報、フォントサイズ、色）　※色は省略可能、省略した場合白色
//ポジション情報（0：下寄せ、1：中央寄せ、2：上寄せ）
MyDrawTextV::MyDrawTextV(Font *font, const char *str, const float x, const float y, const int pos, const int point, const char *colorName)
	: MyDrawText(font, str, x, y, 0, point, colorName) {
	switch (pos)
	{
	case 0:
		RotCenterX = 0;
		break;
	case 1:
		RotCenterX = GetWidth() / SIZE_RATE / 2;
		break;
	case 2:
		RotCenterX = GetWidth() / SIZE_RATE;
		break;
	}
}

//縦書きテキスト表示
void MyDrawTextV::ContentView() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawRotaStringToHandle(x, y, 1, 1, RotCenterX, GetHeight() / SIZE_RATE / 2, - 1.0 / 2.0 * 3.141592, Color::Get(), f, -1, FALSE, s.c_str());
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

//複数行のテキスト
//MyDrawTexts（フォントポインタ、表示文字、x座標、y座標、ポジション情報、フォントサイズ、行間隔、色）　※色は省略可能、省略した場合白色
//ポジション情報（0：左寄せ、1：中央寄せ、2：右寄せ）
MyDrawTexts::MyDrawTexts(Font *font, const char *str, const float x, const float y, const int pos, const int point, const float lineInterval, const char *colorName)
	: Color(colorName) , Draw(x, y) {

	p = pos; //位置情報
	inter = lineInterval; //間隔
	strcpy_s(color, sizeof(color), colorName);
	this->point = point;
	f = font;

	ChangeText(str);
}

//MyDrawTexts（フォントポインタ、表示文字、x座標、文章を収めたいx座標の範囲、ポジション情報、フォントサイズ、行間隔、色）　※色は省略可能、省略した場合白色
//ポジション情報（ALIGNMENT_LEFT：左寄せ、ALIGNMENT_CENTER：中央寄せ、ALIGNMENT_RIGHT：右寄せ）
MyDrawTexts::MyDrawTexts(Font *font, const char *str, const float x1, const float x2, const float y, const int pos, const int point, const float lineInterval, const char *colorName) 
	:Color(colorName), Draw(x1, y){

	p = pos;
	inter = lineInterval;
	strcpy_s(color, sizeof(color), colorName);
	this->point = point;
	f = font;
	std::string s(str);
	MakeNewLine(s, x2);
}

//複数行のテキスト表示
void MyDrawTexts::ContentView() {
	for (int i = 0; i < l; i++)
		myDrawText[i]->ContentView();
}

//複数行のテキスト表示位置変更
void MyDrawTexts::ChangePos(const float x, const float y) {
	Draw::ChangePos(x, y);
	float height = myDrawText[0]->GetHeight();
	float yy = y - (height + inter) / 2 * (l - 1);
	for (int i = 0; i < l; i++) {
		myDrawText[i]->ChangePos(myDrawText[i]->GetX(), yy);
		yy += height + inter;
	}
}

//複数行のテキスト表示文字変更
void MyDrawTexts::ChangeText(const char *str) {
	for (int i = 0; i < l; i++)
		delete myDrawText[i];
	l = 0;
	char a[256];
	int i, j;
	for (i = 0, j = 0; i < strlen(str); i++) {
		a[j++] = str[i];
		if (str[i + 1] == '\n' || i == strlen(str) - 1) {
			a[j] = '\0';
			myDrawText[l] = new MyDrawText(f, a, GetX(), 0, p, point, color);
			l++; i++; j = 0;
		}
	}
	if (i == 0) {
		myDrawText[0] = new MyDrawText(f, str, GetX(), 0, p, point, color);
		l = 1;
	}
	ChangePos(GetX(), GetY());
}

//文字が適切な範囲に入るように改行文字を入れる
//x:文字列を収めたい横幅
void MyDrawTexts::MakeNewLine(std::string str, const float x) {
	//std::string str = "あiうeお";

	//文字列の全角と半角のデータを格納する配列
	int data[100] = { 0 };
	//文字列のコピー
	std::string copy_s = str;
	
	for (int i = 0; !copy_s.empty(); i++) {
		//IsDBCSLeadByteは先頭文字が全角か半角かを判定
		if (IsDBCSLeadByte(copy_s[0]) == 0) {
			data[i] = 1;	//半角のバイト数
			copy_s.erase(0, 1);
		} else {
			data[i] = 2;	//全角のバイト数
			copy_s.erase(0, 2);
		}
	}

	//この変数に文字の幅を入れていきxを超えたところで改行文字を挿入する
	int length = 0;
	for (int i = 0, n = 0; data[n] != 0; i += data[n], n++) {
		char c[3];

		c[0] = str[i];
		switch (data[n]) {
		case 1:
			c[1] = '\0';
			break;
		case 2:
			c[1] = str[i + 1];	
			c[2] = '\0';
			break;
		}
		length += GetDrawStringWidthToHandle(c, strlen(c), f->Get(point)) * SIZE_RATE;
		if (length > x) {
			str.insert(i, "\n");
			i++;
			length = 0;
		}
	}

	this->ChangeText(str.c_str());
}


//複数行のテキスト表示幅取得
float MyDrawTexts::GetWidth() {
	float max = 0;
	for (int i = 0; i < l; i++) {
		if (max < myDrawText[i]->GetWidth())
			max = myDrawText[i]->GetWidth();
	}
	return max;
}

//複数行のテキスト表示高さ取得
float MyDrawTexts::GetHeight() {
	return 	myDrawText[0]->GetHeight() * l;
}

//複数行のテキストデストラクタ
MyDrawTexts::~MyDrawTexts() {
	for (int i = 0; i < l; i++)
		delete myDrawText[i];
}

//アンダーライン付きテキスト
//MyDrawTextLine（フォントポインタ、表示文字、x座標、y座標、ポジション情報、フォントサイズ、線の長さ、線の太さ、色）　※色は省略可能、省略した場合白色
//ポジション情報（0：左寄せ、1：中央寄せ、2：右寄せ）
MyDrawTextLine::MyDrawTextLine(Font *font, const char *str, const float x, const float y, const int pos, const int point, const float lineLength, const float lineWidth, const char *colorName)
	: Color(colorName), Draw(x, y) {
	myDrawText = new MyDrawText(font, str, x, y, pos, point, colorName);
	l = lineLength / SIZE_RATE;
	w = lineWidth / SIZE_RATE;
	this->pos = pos;
	ChangePos(x, y);
}

//アンダーライン付きテキスト描画
void MyDrawTextLine::ContentView() {
	myDrawText->View();
	DrawLineAA(x1, y1, x2, y2, Color::Get(), w);
}

//アンダーライン付きテキスト表示位置変更
void MyDrawTextLine::ChangePos(const float x, const float y) {
	x1 = x / SIZE_RATE - l / 2;
	x2 = x / SIZE_RATE + l / 2;
	y1 = y2 = (y + myDrawText->GetHeight() * 0.9) / SIZE_RATE;

	float xx;
	switch (pos)
	{
	case 0:
		xx = x1 * SIZE_RATE + 10;
		break;
	case 1:
		xx = x;
		break;
	case 2:
		xx = x2 * SIZE_RATE - 10;
		break;
	}
	myDrawText->ChangePos(xx, y);
}

//アンダーライン付きテキスト表示文字変更
void MyDrawTextLine::ChangeText(char *str) {
	myDrawText->ChangeText(str);
	ChangePos(GetX(), GetY());
}

//アンダーライン付きテキストデストラクタ
MyDrawTextLine::~MyDrawTextLine() {
	delete myDrawText;
}