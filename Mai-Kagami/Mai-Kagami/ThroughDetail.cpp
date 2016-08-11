#include "ThroughDetail.h"

ThroughDetail::ThroughDetail(Font *font) {
	title = new DrawTitle(font, "採点結果");
	button = new CircleButton2(font, "次へ", 4);
}

void ThroughDetail::View() {
	title->View();
	button->View();
}

ThroughDetail::~ThroughDetail() {
	delete title;
	delete button;
}