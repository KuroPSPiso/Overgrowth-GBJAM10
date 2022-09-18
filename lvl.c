#include "lvl.h"

uint8_t lvlTimer = 0;
uint8_t level = 0;
const uint8_t maxLevel = 0;

void SetLevel(int level)
{
    if(level > maxLevel) level = maxLevel;
}

void LevelLoad(void)
{
    //set_bkg_data(0, 47, alpha);

    switch (level)
    {
    case 1:
        Stage1();
        break;
    default:
        MainMenu();
        break;
    }
}

void MainMenu(void)
{
    //draw bg
    SPRITES_8x16;
    set_bkg_data(0,16,bg_image_p1);
}

void Stage1(void)
{
    return;
}