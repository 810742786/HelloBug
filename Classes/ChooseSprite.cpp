#include "ChooseSprite.h"
#include "Soldier.h"

ChooseSprite* ChooseSprite::m_ChooseSprite = NULL;

ChooseSprite* ChooseSprite::getInstance(){
	if (m_ChooseSprite == NULL){
		m_ChooseSprite = ChooseSprite::create();
		m_ChooseSprite->retain();
	}
	return m_ChooseSprite;
}
bool ChooseSprite::init(){
	initWithFile("choose.png");
	setAnchorPoint(Vec2(0.0, 0.0f));
	return true;
}
void ChooseSprite::setChooseSprite(Soldier* soldier){
	removeFromParent();
	m_ChooseSprite->setContentSize(soldier->m_sprite->getContentSize());
	soldier->m_sprite->addChild(m_ChooseSprite);
}