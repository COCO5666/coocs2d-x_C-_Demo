#pragma execution_character_set("utf-8")

#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
	if (!Layer::init()) { return false; }

	auto bgSprite=Sprite::create("background4.jpg");
	bgSprite->setPosition(240, 160);
	//addChild(bgSprite);

	//testScale9Sprite();
	//testEditBox();  
	//testText();
	//testButton();
	//testCheckBox();
	//testSlider();
	//testLoadingBar();
	//testListView();
	//testPageView(); 
	testScrollView();
	return true;
}

//1.测试九宫格，对比显示九宫格和普通精灵
void HelloWorld::testScale9Sprite()
{
    auto _sprite=Scale9Sprite::create("nine.png");
    _sprite->setPosition(Vec2(320,150));
    _sprite->setContentSize(Size(120,70));//80*40
	_sprite->setScale(1.0);//不设置为1将失真
    addChild(_sprite);
    auto _sprite2=Sprite::create("nine.png");
    _sprite2->setPosition(320, 250);
	_sprite2->setScale(1.5);//80*40,也放大到原来的1.5倍
    addChild(_sprite2);
}
//2.测试文本编辑框EditBox，本身带有事件，即下面的4个事件
void HelloWorld:: testEditBox()
{
	auto userNameBox=EditBox::create(Size(200, 25), Scale9Sprite::create("green_edit.png"));
    userNameBox->setPosition(Vec2(240,280));
    userNameBox->setFontName("fonts/arial.ttf");
    userNameBox->setFontSize(16);
    userNameBox->setFontColor(Color3B(0,0,255));
    userNameBox->setPlaceholderFontColor(Color3B(255,0,0));
    userNameBox->setPlaceHolder("Please Enter Name");////当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
    userNameBox->setPlaceholderFontName("fonts/arial.ttf");
    userNameBox->setPlaceholderFontSize(16);
	userNameBox->setMaxLength(20);   //设置文本框中文本的最大长度
	userNameBox->setInputMode(EditBox::InputMode::ANY);//输入键盘模式,任何符号
    userNameBox->setReturnType(EditBox::KeyboardReturnType::DONE);//设置软键盘中回车按钮的样子
    userNameBox->setDelegate(this);//开启委托
	userNameBox->setTag(0);
    addChild(userNameBox);

    auto userPasswordBox=EditBox::create(Size(200, 25), Scale9Sprite::create("orange_edit.png"));
    userPasswordBox->setPosition(Vec2(240,220));
    userPasswordBox->setFontName("fonts/arial.ttf");
    userPasswordBox->setFontSize(16);
    userPasswordBox->setFontColor(Color3B(0,0,255));
    userPasswordBox->setPlaceHolder("Please Enter password");
    userPasswordBox->setPlaceholderFontName("fonts/arial.ttf");
    userPasswordBox->setPlaceholderFontSize(16);
    userPasswordBox->setPlaceholderFontColor(Color3B(255,0,0));
    userPasswordBox->setMaxLength(1);
	userPasswordBox->setInputMode(EditBox::InputMode::DECIMAL);//输入模式,十进制数字
    userPasswordBox->setReturnType(EditBox::KeyboardReturnType::GO);//默认使用键盘DONE字样类型
    userPasswordBox->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
    userPasswordBox->setDelegate(this);
	//文本框代理，需要实现EditBoxDelegate代理中的方法，就可以对EditBox进行控制
    addChild(userPasswordBox);
}
//编辑框的键盘编辑事件
void HelloWorld::editBoxEditingDidBegin(EditBox* editBox)
{
	CCLOG("editBoxEditingDidBegin");
	CCLOG("%d", editBox->getTag());
}
 void HelloWorld::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	 CCLOG("editBoxTextChanged");
}
 void HelloWorld:: editBoxEditingDidEnd(EditBox* editBox)
{
	 CCLOG("editBoxEditingDidEnd");
}

void HelloWorld:: editBoxReturn(EditBox* editBox)
{
	CCLOG("editBoxReturn");
	CCLOG(editBox->getText());
}

//3.测试文本text，继承自Widget，本身没有触摸事件TouchEvent，可以增加父类widget的一个callback事件
void HelloWorld::testText()
{
   //text 自动换行ui
    Text *text=Text::create("I study in pingdingshan university!", "Marker Felt.ttf", 25);//设置.ttf字体
	//Text *text=Text::create();
	//text->setString("I study in pingdingshan university!");
	//text->setFontName("Marker Felt");//设置系统字体Marker Felt
	//text->setFontSize(25);
	text->setTextColor(Color4B(255,0,0,255));
    text->ignoreContentAdaptWithSize(false);
    text->setContentSize(Size(280,180));//设置宽度280之后才会识别换行
    text->setTextHorizontalAlignment(TextHAlignment::LEFT);
    text->addTouchEventListener(CC_CALLBACK_2(HelloWorld::textCallCack, this));//触摸监听事件
    text->setPosition(Vec2(240,30));
    text->setTouchEnabled(true);//允许触摸
    addChild(text);
}
//Text增加父类的触摸事件，这里用来改变文本的显示宽度。
void HelloWorld::textCallCack( Ref *sender,Widget::TouchEventType type)
{
    auto _text=(Text *)sender;
    if (type == Widget::TouchEventType ::ENDED)
    {
        _text->setContentSize(Size(380,250)); 
		_text->setText("width and text can be changed!");
    }
    
}
//4.测试按钮button
void HelloWorld::testButton()
{
	auto btn=Button::create("bird.png");
    btn->setScale9Enabled(true);
    btn->setContentSize(Size(50,50));
    btn->setPosition(Vec2(60,120));
    btn->setTitleText("Single Click");
    btn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnClicked, this));//触摸监听事件
    addChild(btn);
}
//移动button的normalImage的图片，换到移动点
void HelloWorld::btnClicked(Ref *sender,Widget::TouchEventType type)
{
    if (type==Widget::TouchEventType::ENDED)
    {
       CCLOG("You have clicked the button!");
     }
    else if(type==Widget::TouchEventType::MOVED)
    {
        auto btn=(Button*)sender;
	    Vec2 pos=btn->getTouchMovePosition();
		/*只能通过此方法获取触摸点的位置，与btn->getWorldPosition()和btn->getPosition()不同，
		后两个不能获取移动的位置。*/
		log("pos.x=%f,pos.y=%f",pos.x,pos.y);
		pos=this->convertToNodeSpace(pos); //通过输出语句验证，此处不需转换, 用此语句pos=this->convertToWorldSpace(pos)效果与前同。
		log("pos.x=%f,pos.y=%f",pos.x,pos.y);
	    btn->setPosition(pos);
    }
}


//5.测试滑动条Slider，用来设置声音大小和屏幕亮度
void HelloWorld::testSlider()
{
    auto _slider=Slider::create();
    _slider->loadBarTexture("sliderTrack.png");//底图资源，纹理
    _slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "sliderThumb.png");//不同状态下的节点资源，滚球纹理
    _slider->loadProgressBarTexture("sliderProgress.png");//内部进度条资源/纹理
    _slider->setPosition(Vec2(240,180));
    _slider->addEventListener(CC_CALLBACK_2(HelloWorld::changeProgress, this));//触摸监听事件
    addChild(_slider);
	_displayValueLabel=Text::create("Move sliderTack!","Marker Felt.ttf",25);
	_displayValueLabel->setPosition(Vec2(240,150));
	this->addChild(_displayValueLabel);
}
//Slider的回调函数
void HelloWorld:: changeProgress(Ref *sender, Slider::EventType type)
{
    auto _slider=(Slider*)sender;
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		//ON_PERCENTAGE_CHANGED 表示slider滑动条的百分比正在发生变化
    {
       CCLOG("%d",_slider->getPercent());//getPercent()获取0-100的整数
		String value=StringUtils::format("Percent=%d",_slider->getPercent());
		_displayValueLabel->setString(value.getCString());
		//注意value的值将cocos2dx的__string转化成C语言的字符串
    }
}

//6.测试进度条loadingbar
void HelloWorld::testLoadingBar()
 {
     auto _loadingBar=LoadingBar::create("sliderProgress.png");
     _loadingBar->setPosition(Vec2(240,30));
     _loadingBar->setDirection(LoadingBar::Direction::LEFT);
     _loadingBar->setTag(2);
     addChild(_loadingBar);
	 this->scheduleUpdate();//更新调度下面的update函数
}
//loadingbar 更新事件，小写的update（）函数为系统默认的更新函数，会每帧都调用更新屏幕
void HelloWorld::update(float f)
{
    static int count=0;//思考为何使用static？
    auto _loadingBar=(LoadingBar*)this->getChildByTag(2);
    _loadingBar->setPercent(count++);
    if (count>=100)
    {
        count=0;
    }
}
//7.测试复选框CheckBox
void HelloWorld::testCheckBox()
{
    auto _checkBox=CheckBox::create("check_box_normal.png", "check_box_active_press.png", "check_box_active.png", "check_box_normal_disable.png", "check_box_active_disable.png");
    _checkBox->setPosition(Vec2(400,300));
    _checkBox->addEventListener(CC_CALLBACK_2(HelloWorld::checkBoxSelected, this));
    addChild(_checkBox);
}
//复选框CheckBox的选择事件
void HelloWorld::checkBoxSelected(Ref *sender,CheckBox::EventType type)
{
    if (type==CheckBox::EventType::SELECTED)
    {
        CCLOG("selected");
    }
    else if (type==CheckBox::EventType::UNSELECTED)
    {
		CCLOG("UnSelected!");
    }
        
}

//8.测试列表框ListView
void HelloWorld::testListView()
{
    auto _listView=ListView::create();
    _listView->setDirection(ScrollView::Direction::VERTICAL);
    _listView->setBounceEnabled(true);//回弹效果
    _listView->setBackGroundImage("green_edit.png");
    _listView->setBackGroundImageScale9Enabled(true);
    _listView->setContentSize(Size(240,130));
    _listView->setPosition(Vec2(120,160));
    addChild(_listView);
    for (int i=0; i<10; i++)
    {
        Layout *widget=Layout::create();
        widget->setContentSize(Size(240,50));
       auto *str=String::createWithFormat("TextArea Widget can line wrap %d",i+1);
        Text *text=Text::create(str->getCString(), "Marker Felt.ttf", 13);
        text->setContentSize(Size(60,10));
        text->setPosition(Vec2(20,25));
        text->setAnchorPoint(Vec2(0,0));
        widget->addChild(text);
        _listView->pushBackCustomItem(widget);
    }    
}

//9.测试翻页PageView和ImageView，一次翻一页显示图片
void HelloWorld::testPageView()
{
    auto _pageView=PageView::create();
    _pageView->setContentSize(Size(120,215)); //因为图片的高度为215
    _pageView->setPosition(Vec2(240,160));
    _pageView->setAnchorPoint(Vec2(0.5, 0.5));
    _pageView->setTag(1);
    _pageView->addEventListener(CC_CALLBACK_2(HelloWorld::pageViewCallBack, this));
    addChild(_pageView);
    for (int i=0; i<9; i++)
    {
        Layout *out=Layout::create();
        out->setContentSize(Size(120,215));//因为图片的高度为215
        auto str=__String::createWithFormat("LEVELSELECTION_%d.png",i+1);
        ImageView *imageView=ImageView::create(str->getCString());
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(120,215));//因为图片的高度为215
        imageView->setPosition(Vec2(60,107.5));//让图片显示在layout容器的中心
        out->addChild(imageView);
        _pageView->addPage(out);
    }
}

void HelloWorld:: pageViewCallBack(Ref *sender,PageView::EventType type)
{
    auto _pageView=(PageView*)sender;
    if (type==PageView::EventType::TURNING)
    {
       CCLOG("这是第%d页！",(int)_pageView->getCurPageIndex()+1);
    }
}
//10.测试图片滑动ScrollView ,为了让每张图片能够点击选中进入下一关，故设置button
void HelloWorld::testScrollView()
{
	auto s=Scale9Sprite::create("green_edit.png");  //设置ScrollView背景，便于查看容器大小
	s->setContentSize(Size(400,215));
	s->setPosition(Vec2(240,160));
	addChild(s);
    auto _scrollView=ScrollView::create();
    _scrollView->setContentSize(Size(400,215));//因为图片的高度为215
    _scrollView->setAnchorPoint(Vec2(.5,.5));
    _scrollView->setPosition(Vec2 (240,160));
	_scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    _scrollView->setBounceEnabled(true);
    _scrollView->setInnerContainerSize(Size(135*9,215)); 
	//因为图片的高度为215,135=图片的宽度120+缝隙15
    _scrollView->addEventListener(CC_CALLBACK_2(HelloWorld::scrollViewSdidScroll, this));
    this->addChild(_scrollView);
    for ( int i=0; i<9; i++)
    {
        __String *str=__String::createWithFormat("LEVELSELECTION_%d.png",i+1);
        auto btn=Button::create(str->getCString(),str->getCString());
        btn->setScale9Enabled(true);
        btn->setContentSize(Size(120,215));
        btn->setPosition(Vec2(135*i+70, 107.5));// 215/2=107.5，75=120/2+15，加70是为了让左右边界处都留有缝隙
        btn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::selectScene, this));
        btn->setTag(i+1);
        _scrollView->addChild(btn);
    }
}
//scrollView滑动选项
void HelloWorld:: scrollViewSdidScroll( Ref *sender,ScrollView::EventType type)
{
    switch (type)
    {
        case ScrollView::EventType::SCROLL_TO_TOP:
        {
           CCLOG("滑倒顶部了！");
            break;
        }
        case ScrollView::EventType::SCROLL_TO_BOTTOM:
        {
           CCLOG("滑倒底部了！");
             break;
        }
        case ScrollView::EventType::SCROLL_TO_LEFT:
        {
           CCLOG("滑倒左边了！");
             break;
        }
        case ScrollView::EventType::SCROLL_TO_RIGHT:
        {
           CCLOG("滑倒右边了！");
             break;
        }
        case ScrollView::EventType::SCROLLING:
        {
           CCLOG("正在滑动中！");
             break;
        }
        case ScrollView::EventType::BOUNCE_BOTTOM:
        {
           CCLOG("回弹到底部了！");
             break;
        }
        case ScrollView::EventType::BOUNCE_LEFT:
        {
           CCLOG("回弹到左边了！");
             break;
        }
        case ScrollView::EventType::BOUNCE_TOP:
        {
           CCLOG("回弹到顶部了！");
             break;
        }
        case ScrollView::EventType::BOUNCE_RIGHT:
        {
           CCLOG("回弹到右边了！");
             break;
        }
    
    }
}
void HelloWorld:: selectScene( Ref *sender,Widget::TouchEventType type)
{
    auto btn=(Button*)sender;
    if (type==Widget::TouchEventType::ENDED)
    {
       CCLOG("您选择了第%d关！",btn->getTag());
    }
}