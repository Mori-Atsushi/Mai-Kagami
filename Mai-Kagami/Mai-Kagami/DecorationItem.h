#ifndef _DECORATIONITEM_H_INCLUDE_
#define _DECORATIONITEM_H_INCLUDE_

#include "Font.h"
#include "Sound.h"
#include "DxLib.h"

class DecorationItem 
	:public Font, public SoundEffect{
public :
	DecorationItem();
	~DecorationItem();
private :
};
#endif // !_DECORATIONITEM_H_INCLUDE_
