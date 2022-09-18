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
    set_bkg_data(0,25,bg_sprite_top);
    set_bkg_tiles(8,4,8,4,bg_map_top);
}

void Stage1(void)
{
    return;
}