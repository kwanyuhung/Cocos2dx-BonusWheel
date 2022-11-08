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

    //generate random seed
    srand((unsigned)time(NULL));
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    screenMiddleX = origin.x + visibleSize.width/2;
    screenMiddleY = origin.y + visibleSize.height/2;
    
    wheelNode = Node::create();
    wheelNode->setPosition(Vec2(screenMiddleX,screenMiddleY));
    this->addChild(wheelNode);
    
    wheelBoard = createImage("wheel_sections_8.png");
    wheelBoard->setScale(0.6);
    
    wheelBoard->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    wheelBoard->setPosition(Vec2(screenMiddleX,screenMiddleY));
    wheelNode->addChild(wheelBoard,0);
    
    auto border = createImage("wheel_border.png");
    border->setAnchorPoint(Point::ANCHOR_MIDDLE);
    border->setScale(0.6f);
//    border->setPosition(Vec2(screenMiddleX,screenMiddleY));
    wheelNode->addChild(border,1);
    
    Button* arrow = Button::create("wheel_arrow.png");
    arrow->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    arrow->setPosition(Vec2(border->getContentSize().width*0.5, border->getContentSize().height+5));
    arrow->addClickEventListener(CC_CALLBACK_1(BonusWheelScene::showDebugMenuBallBack,this));
    border->addChild(arrow);
        
    playOnBtn = Button::create("spin_button.png");
    playOnBtn->setScale(0.4f);
    playOnBtn->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    playOnBtn->setPosition(Vec2(0,-wheelBoard->getContentSize().height*0.5+20));
    playOnBtn->addClickEventListener(CC_CALLBACK_0(BonusWheelScene::spin, this));
    wheelNode->addChild(playOnBtn);
    
    addButtonText(playOnBtn, "Play On");
    
    claimBtn = Button::create("spin_button.png");
    claimBtn->setScale(0.4f);
    claimBtn->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    claimBtn->setPosition(Vec2(screenMiddleX,screenMiddleY-wheelBoard->getContentSize().height*0.5+20));
    claimBtn->addClickEventListener(CC_CALLBACK_0(BonusWheelScene::refreshScreen, this));
    this->addChild(claimBtn);
    //init not showing , will show when spin finsih
    claimBtn->setVisible(false);
    
    addButtonText(claimBtn, "Claim");
    
        
    float eachContentDis = 360/BonusWheelData.size();
    
    //create wheel contant
    for(int i=0;i<BonusWheelData.size();i++){
       
        float angle = (eachContentDis*(i+0.5f))*M_PI/180;
        
        CCLOG("angle = %f",angle);
        
        float radius = BOARD_ICON_RADIUS;

        //sin(x),cos(y) sequence order
        //cos(x),sin(y) reverse order
        float wheelX = wheelBoard->getContentSize().width*0.5 + sin(angle) * radius;
        float wheelY = wheelBoard->getContentSize().height*0.5 + cos(angle) * radius;

        auto image = createIconImage(BonusWheelData[i]);
        image->setPosition(Point(wheelX,wheelY));
        image->setRotation(eachContentDis*(i+0.5f));
        wheelBoard->addChild(image);
    }
    return true;
}

Node* BonusWheelScene::createRect(Size size){
    DrawNode* drawNode = DrawNode::create();
    drawNode->setAnchorPoint(Point::ANCHOR_MIDDLE);
    
    Vec2 point1[4];
    point1[0] = Vec2(0, size.height);
    point1[1] = Vec2(0, 0);
    point1[2] = Vec2(size.width, 0);
    point1[3] = Vec2(size.width, size.height);
    
    drawNode->drawPolygon(point1, 4, Color4F::GRAY, 0.5, Color4F::WHITE);
    drawNode->setContentSize(Size(size.width, size.height));
    
    return drawNode;
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

Sprite* BonusWheelScene::createIconImage(BonusWheel data){
    auto image = createImage(getRewardIconPath(data.type));
    image->setScale(0.9);
    
    Label* text = Label::createWithTTF(StringUtils::format("x%d",data.value), "fonts/arial.ttf", 20);
    text->enableOutline(Color4B::RED, 1);
    text->setPosition(Vec2(image->getContentSize().width*0.5,image->getContentSize().height*0.5-20));
    image->addChild(text);

    //heart text will have special handle
    if(data.type== reward_heart){
        text->setString(StringUtils::format("%d", data.value));

        Label* heartText = Label::createWithTTF("min", "fonts/arial.ttf", 10);
        heartText->enableOutline(Color4B::RED,1);
        heartText->setOpacity(255*0.9f);
        heartText->setPosition(text->getContentSize().width,1);
        text->addChild(heartText);
    }
    
    return image;
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
    
    Label* textLable = Label::createWithTTF(text.c_str(), "fonts/arial.ttf", 20);
    textLable->enableOutline(Color4B::BLACK,1);
    textLable->setPosition(Vec2(btn->getContentSize().width*0.5,btn->getContentSize().height*0.5));
    btn->addChild(textLable);
    
    //can custom label
    return textLable;
}

void BonusWheelScene::spin(){
    
    int rewardID = randomReward();
    
    float singleAngle = 360/BonusWheelData.size();
        
    int spinCount = 3;
    float spinRotateTime = 2.5;
        
    float spinToRewardAngle = singleAngle*((rewardID-1)+0.5f);
    float spinRoundAngle = 360*spinCount;
    
    float timeCal = spinRotateTime;
        
    float finalSpin = spinRoundAngle-spinToRewardAngle;
        
    playOnBtn->setVisible(false);
    
    wheelBoard->runAction(Sequence::create(RotateTo::create(0, 0),
                                           DelayTime::create(0.5f),
                                           RotateBy::create(0.2f, -10),
                                           EaseSineInOut::create(RotateBy::create(timeCal, finalSpin+15)),
                                           EaseSineOut::create(RotateBy::create(0.6f,-5)),
                                           DelayTime::create(0.3f),
                                           CallFunc::create([&,rewardID]{
        claimReward(rewardID);
    }),
                                           NULL));
}

void BonusWheelScene::claimReward(int reward){
    wheelNode->setVisible(false);
    claimBtn->setVisible(true);

    auto image = createIconImage(BonusWheelData[reward-1]);
    image->setScale(wheelBoard->getScale()*image->getScale());
    image->setPosition(screenMiddleX,screenMiddleY+ BOARD_ICON_RADIUS*wheelBoard->getScale());
    image->setName("claimImage");
    this->addChild(image,100);
    
    image->runAction(EaseSineOut::create(Spawn::create(ScaleTo::create(0.6f, image->getScale()*1.3),
                                                      MoveBy::create(0.8f, Point(0,-20)),
                                                      NULL)));
}


void BonusWheelScene::refreshScreen(){
    //after claimBtn click, screen refresh
    
    wheelNode->setVisible(true);
    playOnBtn->setVisible(true);
    
    //remove reward image
    this->getChildByName("claimImage")->removeFromParent();
    claimBtn->setVisible(false);
    
    wheelBoard->setRotation(0);
    
    
}

string BonusWheelScene::getRewardIconPath(BonusRewardType type){
    return BonusWheelImage[type];
}


void BonusWheelScene::showDebugMenuBallBack(Ref* pSender)
{
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    debugMenu = createRect(Size(screenSize.width*0.95,screenSize.height*0.6));
    debugMenu->setAnchorPoint(Point::ANCHOR_MIDDLE);
    debugMenu->setPosition(screenMiddleX,screenMiddleY);
    //screen front
    this->addChild(debugMenu,10);
    
    Button* closeButton = Button::create("spin_button.png");
    closeButton->setScale(0.4f);
    closeButton->setPosition(Vec2(debugMenu->getContentSize().width-10,debugMenu->getContentSize().height));
    closeButton->addClickEventListener([=](Ref*){
        //close menu
        debugMenu->removeFromParent();
    });
    debugMenu->addChild(closeButton);
    
    addButtonText(closeButton, "close");
    
    Button* spinTextButton = Button::create("spin_button.png");
    spinTextButton->setScale(0.5);
    spinTextButton->setAnchorPoint(Vec2(0.5,0));
    spinTextButton->setPosition(Vec2(debugMenu->getContentSize().width*0.5,10));
    spinTextButton->addClickEventListener(CC_CALLBACK_0(BonusWheelScene::spinSimulate, this, DEBUG_SPIN_TIME));
    debugMenu->addChild(spinTextButton);
    
    addButtonText(spinTextButton, StringUtils::format("Spin X%d",DEBUG_SPIN_TIME));
    
    debugView = ListView::create();
    debugView->setDirection(ScrollView::Direction::VERTICAL);
    debugView->setTopPadding(10);
    debugView->setItemsMargin(10);
    debugView->setScrollBarEnabled(false);
    debugView->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    debugView->setPosition(Point(debugMenu->getContentSize().width*0.5f,spinTextButton->getContentSize().height*0.5f+10));
    debugView->setContentSize(Size(debugMenu->getContentSize().width*0.95f,debugMenu->getContentSize().height*0.75f));
    debugMenu->addChild(debugView);
}

void BonusWheelScene::spinSimulate(int count){
    
    auto menu = createRect(Size(debugView->getContentSize().width*0.9,50));
    menu->setAnchorPoint(Point::ANCHOR_MIDDLE);
    menu->setPosition(debugView->getContentSize().width*0.5, menu->getContentSize().height*0.5);
    
    
    Layout* debugLayout = Layout::create();
    debugLayout->setAnchorPoint(Point::ANCHOR_MIDDLE);
    
    debugLayout->addChild(menu);
    debugLayout->setContentSize(menu->getContentSize());
    
    Label* debugCountText = Label::createWithTTF(StringUtils::format("Test(%zd)",debugView->getItems().size()), "fonts/arial.ttf", 7);
    debugCountText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    debugCountText->setColor(Color3B::BLACK);
    debugCountText->setPosition(Vec2(2,menu->getContentSize().height));
    menu->addChild(debugCountText);
    
    Label* basePerText = Label::createWithTTF("■Data%", "fonts/arial.ttf", 5);
    basePerText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    basePerText->setColor(Color3B::BLACK);
    basePerText->setPosition(Vec2(debugCountText->getPosition().x+debugCountText->getContentSize().width+2,menu->getContentSize().height-2));
    menu->addChild(basePerText);
    
    Label* resultCountText = Label::createWithTTF("■TotalCount", "fonts/arial.ttf", 5);
    resultCountText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    resultCountText->setColor(Color3B::GREEN);
    resultCountText->setPosition(Vec2(basePerText->getPosition().x+basePerText->getContentSize().width+2,basePerText->getPosition().y));
    menu->addChild(resultCountText);
    
    Label* resultPerText = Label::createWithTTF("■Result%", "fonts/arial.ttf", 5);
    resultPerText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    resultPerText->setColor(Color3B::YELLOW);
    resultPerText->setPosition(Vec2(resultCountText->getPosition().x+resultCountText->getContentSize().width+2,basePerText->getPosition().y));
    menu->addChild(resultPerText);

    
    int spinData[BonusWheelData.size()];
    //reset to 0
    for(int i=0;i<BonusWheelData.size();i++){
        spinData[i] = 0;
    }
    
    //do 1000times
    for(int i=0;i<=count;i++){
        int reward = randomReward();
        spinData[reward-1] += 1;
    }
    
    auto iconView = ListView::create();
    iconView->setDirection(ScrollView::Direction::HORIZONTAL);
    iconView->setLeftPadding(2);
    iconView->setItemsMargin(2);
    iconView->setScrollBarEnabled(false);
    iconView->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    iconView->setPosition(Point(menu->getContentSize().width*0.5f,menu->getContentSize().height-debugCountText->getContentSize().height-2));
    iconView->setContentSize(Size(menu->getContentSize().width,menu->getContentSize().height-debugCountText->getContentSize().height));
    menu->addChild(iconView);
    
    for(int i=0;i<BonusWheelData.size();i++){

        Layout* iconLayout = Layout::create();
        iconLayout->setAnchorPoint(Point::ANCHOR_MIDDLE);
        
        BonusRewardType reward = BonusWheelData[i].type;

        auto image = createIconImage(BonusWheelData[i]);
        image->setAnchorPoint(Point::ANCHOR_MIDDLE);
        image->setScale(0.4f);
        image->setPosition(image->getContentSize().width*0.25,20);
        iconLayout->addChild(image);
    
        Label* basePerText = Label::createWithTTF(StringUtils::format("(%d%%)",(int)BonusWheelData[i].percentage), "fonts/arial.ttf", 10);
        basePerText->setColor(Color3B::BLACK);
        basePerText->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        basePerText->setPosition(Vec2(0, -30));
        if(reward == reward_brush){
            basePerText->setPosition(Vec2(0, -20));
        }
        image->addChild(basePerText);
        
        Label* totalConutText = Label::createWithTTF(StringUtils::format("(%d)",spinData[i]), "fonts/arial.ttf", 10);
        totalConutText->setColor(Color3B::GREEN);
        totalConutText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        totalConutText->setPosition(Vec2(0, -0.5));
        basePerText->addChild(totalConutText);
        
        float resultPer = (float)spinData[i]/(float)DEBUG_SPIN_TIME*100.0f;
        
        Label* resultPerText = Label::createWithTTF(StringUtils::format("(%.1f%%)",resultPer), "fonts/arial.ttf", 8);
        resultPerText->setColor(Color3B::YELLOW);
        resultPerText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        resultPerText->setPosition(Vec2(0, -0.5));
        totalConutText->addChild(resultPerText);
        
        iconLayout->setContentSize(image->getContentSize()*image->getScale()*1.1f);
        iconView->pushBackCustomItem(iconLayout);
    }
    
    debugView->pushBackCustomItem(debugLayout);
    
    debugView->scrollToBottom(0.1, false);
}
