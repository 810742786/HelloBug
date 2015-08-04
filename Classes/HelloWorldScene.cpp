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
	//下面用于测试并没什么用
	TMXTiledMap* map = TMXTiledMap::create("map.tmx");
	addChild(map);	
	Soldier* soldier = Soldier::create();
	addSoldier(map,soldier);
	//
	
	auto listeners = EventListenerMouse::create();
	listeners->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listeners, this);
	//
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//上面那些是测试的
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HelloWorld:: addSoldier(TMXTiledMap* map,Soldier *msoldier){//将士兵添加到map中
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* soldierSprite = Sprite::create();	
	msoldier->bindSprite(soldierSprite);
	msoldier->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	map->addChild(msoldier);	
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	
	
	
	log("%f,%f", touch->getLocation().x, touch->getLocation().y);

}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	
	
	return true;

}
void HelloWorld::onMouseScroll(cocos2d::Event* event){
	
}