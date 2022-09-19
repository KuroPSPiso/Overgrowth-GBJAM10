#include "lvl.h"

uint8_t lvlTimer = 1;
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
    
    set_bkg_data(26,32,bg_sprite_bottom);
    //
    set_bkg_based_tiles(8,8,8,4,bg_map_bottom,0x1A);
    /*uint8_t bg_map_bottom_offset[32];
    vmemcpy(bg_map_bottom, bg_map_bottom_offset, 32);
    for(uint8_t x = 0; x < 32; x++){
        bg_map_bottom_offset[x] += 0x1A;
    }
    set_bkg_tiles(8,8,8,4,bg_map_bottom_offset);
    */

}

void Stage1(void)
{
    return;
}