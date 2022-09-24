#ifndef FUNC_H
#define FUNC_H

//TODO: rem line on compile
//#include <../../../include/gb/gb.h>
#include <gb/gb.h>
#include <time.h>

#include <stdint.h>
#include <stdio.h>

#include "sounds/sfx.h"

typedef void (*CallPTR)(void);
typedef unsigned char BOOL;

#define FALSE 0
#define TRUE 1

extern uint8_t currSnd[6];

extern void snd_set(uint8_t snd);
extern void snd_playOneShot(void);
#endif //FUNC_H