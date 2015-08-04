#ifndef _Soldier_H_
#define _Soldier_H_
#include "string"
#include "cocos2d.h"
#include "GameManager.h"
USING_NS_CC;
using namespace std;
class Soldier :public CCNode
{
public:
	Soldier();
	~Soldier();
	virtual bool init();
	CREATE_FUNC(Soldier);//同cocos提供的宏来创建Soldier
	void StartMoveAction(Vec2 vec);//用于移动
	void endMoveAction();//自己调用，用于判断移动是否终止
	void bindSprite(Sprite *sprite);//给soldier绑定一个精灵
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void update(float dt);
	void attack(int id);
protected:
	bool isMoving = false;
	Sprite* m_sprite;
	string direction="up";//这里是方向属性有8个分别为up,down,right,left,ur,rl,dr,dl
	string kind="qm2";//种类，决定动作图片
	int id=0;//ID是这个对象的唯一的标识
	int HP;//当前HP
	int HP_MAX;//HP最大值
	int ANT;//攻击力 攻击力与防御力我建议写在服务器的数据库里
	int DEF;//防御力
	int skill[5];//技能，最大为四个。0代表普通攻击,-1代表无
	int sp;//技能点
	int sp_MAX;//技能点最大值
	int owner;//所属,0代表中立
	int soldierSpeed=5;//速度，速度值越大人物行走的越慢——。我暂时想到了这个方法
	int compareSpeed=0;//与speed比较相同就前进。	
	int physical=10;//体力值
	int physical_Max=10;//体力值上限
	int sunhao=10;//损耗的速率
	int SunhaoStep=0;//
	CCAnimationCache *animCache;//人物8个方向的动作缓存
	
	Map<string, SpriteFrame*>standMap;//储存了人物站立的8个方向

	MoveTo *moveToAction;
	CCAnimation *animationUp;
	CCAnimation *animationDown;
	CCAnimation *animationRight;
	CCAnimation *animationLeft;
	CCAnimation *animationUR;
	CCAnimation *animationUL;
	CCAnimation *animationDR;
	CCAnimation *animationDL;
};
#endif