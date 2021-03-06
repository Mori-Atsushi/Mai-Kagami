#include "Sound.h"

//効果音ロード
SoundEffect::SoundEffect() {
	for (int i = 0; i < SOUND_NUM; i++) 
		id[i] = LoadSoundMem(path[i]);
}

//効果音再生
void SoundEffect::PlaySoundEffect(int SoundType) {
	PlaySoundMem(id[SoundType], DX_PLAYTYPE_BACK);
}

SoundEffect::~SoundEffect() {
	for (int i = 0; i < SOUND_NUM; i++)
		DeleteSoundMem(id[i]);	//効果音を削除
}