/* ----------------------------------------------------------------
 * NIRVANA ENGINE DEMO - converted to z88dk C Compiler
 *
 * This program can be compiled as follows:
 *
 * 1. SCCZ80 + New C Library
 *
 *    zcc +zx -vn -startup=1 -clib=new nirvanadem.c btile.asm -o nirvanadem
 *    appmake +zx -b nirvanadem_CODE.bin -o nirvanadem.tap --noloader --org 32768 --blockname nirvanadem
 *    copy /B loader.tap+nirvanadem.tap demo.tap
 *
 * 2. SDCC + New C Library
 *
 *    zcc +zx -vn -SO3 -startup=1 -clib=sdcc_ix --reserve-regs-iy --max-allocs-per-node200000 nirvanadem.c btile.asm -o nirvanadem
 *    appmake +zx -b nirvanadem_CODE.bin -o nirvanadem.tap --noloader --org 32768 --blockname nirvanadem
 *    copy /B loader.tap+nirvanadem.tap demo.tap
 *
 * After compiling, a binary "nirvanadem_CODE.bin" containing the program is produced.
 * appmake is run to turn that portion into a CODE-only tap file.
 * Windows "copy" is used to concatenate that tap to the end of "loader.tap" to form the final tap file "demo.tap"
 *
 * "loader.tap" contains this basic loader:
 *
 * 10 CLEAR VAL "32767"
 * 20 LOAD "NIRVANA+"CODE
 * 30 LOAD ""CODE
 * 40 RANDOMIZE USR VAL "32768"
 *
 * followed by the NIRVANA+ engine code.  This engine code is supplied separately from z88dk (and is contained in this tap file).
 *
 * Thanks to Timmy for the first conversion to C of this demo.
 *
 * ----------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <input.h>
#include <arch/zx.h>
#include <arch/zx/nirvana-.h>

#pragma output CLIB_OPT_PRINTF       = 0x00000400   // enable %c for printf only

#pragma output CLIB_MALLOC_HEAP_SIZE = 0            // do not create a heap
#pragma output REGISTER_SP           = -1           // do not change sp

#define printInk(k)          printf("\x10%c", (k))
#define printPaper(k)        printf("\x11%c", (k))
#define printAt(row, col)    printf("\x16%c%c", (col), (row))

extern unsigned char btiles[];

const unsigned char pos[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0,
                              0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0,
                              0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0,
                              0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0,
                              0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0,
                              0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0,
                              0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char dlin[8], dcol[8];
unsigned char lin, col, tile, sprite, counter;
unsigned char *addr;

main()
{
    // Initialize screen
    zx_border(0);
    zx_cls(9);

    printPaper(1);
    printInk(7);
    printAt(0, 9);
    printf("NIRVANA ENGINE");
    printAt(23, 6);
    printf("(c)2013 Einar Saukas");

    // Set btiles address
    NIRVANAM_tiles(btiles);

    // Activate NIRVANA ENGINE
    NIRVANAM_start();

    for (;;) {

        // Draw or erase tiles on screen until key is pressed
        do {
            lin = ((rand()%11)<<4)+16;                      // random values 16,32,..,176
            col = ((rand()%15)<<1)+1;                       // random values 1,3,5,..,29
            if (pos[(lin-16)+(col>>1)] > 0) {
                NIRVANAM_halt();
                NIRVANAM_drawT(8, lin, col);
            } else if (rand()&1) {
                NIRVANAM_halt();
                NIRVANAM_drawT(rand()&7, lin, col);
            } else {
                NIRVANAM_halt();
                NIRVANAM_fillT(0, lin, col);
            }
        } while (!in_test_key());  // test if a key is pressed, smaller than in_inkey()

        // Wait until key is released
        in_wait_nokey();

        // Erase all tiles
        for (lin = 16; lin != 192; lin += 16) {
            NIRVANAM_halt();
            for (col = 1; col != 31; col+=2) {
                NIRVANAM_fillT(0, lin, col);
            }
        }

        // Initialize sprites randomly
        for (sprite = 0; sprite != 8; sprite++) {
            lin = ((rand()%95)<<1)+2;                       // random values 2,4,..,190
            col = (rand()%29)+1;                            // random values 1,2,..,29
            dlin[sprite] = ((rand()%2)<<2)-2;               // random values -2,2
            dcol[sprite] = (rand()%3)-1;                    // random values -1,0,1
            NIRVANAM_halt();
            NIRVANAM_spriteT(sprite, sprite, lin, col);
        }

        // Move sprites on screen until key is pressed
        do {
            counter++;
            for (sprite = 0; sprite < 8; sprite++) {
                lin = *SPRITELIN(sprite);
                col = *SPRITECOL(sprite);
                tile = *SPRITEVAL(sprite);
                if (sprite == 0 || sprite == 3 || sprite == 6)
                    NIRVANAM_halt();
                NIRVANAM_fillT(0, lin, col);
                lin += dlin[sprite];
                col += dcol[sprite];
                if ((counter & 7) == sprite)
                    tile ^= 1;
                NIRVANAM_spriteT(sprite, tile, lin, col);
                if (lin == 0 || lin == 192)
                    dlin[sprite] = -dlin[sprite];
                if (col == 0 || col == 30)
                    dcol[sprite] = -dcol[sprite];
            }
        } while (!in_test_key());  // test if a key is pressed, smaller than in_inkey()

        // Wait until key is released
        in_wait_nokey();

        // Erase and hide sprites (moving each sprite to line zero)
        NIRVANAM_halt();
        for (sprite = 0; sprite < 8; sprite++) {
            lin = *SPRITELIN(sprite);
            col = *SPRITECOL(sprite);
            *SPRITELIN(sprite) = 0;
            NIRVANAM_fillT(0, lin, col);
        }
    }
}
