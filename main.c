//      zcc +zx -vn -SO3 -m -lm -clib=new main.c -o main -create-app



//https://web.archive.org/web/20130927121234/http://devmaster.net/posts/9648/fast-and-accurate-sine-cosine
//https://web.archive.org/web/20180105200343if_/http://forum.devmaster.net/t/fast-and-accurate-sine-cosine/9648
//https://stackoverflow.com/questions/47906401/generate-sine-signal-in-c-without-using-the-standard-function
//https://www.coder.work/article/569467





#pragma printf %f

#include <arch/zx.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <input.h>
#include <intrinsic.h>//temp to place labels	powerful troubleshooting tool

#define cpu_bpeek(a)    (*(unsigned char *)(a))
#define cpu_bpoke(a,b)  (*(unsigned char *)(a) = b)
#define PI 3.14

int x, y;
float t;
float YY;
float freq;
float sinCalc;
int halfHeight;
int yHeight;//height of the display
int xWidth;//width of the display

void plot (unsigned char x, unsigned char y)
{
	//just in case you are testing a new algorythm
	/*
	if (x > 255)	x = 255;
	if (x < 0)		x = 0;
	if (y > 172)	y = 172;
	if (y < 0)		y = 0;
	*/
	*zx_pxy2saddr (x,y) |= zx_px2bitmask(x);
}

#include "sine.h"







float sine_caller ()//standard SIN calculation
{
	sinCalc = sin( x * freq * PI / xWidth );
	YY = ( ( sinCalc + 1.0) * (yHeight - 1) / 2.0);
	y = (int)  YY;
	return y;
}

void z88dk_sine (void)
{
    intrinsic_label(sine_caller_start);
	for (x=0; x <= xWidth; x++)
	{
		sine_caller();
		plot(x, y);
	}
	intrinsic_label(sine_caller_end);
}

float cosine_caller ()//standard SIN calculation
{
	sinCalc = cos( x * freq * PI / xWidth );
	YY = ( ( sinCalc + 1.0) * (yHeight - 1) / 2.0);
	y = (int)  YY;
	return y;
}

void z88dk_cosine (void)
{
    intrinsic_label(cosine_caller_start);
	for (x=0; x <= xWidth; x++)
	{
		cosine_caller();
		plot(x, y);
	}
	intrinsic_label(cosine_caller_end);
}



void drawCenterLine (void)
{
    //draw straight line
	for (x=0; x<= xWidth; x+=2)
	{
		plot(x, halfHeight);
	}
}




void printIntro (void)
{
    zx_cls(PAPER_WHITE | INK_BLUE);
    printf("\x16\x01\x02");
    printf ("Welcome to the Fast Sine and Cosine tester");
    printf ("\n");
    printf ("press a key for test");
    printf ("\n\n");
    printf ("Q - Standard Z88DK Sine");
    printf ("\n");
    printf ("W - Nick Sine - NO freq");
    printf ("\n");
    printf ("E - Quadratic Fast- NO freq");
    printf ("\n");
    printf ("R - Quadratic Accurate - NO freq");
    printf ("\n");
    printf ("T - sine Smile - FREQ");
    printf ("\n");
    printf ("Y - aPackOf sin - FREQ");
    printf ("\n");
    printf ("U - Dan_Ritchie_sine - FREQ?");
    printf ("\n");
    printf ("I - sine Smile - FREQ");
    printf ("\n");


    printf ("\n");
    printf ("\n");
    printf ("N - Standard Z88DK Cosine");
}

void waitForKey (void)
{
    printf("\x16\x01\x02");
    printf ("Press a Key");
    printf ("\n");
    //in_WaitForKey();
    in_wait_key();
}

void options (void)
{
    while (1)
    {
        //key presses
        if (in_key_pressed( IN_KEY_SCANCODE_q ))
		{
		    //Q
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			z88dk_sine ();

			waitForKey();
			break;
		}

		if (in_key_pressed( IN_KEY_SCANCODE_w ))
		{
		    //W
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			sineStuff_sin_nick();

			waitForKey();
            break;
		}

		if (in_key_pressed( IN_KEY_SCANCODE_e ))
		{
		    //E
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			quad_Sine_fast();

			waitForKey();
            break;
		}

		if (in_key_pressed( IN_KEY_SCANCODE_r ))
		{
		    //R
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			quad_Sine_accurate();

			waitForKey();
            break;
		}

        if (in_key_pressed( IN_KEY_SCANCODE_t ))
		{
		    //R
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			sine_Smile();

			waitForKey();
            break;
		}

        if (in_key_pressed( IN_KEY_SCANCODE_u ))
		{
		    //R
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			Dan_Ritchie_sine();

			waitForKey();
            break;
		}

		if (in_key_pressed( IN_KEY_SCANCODE_y ))
		{
		    //R
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			aPackOf_fast_sin();

			waitForKey();
            break;
		}



		if (in_key_pressed( IN_KEY_SCANCODE_n ))
		{
		    //N
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			z88dk_cosine();

			waitForKey();
            break;
		}


    }//end keypresses
}

void main()
{
	__asm
	ei
	__endasm

	zx_cls(PAPER_WHITE | INK_BLUE);

	freq = 2.0;
	yHeight = 172;
	xWidth = 255;
	halfHeight = yHeight / 2;

    while (1)
    {
        printIntro();
        options();
    }







}

//leave blank line after
