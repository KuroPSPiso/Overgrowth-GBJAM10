#include "controls.h"

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

uint8_t joypad_state;
void defaultInput(void)
{
	joypad_state = joypad();
	if (joypad_state == J_START)
	{
		snd_set(SFX_MENU_SELECT);
		snd_playOneShot();
		snd_set(SFX_NO_SOUND);
		isFading = TRUE;
		delay(1000); //joypad delay
	}
}

void MainMenu_Controls(void)
{
	joypad_state = joypad();
	if (joypad_state == J_START) 
	{
		delay(1000); //joypad delay
	}
}

void GameOver_Controls(void)
{
	joypad_state = joypad();
	if (joypad_state == J_START)
	{
		delay(100); //joypad delay
	}
}

/*
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
*/