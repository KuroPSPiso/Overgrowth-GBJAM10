#include "lvl.h"

void SetLevel(int level)
{
    if(level > maxLevel) level = maxLevel;
}

void LevelLoad(void)
{
    //set_bkg_data(0, 47, alpha);

    return;

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
    set_bkg_data(0,8,bg_image);
}
