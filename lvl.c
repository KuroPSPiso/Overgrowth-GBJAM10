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

    set_sprite_data(0, 23, sprite_farmer); //5 frames
    set_sprite_tile(0, 1); //top_left
    set_sprite_tile(1, 1); //bottom_left
    set_sprite_tile(2, 1); //top_right
    set_sprite_tile(3, 1); //bottom_right
    move_sprite(0, 0, 0);
    move_sprite(1, 0, 0);
    move_sprite(2, 0, 0);
    move_sprite(3, 0, 0);

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
    player_x = 0x00;
    player_y = 126;
    set_sprite_data(0, 23, sprite_farmer); //5 frames
    set_sprite_tile(0, 1); //top_left
    set_sprite_tile(1, 1); //bottom_left
    set_sprite_tile(2, 1); //top_right
    set_sprite_tile(3, 1); //bottom_right
    move_sprite(0, 0, 0);
    move_sprite(1, 0, 0);
    move_sprite(2, 0, 0);
    move_sprite(3, 0, 0);

    set_interrupts(VBL_IFLAG);

    inputCallIndex = CONTROLS_PLAYER_INDEX;
}

void Update(void)
{
    switch (level)
    {
    case LVL_STAGE1:
        Stage1_Update();
        break;
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

#define GRAVITY 2

BOOL player_SpriteFlip = FALSE;
BOOL player_SpriteFlipLEFT = FALSE;
BOOL fixedY = FALSE;
uint8_t player_JumpVelocity = 0;
uint16_t old_player_x = 0;
uint8_t animation_timer = 0;

void PlayerInteraction(void)
{
    BOOL hitFloor = fixedY;
    BOOL hitWall = FALSE;

    player_y += GRAVITY; //gravity
    //check if tile above(below) is groundtiletype
    uint8_t hitTile[16];
    //uint8_t centerXInBG = (SCX_REG / 8) + ((player_x - 8) / 8); //minus -8 range
    //uint8_t centerYInBG = (SCY_REG / 8) + ((player_y - 16) / 8); //minus -16 range
    uint8_t centerXInBG = (SCX_REG >> 3) + ((player_x - 16) >> 3); //offset -1 tile X
    uint8_t centerYInBG = (SCY_REG >> 3) + ((player_y - 24 - 3) >> 3); //offset -1 tile Y


    //offscreen
    if (centerXInBG >= 0xFE)
    {
        uint8_t tempHitTile[12];
        get_bkg_tiles(0, centerYInBG, 3, 4, tempHitTile);
        hitTile[0] = wall_tiles[0] + 0x01;
        hitTile[1] = tempHitTile[0];
        hitTile[2] = tempHitTile[1];
        hitTile[3] = tempHitTile[2];
        hitTile[4] = wall_tiles[0] + 0x01;
        hitTile[5] = tempHitTile[3];
        hitTile[6] = tempHitTile[4];
        hitTile[7] = tempHitTile[5];
        hitTile[8] = wall_tiles[0] + 0x01;
        hitTile[9] = tempHitTile[6];
        hitTile[10] = tempHitTile[7];
        hitTile[11] = tempHitTile[8];
        hitTile[12] = wall_tiles[0] + 0x01;
        hitTile[13] = tempHitTile[9];
        hitTile[14] = tempHitTile[10];
        hitTile[15] = tempHitTile[11];
    }
    else
    {
        get_bkg_tiles(centerXInBG, centerYInBG, 4, 4, hitTile);
    }

    //2=x, 4=y = 14-16 (DOWN) 
    //-0x01 (offset in tilemap) 
    if (hitTile[13] - 0x01 == floor_tiles[0] ||
        hitTile[13] - 0x01 == floor_tiles[1] ||
        hitTile[13] - 0x01 == floor_tiles[2] ||
        hitTile[13] - 0x01 == floor_tiles[3] ||
        hitTile[13] - 0x01 == floor_tiles[4] ||
        hitTile[14] - 0x01 == floor_tiles[0] ||
        hitTile[14] - 0x01 == floor_tiles[1] ||
        hitTile[14] - 0x01 == floor_tiles[2] ||
        hitTile[14] - 0x01 == floor_tiles[3] ||
        hitTile[14] - 0x01 == floor_tiles[4])
    {
        hitFloor = TRUE;
    }
    //1=x, 2=y || 1=x, 3=y(LEFT)
    if (hitTile[4] - 0x01 == wall_tiles[0] ||
        hitTile[4] - 0x01 == wall_tiles[1] ||
        hitTile[8] - 0x01 == wall_tiles[0] ||
        hitTile[8] - 0x01 == wall_tiles[1])
    {
        hitWall = TRUE;
        player_x++;
    }
    //3=x, 2=y || 3=x, 2=y (RIGHT)
    if (hitTile[7] - 0x01 == wall_tiles[0] ||
        hitTile[7] - 0x01 == wall_tiles[1] ||
        hitTile[11] - 0x01 == wall_tiles[0] ||
        hitTile[11] - 0x01 == wall_tiles[1])
    {
        hitWall = TRUE;
        player_x--;
    }

    //animations
    uint8_t sprite_prop = get_sprite_prop(0);
    if (hitFloor == FALSE)
    {
        //in air
        set_sprite_tile(0, 0x08);
        set_sprite_tile(1, 0x09);
        set_sprite_tile(2, 0x0A);
        set_sprite_tile(3, 0x0B);
    }
    else if (old_player_x == player_x)
    {
        //idle
        if (animation_timer > 16)
        {
            player_SpriteFlip = (player_SpriteFlip == TRUE) ? FALSE : TRUE;
            animation_timer = 0;
        }
        else
        {
            animation_timer++;
        }
        set_sprite_tile(0, 0x00 + (player_SpriteFlip << 2));
        set_sprite_tile(1, 0x01 + (player_SpriteFlip << 2));
        set_sprite_tile(2, 0x02 + (player_SpriteFlip << 2));
        set_sprite_tile(3, 0x03 + (player_SpriteFlip << 2));
    }
    else if (old_player_x != player_x)
    {
        //running
        if (animation_timer > 4)
        {
            player_SpriteFlip = (player_SpriteFlip == TRUE) ? FALSE : TRUE;
            animation_timer = 0;
        }
        else
        {
            animation_timer++;
        }
        set_sprite_tile(0, 0x08 + (player_SpriteFlip << 2));
        set_sprite_tile(1, 0x09 + (player_SpriteFlip << 2));
        set_sprite_tile(2, 0x0A + (player_SpriteFlip << 2));
        set_sprite_tile(3, 0x0B + (player_SpriteFlip << 2));
        if(old_player_x < player_x && sprite_prop > 7 == 0x01)
        {
            set_sprite_prop(0, sprite_prop - S_FLIPX);
            set_sprite_prop(1, sprite_prop - S_FLIPX);
            set_sprite_prop(2, sprite_prop - S_FLIPX);
            set_sprite_prop(3, sprite_prop - S_FLIPX);
            player_SpriteFlipLEFT = FALSE;
        }
        else if(old_player_x > player_x && sprite_prop > 7 == 0x00)
        {
            set_sprite_prop(0, sprite_prop + S_FLIPX);
            set_sprite_prop(1, sprite_prop + S_FLIPX);
            set_sprite_prop(2, sprite_prop + S_FLIPX);
            set_sprite_prop(3, sprite_prop + S_FLIPX);
            player_SpriteFlipLEFT = TRUE;
        }

    }

    //set_sprite_prop(0, sprite_prop & S_FLIPX ? sprite_prop | S_FLIPX : sprite_prop & S_FLIPX);
    old_player_x = player_x;

    if (player_JumpVelocity > 0)
    {
        player_y -= player_JumpVelocity;
        player_JumpVelocity >>= 1;
    }

    if (hitFloor == TRUE && player_JUMP == TRUE)
    {
        player_JumpVelocity += PLAYER_JUMP_VELOCITY;
        player_y -= PLAYER_JUMP_VELOCITY >> 2;
        hitFloor = FALSE;
    }
    player_JUMP = FALSE; //always false if not on the ground
    if(hitFloor || fixedY) player_y -= GRAVITY; //cancel gravity (check if need to pop back up)

#if DEBUG == 1
    uint8_t offsetX = cam_x / 8;
    uint8_t offsetY = cam_y / 8;

    //debug floor hit
    uint8_t map_debug_hit[] = {
        0x27 + hitFloor
    };
    set_bkg_based_tiles(offsetX + 2, offsetY + 2, 1, 1, map_debug_hit, 0x01);
    //debug wall hit
    map_debug_hit[0] = 0x27 + hitWall;
    set_bkg_based_tiles(offsetX + 4, offsetY + 2, 1, 1, map_debug_hit, 0x01);
    //debug tile_detection
    uint8_t no1 = hitTile[0] >> 4;
    uint8_t no2 = hitTile[0] & 0x0F;
    uint8_t map_debug_currFloorTile[] = {
        0x27 + no1,
        0x27 + no2
    };
    set_bkg_based_tiles(offsetX + 2, offsetY + 4, 2, 1, map_debug_currFloorTile, 0x01);
    no1 = hitTile[1] >> 4;
    no2 = hitTile[1] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 5, offsetY + 4, 2, 1, map_debug_currFloorTile, 0x01);
    no1 = hitTile[2] >> 4;
    no2 = hitTile[2] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 8, offsetY + 4, 2, 1, map_debug_currFloorTile, 0x01);

    no1 = hitTile[3] >> 4;
    no2 = hitTile[3] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 2, offsetY + 5, 2, 1, map_debug_currFloorTile, 0x01);
    no1 = hitTile[4] >> 4;
    no2 = hitTile[4] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 5, offsetY + 5, 2, 1, map_debug_currFloorTile, 0x01);
    no1 = hitTile[5] >> 4;
    no2 = hitTile[5] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 8, offsetY + 5, 2, 1, map_debug_currFloorTile, 0x01);

    no1 = hitTile[6] >> 4;
    no2 = hitTile[6] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 2, offsetY + 6, 2, 1, map_debug_currFloorTile, 0x01);
    no1 = hitTile[7] >> 4;
    no2 = hitTile[7] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 5, offsetY + 6, 2, 1, map_debug_currFloorTile, 0x01);
    no1 = hitTile[8] >> 4;
    no2 = hitTile[8] & 0x0F;
    map_debug_currFloorTile[0] = 0x27 + no1;
    map_debug_currFloorTile[1] = 0x27 + no2;
    set_bkg_based_tiles(offsetX + 8, offsetY + 6, 2, 1, map_debug_currFloorTile, 0x01);

    //debug player_pos
    no1 = centerXInBG >> 4;
    no2 = centerXInBG & 0x0F;
    uint8_t map_debug_centerXInBG[] = {
        0x27 + no1,
        0x27 + no2
    };
    set_bkg_based_tiles(offsetX + 2, offsetY + 8, 2, 1, map_debug_centerXInBG, 0x01);
    no1 = centerYInBG >> 4;
    no2 = centerYInBG & 0x0F;
    uint8_t map_debug_centerYInBG[] = {
        0x27 + no1,
        0x27 + no2
    };
    set_bkg_based_tiles(offsetX + 2, offsetY + 9, 2, 1, map_debug_centerYInBG, 0x01);
#endif

    uint8_t spritePos[4];
    if (player_SpriteFlipLEFT == TRUE)
    {
        spritePos[0] = 2;
        spritePos[1] = 3;
        spritePos[2] = 0;
        spritePos[3] = 1;
    }
    else
    {
        spritePos[0] = 0;
        spritePos[1] = 1;
        spritePos[2] = 2;
        spritePos[3] = 3;
    }


    move_sprite(spritePos[0], player_x, player_y);
    move_sprite(spritePos[1], player_x, player_y + 8);
    move_sprite(spritePos[2], player_x + 8, player_y);
    move_sprite(spritePos[3], player_x + 8, player_y + 8);
}

void MainMenu_Update(void)
{
    fixedY = TRUE;
    PlayerInteraction();
    player_y = 140;
    player_x++;
    return;
}

void GameOver_Update(void)
{
    /*move_sprite(0, player_x, player_y);
    move_sprite(1, player_x, player_y + 8);
    move_sprite(2, player_x + 8, player_y);
    move_sprite(3, player_x + 8, player_y + 8);*/
    set_sprite_tile(0, 0x10);
    set_sprite_tile(1, 0x11);
    set_sprite_tile(2, 0x12);
    set_sprite_tile(3, 0x13);
    return;
}

uint16_t old_cam_x = 19200; //unset
uint16_t old_cam_y = 19200; //unset

void Stage1_Update(void)
{
    fixedY = FALSE;

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

    PlayerInteraction();
    return;
}