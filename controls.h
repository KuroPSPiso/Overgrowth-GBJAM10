#ifndef CONTROLS_H
#define CONTROLS_H

#include "FUNC.H"
#include "lvl.h"

#define PLAYER_SPEED 4;
//extern uint8_t player_x;
//extern uint8_t player_y; //move to another class

#define CAM_SPEED 4;
extern uint16_t cam_x, cam_y;

extern int inputCallIndex;

#define CONTROLS_DEFAULT_INDEX 0
#define CONTROLS_MAINMENU_INDEX 1
#define CONTROLS_GAMEOVER_INDEX 2
#define CONTROLS_PLAYER_INDEX 3

extern const CallPTR inputCallPTR[];

void default_Controls(void);
void MainMenu_Controls(void);
void GameOver_Controls(void);
void Player_Controls(void);

#endif // !CONTROLS_H
