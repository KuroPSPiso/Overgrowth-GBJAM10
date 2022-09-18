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
    set_bkg_data(0,11,bg_image_p1);

    uint8_t arr[] = {
        0x00, 0x00, 0x03, 0x05,
        0x00, 0x00, 0x04, 0x06,
        0x00, 0x01, 0x07, 0x09,
        0x00, 0x02, 0x08, 0x0A
    };

    set_bkg_tiles(0,0,4,4,arr);
}

void Stage1(void)
{
    return;
}