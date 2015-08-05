#ifndef _CHOOSESPRITE_H_
#define _CHOOSESPRITE_H_
#include "cocos2d.h"

USING_NS_CC;
class Soldier;
class ChooseSprite :public Sprite{
public:
	static ChooseSprite* getInstance();
	static ChooseSprite* m_ChooseSprite;
	CREATE_FUNC(ChooseSprite);
	virtual bool init();
	void setChooseSprite(Soldier* soldier);
};
	






#endif