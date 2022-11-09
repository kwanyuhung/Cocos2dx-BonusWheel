# Cocos2dx-BonusWheel

# __Test video__

Android:
https://www.youtube.com/watch?v=5ShNyRewlGo&ab_channel=Henrykwan

IOS:
https://www.youtube.com/shorts/6q77NlADG4Y

# Debug test

By tapping the "arrow.icon" in screen

![wheel_arrow](https://user-images.githubusercontent.com/13161202/200734602-29b91cfa-f655-4bb1-a798-b32a32b58473.png)

# Debug menu

Clicking the spin 1000, will show a new result included 

Data Percentages (Black)

Total item Count after spin 1000 (Green)

The percentage of spin 1000 result (Yellow)

<img width="421" alt="螢幕截圖 2022-11-08 下午10 53 54" src="https://user-images.githubusercontent.com/13161202/200734551-f99a244d-72b6-416d-a4b0-e6fc22e62a6f.png">



# Extent 

Reward Item data are extendable, by adding a new data in BonusWheelData

Adding data will also auto apply in debug view

```C++
//Bonus wheel data
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
    {9,GameData::reward_hammer,90,20},
    {10,GameData::reward_coin,900,5}
};
```
# Extent Image

![IMG_AD0D0645D162-1](https://user-images.githubusercontent.com/13161202/200732913-1c3d2844-c20c-417b-8b98-8e4621036553.jpeg)
