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

uint16_t carrousel = 0;
BOOL carrouselNormal = TRUE;

void scrollMainMenuLCD(){
    if(carrousel >= 80) carrouselNormal = FALSE;
    if(carrousel <= 0) carrouselNormal = TRUE;
    /*if(carrousel >= 10) carrouselNormal = FALSE;
    if(carrousel <= 0) carrouselNormal = TRUE;
    for(LYC_REG = 0; LYC_REG < 100; LYC_REG++)
    {
        if(LY_REG == LYC_REG)
        {
            if(carrouselNormal) carrousel++;
            else carrousel--;
            SCX_REG -= 2 + (carrousel - 5);
        }
    }*/

    if(carrouselNormal)
    {
        carrousel++;
    } 
    else
    {
        carrousel--;
    }
    uint8_t parallaxOffset = 0;

    for(LYC_REG = 0; LYC_REG < 60; LYC_REG++)
    {
        if(LYC_REG < 60)
        {
            SCX_REG = 10 - (carrousel / 4);
        }
        else
        {
            SCX_REG= 0;
        }
    }
    SCX_REG= 0;

    LYC_REG = 0;

    /*
    if(LY_REG == LYC_REG)
        {
            SCX_REG = carrousel;
        }
    */


    /*
    SCX_REG = 0;
    if(LY_REG == LYC_REG)
    {
        for(LYC_REG = 0; LYC_REG < 40; LYC_REG++)
        {
            SCX_REG-= (1 + (carrousel-10));
            carrousel++;
        }
    }
    */


    /*
    SCX_REG = 0;
    if(LY_REG == LYC_REG)
    {
        if(LYC_REG < 40)
        {
            carrousel++;
            if(carrousel > 5) carrousel = 0;
            for(; LYC_REG < 5; LYC_REG++)
            {
                SCX_REG+= (carrousel);
            }
            for(; LYC_REG < 10; LYC_REG++)
            {
                SCX_REG+= (carrousel);
            }
            for(; LYC_REG < 15; LYC_REG++)
            {
                SCX_REG+= (carrousel);
            }
            for(; LYC_REG < 20; LYC_REG++)
            {
                SCX_REG+= (carrousel);
            }
            for(; LYC_REG < 40; LYC_REG++)
            {
                SCX_REG+= (carrousel);
            }
        } else {
            SCX_REG = 0;
            LYC_REG = 0;
        }
    }*/
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
    LYC_REG = 0x00;

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


void MainMenu_Update(void)
{
    //printf("%x\r", LY_REG);
    //animate carrousel
    /*if(LYC_REG > 0 && LYC_REG < 100)
    {
        SCX_REG = carrousel;

        carrousel++;
    }
    SCX_REG = 0;*/
}