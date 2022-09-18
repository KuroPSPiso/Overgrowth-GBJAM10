#include "FUNC.H"

uint8_t player_x;
uint8_t player_y;
BOOL player_JUMP;
BOOL player_ATTACK;
BOOL player_ITEM; //item selection - POP MENU
BOOL player_PAUSE; //POP MENU

uint8_t menu_x;
uint8_t menu_y;
uint8_t menu_x_max;
uint8_t menu_y_max;

void MenuMovement()
{

}

void GameplayMovement()
{

}

void CheckInput(BOOL inMenu)
{
    if(inMenu == TRUE)
    {
        MenuMovement();
    }
    else
    {
        GameplayMovement();
    }
}