#include "ThroughResultObject.h"

ScoreBar::ScoreBar(DecorationItem *decorationItem, const float y, const char *title, const char *para1, const char *para2)
 : Draw(WIDTH * 0.475, y) {
	const float height = 110;
	this->title = new MyDrawTextLine(decorationItem, title, GetX(), GetY(), 0, 24, WIDTH * 0.3, 2);
	mark = new MyDrawGraph(0, GetY() + height - 50, "img/mark.png");
	score = new MyDrawText(decorationItem, "", 0, GetY() + height - 55, ALIGNMENT_CENTER, 30);
	para[0] = new MyDrawText(decorationItem, para1, GetX() - 100, GetY() + height, ALIGNMENT_RIGHT, 20);
	para[1] = new MyDrawText(decorationItem, para2, GetX() + 100, GetY() + height, ALIGNMENT_LEFT, 20);
	for (int i = 0; i < 8; i++)
		box[i] = new MyDrawBox(GetX() - 77 + i * 22, GetY() + height, 20, 40);
}

void ScoreBar::Load(const int p) {
	char point[10];
	sprintf_s(point, sizeof(point), "%d", p);
	mark->Load();
	const float x = GetX() - 88 + p * 22;
	mark->ChangePos(x, mark->GetY());
	score->ChangePos(x, score->GetY());
	score->ChangeText(point);
	for (int i = 0; i < 8; i++) {
		if (i < p)
			box[i]->SetAlpha();
		else
			box[i]->SetAlpha(100);
	}
}

void ScoreBar::ContentView() {
	title->View();
	mark->View();
	score->View();
	for (int i = 0; i < 2; i++)
		para[i]->View();
	for (int i = 0; i < 8; i++)
		box[i]->View();
}

ScoreBar::~ScoreBar() {
	delete title;
	delete mark;
	delete score;
	for (int i = 0; i < 2; i++)
		delete para[i];
	for (int i = 0; i < 8; i++)
		delete box[i];
}

TimingBar::TimingBar(DecorationItem *decorationItem) : ScoreBar(decorationItem, HEIGHT * 0.44, "�^�C�~���O", "slow", "early") {}

ExpressionBar::ExpressionBar(DecorationItem *decorationItem) : ScoreBar(decorationItem, HEIGHT * 0.54, "�\��", "bad", "good") {}

ResultComment::ResultComment(DecorationItem *decorationItem)
	: Draw(WIDTH * 0.6, HEIGHT * 0.64) {
	title = new MyDrawTextLine(decorationItem, "�R�����g", GetX(), GetY(), ALIGNMENT_LEFT, 24, WIDTH * 0.55, 2);
	comment = new MyDrawTexts(decorationItem, "", WIDTH * 0.35, GetY() + 72, ALIGNMENT_LEFT, 20, 16);
}

void ResultComment::Load(const char *str) {
	comment->MakeNewLine(str, WIDTH * 0.5);
}

void ResultComment::ContentView() {
	title->View();
	comment->View();
}

ResultComment::~ResultComment() {
	delete title;
	delete comment;
}

ResultBody::ResultBody(DecorationItem *decorationItem) 
	: Draw(WIDTH * 0.8, HEIGHT * 0.53) {
	body = new MyDrawGraph(GetX(), GetY(), "img/man.png");
	part[0] = new MyDrawText(decorationItem, "����", GetX() - 106, GetY() - 68, ALIGNMENT_CENTER, 20);
	part[1] = new MyDrawText(decorationItem, "�E��", GetX() + 140, GetY() - 55, ALIGNMENT_CENTER, 20);
	part[2] = new MyDrawText(decorationItem, "����", GetX() - 100, GetY() + 68, ALIGNMENT_CENTER, 20);
	part[3] = new MyDrawText(decorationItem, "�E��", GetX() + 122, GetY() + 55, ALIGNMENT_CENTER, 20);

	point[0] = new MyDrawText(decorationItem, "", GetX() - 147, GetY() - 70, 1, 30, "Yellow");
	point[1] = new MyDrawText(decorationItem, "", GetX() + 99, GetY() - 57, 1, 30, "Yellow");
	point[2] = new MyDrawText(decorationItem, "", GetX() - 141, GetY() + 66, 1, 30, "Yellow");
	point[3] = new MyDrawText(decorationItem, "", GetX() + 81, GetY() + 53, 1, 30, "Yellow");
}

void ResultBody::Load(const int point[4]) {
	body->Load();
	for (int i = 0; i < 4; i++) {
		
		switch (point[i]) {
		case 1:
			this->point[i]->ChangeText("A");
			this->point[i]->ChangeColor("Red");
			break;
		case 2:
			this->point[i]->ChangeText("B");
			this->point[i]->ChangeColor("Yellow");
			break;
		case 3:
			this->point[i]->ChangeText("C");
			this->point[i]->ChangeColor("Green");
			break;
		}
	}
}

void ResultBody::ContentView() {
	body->View();
	for (int i = 0; i < 4; i++) {
		part[i]->View();
		point[i]->View();
	}
}

void ResultBody::Delete() {
	body->Release();
}

ResultBody::~ResultBody() {
	delete body;
	for (int i = 0; i < 4; i++) {
		delete part[i];
		delete point[i];

	}
}

ResultGraph::ResultGraph(DecorationItem *decorationItem) 
	: Draw(WIDTH * 0.65, HEIGHT * 0.32) {
	this->decorationItem = decorationItem;

	text = new MyDrawText(decorationItem, "��ԕʍ̓_", WIDTH*0.35, HEIGHT*0.245, 0, 20);
	frame[0] = new MyDrawLine(GetX() - w / 2, GetY() - h / 2, GetX() - w / 2, GetY() + h / 2, 6, "White");
	frame[1] = new MyDrawLine(GetX() - w / 2, GetY() + h / 2, GetX() + w / 2, GetY() + h / 2, 6, "White");
	scale = new MyDrawTexts(decorationItem, "100\n�E\n�E\n�E\n�E\n50\n�E\n�E\n�E\n�E\n0", GetX() - w / 2 - WIDTH * 0.025, GetY(), ALIGNMENT_CENTER, 20, 4);
}

void ResultGraph::Load(const int *point, const int num, Song *song) {
	pointMax = num;
	partMax = song->GetPartNum();
	for (int i = 0; i < num; i++) {
		float x1 = GetX() - w / 2 + (float)i / (num - 1) * w;
		float y1 = GetY() + h / 2 - (float)point[i] / 100 * h;
		if (i > 0) {
			float x2 = GetX() - w / 2 + (float)(i - 1) / (num - 1) * w;
			float y2 = GetY() + h / 2 - (float)point[i - 1] / 100 * h;
			line[i - 1] = new MyDrawLine(x1, y1, x2, y2, 3);
		}
		dot[i] = new MyDrawGraph(x1, y1, "img/star.png", 0.1);
		dot[i]->Load();
		if (point[i] > 80)
			dot[i]->SetViewFlag(TRUE);
		else
			dot[i]->SetViewFlag(FALSE);
	}

	for (int i = 0; i < partMax; i++) {
		SongPart *songPart = song->GetPart(i);
		float x = GetX() - w / 2 + w * (float)songPart->GetFlame() / song->danceMovie->GetEndFlame();
		part[i] = new MyDrawTextV(decorationItem, songPart->GetName(),  x, GetY() + HEIGHT * 0.075, 2, 16);
	}
}

void ResultGraph::ContentView() {
	for (int i = 0; i < partMax; i++)
		part[i]->View();
	for (int i = 0; i < pointMax - 1; i++)
		line[i]->View();
	for(int i = 0; i < pointMax; i++)
		dot[i]->View();
	for (int i = 0; i < 2; i++)
		frame[i]->View();
	scale->View();
	text->View();
}

void ResultGraph::Delete() {
	for (int i = 0; i < pointMax; i++) {
		delete dot[i];
		if (i > 0)
			delete line[i - 1];
	}
	for (int i = 0; i < partMax; i++)
		delete part[i];
}

ResultGraph::~ResultGraph() {
	for (int i = 0; i < 2; i++)
		delete frame[i];
	scale->View();
}