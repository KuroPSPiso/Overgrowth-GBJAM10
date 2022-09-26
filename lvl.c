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

    SCX_REG = 0;
    SCY_REG = 0;

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

    SCX_REG = 0;
    SCY_REG = 0;

    set_bkg_data(1, 48, sprite_alpha);
    set_bkg_based_tiles(5, 6, 10, 1, map_alpha_gameOver, 0x01);
    set_bkg_based_tiles(6, 8, 8, 1, map_alpha_line, 0x01);
    set_bkg_based_tiles(4, 12, 5, 1, map_alpha_press, 0x01);
    set_bkg_based_tiles(11, 12, 5, 1, map_alpha_start, 0x01);

    set_interrupts(VBL_IFLAG);

    inputCallIndex = CONTROLS_GAMEOVER_INDEX;
}

void drawMap(uint8_t mapXPos, uint16_t mapOffset, uint8_t *map_bg_lvl)
{
    uint8_t short_map[24];
    short_map[0] = map_bg_lvl[mapOffset + 0];
    short_map[1] = map_bg_lvl[mapOffset + 1];
    short_map[2] = map_bg_lvl[mapOffset + 2];
    short_map[3] = map_bg_lvl[mapOffset + 3];
    short_map[4] = map_bg_lvl[mapOffset + 4];
    short_map[5] = map_bg_lvl[mapOffset + 5];
    short_map[6] = map_bg_lvl[mapOffset + 6];
    short_map[7] = map_bg_lvl[mapOffset + 7];
    short_map[8] = map_bg_lvl[mapOffset + 8];
    short_map[9] = map_bg_lvl[mapOffset + 9];
    short_map[10] = map_bg_lvl[mapOffset + 10];
    short_map[11] = map_bg_lvl[mapOffset + 11];
    short_map[12] = map_bg_lvl[mapOffset + 12];
    short_map[13] = map_bg_lvl[mapOffset + 13];
    short_map[14] = map_bg_lvl[mapOffset + 14];
    short_map[15] = map_bg_lvl[mapOffset + 15];
    short_map[16] = map_bg_lvl[mapOffset + 16];
    short_map[17] = map_bg_lvl[mapOffset + 17];
    short_map[18] = map_bg_lvl[mapOffset + 18];
    short_map[19] = map_bg_lvl[mapOffset + 19];
    short_map[20] = map_bg_lvl[mapOffset + 20];
    short_map[21] = map_bg_lvl[mapOffset + 21];
    short_map[22] = map_bg_lvl[mapOffset + 22];
    short_map[23] = map_bg_lvl[mapOffset + 23];
    set_bkg_based_tiles(mapXPos, 0, 1, 24, short_map, 0x01);
}

void Stage1_Load(void)
{
    clsBG();

    //set player/cam positions
    cam_x = 0;
    cam_y = 56;

    //reset bg position
    SCX_REG = cam_x;
    SCY_REG = cam_y;

    //set bg sprite data
    set_bkg_data(1, 64, sprite_bg_lvl);
    uint8_t offset = cam_x / 8;
    uint16_t mapOffset = 0;
    for (uint8_t x = 0; x < 0x20; x++)
    {
        mapOffset = 24 * x;
        mapOffset += 24 * offset;
        
        drawMap(x, mapOffset, map_bg_lvl1);
    }

    //spawn player
    player_x = 24;
    player_y = 40;
    set_sprite_data(0, 5, sprite_alpha);
    set_sprite_tile(0, 1);
    move_sprite(0, player_x, player_y);

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

    for (int x = 0; x < 0x20; x++)
    {
        for (int y = 0; y < 0x17; y++)
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

#define GRAVITY 2

BOOL player_SpriteFlip_Walk = FALSE;
uint8_t player_JumpVelocity = 0;
BOOL hitFloor = TRUE;

void PlayerInteraction()
{
    player_x;
    player_y += GRAVITY; //gravity
    //check if tile above(below) is groundtiletype
    

    if (player_JumpVelocity > 0)
    {
        player_y -= player_JumpVelocity;
        player_JumpVelocity >>= 1;
    }

    if (hitFloor == TRUE && player_JUMP == TRUE)
    {
        player_JumpVelocity += PLAYER_JUMP_VELOCITY;
        player_y-=PLAYER_JUMP_VELOCITY >> 1;
        player_JUMP = FALSE;
        hitFloor = FALSE;
    }
    if(hitFloor) player_y -= GRAVITY; //cancel gravity (check if need to pop back up)

    //debug
    uint8_t map_debug_hitFloor[] = {
        0x27 + hitFloor
    };
    uint8_t offsetX = cam_x / 8;
    uint8_t offsetY = cam_y / 8;
    set_bkg_based_tiles(offsetX + 2, offsetY + 2, 1, 1, map_debug_hitFloor, 0x01);


    move_sprite(0, player_x, player_y);
}

uint16_t old_cam_x = 19200; //unset
uint16_t old_cam_y = 19200; //unset

void Stage1_Update(void)
{
    PlayerInteraction();

    if (cam_x > 1000) cam_x = 0; //limit camera min
    if (cam_x > 640) cam_x = 640; //limit camera max

    if (old_cam_x == 19200 || (32 + cam_x - old_cam_x) >= 40)
    {
        uint8_t offset = cam_x / 8;
        uint16_t mapOffset = 0;
        for (uint8_t x = 0; x < 0x2; x++)
        {
            mapOffset = 24 * x;
            mapOffset += 24 * offset;
            mapOffset += 24 * 0x1E;

            drawMap((x + 0x1E + offset)%0x20, mapOffset, map_bg_lvl1);
        }
        old_cam_x = cam_x;
    }
    //needs fixing but fine for now
    if ((32 + cam_x - old_cam_x) < 32)
    {
        uint8_t offset = cam_x / 8;
        uint16_t mapOffset = 0;
        for (uint8_t x = 0; x < 0x2; x++)
        {
            mapOffset = 24 * x;
            mapOffset = 24 * offset;
            //mapOffset -= 24;

            drawMap((x - 0x01 + offset) % 0x20, mapOffset, map_bg_lvl1);
        }
        old_cam_x = cam_x;
    }

    SCX_REG = cam_x;
    SCY_REG = cam_y;
    return;
}