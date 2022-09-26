#include "FUNC.H"

#include "sprites/alpha.h"
#include "lvl.h"
#include "controls.h"

/*================================
 *----------[INTERUPTS]-----------
 *================================
 */
//timer tick
UWORD count;

void timer_isr(void)
{
    count++;
}

/*================================
 *----------[FUNCTIONS]-----------
 *================================
 */
//init settings
void init(void)
{
    lvlTimer = 0;

    DISPLAY_OFF;
	ENABLE_RAM;
	SWITCH_RAM_MBC1(1);
    NR52_REG = 0x80; //0x8F;	// Turn on the sound
	NR50_REG = 0x77;	// Increase the volume to its max
	NR51_REG = 0xFF; //0x11;	// Enable the sound channels
	//BGP_REG = OBP0_REG;	// Set Palette
	BGP_REG = 0xE4U;

    //interupts
    //disable_interrupts();
    //add_TIM(timer_isr);
	
    //enable_interrupts();

    //set_interrupts(TIM_IFLAG);
    
    DISPLAY_ON;
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
	inputCallIndex = CONTROLS_DEFAULT_INDEX;

	init();
	clsBG();
	level = LVL_MAINMENU;
	LevelLoad();

	uint16_t localTimer = 0;

	for (;;) {
		BOOL doFadeTick = (localTimer >= (CLOCKS_PER_SEC / 12));
		if (doFadeTick == FALSE)
		{
			//add clock
			localTimer++;
		}
		else
		{
			//reset clock
			localTimer = 0;
		}
		if (transitionLvl == TRUE)
		{
			transitionLvl = FALSE;
			LevelLoad();
		}
		if (!doFade(doFadeTick))
		{
			Update();

			inputCallPTR[inputCallIndex]();
		}
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory
	}
}