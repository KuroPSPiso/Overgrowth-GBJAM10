#include "FUNC.H"

#include "sprites/alpha.h"
#include "lvl.h"
#include "controls.c"

/*================================
 *----------[INTERUPTS]-----------
 *================================
 */
//timer tick
void timer_isr(void)
{
	lvlTimer++;
}

/*================================
 *----------[FUNCTIONS]-----------
 *================================
 */
//init settings
void init(void)
{
    lvlTimer = 0;

    //interupts
    DISPLAY_OFF;
    NR52_REG = 0x8F;	// Turn on the sound
	NR51_REG = 0x11;	// Enable the sound channels
	NR50_REG = 0x77;	// Increase the volume to its max

    disable_interrupts();
	add_TIM(timer_isr);
	enable_interrupts();
    
    DISPLAY_ON;
}

//clear screen
void cls(void)
{
	uint8_t sprite_cls[16] = {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};

	set_bkg_data(0x00,0x01,bg_sprite_cls);
	uint8_t cls_map[] = { 0x00 };

	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 18; y++)
		{
    		set_bkg_tiles(x,y,1,1,cls_map);
		}
	}
}

void checkInput(void) {

	if (joypad() & J_B) {
		// The B button was pressed!
	}

}

void updateSwitches(void) {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

/*================================
 *-------------[MAIN]-------------
 *================================
 */
void main() {

	init();
	cls();
	LevelLoad();
	//set_bkg_data(0, 47, alpha);		// Load 47 tiles into background memory

	for(;;) {
		checkInput();				  // Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory
	}
}