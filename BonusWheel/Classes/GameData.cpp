//
//  GameData.cpp
//  BonusWheel
//
//  Created by kwan yu hung on 5/11/2022.
//

#include "GameData.h"

USING_NS_CC;


const vector<string> BonusWheelImage = {
    {"heart.png"},
    {"brush.png"},
    {"hammer.png"},
    {"gem.png"},
    {"coin.png"}
};

const vector<GameData::BonusWheel> BonusWheelData = {
    //.ID, .type, .value, .percentage
    {1,GameData::reward_heart,30,20},
    {2,GameData::reward_brush,3,10},
    {3,GameData::reward_gem,35,10},
    {4,GameData::reward_hammer,3,10},
    {5,GameData::reward_coin,750,5},
    {6,GameData::reward_brush,1,20},
    {7,GameData::reward_gem,75,5},
    {8,GameData::reward_hammer,1,20},
    
    //extent test
//    {9,GameData::reward_hammer,1,20}
};
