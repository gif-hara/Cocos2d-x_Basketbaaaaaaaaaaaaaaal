#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
    void onEnter();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	bool onContactBegin(cocos2d::PhysicsContact& contact);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

private:

	cocos2d::PhysicsWorld* world;

	// 地面オブジェクト.
	cocos2d::Sprite* floor;

	// ボールオブジェクト.
	std::vector<cocos2d::Sprite*> ballList;

	// スコアラベル.
	cocos2d::LabelTTF* scoreLabel;
};
#endif // __HELLOWORLD_SCENE_H__
