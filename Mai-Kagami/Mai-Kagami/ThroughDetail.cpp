#include "ThroughDetail.h"

ThroughFinish::ThroughFinish(DecorationItem *decorationItem, Songs *songs, Touch *touch, Result *result) {
	this->songs = songs;
	this->result = result;
	blackBox = new BlackBox();
	rButton = new RecommendButton(decorationItem, songs, touch, result, 0);
	button[0] = new CircleButton(decorationItem, touch, "������x", 1, WIDTH * 0.75, "Blue");
	button[1] = new CircleButton(decorationItem, touch, "�������K", 2, WIDTH * 0.75, "Blue");
	button[2] = new CircleButton(decorationItem, touch, "�ȑI�����", 3, WIDTH * 0.75, "Blue");
}

ThroughResultScene ThroughFinish::Switch(const ThroughResultScene scene) {
	Song *song = songs->GetSong(songs->GetNowSong());
	if (rButton->GetTouch() == 1) {
		song->SetStart(result->GetBadPart());
		song->SetEnd(result->GetBadPart());
		song->SetSpeed(result->GetBadSpeed());
		return THROUGH_RESULT_BACK_PART_OPTION;
	}
	if (button[0]->GetTouch() == 1)
		return THROUGH_RESULT_BACK_PLAY;
	if (button[1]->GetTouch() == 1)
		return THROUGH_RESULT_BACK_PART_OPTION;
	if (button[2]->GetTouch() == 1)
		return THROUGH_RESULT_BACK_SONG_SELECT;
	return scene;
}

void ThroughFinish::ContentUpdate() {
	if (nowScene == THROUGH_RESULT_FINISH) {
		rButton->Update();
		viewFlag = TRUE;
	}
	else {
		viewFlag = FALSE;
	}
}

void ThroughFinish::ContentView() {
	blackBox->View();
	rButton->View();
	for (int i = 0; i < 3; i++)
		button[i]->View();
}

ThroughFinish::~ThroughFinish() {
	delete blackBox;
	delete rButton;
	for (int i = 0; i < 3; i++)
		delete button[i];
}

ThroughDetailScreen::ThroughDetailScreen(DecorationItem *decorationItem, Songs *songs, Touch *touch, Result *result) {
	this->decorationItem = decorationItem;
	this->songs = songs;
	this->result = result;
	title = new DrawTitle(decorationItem, "�̓_����");
	timingBar = new TimingBar(decorationItem);
	expressionBar = new ExpressionBar(decorationItem);
	resultComment = new ResultComment(decorationItem);
	resultBody = new ResultBody(decorationItem);
	resultGraph = new ResultGraph(decorationItem);
	button = new CircleButton2(decorationItem, touch, "����", 4);
}

ThroughResultScene ThroughDetailScreen::Switch(const ThroughResultScene scene) {
	if (button->GetTouch() == 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_DECIDE);
		return THROUGH_RESULT_FINISH;
	}
	return scene;
}

void ThroughDetailScreen::Load() {
	Song *song = songs->GetSong(songs->GetNowSong());
	int point[4];
	int score[100];
	int max = result->GetScore(score);
	timingBar->Load(result->GetTiming());
	expressionBar->Load(result->GetExpression());
	result->GetPoint(point);
	resultBody->Load(point);
	resultComment->Load(result->GetComment());
	resultGraph->Load(score, max, song);
}

void ThroughDetailScreen::ContentUpdate() {
	if (nowScene == THROUGH_RESULT_DETAIL || nowScene == THROUGH_RESULT_FINISH)
		viewFlag = TRUE;
	else
		viewFlag = FALSE;
}

void ThroughDetailScreen::ContentView() {
	title->View();
	timingBar->View();
	expressionBar->View();
	resultComment->View();
	button->View();
	resultBody->View();
	resultGraph->View();
}

void ThroughDetailScreen::Delete() {
	resultGraph->Delete();
	resultBody->Delete();
}

ThroughDetailScreen::~ThroughDetailScreen() {
	delete title;
	delete timingBar;
	delete expressionBar;
	delete resultComment;
	delete button;
	delete resultGraph;
}

ThroughDetail::ThroughDetail(DecorationItem *decorationItem, Songs *songs, Touch *touch, Result *result) {
	throughDetailScreen = new ThroughDetailScreen(decorationItem, songs, touch, result);
	throughFinish = new ThroughFinish(decorationItem, songs, touch, result);
}

ThroughResultScene ThroughDetail::Switch(const ThroughResultScene scene) {
	switch (scene)
	{
	case THROUGH_RESULT_DETAIL:
		return throughDetailScreen->Switch(scene);
	case THROUGH_RESULT_FINISH:
		return throughFinish->Switch(scene);
	}
	return scene;
}

void ThroughDetail::Load() {
	throughDetailScreen->Load();
	throughFinish->Load();
}

void ThroughDetail::ContentUpdate() {
	throughFinish->Update(nowScene);
	throughDetailScreen->Update(nowScene);
	if (nowScene == THROUGH_RESULT_DETAIL || nowScene == THROUGH_RESULT_FINISH)
		viewFlag = TRUE;
	else
		viewFlag = FALSE;
}

void ThroughDetail::ContentView() {
	throughDetailScreen->View();
	throughFinish->View();
}

void ThroughDetail::Delete() {
	throughDetailScreen->Delete();
}

ThroughDetail::~ThroughDetail() {
	delete throughDetailScreen;
	delete throughFinish;
}

RecommendButton::RecommendButton(DecorationItem *decorationItem, Songs *songs, Touch* touch, Result *result, const int num)
	: Button(num, touch){
	this->songs = songs;
	this->result = result;
	text = new MyDrawTextLine(decorationItem, "�������ߗ��K", WIDTH * 0.75, GetY() - HEIGHT * 0.015, 1, 30, WIDTH * 0.25,  3, "White");
	myDrawCircle = new MyDrawCircle(WIDTH * 0.97, GetY(), WIDTH * 0.015, 7, "Blue");
	textSub = new MyDrawText(decorationItem, "", WIDTH * 0.75, GetY() + HEIGHT * 0.015, 1, 24, "Blue");
}

void RecommendButton::Update() {
	const double s[6] = { 1.0, 0.9, 0.8, 0.7, 0.6, 0.5 };
	Song *song = songs->GetSong(songs->GetNowSong());
	char buf[256];
	sprintf_s(buf, sizeof(buf), "%s �` %s �@���x:�~%1.1f", song->GetPart(result->GetBadPart())->GetName(), song->GetPart(result->GetBadPart())->GetName(), s[result->GetBadSpeed()]);
	textSub->ChangeText(buf);
}

void RecommendButton::ContentView() {
	myDrawCircle->View();
	text->View();
	textSub->View();
}

RecommendButton::~RecommendButton() {
	delete text;
	delete myDrawCircle;
	delete textSub;
}