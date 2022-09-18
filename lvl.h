#ifndef LVL_H
#define LVL_H

#include "FUNC.H"
#include "sprites/bg.h"
#include "sprites/alpha.h"
#include "maps/bg.h"

extern uint8_t level;
extern const uint8_t maxLevel;
extern uint8_t lvlTimer;

/* Level details:
 * - -1: ERR?
 * - 0: Main Menu
 * - 1: Stage 1
 * - 2: Stage 2
 * - 3: End
 */

void SetLevel(int level);
void LevelLoad(void);
void MainMenu(void);
void Stage1(void);

#endif //LVL_H