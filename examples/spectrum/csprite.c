
/*
	Coloured sprites demo - shows the zxlowgfx capabilities
	uses cputsprite

	The "lr64x48" #define activates the alternate resolution,

	build with:   zcc +zx -lndos -create-app csprite.c
	              - or -
	              zcc +zx -lndos -create-app -Dlr64x48 csprite.c

	$Id: csprite.c,v 1.2 2007/01/17 19:32:50 stefano Exp $
*/


//#define lr64x48  1

#include <stdio.h>
#include <zxlowgfx.h>

extern char mysprite[];

// sprite generated by Daniel McKinnon's z88dk Sprite Editor
char hello[] = { 20, 6, 0x90 , 0x24 , 0x00 , 0x93 , 0x24 , 0x60 , 0xF4 , 0xA4 , 0x90 , 0x97 , 0x24 
, 0x90 , 0x94 , 0x24 , 0x90 , 0x93 , 0x92 , 0x60  };

char chesspiece[] = { 21, 23, 0x00 , 0x00 , 0x00 , 0x3D , 0xF7 , 0x80 , 0x25 , 0x14 , 0x80 , 0x25 , 0x14 
, 0x80 , 0x27 , 0x1C , 0x80 , 0x20 , 0x00 , 0x80 , 0x18 , 0x03 , 0x00 , 0x04 
, 0x04 , 0x00 , 0x04 , 0x04 , 0x00 , 0x04 , 0x84 , 0x00 , 0x04 , 0x84 , 0x00 
, 0x04 , 0x04 , 0x00 , 0x04 , 0x84 , 0x00 , 0x04 , 0x84 , 0x00 , 0x04 , 0x84 
, 0x00 , 0x04 , 0x84 , 0x00 , 0x08 , 0x82 , 0x00 , 0x11 , 0x01 , 0x00 , 0x20 
, 0x00 , 0x80 , 0x40 , 0x00 , 0x40 , 0x40 , 0x00 , 0x40 , 0x7F , 0xFF , 0xC0 
, 0x00 , 0x00 , 0x00 };
 

// You have two ways to define a sprite; this one is done with the built-in assembler	
#asm

._mysprite
 defb    8,6
 defb    @10000001
 defb    @01011010
 defb    @00100100
 defb    @00100100
 defb    @01011010
 defb    @10000001

#endasm

void main()
{

	cclg(1);  // Blue background

	cputsprite(4,15,2,chesspiece);
	cputsprite(5,14,3,chesspiece);
	cputsprite(6,14,2,chesspiece);

	cputsprite(0,1,0,hello);
	cputsprite(2,0,0,hello);

	cputsprite(0,10,11,mysprite);
	cputsprite(3,9,11,mysprite);

}

