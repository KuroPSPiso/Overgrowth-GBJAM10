#include "lvl.h"

uint8_t lvlTimer = 1;
uint8_t level = 0;

void SetLevel(int changeTo)
{
    level = changeTo;
}

void LevelLoad(void)
{
    disable_interrupts();
    remove_LCD(scrollMainMenuLCD);
    enable_interrupts();
    //set_interrupts(LCD_IFLAG);

    switch (level)
    {
    case LVL_STAGE1:
        Stage1_Load();
        break;
    case LVL_GAMEOVER:
        GameOver_Load();
        break;
    default: //load mainmenu
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
    clsBG();

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

    inputCallIndex = CONTROLS_MAINMENU_INDEX;
}

void GameOver_Load(void)
{
    clsBG();

    set_bkg_data(1, 48, sprite_alpha);
    set_bkg_based_tiles(5, 6, 10, 1, map_alpha_gameOver, 0x01);
    set_bkg_based_tiles(6, 8, 8, 1, map_alpha_line, 0x01);
    set_bkg_based_tiles(4, 12, 5, 1, map_alpha_press, 0x01);
    set_bkg_based_tiles(11, 12, 5, 1, map_alpha_start, 0x01);

    set_interrupts(VBL_IFLAG);

    inputCallIndex = CONTROLS_GAMEOVER_INDEX;
}

void Stage1_Load(void)
{
    SCX_REG = 0x00;
    clsBG();

    set_bkg_data(1, 64, sprite_bg_lvl);
    //TODO: re-export lvl maps

    uint8_t offset = 0;
    uint8_t short_map[24];
    uint16_t mapOffset = 0;
    for (uint8_t x = 0; x < 0x20; x++)
    {
        mapOffset += 24 * offset;
        mapOffset = 24 * x;
        short_map[0] = map_bg_lvl1[mapOffset + 0];
        short_map[1] = map_bg_lvl1[mapOffset + 1];
        short_map[2] = map_bg_lvl1[mapOffset + 2];
        short_map[3] = map_bg_lvl1[mapOffset + 3];
        short_map[4] = map_bg_lvl1[mapOffset + 4];
        short_map[5] = map_bg_lvl1[mapOffset + 5];
        short_map[6] = map_bg_lvl1[mapOffset + 6];
        short_map[7] = map_bg_lvl1[mapOffset + 7];
        short_map[8] = map_bg_lvl1[mapOffset + 8];
        short_map[9] = map_bg_lvl1[mapOffset + 9];
        short_map[10] = map_bg_lvl1[mapOffset + 10];
        short_map[11] = map_bg_lvl1[mapOffset + 11];
        short_map[12] = map_bg_lvl1[mapOffset + 12];
        short_map[13] = map_bg_lvl1[mapOffset + 13];
        short_map[14] = map_bg_lvl1[mapOffset + 14];
        short_map[15] = map_bg_lvl1[mapOffset + 15];
        short_map[16] = map_bg_lvl1[mapOffset + 16];
        short_map[17] = map_bg_lvl1[mapOffset + 17];
        short_map[18] = map_bg_lvl1[mapOffset + 18];
        short_map[19] = map_bg_lvl1[mapOffset + 19];
        short_map[20] = map_bg_lvl1[mapOffset + 20];
        short_map[21] = map_bg_lvl1[mapOffset + 21];
        short_map[22] = map_bg_lvl1[mapOffset + 22];
        short_map[23] = map_bg_lvl1[mapOffset + 23];

        set_bkg_based_tiles(x, 0, 1, 24, short_map, 0x01);
    }
    //set_bkg_based_tiles(5, 0, 5, 24, map_bg_lvl1BLK1, 0x01);
    //despawn every 0x10 blocks
    //set_bkg_based_tiles(0, 0, map_bg_lvl1_Width, map_bg_lvl1_Height, map_bg_lvl1, 0x01);

    set_interrupts(VBL_IFLAG);

    inputCallIndex = CONTROLS_PLAYER_INDEX;
}

void Update(void)
{
    switch (level)
    {
    case LVL_STAGE1:
        Stage1_Update();
    case LVL_GAMEOVER:
        GameOver_Update();
        break;
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

    for (int map0 = 0; map0 < 256; map0++)
    {
        set_bkg_data(map0, 0x01, sprite_bg_cls);
    }
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
    return;
}

void GameOver_Update(void)
{
    return;
}

void Stage1_Update(void)
{
    return;
}