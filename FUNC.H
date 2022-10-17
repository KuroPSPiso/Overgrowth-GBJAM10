#ifndef FUNC_H
#define FUNC_H

#define DEBUG 1

//TODO: rem line on compile
//#include <../../../include/gb/gb.h>
#include <gb/gb.h>
#include <time.h>

#include <stdint.h>
#include <stdio.h>

#include "sounds/sfx.h"

//====> custom types
//function pointer/callback
typedef void (*CallPTR)(void);

//boolean feature
typedef unsigned char BOOL;
#define FALSE 0
#define TRUE 1

//====> sound management
extern uint8_t currSnd[6];

//Set a new Sound
extern void snd_set(uint8_t snd);
//Play previously set sound
extern void snd_playOneShot(void);

//====> transitions
//check if faded once
extern BOOL isFading;
//check if in fade-in else fade-out (currently name is opposite)
extern BOOL fadedOut;
extern int fadeIndex; //0-3
extern BOOL transitionLvl;

//used for lvl transitions
extern BOOL doFade(BOOL doTick);


//math
struct MODCHECK
{
	uint8_t R; //result
	BOOL F; //checkflag
};
typedef struct MODCHECK MODCHECK;

extern uint8_t mul(uint8_t x, uint8_t y);
extern uint8_t div(uint8_t x, uint8_t y);
extern uint8_t mod(uint8_t x, uint8_t y);
extern void modLoopCheck(MODCHECK* rCheck, uint8_t x, uint8_t y);

#endif //FUNC_H