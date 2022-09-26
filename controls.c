#include "controls.h"

uint8_t player_x;
uint8_t player_y;

uint16_t cam_x, cam_y;

BOOL player_JUMP;
BOOL player_ATTACK;
BOOL player_ITEM; //item selection - POP MENU
BOOL player_PAUSE; //POP MENU

uint8_t menu_x;
uint8_t menu_y;
uint8_t menu_x_max;
uint8_t menu_y_max;

uint8_t joypad_state;

int inputCallIndex = 0;
const CallPTR inputCallPTR[] = {
	&default_Controls,
	&MainMenu_Controls,
	&GameOver_Controls,
	&Player_Controls
};

//does nothing other than play sound/testing purposes.
void default_Controls(void)
{
	joypad_state = joypad();
	if (joypad_state == J_START)
	{
		snd_set(SFX_PLAYER_JUMP);
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
		SetLevel(LVL_STAGE1);
		snd_set(SFX_MENU_SELECT);
		snd_playOneShot();
		snd_set(SFX_NO_SOUND);
		isFading = TRUE;
		delay(200); //joypad delay
	}
}

void GameOver_Controls(void)
{
	joypad_state = joypad();
	if (joypad_state == J_START)
	{
		SetLevel(LVL_MAINMENU);
		snd_set(SFX_PLAYER_HIT);
		snd_playOneShot();
		snd_set(SFX_NO_SOUND);
		isFading = TRUE;
		delay(200); //joypad delay
	}
}

void Player_Controls(void)
{
	joypad_state = joypad();
	if (joypad_state & J_LEFT)
	{
		player_x--;
		//cam_x -= CAM_SPEED;
		//delay(100); //joypad delay
	}
	else if (joypad_state & J_RIGHT)
	{
		player_x++;
		//cam_x += CAM_SPEED;
		//delay(100); //joypad delay
	}
	if (joypad_state & J_UP)
	{
		player_y--;
	}
	if (joypad_state & J_DOWN)
	{
		player_y++;
	}

	if (joypad_state == (J_START | J_SELECT))
	{
		//manual surrender
		SetLevel(LVL_GAMEOVER);
		snd_set(SFX_MENU_SELECT);
		snd_playOneShot();
		snd_set(SFX_NO_SOUND);
		isFading = TRUE;
		delay(200); //joypad delay
	}
	else if (joypad_state & J_START)
	{
		player_PAUSE = TRUE;
	}
	else if (joypad_state == J_SELECT)
	{
		player_ITEM = TRUE;
	}

	if (joypad_state & J_A)
	{
		player_JUMP = TRUE;
	}

	if (joypad_state & J_B)
	{
		player_ATTACK = TRUE;
	}
}