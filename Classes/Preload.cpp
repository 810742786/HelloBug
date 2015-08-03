/*

#include "Preload.h"
Preload:: Preload(){
	Vector<std::string>strVector;
	strVector.pushBack("qm1");
	for (std::string kind : strVector){
		SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("./Soldier/" + kind + ".plist", "./Soldier/" + kind + ".png");
		sprMap.insert(kind, frameCache);		
	}
}
SpriteFrameCache* Preload:: getSpriteFrameCache(std::string key){
	return sprMap.at(key);
}
*/