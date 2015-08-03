#include "Soldier.h"
Soldier::Soldier()
{
}

Soldier::~Soldier()
{
}
bool Soldier::init(){
	//��plist���ص������
	//�½�һ����������ڴ������ľŸ�����
	/*
	up1~up8�������ƶ���8������������˳����8��1��up9������վ��
	ͬ����down,right,left,ur,ul,dr,dl
	*/
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("./Soldier/" + kind + ".plist", "./Soldier/" + kind + ".png");
	//�����ﴴ��9���˶��ļ��ϣ��ھŸ���վ������Map������Ƚ����ײ�ѯ    �����Vector��Map��cocos�Դ���
	//��ΪStandMapҪ�������ķ����е��ã������Ҷ����ȫ�ֵ���
	Vector<SpriteFrame*>frameVec_Up;
	Vector<SpriteFrame*>frameVec_Down;
	Vector<SpriteFrame*>frameVec_Right;
	Vector<SpriteFrame*>frameVec_Left;
	Vector<SpriteFrame*>frameVec_UR;
	Vector<SpriteFrame*>frameVec_UL;
	Vector<SpriteFrame*>frameVec_DR;
	Vector<SpriteFrame*>frameVec_DL;
	for (int i = 0; i < 8; i++){
		//StringUtils��cocos�Դ��ĸ�ʽ���ַ����ĺ���
		frameVec_Up.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("up%d.png",(8-i))));
		frameVec_Down.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("down%d.png", (8 - i))));
		frameVec_UR.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("ur%d.png", (8 - i))));
		frameVec_UL.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("ul%d.png", (8 - i))));
		frameVec_Right.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("right%d.png", (8 - i))));
		frameVec_Left.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("left%d.png", (8 - i))));
		frameVec_DR.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("dr%d.png", (8 - i))));
		frameVec_DL.pushBack(frameCache->getSpriteFrameByName(StringUtils::format("dl%d.png", (8 - i))));
	}
	//���ｫվ���Ķ�����ӵ�standMap��
	standMap.insert("up", frameCache->getSpriteFrameByName("up9.png"));
	standMap.insert("down", frameCache->getSpriteFrameByName("down9.png"));
	standMap.insert("ur", frameCache->getSpriteFrameByName("ur9.png"));
	standMap.insert("ul", frameCache->getSpriteFrameByName("ul9.png"));
	standMap.insert("right", frameCache->getSpriteFrameByName("right9.png"));
	standMap.insert("left", frameCache->getSpriteFrameByName("left9.png"));
	standMap.insert("dr", frameCache->getSpriteFrameByName("dr9.png"));
	standMap.insert("dl", frameCache->getSpriteFrameByName("dl9.png"));
	//��ʼ�����ֶ���
	CCAnimation *animationUp = CCAnimation::createWithSpriteFrames(frameVec_Up);
	CCAnimation *animationDown = CCAnimation::createWithSpriteFrames(frameVec_Down);
	CCAnimation *animationRight = CCAnimation::createWithSpriteFrames(frameVec_Right);
	CCAnimation *animationLeft = CCAnimation::createWithSpriteFrames(frameVec_Left);
	CCAnimation *animationUR = CCAnimation::createWithSpriteFrames(frameVec_UR);
	CCAnimation *animationUL = CCAnimation::createWithSpriteFrames(frameVec_UL);
	CCAnimation *animationDR = CCAnimation::createWithSpriteFrames(frameVec_DR);
	CCAnimation *animationDL = CCAnimation::createWithSpriteFrames(frameVec_DL);
	//��������һЩ������setLoops����������Ϊѭ�����ţ�setDelayPerUnit����ÿ֡�ļ��Ϊ0.2��
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
	//�������ӵ�����������
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationUp,"up");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationDown, "down");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationRight, "right");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationLeft, "left");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationUR, "ur");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationUL, "ul");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationDR, "dr");
	CCAnimationCache::sharedAnimationCache()->addAnimation(animationDL, "dl");
	//����������
	animCache = CCAnimationCache::sharedAnimationCache();
	//����¼�����
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Soldier::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//������Ӹ���ͨ�����ļ���
	skill[0] = 0;
	//����ƶ���Ϣ�ļ���
	log("%d",id);
	GameManager::getInstance()->addMoveObsever(StringUtils::format("%d", id), [&](Vec2 vec){
		log("start move action");	
		StartMoveAction(vec);
	});
	return true;
	
}
//��������Ƕ�soldier��һ������
void Soldier:: bindSprite(Sprite *sprite){
	m_sprite = sprite;
	//����һ���ǶԾ�������һ����ʼ��ͼƬ
	m_sprite->setSpriteFrame(standMap.at(direction));
	this->addChild(m_sprite);	
}

//�ƶ����̣���һ����һ���㣨һ��һ�������ƶ�����֤ͬ��
void Soldier::StartMoveAction(Vec2 vec){
	//�����ƶ���ʼ����.
	
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
		//�����غ�˵���ߵ��ˣ�ͣ�ö���
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
//�����ƶ���������
void Soldier::endMoveAction(){
	m_sprite->stopAllActions();
	isMoving = false;
	//ͣ�º�Ҫ����ͣ�º��վλ
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
	//������ȫ�ǲ���
	GameManager::getInstance()->postMoveNotification("0",touch->getLocation());
}
void Soldier::attack(int id){

}