//
//  BonusWheelScene.cpp
//  BonusWheelScene
//
//  Created by kwan yu hung on 4/11/2022.
//

#include "BonusWheelScene.h"
#include "ui/CocosGUI.h"
#include "GameData.h"

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
    
    screenMiddleX = origin.x + visibleSize.width/2;
    screenMiddleY = origin.y + visibleSize.height/2;
    
    wheel = createImage("wheel_sections_8.png");
    wheel->setScale(0.6);
    
    wheel->setAnchorPoint(Vec2(0.5f, 0.5f));
    wheel->setPosition(Vec2(screenMiddleX,screenMiddleY));
    this->addChild(wheel,0);
    
    auto border = createImage("wheel_border.png");
    border->setAnchorPoint(Vec2(0.5f, 0.5f));
    border->setScale(0.6f);
    border->setPosition(Vec2(screenMiddleX,screenMiddleY));
    this->addChild(border,1);
    
    Button* arrow = Button::create("wheel_arrow.png");
    arrow->setAnchorPoint(Vec2(0.5f,1));
    arrow->setPosition(Vec2(border->getContentSize().width*0.5, border->getContentSize().height+5));
    arrow->addClickEventListener(CC_CALLBACK_1(BonusWheelScene::showDebugMenuBallBack,this));
    border->addChild(arrow);
        
    playOnBtn = Button::create("spin_button.png");
    playOnBtn->setScale(0.4f);
    playOnBtn->setAnchorPoint(Vec2(0.5,0));
    playOnBtn->setPosition(Vec2(screenMiddleX,screenMiddleY-wheel->getContentSize().height*0.5+20));
    this->addChild(playOnBtn);
    
    addButtonText(playOnBtn, "Play On");
    
    claimBtn = Button::create("spin_button.png");
    claimBtn->setScale(0.4f);
    claimBtn->setAnchorPoint(Vec2(0.5,0));
    claimBtn->setPosition(Vec2(screenMiddleX,screenMiddleY-wheel->getContentSize().height*0.5+20));
    this->addChild(claimBtn);
    //init not showing , will show when spin finsih
    claimBtn->setVisible(false);
    
    addButtonText(claimBtn, "Claim");
    
        
    float eachContentDis = 360/BonusWheelData.size();
    
    //create wheel contant
    for(int i=0;i<BonusWheelData.size();i++){
       
        float angle = (eachContentDis*(i+0.5f))*M_PI/180;
        float radies = 80;

        //sin(x),cos(y) sequence order
        //cos(x),sin(y) reverse order
        float wheelX = wheel->getContentSize().width*0.5 + sin(angle) * radies;
        float wheelY = wheel->getContentSize().height*0.5 + cos(angle) * radies;

        auto image = createImage(getRewardIconPath(BonusWheelData[i].type));
        image->setScale(0.9);
        image->setPosition(Vec2(wheelX,wheelY));
        image->setRotation(eachContentDis*(i+0.5f));
        wheel->addChild(image);

        Label* text = Label::createWithTTF(StringUtils::format("x%d",BonusWheelData[i].value), "fonts/Marker Felt.ttf", 20);
        text->enableOutline(Color4B::RED, 1);
        text->setPosition(Vec2(image->getContentSize().width*0.5,image->getContentSize().height*0.5-20));
        image->addChild(text);


        //heart text will have special handle
        if(BonusWheelData[i].type== reward_heart){
            text->setString(StringUtils::format("%d", BonusWheelData[i].value));

            Label* heartText = Label::createWithTTF("min", "fonts/Marker Felt.ttf", 10);
            heartText->enableOutline(Color4B::RED,1);
            heartText->setOpacity(255*0.9f);
            heartText->setPosition(text->getContentSize().width,1);
            text->addChild(heartText);
        }
    }
    return true;
}

Sprite* BonusWheelScene::createImage(string name){
    auto sprite = Sprite::create(name);
    if (sprite == nullptr)
    {
        problemLoading(StringUtils::format("'%s'",name.c_str()).c_str());
        //return error image
        return Sprite::create("error.png");
    }
    return sprite;
}

int BonusWheelScene::randomReward(){
    vector<int> sector;
    
    for(int i=0;i<BonusWheelData.size();i++){
        //each percentage add +1 to random pool
        for(int per = 0;per<BonusWheelData[i].percentage;per++){
            sector.push_back(BonusWheelData[i].ID);
        }
    }
    return sector[rand()%sector.size()-1];
}

Label* BonusWheelScene::addButtonText(Button* btn, string text){
    
    Label* textLable = Label::createWithTTF(text.c_str(), "fonts/Marker Felt.ttf", 20);
    textLable->enableOutline(Color4B::BLACK,1);
    textLable->setPosition(Vec2(btn->getContentSize().width*0.5,btn->getContentSize().height*0.5));
    btn->addChild(textLable);
    
    //can custom label
    return textLable;
}

string BonusWheelScene::getRewardIconPath(BonusRewardType type){
    return BonusWheelImage[type];
}


void BonusWheelScene::showDebugMenuBallBack(Ref* pSender)
{
    auto menu = createImage("menu.png");
    menu->setScale(0.65f);
    menu->setPosition(screenMiddleX,screenMiddleX);
    //screen front
    this->addChild(menu,10);
    
    Button* closeButton = Button::create("spin_button.png");
    closeButton->setScale(0.4f);
    closeButton->setPosition(Vec2(menu->getContentSize().width-10,menu->getContentSize().height));
    closeButton->addClickEventListener([=](Ref*){
        //close menu
        menu->removeFromParent();
    });
    menu->addChild(closeButton);
    
    addButtonText(closeButton, "close");
    
    Button* spinTextButton = Button::create("spin_button.png");
    spinTextButton->setScale(0.5);
    spinTextButton->setAnchorPoint(Vec2(0.5,0));
    spinTextButton->setPosition(Vec2(menu->getContentSize().width*0.5,10));
    menu->addChild(spinTextButton);
    
    addButtonText(spinTextButton, StringUtils::format("Spin X%d",DEBUG_SPIN_TIME));

}
