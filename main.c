#include "FUNC.H"

#include "sprites/alpha.h"
#include "lvl.h"
#include "controls.c"

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
    NR52_REG = 0x8F;	// Turn on the sound
	NR51_REG = 0x11;	// Enable the sound channels
	NR50_REG = 0x77;	// Increase the volume to its max
	//BGP_REG = OBP0_REG;	// Set Palette
	BGP_REG = 0xE4U;

    //interupts
    disable_interrupts();
    add_TIM(timer_isr);
    enable_interrupts();

    //set_interrupts(TIM_IFLAG);
    
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


uint8_t fadeTimer = 0;
uint8_t fadeLvl = 1;
BOOL fade(BOOL in)
{
	if(fadeTimer >= CLOCKS_PER_SEC){
		switch (fadeLvl)
		{
		case 01:
			BGP_REG = 0xFEU;
			break;
		case 02:
			BGP_REG = 0xFFU;
			break;
		case 03:
			BGP_REG = 0xE4U;
			break;
		default:
			BGP_REG = 0xF9U;
			break;
		}

		(in == TRUE)? fadeLvl++ : fadeLvl--;
	}
	if(in == FALSE)
	{
		return (fadeLvl >= 3)? TRUE : FALSE;
	}
	else
	{
		return (fadeLvl <= 0)? TRUE : FALSE;
	}
}

/*================================
 *-------------[MAIN]-------------
 *================================
 */
void main() {

	init();
	cls();
	LevelLoad();


	for(;;) {
		// CHECKFADE:		
		// if(fade(FALSE) == FALSE) goto CHECKFADE;
		// localTimer++;
		// if(localTimer >= CLOCKS_PER_SEC){
		// 	TIMA_REG++; //every 0.1sec on /10 == 1:1 per CLOCKS_PER_SEC
		// 	switch (TIMA_REG)
		// 	{
		// 	case 01:
		// 		BGP_REG = 0xF9U;
		// 		break;
		// 	case 02:
		// 		BGP_REG = 0xFEU;
		// 		break;
		// 	case 03:
		// 		BGP_REG = 0xFFU;
		// 		break;
		// 	default:
		// 		BGP_REG = 0xE4U;
		// 		break;
		// 	}
		// 	localTimer = 0;
		// }
		// //BGP_REG = TIMA_REG;

		checkInput();				  // Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting visual memory
	}
}