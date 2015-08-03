#include "GameManager.h"
GameManager* GameManager::m_GameManager = NULL;
GameManager* GameManager::getInstance(){
	if (m_GameManager == NULL){
		m_GameManager = GameManager::create();
		m_GameManager->retain();
	}
	return m_GameManager;	
}
bool GameManager::init(){
	return true;
}
void GameManager::addObsever(const std::string &sMsgName, std::function<void(Ref*)>func){
	if (m_funcMap.find(sMsgName) != m_funcMap.end){
		std::vector<std::function<void(Ref*)>> &funcList = m_funcMap.at(sMsgName);
		funcList.push_back(func);
	}

else{
	std::vector<std::function<void(Ref*)>> funcList;
	funcList.push_back(func);
	m_funcMap[sMsgName] = funcList;
}
}
void GameManager::postNotification(const std::string &sMsgName, Ref* data){
	if (m_funcMap.find(sMsgName) != m_funcMap.end()){
		std::vector<std::function<void(Ref*)>> funcList = m_funcMap.at(sMsgName);
		for (auto func : funcList){
			func(data);
		}
	}
}
void GameManager:: addMoveObsever(const std::string &sMsgName, std::function<void(Vec2)>func){
	if (move_map.find(sMsgName) != move_map.end()){
		move_map[sMsgName] = func;
	}	
}
void GameManager::postMoveNotification(const std::string &sMsgName,Vec2 data){
	if (move_map.find(sMsgName) != move_map.end()){
		move_map.at(sMsgName)(data);
	}
}