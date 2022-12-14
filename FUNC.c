#include "FUNC.H"

uint8_t currSnd[6];
void snd_set(uint8_t snd)
{
	switch (snd)
	{
	case 0x23:
		currSnd[0] = snd_spray[0];
		currSnd[1] = snd_spray[1];
		currSnd[2] = snd_spray[2];
		currSnd[3] = snd_spray[3];
		currSnd[4] = snd_spray[4];
		break;
	case 0x22:
		currSnd[0] = snd_hit[0];
		currSnd[1] = snd_hit[1];
		currSnd[2] = snd_hit[2];
		currSnd[3] = snd_hit[3];
		currSnd[4] = snd_hit[4];
		currSnd[5] = snd_hit[5];
		break;
	case 0x21:
		currSnd[0] = snd_attack[0];
		currSnd[1] = snd_attack[1];
		currSnd[2] = snd_attack[2];
		currSnd[3] = snd_attack[3];
		currSnd[4] = snd_attack[4];
		break;
	case 0x20:
		currSnd[0] = snd_jump[0];
		currSnd[1] = snd_jump[1];
		currSnd[2] = snd_jump[2];
		currSnd[3] = snd_jump[3];
		currSnd[4] = snd_jump[4];
		currSnd[5] = snd_jump[5];
		break;
	case 0x10:
		currSnd[0] = snd_select[0];
		currSnd[1] = snd_select[1];
		currSnd[2] = snd_select[2];
		currSnd[3] = snd_select[3];
		currSnd[4] = snd_select[4];
		currSnd[5] = snd_select[5];
		break;
	default:
		currSnd[0] = snd_NONE[0];
		break;
	}
}

void snd_playOneShot(void)
{
	switch (currSnd[0])
	{
	case 0x04:
		NR41_REG = currSnd[1];
		NR42_REG = currSnd[2];
		NR43_REG = currSnd[3];
		NR44_REG = currSnd[4];
		break;
	case 0x01:
		NR10_REG = currSnd[1];
		NR11_REG = currSnd[2];
		NR12_REG = currSnd[3];
		NR13_REG = currSnd[4];
		NR14_REG = currSnd[5];
		break;
	}
}


//track transition
BOOL isFading = FALSE;
BOOL fadedOut = FALSE;
BOOL transitionLvl = FALSE;
int fadeIndex = 3; //0-3

BOOL doFade(BOOL doTick)
{
	if(!isFading) return FALSE;
	if (doTick == FALSE) return TRUE;

	switch(fadeIndex)
	{
		case 03:
			BGP_REG = 0xE4U;
			break;
		case 02:
			BGP_REG = 0xF9U;
			break;
		case 01:
			BGP_REG = 0xFEU;
			break;
		default:
			BGP_REG = 0xFFU;
		break;
	}

	if(!fadedOut)
	{
		if(fadeIndex == 0)
		{
			fadedOut = TRUE;
			transitionLvl = TRUE;
		}
		else
		{
			fadeIndex--;
		}
	}
	else
	{
		if(fadeIndex == 3)
		{
			//faded back in
			isFading = FALSE;
			fadedOut = FALSE;
		}
		else
		{
			fadeIndex++;
		}
	}

	return TRUE;
}