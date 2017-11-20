// Author: Cyle Riggs (@beardedfoo)
// This program for the Sega Genesis/Megadrive demonstrates the
// most basic use the VDP tile subsystem by displaying a solid box
// on the screen. The buttons on the Player 1 gamepad (A/B/C/X/Y/Z)
// are used to set the color of box to be displayed.
#include <genesis.h>

// This program loads tiles into the VDP one at a time
#define LOAD_TILE_COUNT 1

// Disable the use of DMA for tile loading
#define LOAD_TILE_WITH_DMA FALSE

// Place the tile at coordinates 10,13 on a grid of 40x28 tiles
#define COORD_X 10
#define COORD_Y 13

// Define tile A as a solid block of color from palette entry 1
#define VRAM_POS_TILE_A 1
const u32 TILE_A[8] =
{
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
};

// Define tile B as a solid block of color from palette entry 2
#define VRAM_POS_TILE_B 2
const u32 TILE_B[8] =
{
	0x22222222,
  0x22222222,
  0x22222222,
  0x22222222,
  0x22222222,
  0x22222222,
  0x22222222,
  0x22222222,
};

// Define tile C as a solid block of color from palette entry 3
#define VRAM_POS_TILE_C 3
const u32 TILE_C[8] =
{
  0x33333333,
  0x33333333,
  0x33333333,
  0x33333333,
  0x33333333,
  0x33333333,
  0x33333333,
  0x33333333,
};

// Define tile X as a solid block of color from palette entry 4
#define VRAM_POS_TILE_X 4
const u32 TILE_X[8] =
{
  0x44444444,
  0x44444444,
  0x44444444,
  0x44444444,
  0x44444444,
  0x44444444,
  0x44444444,
  0x44444444,
};

// Define tile Y as a solid block of color from palette entry 5
#define VRAM_POS_TILE_Y 5
const u32 TILE_Y[8] =
{
  0x55555555,
  0x55555555,
  0x55555555,
  0x55555555,
  0x55555555,
  0x55555555,
  0x55555555,
  0x55555555,
};

// Define tile Z as a solid block of color from palette entry 6
#define VRAM_POS_TILE_Z 6
const u32 TILE_Z[8] =
{
  0x66666666,
  0x66666666,
  0x66666666,
  0x66666666,
  0x66666666,
  0x66666666,
  0x66666666,
  0x66666666,
};

// On the mega drive VDP the CRAM (Color RAM) stores 4 palettes.
// Palettes provide a selection of colors which can be referenced
// by pixel data in tiles. Each tile can be assigned to a palette
// and each nibble in the tiles assign the specified color from the
// palette to that pixel.
//
// Each of the 16 (0-F) entries in the palette is an encoded 9-bit
// RGB color. The colors are specified in the format of:
// 0000BBBSGGGSRRRS (B=blue, G=green, R=red, S=shadow)
//
// The first four bits of the color are unused, followed by a 3-bit
// value for blue, a shadow bit, a 3-bit value for green, another
// shadow bit, a 3-bit value for red, and finally another shadow
// bit. Conveniently this aligns to nibbles and allows the colors
// to be specified in the following hex value format:
// 0xBGR - one hex digit for each color (B=blue, G=green, R=red)
//
// Ignoring the shadow bits the following are valid values for
// each color nibble: 0, 2, 4, 6, 8, A, C, E
// The lower the value that is specified for a color the less
// intense that color will be represented.
//
// Using these values for R, G, and B allows a possible 512 colors
// for each entry in the palette.
//
// The first entry in a palette has the special purpose of providing
// a value for transparency and should usually be used for black.
const u16 palette_basic[16] = {
  0x000, // color 0 = black
  0x00E, // color 1 = red
  0x0E0, // color 2 = green
  0xE00, // color 3 = blue
  0xEE0, // color 4 = cyan
  0x0EE, // color 5 = yellow
  0xE0E, // color 6 = magenta

  // Rest of the palette is unused in this application
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
};

// Select the tile to show based on gamepad input
u16 select_tile = NULL;
void joyHandler(u16 joy, u16 changed, u16 state) {
  // Ignore input from anything except player one
  if (joy != JOY_1) {
    return;
  }

  // Choose a tile to display based on the current input
  if (state & BUTTON_A) {
    select_tile = VRAM_POS_TILE_A;
  } else if (state & BUTTON_B) {
    select_tile = VRAM_POS_TILE_B;
  } else if (state & BUTTON_C) {
    select_tile = VRAM_POS_TILE_C;
  } else if (state & BUTTON_X) {
    select_tile = VRAM_POS_TILE_X;
  } else if (state & BUTTON_Y) {
    select_tile = VRAM_POS_TILE_Y;
  } else if (state & BUTTON_Z) {
    select_tile = VRAM_POS_TILE_Z;
  }
}

int main()
{
  // Setup the video chip
  VDP_init();

  // Setup gamepad input handling
  JOY_init();
  JOY_setEventHandler(&joyHandler);

  // Load the tile data into the video chip (one at a time)
  VDP_loadTileData(TILE_A, VRAM_POS_TILE_A, LOAD_TILE_COUNT, LOAD_TILE_WITH_DMA);
  VDP_loadTileData(TILE_B, VRAM_POS_TILE_B, LOAD_TILE_COUNT, LOAD_TILE_WITH_DMA);
  VDP_loadTileData(TILE_C, VRAM_POS_TILE_C, LOAD_TILE_COUNT, LOAD_TILE_WITH_DMA);
  VDP_loadTileData(TILE_X, VRAM_POS_TILE_X, LOAD_TILE_COUNT, LOAD_TILE_WITH_DMA);
  VDP_loadTileData(TILE_Y, VRAM_POS_TILE_Y, LOAD_TILE_COUNT, LOAD_TILE_WITH_DMA);
  VDP_loadTileData(TILE_Z, VRAM_POS_TILE_Z, LOAD_TILE_COUNT, LOAD_TILE_WITH_DMA);

  // Load the color palette as palette 0
  VDP_setPalette(PAL0, palette_basic);

  // Load different tiles on screen as buttons are pressed
  while(1)
  {
    // Wait for the VDP to finish drawing the frame so that screen
    // updates work as expected.
    VDP_waitVSync();

    // Watch `select_tile` for choices made by the user and present
    // the selected tile on the screen. The variable `select_tile`
    // will be filled with one of VRAM_POS_TILE_{A,B,C,X,Y,Z} by the
    // gamepad input handling function. This will in turn change
    // the color of block displayed on the screen.
    if (select_tile != NULL) {
      VDP_setTileMapXY(PLAN_A, select_tile, COORD_X, COORD_Y);
      select_tile = NULL;
    }
  }
}
