#ifndef LVL_H
#define LVL_H

#include "FUNC.H"
#include "sprites/bg.h"
#include "sprites/bg_lvl.h"
#include "sprites/alpha.h"
#include "maps/bg.h"
#include "maps/alpha.h"
#include "controls.h"

extern uint8_t level;
extern uint8_t lvlTimer;

void clsBG(void);
/* Level details:
 * - -1: ERR?
 * - 0: Main Menu
 * - 1: GameOver
 * - 2: Stage 1
 * - 3: Stage 2
 * etc...
 */

#define LVL_MAINMENU 0
#define LVL_GAMEOVER 1
#define LVL_STAGE1	2
void SetLevel(int level);

void LevelLoad(void);
void MainMenu_Load(void);
void GameOver_Load(void);
void Stage1_Load(void);

void Update(void);
void MainMenu_Update(void);
void GameOver_Update(void);
void Stage1_Update(void);

//interupts
void scrollMainMenuLCD();

#endif //LVL_H