#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

	// 重力の設定.
	layer->world = scene->getPhysicsWorld();
	Vect gravity;
	gravity.setPoint(0.0f, -1500.0f);
	layer->world->setGravity(gravity);

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

	//world = Director::getInstance()->getRunningScene()->getPhysicsWorld();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 地面の描画.
	floor = Sprite::create("Texture/Background.png");
	auto backgroundSize = floor->getContentSize();
	floor->setPosition(Vec2(visibleSize.width / 2 + origin.x, backgroundSize.height / 2.0f));
	this->addChild(floor, 0);

	// 地面の物理設定.
	auto floorPhysicsBody = PhysicsBody::createBox(backgroundSize);
	floorPhysicsBody->setDynamic(false);
	floorPhysicsBody->setCollisionBitmask(0xFFFFFFFF);
	auto dummyPhysicsBody = PhysicsBody::createBox(Size(0, 0));
	dummyPhysicsBody->setPositionOffset(floor->getPosition());
	dummyPhysicsBody->setDynamic(false);
	//auto joint = PhysicsJointDistance::construct(floorPhysicsBody, dummyPhysicsBody, floor->getPosition(), Vec2(0, 10));
	auto pin = PhysicsJointPin::construct(floorPhysicsBody, dummyPhysicsBody, Vec2(0, 0));
	pin->setCollisionEnable(false);
	floor->setPhysicsBody(floorPhysicsBody);

	for (int i = 0; i < 2; i++)
	{
		// ボールの描画.
		auto ball = Sprite::create("Texture/Ball.png");
		ballList.push_back(ball);
		ball->setPosition(Vec2(visibleSize.width / 2 + origin.x + i * 32, visibleSize.height / 2.0f + i * 256));

		// ボールの物理設定.
		auto ballMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
		ballMaterial.restitution = 1.5f;
		ballMaterial.friction = 0.8f;
		auto ballPhysicsBody = PhysicsBody::createCircle(ball->getContentSize().width / 2.0f, ballMaterial);
		ballPhysicsBody->setMass(10.0f);
		ballPhysicsBody->setCollisionBitmask(i*2+1);
		CCLog("%x", ballPhysicsBody->getCollisionBitmask());
		ball->setPhysicsBody(ballPhysicsBody);

		this->addChild(ball, 1);
	}
	

	//closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
	//	origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	// スコアラベルの初期化.
    scoreLabel = LabelTTF::create("Hello World", "Arial", 24);
	scoreLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - scoreLabel->getContentSize().height));
	this->addChild(scoreLabel, 1);

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	//auto listner = EventListenerPhysicsContact::create();
	//listner->onContactBegin = CC_CALLBACK_2(HelloWorld::onContactBegan, this);

    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)
{
	// ボールをタッチしたか？.
	for (std::vector<Sprite*>::iterator i = ballList.begin(); i != ballList.end(); ++i)
	{
		auto ballPos = (*i)->getPosition();
		auto ballRadius = (*i)->getContentSize().width / 2.0f;
		auto location = touch->getLocation();

		if (ballPos.getDistance(location) <= ballRadius)
		{
			(*i)->getPhysicsBody()->applyImpulse(Vec2(0.0f, -3000.0f));
		}
	}



	floor->getPhysicsBody()->applyTorque(100);

	return true;
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	CCLog("Physics Began!");
	return true;
}