#ifndef  _GAMEMANAGER_H_
#define  _GAMEMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;
//这个类是用来操控全局的，给各个组件发送消息。
class GameManager :public Ref{
public :
	static GameManager* getInstance();
	CREATE_FUNC(GameManager);
	virtual bool init();
	//订阅消息
	void addObsever(const std::string &sMsgName, std::function<void(Ref*)>func);
	//发布消息
	void postNotification(const std::string &sMsgName, Ref* data);
	static GameManager* m_GameManager;
	std::map<std::string, std::vector<std::function<void(Ref*)>>> m_funcMap;//通过map记录了订阅消息的全部对象
};
#endif
/*通过二维int数组模拟地图*/