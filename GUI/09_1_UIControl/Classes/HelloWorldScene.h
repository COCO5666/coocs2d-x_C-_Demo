#pragma execution_character_set("utf-8")

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"  
//libcocos2d--> ui-->system-->CocosGUI.h,里面包括常用UI控件的头文件
using namespace ui; //小写的ui

class HelloWorld :public Layer,public EditBoxDelegate

{
public:
       static cocos2d::Scene* createScene();
	   virtual bool init();
       CREATE_FUNC(HelloWorld);
	  
	   //1.测试九宫格，对比显示九宫格和普通精灵
	   void testScale9Sprite(); 
	   
	   //2. 测试文本编辑框，本身带有事件，即下面的4个事件
	   void testEditBox();
       virtual void editBoxEditingDidBegin(EditBox* editBox);    
	   virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
	   virtual void editBoxEditingDidEnd(EditBox* editBox);  
	   virtual void editBoxReturn(EditBox* editBox);
	  
	   //3.测试文本
	   void testText();
	   void textCallCack( Ref *sender,Widget::TouchEventType type);
	 	  
	   //4.测试按钮button
	   void testButton();
	   void btnClicked(Ref *sender,Widget::TouchEventType type);

	   //5.测试滑动条Slider 
	   void testSlider();
	   void changeProgress(Ref *sender,Slider::EventType); 
	   Text *_displayValueLabel;

	   //6.测试进度条loadingbar
	    void testLoadingBar();
		void update(float f);
	   //7.测试复选框CheckBox
	   void testCheckBox();
	   void checkBoxSelected(Ref *sender, CheckBox::EventType type );
	    
	   //8.测试列表框ListView
	   void testListView();

	   //9.测试翻页PageView ，一次翻一页
		void testPageView();
		void pageViewCallBack(Ref *sender,PageView::EventType type);
	   //10.测试图片滑动ScrollView ,为了让每张图片能够点击选中进入下一关，故设置button
		void testScrollView();
		void scrollViewSdidScroll( Ref *sender,ScrollView::EventType type);
		void selectScene( Ref *sender,Widget::TouchEventType type);    
};

#endif // __HELLOWORLD_SCENE_H__
