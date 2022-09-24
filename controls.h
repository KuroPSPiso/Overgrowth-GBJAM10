#ifndef CONTROLS_H
#define CONTROLS_H

#include "FUNC.H"
#include "lvl.h"

extern uint8_t player_x;
extern uint8_t player_y;

extern int inputCallIndex;
extern const CallPTR inputCallPTR[];

extern void default_Controls(void);
extern void MainMenu_Controls(void);
extern void GameOver_Controls(void);

#endif // !CONTROLS_H
