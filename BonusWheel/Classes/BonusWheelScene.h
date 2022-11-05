//
//  BonusWheel.h
//  BonusWheel
//
//  Created by kwan yu hung on 4/11/2022.
//

#ifndef BonusWheelScene_h
#define BonusWheelScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameData.h"
using namespace cocos2d;
using namespace std;
using namespace ui;
using namespace GameData;

class BonusWheelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
        
    void showDebugMenuBallBack(Ref* pSender);
    
    int randomReward();
    
    void spin();
    
    int screenMiddleX;
    int screenMiddleY;
    
    Sprite* wheel;
    Button* playOnBtn;
    Button* claimBtn;
    
    
    string getRewardIconPath(BonusRewardType type);
    
    Sprite* createImage(string name);
    Label* addButtonText(Button* btn, string text);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(BonusWheelScene);
};

#endif /* BonusWheel_h */
