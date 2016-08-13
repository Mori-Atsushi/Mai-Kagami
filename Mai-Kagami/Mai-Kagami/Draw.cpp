#include "Draw.h"

//色指定
Color::Color(const char *color) {
	ChangeColor(color);
}

//色取得
int Color::Get() {
	return c;
}

void Color::ChangeColor(const char *color) {
	if (!strcmp(color, "White"))
		c = GetColor(255, 255, 255); //白色
	else if (!strcmp(color, "Blue"))
		c = GetColor(127, 210, 234); //青色
	else if (!strcmp(color, "Black"))
		c = GetColor(0, 0, 0); //黒色
	else if (!strcmp(color, "Yellow"))
		c = GetColor(255, 255, 0); //黄色
}

//表示位置用クラスコンストラクタ
Pos::Pos() {
	x = 0; y = 0;
}

//表示位置用クラスコンストラクタ
Pos::Pos(const float x, const float y) {
	this->x = x / SIZE_RATE; this->y = y / SIZE_RATE;
}

//表示位置変更
void Pos::ChangePos(const float x, const float y) {
	this->x = x / SIZE_RATE; this->y = y / SIZE_RATE;
}

// アニメーション用パラメータセット Jaity
void Pos::SetPosAnimation(float target_x, float target_y, MyTime duration, int ease) {
	if (GetTime() != 0)
		return;
	default_x = GetX() * SIZE_RATE;
	default_y = GetY() * SIZE_RATE;
	this->target_x = target_x;
	this->target_y = target_y;
	SetRate(duration, ease);
	//printfDx("Set: %f %f\n", default_x, default_y);
	//printfDx("Set: %f %f\n", target_x, target_y);
}


// アニメーション更新 Jaity
void Pos::Update() {
	double r = UpdateRate();
	float nx = default_x + (target_x - default_x) * r;
	float ny = default_y + (target_y - default_y) * r;
	//printfDx("Update: %f %f \n", default_x, default_y);
	//printfDx("Update: %f %f\n", GetX(), GetY());
	ChangePos(nx, ny);
}

//x座標取得
float Pos::GetX() {
	return x;
}

//y座標取得
float Pos::GetY() {
	return y;
}

//描画用クラスコンストラクタ
Draw::Draw(){}

//描画用クラスコンストラクタ
Draw::Draw(const float x, const float y) : Pos(x, y) {}

//描画
void Draw::View() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //透明度設定
	ContentView(); //内容表示
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透明度解除
}

//透明度指定
void Draw::SetAlpha(const int alpha) {
	this->alpha = alpha;
}

Draw2::Draw2(const int pos) {
	p = pos;
}

Draw2::Draw2(const float x, const float y, const int pos) {
	p = pos;
	ChangePos(x, y);
}

void Draw2::ChangePos(const float x, const float y) {
	Draw2::x = x;
	Draw2::y = y;
	float a = 0;
	switch (p) {
	case 1:
		a -= GetWidth() / 2;
		break;
	case 2:
		a -= GetWidth();
		break;
	}

	Draw::ChangePos(Draw2::x + a, Draw2::y - GetHeight() / 2);
}