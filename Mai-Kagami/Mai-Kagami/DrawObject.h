#ifndef __DRAWOBJECT_H_INCLUDED__
#define __DRAWOBJECT_H_INCLUDED__

#include "DxLib.h"
#define _USE_MATH_DEFINES
#include "Main.h"
#include "Draw.h"

//円関係
class MyDrawCircle : public Draw, public Color{
public:
	MyDrawCircle(const float x, const float y, const float radius, const char *colorName = "Blue"); //円初期化（塗りつぶしあり）
	MyDrawCircle(const float x, const float y, const float radius, const float width, const char *colorName = "Blue"); //円初期化（塗りつぶしなし）
	void View();
private:
	float r, w; //半径、線の太さ
};

//角度付きの円(線のみ)
class MyDrawCircleGauge : public MyDrawCircle , public Draw{
public:
	MyDrawCircleGauge(const float x, const float y, const float radius, const double degree, const float width, const char *colorName = "Blue");
	void View();
	void ChangeDegree(const double degree);
	float GetEndX();
	float GetEndY();
private:
	float r; //半径
	double rad; //角度（ラジアン）
};

//正三角形関係
class MyDrawTriangle : public Draw, public Color {
public:
	MyDrawTriangle(const float x, const float y, const float width, const int direction, const char *colorName = "Blue");
	void View(); //表示
private:
	int d;
	float w;
};

//四角形関係
class MyDrawBox : public Draw, public Color {
public:
	MyDrawBox(const float x, const float y, const float width, const float height, const char *colorName = "White"); //四角形初期化（塗りつぶしあり）
	MyDrawBox(const float x, const float y, const float width, const float height, const float line, const char *colorName = "Blue"); //四角形初期化（塗りつぶしなし）
	void View();
	void ChangeSize(const float width, const float height);
private:
	float w, h, l; //幅、高さ、線の太さ
};

class MyDrawBar : public MyDrawBox {
public:
	MyDrawBar(const float x, const float y, const float width, const float height, const char *colorName = "White"); //四角形初期化（塗りつぶしあり）
	void ChangeSize(const float width, const float height);
private:
	float x, y; //座標
};

#endif