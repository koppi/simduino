#ifndef LCD_SIM_H
#define LCD_SIM_H

#include <string>

#include <Arduino.h>

#include <sim_sdl.hpp>

extern TTF_Font *sdl_font;

#define var uint8_t

#define RANGE 32

#define ADDR_DDRAM 0
#define ADDR_CGRAM 1

#define DDRAM_LENGTH 104
#define CGRAM_LENGTH 64

class LCD_SIM {
  class Doc {
	
  public:
	class Img {
	};

	Img pix[32];
	Img pixBlank;

	Img b[10];

	var p[RANGE];
	var d[8];  // FIXME 8 corrrect?

  };

  Doc doc;

  char chrtbl[256][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{4, 4, 4, 4, 4, 0, 4},
	{10,10,10, 0, 0, 0, 0},
	{10,10,31,10,31,10,10},
	{4,15,20,14, 5,30, 4},
	{24,25, 2, 4, 8,19, 3},
	{12,18,20, 8,21,18,13},
	{12, 4, 8, 0, 0, 0, 0},
	{2, 4, 8, 8, 8, 4, 2},
	{8, 4, 2, 2, 2, 4, 8},
	{0, 4,21,14,21, 4, 0},
	{0, 4, 4,31, 4, 4, 0},
	{0, 0, 0, 0,12, 4, 8},
	{0, 0, 0,31, 0, 0, 0},
	{0, 0, 0, 0, 0,12,12},
	{0, 1, 2, 4, 8,16, 0},
	{14,17,19,21,25,17,14},
	{4,12, 4, 4, 4, 4,14},
	{14,17, 1, 2, 4, 8,31},
	{31, 2, 4, 2, 1,17,14},
	{2, 6,10,18,31, 2, 2},
	{31,16,30, 1, 1,17,14},
	{6, 8,16,30,17,17,14},
	{31, 1, 2, 4, 8, 8, 8},
	{14,17,17,14,17,17,14},
	{14,17,17,15, 1, 2,12},
	{0,12,12, 0,12,12, 0},
	{0,12,12, 0,12, 4, 8},
	{2, 4, 8,16, 8, 4, 2},
	{0, 0,31, 0,31, 0, 0},
	{16, 8, 4, 2, 4, 8,16},
	{14,17, 1, 2, 4, 0, 4},
	{14,17, 1,13,21,21,14},
	{14,17,17,17,31,17,17},
	{30,17,17,30,17,17,30},
	{14,17,16,16,16,17,14},
	{30,17,17,17,17,17,30},
	{31,16,16,30,16,16,31},
	{31,16,16,30,16,16,16},
	{14,17,16,23,17,17,15},
	{17,17,17,31,17,17,17},
	{14, 4, 4, 4, 4, 4,14},
	{7, 2, 2, 2, 2,18,12 },
	{17,18,20,24,20,18,17},
	{16,16,16,16,16,16,31},
	{17,27,21,21,17,17,17},
	{17,17,25,21,19,17,17},
	{14,17,17,17,17,17,14},
	{30,17,17,30,16,16,16},
	{14,17,17,17,21,18,13},
	{30,17,17,30,20,18,17},
	{15,16,16,14, 1, 1,30},
	{31, 4, 4, 4, 4, 4, 4},
	{17,17,17,17,17,17,14},
	{17,17,17,17,17,10, 4},
	{17,17,17,21,21,21,10},
	{17,17,10, 4,10,17,17},
	{17,17,17,10, 4, 4, 4},
	{31, 1, 2, 4, 8,16,31},
	{14, 8, 8, 8, 8, 8,14},
	{17,10,31, 4,31, 4, 4},
	{14, 2, 2, 2, 2, 2,14},
	{4,10,17, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0,31},
	{8, 4, 2, 0, 0, 0, 0},
	{0, 0,14, 1,15,17,15},
	{16,16,22,25,17,17,30},
	{0, 0,14,16,16,17,14 },
	{1, 1,13,19,17,17,15},
	{0, 0,14,17,31,16,14},
	{6, 9, 8,28, 8, 8, 8},
	{0, 0,15,17,15, 1,14},
	{16,16,22,25,17,17,17},
	{4, 0,12, 4, 4, 4,14 },
	{2, 6, 2, 2, 2,18,12},
	{16,16,18,20,24,20,18},
	{12, 4, 4, 4, 4, 4,14},
	{0, 0,26,21,21,17,17},
	{0, 0,22,25,17,17,17},
	{0, 0,14,17,17,17,14},
	{0, 0,30,17,30,16,16},
	{0, 0,13,19,15, 1, 1},
	{0, 0,22,25,16,16,16},
	{0, 0,15,16,14, 1,30},
	{8, 8,28, 8, 8, 9, 6},
	{0, 0,17,17,17,19,13},
	{0, 0,17,17,17,10, 4},
	{0, 0,17,17,21,21,10},
	{0, 0,17,10, 4,10,17},
	{0, 0,17,17,15, 1,14},
	{0, 0,31, 2, 4, 8,31},
	{2, 4, 4, 8, 4, 4, 2},
	{4, 4, 4, 4, 4, 4, 4},
	{8, 4, 4, 2, 4, 4, 8},
	{0, 4, 2,31, 2, 4, 0},
	{0, 4, 8,31, 8, 4, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0,28,20,28},
	{7, 4, 4, 4, 0, 0, 0},
	{0, 0, 0, 4, 4, 4,28},
	{0, 0, 0, 0,16, 8, 4},
	{0, 0, 0,12,12, 0, 0},
	{0,31, 1,31, 1, 2, 4},
	{0, 0,31, 1, 6, 4, 8},
	{0, 0, 2, 4,12,20, 4},
	{0, 0, 4,31,17, 1, 6},
	{0, 0, 0,31, 4, 4,31},
	{0, 0, 2,31, 6,10,18},
	{0, 0, 8,31, 9,10, 8},
	{0, 0, 0,14, 2, 2,31},
	{0, 0,30, 2,30, 2,30},
	{0, 0, 0,21,21, 1, 6},
	{0, 0, 0, 0,31, 0, 0},
	{31, 1, 5, 6, 4, 4, 8},
	{1, 2, 4,12,20, 4, 4},
	{4,31,17,17, 1, 2, 4},
	{0, 0,31, 4, 4, 4,31},
	{2,31, 2, 6,10,18, 2},
	{8,31, 9, 9, 9, 9,18},
	{4,31, 4,31, 4, 4, 4},
	{0,15, 9,17, 1, 2,12},
	{8,15,18, 2, 2, 2, 4},
	{0,31, 1, 1, 1, 1,31},
	{10,31,10,10, 2, 4, 8},
	{0,24, 1,25, 1, 2,28},
	{0,31, 1, 2, 4,10,17},
	{8,31, 9,10, 8, 8, 7},
	{0,17,17, 9, 1, 2,12},
	{0,15, 9,21, 3, 2,12},
	{2,28, 4,31, 4, 4, 8},
	{0,21,21, 1, 1, 2, 4},
	{14, 0,31, 4, 4, 4, 8},
	{8, 8, 8,12,10, 8, 8},
	{4, 4,31, 4, 4, 8,16},
	{0,14, 0, 0, 0, 0,31},
	{0,31, 1,10, 4,10,16},
	{4,31, 2, 4,14,21, 4},
	{2, 2, 2, 2, 2, 4, 8},
	{0, 4, 2,17,17,17,17},
	{16,16,31,16,16,16,15},
	{0,31, 1, 1, 1, 2,12},
	{0, 8,20, 2, 1, 1, 0},
	{4,31, 4, 4,21,21, 4},
	{0,31, 1, 1,10, 4, 2},
	{0,14, 0,14, 0,14, 1},
	{0, 4, 8,16,17,31, 1},
	{0, 1, 1,10, 4,10,16},
	{0,31, 8,31, 8, 8, 7},
	{8, 8,31, 9,10, 8, 8},
	{0,14, 2, 2, 2, 2,31},
	{0,31, 1,31, 1, 1,31},
	{14, 0,31, 1, 1, 2, 4},
	{18,18,18,18, 2, 4, 8},
	{0, 4,20,20,21,21,22},
	{0,16,16,17,18,20,24},
	{0,31,17,17,17,17,31},
	{0,31,17,17, 1, 2, 4},
	{0,24, 0, 1, 1, 2,28},
	{4,18, 8, 0, 0, 0, 0},
	{28,20,28, 0, 0, 0, 0},
	{0, 0, 9,21,18,18,13 },
	{10, 0,14, 1,15,17,15},
	{0,14,17,30,17,30,16},
	{0, 0,14,16,12,17,14},
	{0,17,17,17,19,29,16},
	{0, 0,15,20,18,17,14},
	{0, 6, 9,17,17,30,16},
	{0,15,17,17,17,15, 1},
	{0, 0, 7, 4, 4,20, 8},
	{2,26, 2, 0, 0, 0, 0},
	{2, 0, 6, 2, 2, 2, 2},
	{0,20, 8,20, 0, 0, 0},
	{4,14,20,21,14, 4, 0},
	{8, 8,28, 8,28, 8,15},
	{14, 0,22,25,17,17,17},
	{10, 0,14,17,17,17,14},
	{0,22,25,17,17,30,16},
	{0,13,19,17,17,15, 1 },
	{14,17,31,17,17,14, 0},
	{0, 0, 0, 0,11,21,26 },
	{0,14,17,17,10,27, 0},
	{10, 0,17,17,17,19,13},
	{31,16, 8, 4, 8,16,31},
	{0,31,10,10,10,19, 0 },
	{31, 0,17,10, 4,10,17},
	{0,17,17,17,17,15, 1},
	{1,30, 4,31, 4, 4, 0},
	{0,31, 8,15, 9,17, 0},
	{0,31,21,31,17,17, 0 },
	{0, 0, 4, 0,31, 0, 4 },
	{0, 0, 0, 0, 0, 0, 0 },
	{31,31,31,31,31,31,31}
  };

  /******************* instructions *************************/
  /**********************************************************/
  // LCD Command "Set Display Data RAM Address" = 10000000
  var instrSetDDRAMadrs  = 0x80;
  var maskSetDDRAMadrs = 0x80;

  //LCD Command "Set Display Character Generator RAM Address" = 01aaaaaa
  var instrSetCGRAMadrs  = 0x40;
  var maskSetCGRAMadrs = 0xc0;

  // LCD Command Function Set =  001dnfxx
  // d = 1 for 8-bit interface or 0 for 4-bit interface
  // n = for 2 line displays, n=1 allows both lines to be displayed
  // while n=0 only allows the first.
  // f = font size. f=1 is for 5x11 dots while f=0 is for 5x8 dots.
  var instrFuncSet   = 0x20;     // LCD Command "Function Set"
  var maskFuncSet  = 0xe0;     // 
  var eithtBitMode     = 0x10;    // d=1, if d=0 4 bit mode
  var twoLines       = 0x08;    // n=1, if d=0 8 bit mode 
  var largeFont    = 0x04;    // f=1 if f=0 large font

  // LCD Command "Cursor Display" = 0 0 0 1 SC RL x x
  // SC = 1 Sets cursor-move or display-shift
  // RL = 1 Shift right 0 = shift left
  var instrCursorDisplay   = 0x10;   // LCD Command "Cursor Display"
  var maskCursorDisplay  = 0xf0;   // 
  var shiftOrCursorMove = 0x8;
  var rightLeft = 0x4;
	
  //LCD Command "Entry Mode" = 000001is
  // i = 1 to increment or 0 to decrement the DDRAM address after each DDRAM access.
  // s = 1 to scroll the display in the direction specified by the i-bit when the
  //      cursor reaches the edge of the display window.
  var instrEntryMode  = 0x04;    // LCD Command "Entry Mode"
  var maskEntryMode = 0xfc;    // 
  var incCursorPos  = 0x02;    // i=1 if i=0 decrement
  
  var scrollDisp        = 0x01;    // s=1 if s=0 no scrolling
  
  // LCD Command Display Control = 00001dcb
  // d = 1 turn display on or 0 to turn display off
    // c = 1 turn cursor on or 0 to turn cursor off
  // b = 1 blinking cursor or 0 non-blinking cursor
  var instrDisplayCtrl   = 0x08;     // LCD Command "Display Control"
  var maskDisplayCtrl  = 0xf8;     // 
  var displayOn        = 0x04;    // d=1
  var cursorOn         = 0x02;    // c=1
  var blinkOn          = 0x01;    // b=1

  //LCD Command "Cursor Home" = 0000001x
  var instrCursorHome   = 0x02;   // LCD Command "Cursor Home"
  var maskCursorHome  = 0xfe;   // 

  // LCD Command Clear Display = 00000001
  var instrClearDisplay  = 0x01;
  var maskClearDisplay = 0xff;

  /**********************************************************/
  /****************** instructions end **********************/

  var *ddram;
  var *cgram;

  var lastAdrsSet;

  var AC    = 0;
  var range = 16;

  var DL = 1;     // 8-bit interface data
  var N  = 0;     // 1-line display
  var F  = 0;     // 5x8 dot char font

  var D  = 0;     // Display off
  var C  = 0;     // Cursor off
  var B  = 0;     // Blinking off

  var ID = 1;     // increment by 1
  var S  = 0;
  
  var RL = 1;     // cursor command
  var SC = 0;     // shift  command

  var adrs = 1;
  var chr  = 0;
  var* currDispChrs[32];
  var shiftChars = 0;

 public:
  LCD_SIM();

  void reset();

 protected:

  void ln2Off();
  void ln2On();

  var dispBlanked = 0;

  var prevDDRAMadrCursAt = 0;
  var cursPos = 0;
  var cursOutOfDisp = 0;
  var undCursClrd = 0;

  var blinked = 0;
  var blinkChar = 0x20;
  var undCntr = 0;

  void initCurrDispChrs();
  void updateDisp();
  void updateStats();
  void blankDisp();
  void setCurrDispChrs();
  
  void setDDRadrs(var address);
  void incdcrDDRadrs(var incordcr);
  void incdcrCGRadrs(var incordcr);
  void updateUndCurs();

 public:
  void lcd(var data, var eGoLow, var rwState, var rsState);
  void blink_callback(void); // should be called 250msec

 protected:
  void clearMsgs(void);

  void writeData(var data);
  void cgramChanged();
  void evalInstr(var instr);
  void instrPeek(var instr);
  void instrpeek(var instr);
  
  void pchr(var chrnum , var _pos);

  var rwState = 0;
  var rsState = 0;

  var upNib = 0;
  var lowNib = 0;
  var gotUpNib = 0;

  void addMsg(const char* msg);
  void addMsgf(const char* fmt, ...);

  std::string messages;

#ifdef HAVE_SDL
 public:
  void sdl_init();
  void sdl_draw(SDL_Surface *s, int x, int y);
  SDL_Surface *sdl_text( TTF_Font *font, const std::string &text, const SDL_Color &fg, const SDL_Color &bg);
#endif
  
};

#endif
