#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")


int main(void)
{
	PlaySound("white.wav",NULL,SND_SYNC); 
	PlaySound("down.wav",NULL,SND_SYNC); 
	PlaySound("blue.wav",NULL,SND_SYNC); 
	PlaySound("up.wav",NULL,SND_SYNC); 
	return 0;
}

