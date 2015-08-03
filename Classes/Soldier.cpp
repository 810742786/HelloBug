#include "Soldier.h"
Soldier::Soldier()
{
}

Soldier::~Soldier()
{
}
bool Soldier::init(){
	//将plist加载到缓存池
	//新建一个缓存池用于存放人物的九个动作
	/*
	up1~up8是向上移动的8个动作，动作顺序是8→1，up9是向上站立
	同理有down,right,left,ur,ul,dr,dl
	*/
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("./Soldier/" + kind + ".plist", "./Soldier/" + kind + ".png");
	//从这里创建9个运动的集合，第九个是站立的用Map集合类比较容易查询    这里的Vector跟Map是cocos自带的
	//因为StandMap要在其他的方法中调用，所以我定义成全局的了
	Vector<SpriteFrame*>frameVec_Up;
	Vector<SpriteFrame*>frameVec_Down;
	Vector<SpriteFrame*>frameVec_Right;
	Vector<SpriteFrame*>frameVec_Left;
	Vector<SpriteFrame*>frameVec_UR;
	Vector<SpriteFrame*>frameVec_UL;
	Vector<SpriteFrame*>frameVec_DR;
	Vector<SpriteFrame*>frameVec_DL;
	for (int i = 0; i < 8; i++){
		//StringUtils是cocos自带的格式化字符串的函数
		frameVec_Up.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("up%d.png",(8-i))));
		frameVec_Down.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("down%d.png", (8 - i))));
		frameVec_UR.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("ur%d.png", (8 - i))));
		frameVec_UL.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("ul%d.png", (8 - i))));
		frameVec_Right.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("right%d.png", (8 - i))));
		frameVec_Left.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("left%d.png", (8 - i))));
		frameVec_DR.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("dr%d.png", (8 - i))));
		frameVec_DL.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("dl%d.png", (8 - i))));
	}
	//这里将站立的动作添加到standMap中
	standMap.insert("up", frameCache->getSpriteFrameByName("up9.png"));
	standMap.insert("down", frameCache->getSpriteFrameByName("down9.png"));
	standMap.insert("ur", frameCache->getSpriteFrameByName("ur9.png"));
	standMap.insert("ul", frameCache->getSpriteFrameByName("ul9.png"));
	standMap.insert("right", frameCache->getSpriteFrameByName("right9.png"));
	standMap.insert("left", frameCache->getSpriteFrameByName("left9.png"));
	standMap.insert("dr", frameCache->getSpriteFrameByName("dr9.png"));
	standMap.insert("dl", frameCache->getSpriteFrameByName("dl9.png"));
	//初始化各种动作
	CCAnimation *animationUp = CCAnimation::createWithSpriteFrames(frameVec_Up);
	CCAnimation *animationDown = CCAnimation::createWithSpriteFrames(frameVec_Down);
	CCAnimation *animationRight = CCAnimation::createWithSpriteFrames(frameVec_Right);
	CCAnimation *animationLeft = CCAnimation::createWithSpriteFrames(frameVec_Left);
	CCAnimation *animationUR = CCAnimation::createWithSpriteFrames(frameVec_UR);
	CCAnimation *animationUL = CCAnimation::createWithSpriteFrames(frameVec_UL);
	CCAnimation *animationDR = CCAnimation::createWithSpriteFrames(frameVec_DR);
	CCAnimation *animationDL = CCAnimation::createWithSpriteFrames(frameVec_DL);
	//这里设置一些参数，setLoops将动画设置为循环播放，setDelayPerUnit设置每帧的间隔为0.2秒
	animationUp->setLoops(-1);
	animationUp->setDelayPerUnit(0.2f);
	animationDown->setLoops(-1);
	animationDown->setDelayPerUnit(0.2f);
	animationRight->setLoops(-1);
	animationRight->setDelayPerUnit(0.2f);
	animationLeft->setLoops(-1);
	animationLeft->setDelayPerUnit(0.2f);
	animationUR->setLoops(-1);
	animationUR->setDelayPerUnit(0.2f);
	animationUL->setLoops(-1);
	animationUL->setDelayPerUnit(0.2f);
	animationDR->setLoops(-1);
	animationDR->setDelayPerUnit(0.2f);
	animationDL->setLoops(-1);
	animationDL->setDelayPerUnit(0.2f);
	//将动画加到动画缓存中
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationUp,"up");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationDown, "down");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationRight, "right");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationLeft, "left");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationUR, "ur");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationUL, "ul");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationDR, "dr");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationDL, "dl");
	//共享动画缓存
	animCache = CCAnimationCache::sharedAnimationCache();
	//鼠标事件监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Soldier::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//给人物加个普通攻击的技能
	skill[0] = 0;
	//添加移动消息的监听
	log("%d",id);
	GameManager::getInstance()->addMoveObsever(StringUtils::format("%d", id), [&](Vec2 vec){
		log("start move action");	
		StartMoveAction(vec);
	});
	return true;
	
}
//这个方法是对soldier绑定一个精灵
void Soldier:: bindSprite(Sprite *sprite){
	m_sprite = sprite;
	//下面一行是对精灵设置一个初始的图片
	m_sprite->setSpriteFrame(standMap.at(direction));
	this->addChild(m_sprite);	
}

//移动过程，是一个点一个点（一步一步）的移动，保证同步
void Soldier::StartMoveAction(Vec2 vec){
	//设置移动开始动画.
	
	string d;
	float d_X = vec.x - this->getPosition().x;
	float d_Y = vec.y - this->getPosition().y;
	if (d_X > 0 && d_Y > 0){
		d = "ur";
	}
	else if (d_X < 0 && d_Y > 0){
		d = "ul";
	}
	else if(d_X > 0 && d_Y < 0){
		d = "dr";
	}
	else if (d_X < 0 && d_Y < 0){
		d = "dl";
	}
	else if (d_X == 0 && d_Y > 0){
		d = "up";
	}
	else if (d_X == 0 && d_Y < 0){
		d = "down";
	}
	else if (d_X > 0 && d_Y == 0){
		d = "right";
	}
	else if (d_X < 0 && d_Y == 0){
		d = "left";
	}
	else {
		//坐标重合说明走到了，停用动画
		endMoveAction();
		return;
	}
	if (isMoving){
		if (d != direction){
			direction = d;
			m_sprite->stopAllActions();
			CCAnimation *normal = animCache->animationByName(direction);
			m_sprite->runAction(Animate::create(normal));
		}
	}
	else{
		direction = d;
		m_sprite->stopAllActions();
		CCAnimation *normal = animCache->animationByName(direction);
		m_sprite->runAction(Animate::create(normal));
	}
	
		
	isMoving = true;
	this->setPosition(vec);
}
//设置移动结束动画
void Soldier::endMoveAction(){
	m_sprite->stopAllActions();
	isMoving = false;
	//停下后要设置停下后的站位
	m_sprite->setSpriteFrame(standMap.at(direction));
}

bool Soldier::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}
void Soldier::onTouchEnded(cocos2d::Touch	* touch, cocos2d::Event* event){
	CCPoint touchPoint = convertTouchToNodeSpace(touch);
	if (m_sprite->boundingBox().containsPoint(touchPoint)){		
//		beChoosedID = this->id;
		log("Soldier is be clicked");
	}
	//下面完全是测试
	GameManager::getInstance()->postMoveNotification("0",touch->getLocation());
}
void Soldier::attack(int id){

}