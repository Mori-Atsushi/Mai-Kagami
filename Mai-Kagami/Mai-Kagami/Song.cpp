#include "Song.h"

//�Ȗ��A�A�[�e�B�X�g���
DrawSongTitle::DrawSongTitle(Font *font, const char *title, const char *artist) {
	songTitle = new MyDrawTextLine(font, title,0, 0, 1, 30, WIDTH * 0.35, 2); //�e�L�X�g������
	songArtist = new MyDrawText(font, artist, 0, 0, 2, 20); //�e�L�X�g������
}

void DrawSongTitle::ChangePos(const float x, const float y) {
	Draw::ChangePos(x, y);
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
SongPart::SongPart(const int flame, const char *name) {
	SongPart::flame = flame;
	strcpy_s(SongPart::name, sizeof(SongPart::name), name);

}

//�t���[�����擾
int SongPart::GetFlame() {
	return flame;
}

//�p�[�g���擾
char *SongPart::GetName() {
	return name;
}

Song::Song(Font *font, const int id, const char *title, const char *artist, const char *folder) {
	char cover[256], movie[256];
	strcpy_s(Song::folder, sizeof(Song::folder), folder); //�t�H���_
	sprintf_s(cover, sizeof(cover), "song/%s/cover.jpg", folder); //�J�o�[�摜
	sprintf_s(music, sizeof(music), "song/%s/music.mp3", folder); //���y
	sprintf_s(movie, sizeof(movie), "song/%s/movie.ogv", folder); //����
	Song::id = id;
	n = new int();

	drawSongTitle = new DrawSongTitle(font, title, artist);
	coverGraph = new MyDrawGraph(cover);
	danceMovie = new MyDrawMovie(movie);
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
		danceMovie->ChangeSpeed(s[x]);
	}
	if (num == -1 && x < 5) {
		x += 1;
		danceMovie->ChangeSpeed(s[x]);
	}
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
	songPartNum = 0;
	while (FileRead_scanf(file, "%d,%[^\n\r]", &flame, buf) != EOF) {
		songPart[songPartNum] = new SongPart(flame, buf);
		songPartNum++;
	}
}

//�p�[�g���擾
SongPart *Song::GetPart(int num) {
	return songPart[num];
}

//�p�[�g���擾
int Song::GetPartNum() {
	return songPartNum;
}