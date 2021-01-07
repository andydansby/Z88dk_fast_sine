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
float freq = 2;
float sinCalc;
int halfHeight;
unsigned char yHeight;//height of the display
unsigned char xWidth;//width of the display

void plot (unsigned char x, unsigned char y)
{
	//just in case you are testing a new algorithm
	/*
	if (x > 255)	x = 255;
	if (x < 0)		x = 0;
	if (y > 172)	y = 172;
	if (y < 0)		y = 0;
	*/
	*zx_pxy2saddr (x,y) |= zx_px2bitmask(x);
}

#include "sine.h"
#include "cosine.h"
#include "tangent.h"





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

float tangent_caller99 ()//standard tangent calculation
{
	//sinCalc =  tan(x * PI / xWidth) / freq;
	//sinCalc = tan(PI / x);//close

	//freq = 100;

    //sinCalc = tan(x  * PI / xWidth + freq); /nice at freq = 2
    //sinCalc = tan((x * PI) / (xWidth -* freq));// at 2 gets off
    //sinCalc = tan(x * PI / xWidth);//ok
	sinCalc = tan((x * PI) / (xWidth - freq));// ok
	//sinCalc = tan(x * freq * PI / xWidth);

	if (sinCalc > freq)
        sinCalc = freq;
    if (sinCalc < -freq)
        sinCalc = -freq;

    sinCalc += freq;


    YY = sinCalc / (freq + freq) * yHeight;//ok
    //YY = sinCalc / (freq * freq) * yHeight;//ok gets real shallow once freq gets high (10)

    //YY = sinCalc / (freq) * yHeight;//junk


	//YY = ( ( sinCalc ) * (yHeight - 1) / 2.0);
	//YY = ( ( sinCalc + 1.0) * (yHeight - 1) / 2.0);
	y = (int)YY;
	return y;
}


float tangent_caller ()//standard tangent calculation
{
	sinCalc = tan((x * PI) / xWidth);// ok

/*	if (sinCalc > freq)
        sinCalc = freq;
    if (sinCalc < -freq)
        sinCalc = -freq;

    sinCalc += freq;*/


    YY = sinCalc / (freq + freq) * yHeight;//ok
	y = (int)YY;
	return y;
}

void z88dk_tangent (void)
{
    intrinsic_label(tangent_caller_start);
	for (x=0; x <= xWidth; x++)
	{
		//tangent_caller();
		tangent_caller99();
		plot(x, y);
	}
	intrinsic_label(tangent_caller_end);
}


void drawCenterLine (void)
{
    //draw straight line
	for (x=0; x<= xWidth; x+=2)
	{
		plot(x, halfHeight);
	}
}

void printPage2(void)
{
    zx_cls(PAPER_WHITE | INK_BLUE);
    freq = 2;
    printf("\x16\x01\x02");
    printf ("\n");
    printf ("Accuracy of Sine Routines");
    printf ("\n");
    printf ("Since Sine,Cosine and Tangent are all based");
    printf ("\n");
    printf ("on one another, we will check sine only");
    printf ("\n");
    printf ("\n");
    printf ("W - Nick Sine vs Z88dk Sine");
    printf ("\n");
    printf ("E - Quadratic Fast vs Z88dk Sine");
    printf ("\n");
    printf ("R - Quadratic Accurate vs Z88dk Sine");
    printf ("\n");
    printf ("T - sine Smile vs Z88dk Sine");
    printf ("\n");
    printf ("Y - aPackOf sin vs Z88dk Sine");
    printf ("\n");
    printf ("U - Dan_Ritchie_sine vs Z88dk Sine");
    printf ("\n");
    printf ("I - Bhaskara Sin vs Z88dk Sine");
    printf ("\n");
    printf ("\n");
    printf ("M - Prior Page");
}


void printPage1(void)
{
    zx_cls(PAPER_WHITE | INK_BLUE);
    printf("\x16\x01\x02");

    printf ("Welcome to the Fast Sine and Cosine tester");
    printf ("\n");
    printf ("press a key for test");
    printf ("\n\n");
    //printf("FREQ = %f", freq);
    //printf ("\n");
    printf ("1-0 Change Frequency   ");
    printf("FREQ = %f", freq);
    printf ("\n");
    printf ("Q - Standard Z88DK Sine - FREQ");
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
    printf ("U - Dan_Ritchie_sine - FREQ");
    printf ("\n");
    printf ("I - Bhaskara Sin - FREQ");
    printf ("\n");
    printf ("\n");
    printf ("A - Standard Z88DK Cosine");
    printf ("\n");
    printf ("S - Smile Cosine");
    printf ("\n");
    printf ("D - Standard Z88DK Tangent");
    printf ("\n");
    printf ("F - Smile Tangent");
    printf ("\n");
    printf ("\n");

    printf ("N - Next Page Visual Accuracy");

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

        //Frequency adjustments
        if (in_key_pressed( IN_KEY_SCANCODE_1 ))
		{
		    //1
			in_wait_nokey();
			freq = 1;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_2 ))
		{
		    //2
			in_wait_nokey();
			freq = 2;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_3 ))
		{
		    //3
			in_wait_nokey();
			freq = 3;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_4 ))
		{
		    //4
			in_wait_nokey();
			freq = 4;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_5 ))
		{
		    //5
			in_wait_nokey();
			freq = 5;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_6 ))
		{
		    //6
			in_wait_nokey();
			freq = 6;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_7 ))
		{
		    //7
			in_wait_nokey();
			freq = 7;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_8 ))
		{
		    //8
			in_wait_nokey();
			freq = 8;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_9 ))
		{
		    //9
			in_wait_nokey();
			freq = 9;
			printPage1();
			break;
		}
		if (in_key_pressed( IN_KEY_SCANCODE_0 ))
		{
		    //0
			in_wait_nokey();
			freq = 10;
			printPage1();
			break;
		}
        //end Frequency adjustments


        //SINE algorythms
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

		if (in_key_pressed( IN_KEY_SCANCODE_i ))
		{
		    //R
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			bhaskaraSin();

			waitForKey();
            break;
		}
        //end SINE algorythms


        //COSINE algorythms
		if (in_key_pressed( IN_KEY_SCANCODE_a ))
		{
		    //A
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			z88dk_cosine();

			waitForKey();
            break;
		}

		if (in_key_pressed( IN_KEY_SCANCODE_s ))
		{
		    //S
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			Cosine_smile();

			waitForKey();
            break;
		}
		//end COSINE algorithms

        //TANGENT algorythms
		if (in_key_pressed( IN_KEY_SCANCODE_d ))
		{
		    //D
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			z88dk_tangent();

			waitForKey();
            break;
		}

		if (in_key_pressed( IN_KEY_SCANCODE_f ))
		{
		    //F
			in_wait_nokey();
			zx_cls(INK_BLACK | PAPER_WHITE);
			drawCenterLine();
			Tangent_smile();

			waitForKey();
            break;
		}
		//end TANGENT algorythms

		//printPage2
		if (in_key_pressed( IN_KEY_SCANCODE_n ))
		{
		    //N
			in_wait_nokey();
			printPage2();
			waitForKey();
            break;
		}

		if (in_key_pressed( IN_KEY_SCANCODE_m ))
		{
		    //m
			in_wait_nokey();
			printPage1();
			waitForKey();
            break;
		}


    }//end key-presses
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
        printPage1();
        options();
    }







}

//leave blank line after
