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
	auto world = scene->getPhysicsWorld();
	Vect gravity;
	gravity.setPoint(0.0f, -1500.0f);
	world->setGravity(gravity);


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

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 地面の描画.
	auto backgroundSprite = Sprite::create("Texture/Background.png");
	auto backgroundSize = backgroundSprite->getContentSize();
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, backgroundSize.height / 2.0f));
	this->addChild(backgroundSprite, 0);

	// 地面の物理設定.
	auto backgroundPhysicsBody = PhysicsBody::createBox(backgroundSize);
	backgroundPhysicsBody->setDynamic(false);
	backgroundSprite->setPhysicsBody(backgroundPhysicsBody);

	// ボールの描画.
	ball = Sprite::create("Texture/Ball.png");
	ball->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2.0f));

	// ボールの物理設定.
	auto ballMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
	ballMaterial.restitution = 1.5f;
	auto ballPhysicsBody = PhysicsBody::createCircle(ball->getContentSize().width / 2.0f,ballMaterial);
	ballPhysicsBody->setMass(10.0f);
	ball->setPhysicsBody(ballPhysicsBody);

	this->addChild(ball, 1);
	
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
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
    
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
	auto ballPos = ball->getPosition();
	auto ballRadius = ball->getContentSize().width / 2.0f;

	auto location = touch->getLocation();

	if (ballPos.getDistance(location) <= ballRadius)
	{
		ball->getPhysicsBody()->applyImpulse(Vec2(0.0f, -3000.0f));
	}

	return true;
}
