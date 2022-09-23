#ifndef SFX_H
#define SFX_H
#include "../FUNC.H"

#define SFX_NO_SOUND 0x00
//snd: 0x00
extern const uint8_t snd_NONE[];

//=====[MENU]=====

#define SFX_MENU_SELECT 0x10
//snd: 0x10
extern const uint8_t snd_select[];


//====[PLAYER]====

#define SFX_PLAYER_JUMP 0x20
//snd: 0x20
extern const uint8_t snd_jump[];

#define SFX_PLAYER_ATTACK 0x21
//snd: 0x21 - deal damage
extern const uint8_t snd_attack[];

#define SFX_PLAYER_HIT 0x22
//snd: 0x22 - take damage
extern const uint8_t snd_hit[];

#define SFX_PLAYER_SPRAY 0x23
//snd: 0x23
extern const uint8_t snd_spray[];

#define SFX_PLAYER_STEP 0x24
//snd: 0x24
//extern const uint8_t snd_step[]; //?


//====[ENEMY]====

#define SFX_ENEMY_HISS 0x30
//snd: 0x30
//extern const uint8_t snd_hiss[]; //?

#endif // !SFX_H
