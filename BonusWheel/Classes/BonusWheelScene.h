//
//  BonusWheel.h
//  BonusWheel
//
//  Created by kwan yu hung on 4/11/2022.
//

#ifndef BonusWheelScene_h
#define BonusWheelScene_h

#include "cocos2d.h"

class BonusWheelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    cocos2d::Sprite* createImage(std::string name);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BonusWheelScene);
};

#endif /* BonusWheel_h */
