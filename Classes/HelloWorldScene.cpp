#include "HelloWorldScene.h"



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//�������ڲ��Բ�ûʲô��
	TMXTiledMap* map = TMXTiledMap::create("map.tmx");
	addChild(map);
	Soldier* soldier = Soldier::create();
	addSoldier(map,soldier);
	//������Щ�ǲ��Ե�
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HelloWorld:: addSoldier(TMXTiledMap* map,Soldier *msoldier){//��ʿ����ӵ�map��
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* soldierSprite = Sprite::create();	
	msoldier->bindSprite(soldierSprite);
	msoldier->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	map->addChild(msoldier);	
}