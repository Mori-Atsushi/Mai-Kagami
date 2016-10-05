#ifndef _SOUND_H_INCLUDE_
#define _SOUND_H_INCLUDE_

#include "DxLib.h"

#define SOUND_NUM 4

enum sound{SOUND_EFFECT_LOGIN, SOUND_EFFECT_CHOICE, SOUND_EFFECT_DECIDE, SOUND_EFFECT_ERROR};


class SoundEffect {
public:
	SoundEffect();
	void PlaySoundEffect(int SoundType);
	~SoundEffect();
private:
	int id[SOUND_NUM];
	char path[SOUND_NUM][64] = {
		"./se/decide.mp3",
		"./se/choice.mp3",
		"./se/decide.mp3",
		"./se/error.mp3"
	};

};
#endif // ! _SOUND_H_INCLUDE_
