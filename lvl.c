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

uint8_t scroll1 = 10, scroll2 = 15, scroll3 = 30;

void scrollMainMenuLCD(){
    
    if (LYC_REG == 0x00)
    {
        //move_bkg(scroll1, 0);
        SCX_REG = scroll1;
        LYC_REG = 0x20;
    }
    else if (LYC_REG == 0x20)
    {
        //move_bkg(scroll2, 0);
        SCX_REG = scroll2;
        LYC_REG = 0x40;
    }
    else if (LYC_REG == 0x40)
    {
        //move_bkg(scroll3, 0);
        SCX_REG = scroll3;
        LYC_REG = 0x00;
    }


    /*carrousel++;
    if (carrousel >= 10)
    {
        carrousel = 0;
        printf("%x %x\n", STAT_REG, STAT_REG & 3);
    }*/
    /*if ((STAT_REG & 3) == 0)
    {
        SCX_REG++;
    }*/
    /*
    carrousel++;
    if (carrousel >= 10)
    {
        carrousel = 0;
        printf("%x %x %x\n", LY_REG, LYC_REG, STAT_REG);
    }*/

    /*
    SCX_REG = 0;
    for (; LYC_REG < 60; LYC_REG++)
    {
        SCX_REG = 20;
    }*/
    /*
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
    */
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
    scroll1++;
    scroll2+=2;
    scroll3+=3;
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