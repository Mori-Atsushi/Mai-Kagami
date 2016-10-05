#ifndef __SONGS_H_INCLUDED__
#define __SONGS_H_INCLUDED__

#include <Windows.h>
#include <winhttp.h>
#include <wchar.h>

#include "Song.h"
#include "DxLib.h"
#include "DrawGraph.h"
#include "DecorationItem.h"

#pragma comment (lib, "winhttp.lib")

class Songs {
public:
	Songs(DecorationItem *decorationItem);
	int GetSongNum(); //�Ȑ��擾
	Song *GetSong(int x);
	int GetNowSong();
	//�������[�h
	//����������0,�G���[�Ȃ��-1��Ԃ�
	int LoadHistory(const char *userId);
private:
	Song *song[256];
	int Search(const int songId);
	int n; //�Ȑ�
};

#endif