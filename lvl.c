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
    disable_interrupts();
    remove_LCD(scrollMainMenuLCD);
    enable_interrupts();
    //set_interrupts(LCD_IFLAG);

    switch (level)
    {
    case 1:
        Stage1_Load();
        break;
    default:
        MainMenu_Load();
        break;
    }
}


uint8_t offsets[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    5,
    4,
    3,
    2,
    1,
    0
};
uint8_t scrollSpeed = 0;
uint8_t scrollIntensity = 1;

void scrollMainMenuLCD(){
    
    if (LYC_REG == 0x00)
    {
        SCX_REG = offsets[(scrollSpeed + LYC_REG)%12] * scrollIntensity;
        LYC_REG = 0x20;
    }
    else if (LYC_REG == 0x20)
    {
        SCX_REG = 0;
        LYC_REG = 0x00;
        scrollSpeed++;
    }
}

void MainMenu_Load(void)
{
    //draw bg
    set_bkg_data(0,25,sprite_bg_top);
    set_bkg_data(26,32,sprite_bg_bottom);
    set_bkg_data(58,48,sprite_alpha);

    set_bkg_based_tiles(5,2,10,1,map_alpha_overgrowth,0x3A);
    set_bkg_tiles(6,5,8,4,map_bg_top);
    set_bkg_based_tiles(6,9,8,4,map_bg_bottom,0x1A);
    set_bkg_based_tiles(4,14,5,1,map_alpha_press,0x3A);
    set_bkg_based_tiles(11,14,5,1,map_alpha_start,0x3A);

    STAT_REG = 0x45;
    LYC_REG = 0;

    disable_interrupts();
    add_LCD(scrollMainMenuLCD);
    enable_interrupts();

    set_interrupts(VBL_IFLAG | LCD_IFLAG);
}

void Stage1_Load(void)
{
    return;
}

void Update(void)
{
    switch (level)
    {
    default:
        MainMenu_Update();
        break;
    }
}

//clear screen
void clsBG(void)
{
    uint8_t sprite_cls[16] = {
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    };

    set_bkg_data(0x00, 0x01, sprite_bg_cls);
    uint8_t cls_map[] = { 0x00 };

    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 18; y++)
        {
            set_bkg_tiles(x, y, 1, 1, cls_map);
        }
    }
}

void MainMenu_Update(void)
{
    //LYC_REG+=2;

    //printf("%x\r", LY_REG);
    //animate carrousel
    /*if(LYC_REG > 0 && LYC_REG < 100)
    {
        SCX_REG = carrousel;

        carrousel++;
    }
    SCX_REG = 0;*/
}