#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#define SIZE_RATE	1
#define WIDTH		1080
#define HEIGHT		1920

#define NFC_POS		HEIGHT * 0.85
#define NFC_FLAG	TRUE	//NFC�J�[�h��ǂݍ��ނ��ǂ���(TRUE:�ǂݍ���/FALSE:�ǂݍ��܂Ȃ�)
#define TOUCH_FLAG	TRUE	//�T�C�h�^�b�`�p�l�����g����
#define KINECT_FLAG	FALSE	//KINECT���g�p���邩�ǂ���(TRUE:�g�p����/FALSE:�g�p���Ȃ�)
#define FULLSCREEN_FLAG	TRUE	//�t���X�N���[���ɂ��邩


typedef enum {
	TOP,
	SONG_SELECT,
	THROUGH,
	THROUGH_RESULT,
	PART,
	PART_RESULT,
	THROUGH_OPTION,
	PART_OPTION
} MainScene;

#endif