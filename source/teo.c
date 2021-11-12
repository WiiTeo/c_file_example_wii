#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "wii.h"

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

/*
 *
 *
 * C File Example for Wii
 * (C) 2021 WiiTeo
 *
 *
 */

void Wii_Init() // Init the screen
{
    VIDEO_Init();
	WPAD_Init();
	rmode = VIDEO_GetPreferredMode(NULL);
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
}

void Wii_Init_Screen() // Init the screen
{
    printf("\x1b[2;0H");
}

int main(int argc, char **argv)
{
    Wii_Init();
    Wii_Init_Screen();

	printf("C File Example for Wii\n");
	printf("----------------------\n\n");

	// First example for Wii :

	int nombre1 = 10;
	int nombre2 = 12;

	int nombre3 = 0;

	nombre3 = nombre1 + nombre2;

	printf("Result for Nombre1 + Nombre2 : %d \n", nombre3);

	// End of First Example for Wii

	//-----------------------------------------------------------------------------------------

	printf("-----------------------\n");

	//-----------------------------------------------------------------------------------------

	// Second Example for the Wii

	unsigned long nombre4 = 0;

	while (nombre4 != 5)
    {
        printf("Value of Nombre4 : %ld \n", nombre4);
        nombre4++;
    }

	printf("Value of Nombre4 : %ld \n", nombre4);

	while(1) {

		WPAD_ScanPads();
		u32 pressed = WPAD_ButtonsDown(0);
		if ( pressed & WPAD_BUTTON_HOME )
        {
            printf("\ncfileexample: loggout.");
            exit(0);
        }
		VIDEO_WaitVSync();
	}

	return 0;
}
