#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Soldier.h"
#include "GameManager.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void addSoldier(TMXTiledMap* map, Soldier *soldier);
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
