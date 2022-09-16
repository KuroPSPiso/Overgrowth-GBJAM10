
#include "FUNC.H"

#include "lvl.h"
#include "controls.c"
#include "sprites/alpha.c"


//timer tick
void timer_isr(void)
{
	lvlTimer++;
}

//init settings
void init()
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
void cls()
{
    //TODO: BLANK
}

void updateSwitches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

//void main(void)
//{
//    //Init();
//    DISPLAY_ON;
//    set_bkg_data(0, 47, alpha);
//    LevelLoad();
//
//    CLS();
//    
//    for(;;)//loop
//    {
//        updateSwitches();
//        wait_vbl_done();
//    }
//}

void checkInput();

void main() {

	init();
	LevelLoad();
	//set_bkg_data(0, 47, alpha);		// Load 47 tiles into background memory

	for(;;) {

		checkInput();				  // Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory
	}

}

void checkInput() {

	if (joypad() & J_B) {
		// The B button was pressed!
	}

}