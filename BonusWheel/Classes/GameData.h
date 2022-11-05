//
//  GameData.h
//  BonusWheel
//
//  Created by kwan yu hung on 5/11/2022.
//

#ifndef GameData_h
#define GameData_h

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;


extern int GameNum;

namespace GameData{

    enum BonusRewardType{
        reward_heart,
        reward_brush,
        reward_hammer,
        reward_gem,
        reward_coin,
    };

    struct BonusWheel{
        int ID;
        BonusRewardType type;
        int value;
        float percentage;
    };
};

const int DEBUG_SPIN_TIME = 1000;
extern const vector<string> BonusWheelImage;
extern const vector<GameData::BonusWheel> BonusWheelData;

#endif /* GameData_h */
