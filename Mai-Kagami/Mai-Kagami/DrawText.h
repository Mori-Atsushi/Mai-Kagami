#ifndef __DRAWTEXT_H_INCLUDED__
#define __DRAWTEXT_H_INCLUDED__

#include <string.h>
#include <string>
#include "DxLib.h"
#include "Font.h"
#include "Draw.h"

//テキスト関係
class MyDrawText : public Color, public Draw2{
public:
	MyDrawText(Font *font, const char *str, const float x, const float y, const int pos, const int point, const char *colorName = "White"); // pos=左寄せ:0 / 中央寄せ:1 / 右寄せ:2
	void ContentView(); //描画
	void ChangeText(char *str); //テキスト変更
	void ChangeFont(Font *font, const int point); //フォントサイズ変更
	float GetHeight(); //縦取得
	float GetWidth(); //幅取得
protected:
	int f, point; //フォント情報、ポジション情報、フォントサイズ
	std::string s; //文字
};

//縦書きテキスト
class MyDrawTextV : public MyDrawText {
public:
	MyDrawTextV(Font *font, const char *str, const float x, const float y, const int pos, const int point, const char *colorName = "White"); // pos=左寄せ:0 / 中央寄せ:1 / 右寄せ:2
	void ContentView();
};

//複数行のテキスト
class MyDrawTexts : public Color, public Draw2 {
public:
	MyDrawTexts(Font *font, const char *str, const float x, const float y, const int pos, const int point, const float lineInterval, const char *colorName = "White");
	void ContentView();
	void ChangePos(const float x, const float y);
	float GetWidth(); //幅取得
	float GetHeight(); //高さ取得
	~MyDrawTexts();
private:
	MyDrawText *myDrawText[256];
	int l, p, inter; //行数, ポジション情報, 間隔
};

//アンダーライン付きテキスト
class MyDrawTextLine : public MyDrawText {
public:
	MyDrawTextLine(Font *font, const char *str, const float x, const float y, const int pos, const int point, const float lineLength, const float lineWidth, const char *colorName = "White");
	void ContentView();
	void ChangePos(const float x, const float y);
private:
	float x1, x2, y1, y2, w, l; //座標、線の太さ、線の長さ
	void Calc(const float x, const float y); //座標計算
};

#endif