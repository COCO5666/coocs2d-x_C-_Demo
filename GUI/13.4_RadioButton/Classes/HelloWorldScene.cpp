#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define NUMBER_BUTTONS 5
#define BUTTON_WIDTH 60

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建RadioButtonGroup对象
	RadioButtonGroup* radioButtonGroup = RadioButtonGroup::create();
	this->addChild(radioButtonGroup);

	// 创建RadioButton
	float startPosX = visibleSize.width / 2.0 - ((NUMBER_BUTTONS - 1) / 2.0) * BUTTON_WIDTH;
	for (int i = 0; i < NUMBER_BUTTONS; ++i)
	{
		RadioButton* radioButton = RadioButton::create("icon/btn_radio_off_holo.png", "icon/btn_radio_on_holo.png");
		float posX = startPosX + BUTTON_WIDTH * i;
		radioButton->setPosition(Vec2(posX, visibleSize.height / 2 + 10));
		radioButtonGroup->addRadioButton(radioButton);
		radioButtonGroup->addEventListener(CC_CALLBACK_3(HelloWorld::onChangedRadioButtonGroup, this));

		this->addChild(radioButton);
	}
	
    return true;
}

//RadioButton单击事件回调函数
void HelloWorld::onChangedRadioButtonGroup(RadioButton* radioButton, int index, RadioButtonGroup::EventType type)
{
	CCLOG("RadioButton Index : %d", index);
}
