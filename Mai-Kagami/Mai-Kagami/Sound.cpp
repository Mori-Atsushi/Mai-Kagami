#include "Sound.h"

//���ʉ����[�h
SoundEffect::SoundEffect() {
	for (int i = 0; i < SOUND_NUM; i++) 
		id[i] = LoadSoundMem(path[i]);
}

//���ʉ��Đ�
void SoundEffect::PlaySoundEffect(int SoundType) {
	PlaySoundMem(id[SoundType], DX_PLAYTYPE_BACK);
}

SoundEffect::~SoundEffect() {
	for (int i = 0; i < SOUND_NUM; i++)
		DeleteSoundMem(id[i]);	//���ʉ����폜
}