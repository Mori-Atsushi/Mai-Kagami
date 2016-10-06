#include "Song.h"

//�����Z�b�g
void SongHistory::Set(const int history[2]) {
	for (int i = 0; i < 2; i++)
		this->history[i] = history[i];
}

//�����擾
void SongHistory::Get(int *history[2]) {
	for (int i = 0; i < 2; i++)
		*history[i] = this->history[i];
}

//�Ȗ��A�A�[�e�B�X�g���
DrawSongTitle::DrawSongTitle(DecorationItem *decorationItem, const char *title, const char *artist) {
	songTitle = new MyDrawTextLine(decorationItem, title,0, 0, 1, 30, WIDTH * 0.35, 2); //�e�L�X�g������
	songArtist = new MyDrawText(decorationItem, artist, 0, 0, 2, 20); //�e�L�X�g������
}

void DrawSongTitle::ChangePos(const float x, const float y) {
	Pos::ChangePos(x, y);
	songTitle->ChangePos(x, y);
	songArtist->ChangePos(x + WIDTH * 0.17, y + HEIGHT * 0.025);
}

void DrawSongTitle::View() {
	songTitle->View();
	songArtist->View();
}

DrawSongTitle::~DrawSongTitle() {
	delete songTitle;
	delete songArtist;
}

//�p�[�g���
void SongPart::Set(const int flame, const char *name) {
	this->flame = flame;
	strcpy_s(this->name, sizeof(this->name), name);
}


//�t���[�����擾
int SongPart::GetFlame() {
	return flame;
}

//�p�[�g���擾
char *SongPart::GetName() {
	return name;
}

Song::Song(DecorationItem *decorationItem, const int id, const char *title, const char *artist, const char *folder) {
	this->decorationItem = decorationItem;
	char cover[256], movie[256];
	strcpy_s(Song::folder, sizeof(Song::folder), folder); //�t�H���_
	sprintf_s(cover, sizeof(cover), "song/%s/cover.jpg", folder); //�J�o�[�摜
	sprintf_s(music, sizeof(music), "song/%s/music.wav", folder); //���y
	sprintf_s(movie, sizeof(movie), "song/%s/movie.ogv", folder); //����
	Song::id = id;
	n = new int();
	songPartNum = new int();
	start = new int();
	end = new int();
	mode = new int();
	*start = 0;
	*end = 0;
	*mode = THROUGH_MODE;
	for(int i = 0; i < 256; i++)
		songPart[i] = new SongPart();

	drawSongTitle = new DrawSongTitle(decorationItem, title, artist);
	coverGraph = new MyDrawGraph(cover);
	coverWhite = new MyDrawGraph("img/box.png");
	danceMovie = new MyDrawMovie(movie);
	songHistory = new SongHistory();
}

//��ID���擾
int Song::GetSongId() {
	return id;
}

//���݂̈ʒuID���擾
int Song::GetNow() {
	return *n;
}

//�ʒuID���Z�b�g
void Song::SetNow(const int n) {
	*Song::n = n;
}

//����̍Đ��X�s�[�h��ύX
void Song::ChangeSpeed(int num) {
	const double s[6] = { 1.0, 0.9, 0.8, 0.7, 0.6, 0.5 };
	static int x = 0;
	if (num == 1 && x > 0) {
		x -= 1;
		decorationItem->PlaySoundEffect(SOUND_EFFECT_CHOICE);
		danceMovie->ChangeSpeed(s[x]);
	} else if (num == 1 && x <= 0) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_ERROR);
	}
	if (num == -1 && x < 5) {
		x += 1;
		decorationItem->PlaySoundEffect(SOUND_EFFECT_CHOICE);
		danceMovie->ChangeSpeed(s[x]);
	} else if (num == -1 && x >= 5) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_ERROR);
	}
}

//����̊J�n�ʒu��ύX
void Song::ChangeStart(int num) {
	if (num == 1 && *start > 0) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_CHOICE);
		(*start) -= 1;
	} else if (num == 1)
		decorationItem->PlaySoundEffect(SOUND_EFFECT_ERROR);

	if (num == -1 && *start < GetPartNum() - 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_CHOICE);
		(*start) += 1;
	} else if (num == -1)
		decorationItem->PlaySoundEffect(SOUND_EFFECT_ERROR);
	danceMovie->SetStartFlame(GetPart(*start)->GetFlame());
}

//����̏I���ʒu��ύX
void Song::ChangeEnd(int num) {
	if (num == 1 && *end > 0) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_CHOICE);
		(*end) -= 1;
	} else if (num == 1)
		decorationItem->PlaySoundEffect(SOUND_EFFECT_ERROR);
	if (num == -1 && *end < GetPartNum() - 1) {
		decorationItem->PlaySoundEffect(SOUND_EFFECT_CHOICE);
		(*end) += 1;
	} else if (num == 1)
		decorationItem->PlaySoundEffect(SOUND_EFFECT_ERROR);

	if (*end + 1 == GetPartNum())
		danceMovie->SetEndFlame(danceMovie->GetAllFlame());
	else
		danceMovie->SetEndFlame(GetPart(*end + 1)->GetFlame());
}

void Song::SetSpeed(const int speed) {
	const double s[6] = { 1.0, 0.9, 0.8, 0.7, 0.6, 0.5 };
	danceMovie->ChangeSpeed(s[speed]);
}

void Song::SetStart(const int startPart) {
	*start = startPart;
}

void Song::SetEnd(const int endPart) {
	*end = endPart;
}


int Song::StartPart() {
	return *start;
}

int Song::EndPart() {
	return *end;
}

//�p�[�g�������[�h
void Song::LoadPart() {
	char part[256];
	sprintf_s(part, sizeof(part), "song/%s/part.csv", folder);
	SetUseASyncLoadFlag(FALSE);
	int file = FileRead_open(part, FALSE);
	SetUseASyncLoadFlag(TRUE);
	char buf[256];
	int flame;
	*songPartNum = 0;
	while (FileRead_scanf(file, "%d,%[^\n\r]", &flame, buf) != EOF) {
		songPart[*songPartNum]->Set(flame, buf);
		(*songPartNum)++;
	}
}

//�p�[�g���擾
SongPart *Song::GetPart(int num) {
	return songPart[num];
}

//�p�[�g���擾
int Song::GetPartNum() {
	return *songPartNum;
}

//�t�H���_�擾
char *Song::GetFolder() {
	return folder;
}

//�v���C���[�h���Z�b�g
void Song::SetPlayMode(const int mode) {
	*this->mode = mode;
	if (mode == PART_MODE) {
		danceMovie->SetStartFlame(GetPart(*start)->GetFlame());
		if (*end + 1 == GetPartNum())
			danceMovie->SetEndFlame();
		else
			danceMovie->SetEndFlame(GetPart(*end + 1)->GetFlame());
	}
	else {
		danceMovie->SetStartFlame();
		danceMovie->SetEndFlame();
	}
	danceMovie->SetPart();
}

int Song::GetStartNum() {
	return *start;
}

int Song::GetEndNum() {
	return *end;
}