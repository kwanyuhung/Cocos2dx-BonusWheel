//
//  BonusWheelScene.cpp
//  BonusWheelScene
//
//  Created by kwan yu hung on 4/11/2022.
//

#include "BonusWheelScene.h"

USING_NS_CC;

Scene* BonusWheelScene::createScene()
{
    return BonusWheelScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BonusWheelScene.cpp\n");
}

bool BonusWheelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //middle
    float x = origin.x + visibleSize.width/2;
    float y = origin.y + visibleSize.height/2;
    
    // add "HelloWorld" splash screen"
    auto wheel = createImage("wheel_sections_8.png");
    wheel->setScale(0.6);
    
    wheel->setAnchorPoint(Vec2(0.5f, 0.5f));
    wheel->setPosition(Vec2(x,y));
    this->addChild(wheel,0);
    
    
    auto border = createImage("wheel_border.png");
    border->setAnchorPoint(Vec2(0.5f, 0.5f));
    border->setScale(0.6f);
    border->setPosition(Vec2(x,y));
//    border->setScale(0.6);
    this->addChild(border,1);
    
    auto arrow = createImage("wheel_arrow.png");
    arrow->setAnchorPoint(Vec2(0.5f,1));
    arrow->setPosition(border->getContentSize().width*0.5, border->getContentSize().height);
    border->addChild(arrow);
    
    return true;
}

Sprite* BonusWheelScene::createImage(std::string name){
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create(name);
    if (sprite == nullptr)
    {
        auto text = StringUtils::format("'%s'",name.c_str()).c_str();
        problemLoading(text);
        return nullptr;
    }
    return sprite;
}
