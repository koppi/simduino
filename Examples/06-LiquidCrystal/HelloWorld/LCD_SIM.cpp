#include "LCD_SIM.h"

#include <string>

LCD_SIM::LCD_SIM() {
  reset();
}

void LCD_SIM::reset() {
  debug("");

  ddram = new var[DDRAM_LENGTH];
  cgram = new var[CGRAM_LENGTH];
  
  lastAdrsSet = ADDR_DDRAM;

  AC  = 0;
  
  // function set
  DL = 1;
  N  = 0;
  F  = 0;
  
  // display control
  D  = 1;
  C  = 1;
  B  = 1;
  
  // entry mode
  ID = 1;
  S  = 0;
  range = 16;
  
  // reset state
  for (int i = 0; i < DDRAM_LENGTH; i++) {
	ddram[i] = 20;
  }
  
  for (int i = 0; i < CGRAM_LENGTH; i++) {
	cgram[i] = 0;
  }
  
  for (var i = 0; i < 8; i++) {
	for (var j = 0; j < 8; j++) {
	  chrtbl[i][j] = 0;
	}
  }
  
  shiftChars = 0;
  
  initCurrDispChrs();
  
  ln2Off();
  
  updateDisp();
  
  updateStats();
}

void LCD_SIM::blink_callback(void)
{
  if (B == 0 || D == 0 || cursOutOfDisp == 1) {
	if (blinked == 1 && cursPos < range && cursOutOfDisp == 0) {
	  pchr(blinkChar, cursPos);
	  blinked = 0;
	  if (C == 1 && cursOutOfDisp == 0) {
		doc.p[cursPos * 8 + 7] = 31;
	  }
	}
	return;
  }

  if (blinked == 1) {
	pchr(blinkChar, cursPos);
	blinked = 0;
	if (C == 1 && cursOutOfDisp == 0) {
	  doc.p[cursPos * 8 + 7] = 31;
	}
  } else {
	pchr(255, cursPos);
	doc.p[cursPos * 8 + 7] = 31;
	blinked = 1;
  }
}

void LCD_SIM::initCurrDispChrs() {
  // debug("");

  for (var i = 0; i < 16; i++) {
	currDispChrs[i] = new var[2];
	currDispChrs[i][chr] = 0x20;
	currDispChrs[i][adrs] = i;
  }
  
  for (var i = 16; i < 32; i++) {
	currDispChrs[i] = new var[2];
	currDispChrs[i][chr] = 0x20;
	currDispChrs[i][adrs] = 48 + i;
  }
}

void LCD_SIM::blankDisp() {
  // debug("");

  for (int i = 0; i < range * 8; i++) {
	doc.p[i] = 0;
  }
}

void LCD_SIM::ln2On() {
  // debug("");

  for (int i = 128; i < 256; i++) {
	doc.p[i] = 0;
  }
}

void LCD_SIM::ln2Off() {
  // debug("");

  for (int i = 128; i < 256; i++) {
	doc.p[i] = 32;
  }
}

void LCD_SIM::updateDisp() {
  // debug("");

  setCurrDispChrs();
  
  if (D == 0) {
	if (dispBlanked != 1) {
	  blankDisp();
	}
	return;
  }
  
  if (N == 0) {
	if (shiftChars > 79 || shiftChars < -79) {
	  shiftChars = 0;
	} 
  } else {
	if (shiftChars > 39 || shiftChars < -39) {
	  shiftChars = 0;
	}
  }
  
  if (N == 0) {
	for (var ln = 0; ln < 16; ln++) {
	  if (currDispChrs[ln][chr] != ddram[currDispChrs[ln][adrs]]) {
		pchr(ddram[currDispChrs[ln][adrs]],ln);
		currDispChrs[ln][chr] = ddram[currDispChrs[ln][adrs]];
	  }
	}
  } else {
	for (var ln = 0; ln < 32; ln++) {
	  if (currDispChrs[ln][chr] != ddram[currDispChrs[ln][adrs]]) {
		pchr(ddram[currDispChrs[ln][adrs]],ln);
		currDispChrs[ln][chr] = ddram[currDispChrs[ln][adrs]];
	  }
	}
  }
  
  // these are to clear the cursor trace in case of LCD scroll
  pchr(currDispChrs[0][chr],   0);
  pchr(currDispChrs[15][chr], 15);
  
  if (range == 32) {
	pchr(currDispChrs[16][chr], 16);
	pchr(currDispChrs[31][chr], 31);
  }
  
  updateUndCurs();
}

void LCD_SIM::setCurrDispChrs() {
  // debug("");

  if (N == 0) {
	for (var i = 0; i < 16; i++) {
	  currDispChrs[i][adrs] = (i + 80 + shiftChars) % 80; // adrs
	}
  } else {
	for (var i = 0; i < 16; i++) {
	  currDispChrs[i][adrs]= (i + 40 + shiftChars) % 40; // adrs
	}
	
	for (var i = 16; i < 32; i++) {
	  if (shiftChars < 0) {
		currDispChrs[i][adrs]= (i + 40 + shiftChars + 48); //adrs
		if (currDispChrs[i][adrs] > 103)
		  currDispChrs[i][adrs] = (currDispChrs[i][adrs] % 104) + 64;
	  } else {
		currDispChrs[i][adrs]= i  + shiftChars + 48; //adrs
		if (currDispChrs[i][adrs] > 103)
		  currDispChrs[i][adrs] = (currDispChrs[i][adrs] % 104) + 64;
	  }
	}
  }
}

void LCD_SIM::setDDRadrs(var address) {
  // debugf("%d", address);

  AC = address;
  
  if (N==0) {
	if (AC > 79) {
	  AC = 0;
	}
  } else {
	if (AC > 64) {
	}
	
	if (AC > 39 && AC < 64) {
	  AC = 64;
	}
	
	if (AC > 103) {
	  AC = 0;
	}
  }
  
  updateUndCurs();
}

void LCD_SIM::incdcrDDRadrs(var incordcr) {
  // debugf("%d", incordcr);

  // alert("ddradrs decreasing !" + AC)
  
  if (N == 0) {
	AC += incordcr;
	if (AC < 0) { AC = 79; }
	
	AC %= 80;
  } else {
	AC += incordcr;
	if (AC < 0) {
	  AC = 103;
	}
	
	if (AC > 39 && AC < 64) {
	  AC = 64;
	}
	
	if (AC > 103) {
	  AC = 0;
	}
  }
  
  // if(AC < 0 || (AC > 39 && AC < 64) || AC >= 104){alert("AC invalid !!!! >>>>"+ AC)}
}

void LCD_SIM::incdcrCGRadrs(var incordcr) {
  // debugf("%d", incordcr);

  AC += incordcr;
  
  if (AC-64 < 0)  { AC = 63; }
  if (AC-64 > 63) { AC =  0; }
}

void LCD_SIM::updateStats() {
  // debug("");

  clearMsgs();

  cursOutOfDisp = 1;
  
  for (int i = 0; i < range; i++) {
	if (currDispChrs[i][adrs] == AC) {
	  cursOutOfDisp = 0;
	}
  }

  addMsg("\n \nStats:\n \n");

  if (D == 1) {
	addMsg(" Display On.\n");
  } else {
	addMsg(" Display Off.\n");
  }
  
  if (cursOutOfDisp == 1) {
	addMsg(" Cursor is invisible.\n");
  } else {
	addMsg(" Cursor is visible.\n");
  }
  
  if (ID == 1) {
	addMsg(" Increase Cursor Position On.\n");
  } else {
	addMsg(" Increase Cursor Position Off.\n");
  }
  
  if (S == 1) {
	addMsg(" Scroll On.\n");
  } else {
	addMsg(" Scroll Off.\n");
  }
  
  if (lastAdrsSet == ADDR_CGRAM) {
	addMsgf(" AC points to CGRAM addr: 0x%02x\n", (AC-64));
  } else {
	addMsgf(" AC points to DDRAM addr: 0x%02x\n", AC);
  }
  
  if (C == 0 && B == 0) {
	addMsg(" Cursor Off.\n");
  } else {
	if (C == 1 && B == 1) {
	  addMsg(" Cursor On, blinking.\n");
	}
	if (C == 0 && B == 1) {
	  addMsg(" Cursor blinking.\n");
	}
	if (C == 1 && B == 0) {
	  addMsg(" Cursor On.\n");
	}
  }
  
  addMsgf(" Line 1 addr: 0x%02x, 0x%02x\n", currDispChrs[0][adrs], currDispChrs[16][adrs]);

  if (N == 1) {
	addMsgf(" Line 2 addr: 0x%02x, 0x%02x\n", currDispChrs[16][adrs],currDispChrs[31][adrs]);
  } else {
	addMsgf(" Line 2 addr: ----, ----\n");
  }
  
}

void LCD_SIM::updateUndCurs() {
  cursOutOfDisp = 1;
  
  if (D == 1) {
	for (int i = 0; i < range; i++) {
	  if (currDispChrs[i][adrs] == prevDDRAMadrCursAt) {
		pchr(ddram[currDispChrs[cursPos][adrs]], cursPos);
	  }
	}
  } else if (D == 0 || (C == 0 && B == 0)) {
	doc.p[cursPos * 8 + 7] = 0;
	return;
  }
  
  for (int i = 0; i < range; i++) {
	if (currDispChrs[i][adrs] == AC) {
	  prevDDRAMadrCursAt = AC;
	  cursPos = i;
	  blinkChar = currDispChrs[i][chr];
	  cursOutOfDisp = 0;
	}
  }
  
  if (C == 1 && cursOutOfDisp == 0) {
	doc.p[cursPos * 8 + 7] = 31;
	undCursClrd = 0;
  }
}

void LCD_SIM::lcd(var data, var eGoLow, var rwState, var rsState) {
  // debugf("0x%02x, %d, %d, %d", data, eGoLow, rwState, rsState);
  
  // E goes LOW, this is when instructions are evaluated, chars written
  if (eGoLow == 1) {
	
	if (rsState == 0 & rwState == 0) {
	  // debug("write to IR, \n evaluate instruction");
	  
	  if (DL == 1) {
		evalInstr(data);
	  } else {
		if (gotUpNib == 0) {
		  upNib = data;
		  gotUpNib = 1;
		  
		  // TODO instrpeek(instr);
		} else {
		  lowNib = data;
		  gotUpNib = 0;
		  evalInstr((upNib << 4) | lowNib);
		}
	  }
	}
	
	if (rsState == 1 & rwState == 0) {
	  // debug("write to DR, print character\n");
	  if (DL == 1) {
		writeData(data);
	  } else {
		if (gotUpNib == 0) {
		  upNib = data;
		  gotUpNib = 1;
		  // TODO instrpeek(instr);
		} else {
		  lowNib = data;
		  gotUpNib = 0;
		  writeData((upNib << 4) | lowNib);
		}
	  }
	  
	  // TODO instrpeek(baseConv(document.ctrl.lcdpinsHex.value,16));
	}
	
	updateStats();
	return;
  }
  
  // E is 1. Data or address reads are done 
  if (eGoLow != 1 & rwState == 1) {
	if (rsState == 0 & rwState == 1) {
	  // debug("Read BF & address, Reads are not implemented!\n");
	}
	
	if (rsState == 1 & rwState == 1) {
	  // debug("Read Data Register, Reads are not implemented!\n");
	}
	return;
  }
}

void LCD_SIM::writeData(var data) {
  // debugf("%d", data);
  
  if (lastAdrsSet == ADDR_DDRAM) {
	ddram[AC] = data;
	
	if (S) {
	  shiftChars += ID;
	}
	
	incdcrDDRadrs(ID);
	
	updateDisp();
  } else {
	//alert("writing to cgram viewer")
	
	cgram[AC%64] = data;
	int ACmn64 = AC % 64;
	chrtbl[(int)(floor(ACmn64/8))][ACmn64 % 8] = data & 31; //this goes to CGRAM viewer
	// TODO document["cgp"+ ACmn64].src = (data & 31) +".gif";
	incdcrCGRadrs(ID); 
	cgramChanged();
  }
}

void LCD_SIM::cgramChanged() {
  // debug("");

  if (D == 1) {
	for (int i = 0; i < range; i++) {
	  if (currDispChrs[i][chr] < 8) {
		pchr(currDispChrs[i][chr], i);
	  }
	}
	
	updateUndCurs();
  }
}

#define add

void LCD_SIM::evalInstr(var instr) {
  // debugf("%d", instr);

  // clearMsgs();
  
  addMsg(" E going LOW, executed instruction was:");
  
  if ((instr & maskSetDDRAMadrs) == instrSetDDRAMadrs) {
	setDDRadrs(instr & 0x7f);
	lastAdrsSet = ADDR_DDRAM;
	
	addMsgf("\n  Set DDRAM addr: 0x%02x", AC);
	return;
  }
  
  if ((instr & maskSetCGRAMadrs) == instrSetCGRAMadrs) {
	AC = (instr & 0x3f)+64;
	updateUndCurs();
	
	lastAdrsSet = ADDR_CGRAM;

	addMsgf("\n  Set CGRAM address to 0x%02x", (AC - 64));
	return;
  }
  
  if ((instr & maskFuncSet) == instrFuncSet) {
	addMsg("\n  Function set cmd: ");
	if (instr & eithtBitMode) {
	  addMsg("8 bit mode ON, ");
	  if (DL == 0) {
		DL = 1;
		for (var i = 0; i < 4; i++) {
		  // TODO togImage("d"+i);
		}
	  }
	  DL = 1;
	} else {
	  addMsg("4 bit mode ON, ");
	  /*
	  //fix... 15 August 2004 14:09
	  if((gotUpNib == 0) && (DL==1)){
	  upNib = instr >> 4;
	  gotUpNib = 1;
	  instr = instr >> 4
	  }
	  // end of fix ...15 August 2004 14:09
	  */

	  DL = 0;

	  for (var i = 0; i < 4; i++) {
		doc.d[i] = 0; // "b1t.gif";
	  }
	  
	  /* TODO 
		 var newVal = document.ctrl.lcdpinsDec.value >> 4;
		 document.ctrl.lcdpinsHex.value = baseDisp(newVal,16);
		 document.ctrl.lcdpinsDec.value = baseDisp(newVal,10);
	  */
	}
	
	if (instr & twoLines) {
	  addMsg("2 lines, ");
	  N = 1;
	  range = 32;
	  ln2On();
	  updateDisp();
	} else{
	  addMsg("1 line, ");
	  N = 0;
	  range = 16;
	  updateDisp();
	  ln2Off();
	}
	
	if (instr & largeFont) {
	  addMsg("5*10 font, ");
	  F = 1;
	  addMsg("\n  This LCD supports only 5*7 fonts !!!");
	} else {
	  addMsg("5*8 font, ");
	  F = 0;
	}
	
	return;
	}
  
  if ((instr & maskCursorDisplay) == instrCursorDisplay) {
	addMsg("\n  Cursor or display shift cmd: ");
	if (instr & rightLeft) {
	  addMsg("right, ");
	  RL = 1;
	} else{
	  addMsg("left, ");
	  RL = -1;
	}
	
	if (instr & shiftOrCursorMove) {
	  addMsg("shift disp. ");
	  SC = 1;
	  shiftChars -=RL;
	  lastAdrsSet = ADDR_DDRAM;
	  updateDisp();
	} else {
	  addMsg("move cursor ");
	  SC = 0;
	  lastAdrsSet = ADDR_DDRAM;
	  incdcrDDRadrs(RL);
	  updateDisp();
	}
	
	return;
  }
  
  if ((instr & maskEntryMode) == instrEntryMode) {
	addMsg("\n  Entry mode set: ");
	if (instr & incCursorPos) {
	  addMsg("inc. cursor pos, ");
	  ID = 1;
	} else{
	addMsg("dec. cursor pos, ");
	  ID = -1; 
	}
	
	if (instr & scrollDisp) {
	  addMsg("scroll disp. ON, ");
	  S = 1;
	} else{
	  addMsg("scroll disp. OFF, ");
	  S = 0;
	}
	  
	return;
  }
  
  if ((instr & maskDisplayCtrl) == instrDisplayCtrl) {
	addMsg("\n  Display ON/OFF control: ");
	if (instr & displayOn) {
	  addMsg("disp. ON, ");
	  D = 1;
	  dispBlanked = 0;
	  updateDisp();
	} else {
	  addMsg("disp. OFF, ");
	  D  = 0;
	  updateDisp();
	}
	
	if (instr & cursorOn) {
	  addMsg("cursor ON, ");
	  C = 1;
	  updateUndCurs();
	} else {
	  addMsg("cursor OFF, ");
	  C  = 0;
	  updateUndCurs();
	}
	
	if (instr & blinkOn) {
	  addMsg("blink ON, ");
	  B = 1;
	} else {
	  addMsg("blink OFF, ");
	  B  = 0;
	}
	
	return;
  }
  
  if ((instr & maskClearDisplay) == instrClearDisplay) {
	addMsg("\n  Clear display.");
	for (var i = 0; i < 104; i++) {
	  ddram[i] = 0x20;
	}
	
	ID = 1;
	setDDRadrs(0);
	lastAdrsSet = ADDR_DDRAM;
	updateDisp();
	
	return;
  }
  
  if ((instr & maskCursorHome) == instrCursorHome) {
	addMsg("\n  Cursor home. ");
	shiftChars = 0;
	setDDRadrs(0);
	lastAdrsSet = ADDR_DDRAM;
	updateDisp();
	
	return;
	}
  
  addMsg("\nInvalid instruction!");
  return;
}

void LCD_SIM::clearMsgs() {
  messages = "";
}

char buf[512];

void LCD_SIM::instrPeek(var instr) {
  // debugf("0x%02x", instr);

  //alert(rsState)
	
  // clearMsgs();

  if (rwState == 1) {
	return;
	}
  
  if (DL == 0) {
	if (gotUpNib == 1) {
	  // instr = (upNib << 4) | parseInt(document.ctrl.lcdpinsHex.value,16);
	  // addMsg("LCD is in 4-Bit mode.\n Upper nibble is: " + upNib +",and the lower one is: " + document.ctrl.lcdpinsHex.value +".\n" )
	}	else {
	  // addMsg("LCD is in 4-Bit mode.\n Cannot evaluate instruction without getting the upper nibble." )
	  return;
	}
  }
  
  if (rsState == 1) {
	// addMsg("RS is 1, data is: " +  baseConv(document.ctrl.lcdpinsHex.value,16))
	if (lastAdrsSet == ADDR_DDRAM) {
	  // addMsg("\n Last address set was DDRAM address.")
	  // addMsg("\n So,if written, data will go to DDRAM address: "+ AC)
	} else {
	  // addMsg("\n Last address set was CGRAM address.")
	  // addMsg("\n So,if written, data will go to CGRAM address: "+ (AC-64))
	}
	
	return;
  }
  
  
  addMsg("RS is 0, the instruction is: ");
  if ((instr & maskSetDDRAMadrs) == instrSetDDRAMadrs) {
	/// alert("set ddr adress instr 11")
	addMsgf("\n Set DDRAM addr: 0x%02x", (instr & 0x7f));
	/// alert("set ddr adress instr 22")
	return;
  }
  
  if ((instr & maskSetCGRAMadrs) == instrSetCGRAMadrs) {
	addMsgf("\n Set CGRAM addr: 0x%02x", (instr & 0x3f));
	return;
  }
  
  if ((instr & maskFuncSet) == instrFuncSet) {
	addMsg("\n Function set cmd: ");
	
	if (instr & eithtBitMode) {
	  addMsg("8 bit mode ON, ");
	} else {
	  addMsg("4 bit mode ON, ");
	}
	
	if( instr & twoLines) {
	  addMsg("2 lines, ");
	} else {
	  addMsg("1 line, ");
	}
	
	if (instr & largeFont) {
	  addMsg("5*10 font, ");
	  addMsg("\nThis LCD supports only 5*7 fonts !!!");
	  addMsg("\nDo not use this cmd!");
	} else {
	  addMsg("5*8 font, ");
	}
	
	return;
  }
  
  if ((instr & maskCursorDisplay) == instrCursorDisplay) {
	addMsg("\n Cursor or display shift cmd: ");
	if (instr & rightLeft) {
	  addMsg("right, ");
	} else {
	  addMsg("left, ");
	}
	
	
	if (instr & shiftOrCursorMove) {
	  addMsg("shift display ");
	} else {
	  addMsg("move cursor ");
	}
	
	return;
	
  }
  
  if ((instr & maskEntryMode) == instrEntryMode) {
	addMsg("\n Entry mode set: ");
	if (instr & incCursorPos) {
	  addMsg("increase cursor position, ");
	} else {
	  addMsg("decrease cursor position, ");
	}
	
	if (instr & scrollDisp) {
	  addMsg("scroll display ON, ");
	} else {
	  addMsg("scroll display OFF, ");
	}
	
	return;
  }
  
  if ((instr & maskDisplayCtrl) == instrDisplayCtrl) {
	addMsg("\n Display ON/OFF control: ");
	
	if (instr & displayOn) {
	  addMsg("display ON, ");
	} else {
	  addMsg("display OFF, ");
	}
	
	if (instr & cursorOn) {
	  addMsg("cursor ON, ");
	} else {
	  addMsg("cursor OFF, ");
	}
	
	if (instr & blinkOn) {
	  addMsg("blink ON, ");
	} else {
	  addMsg("blink OFF, ");
	}
	
	return;
  }
  
  
  if ((instr & maskClearDisplay) == instrClearDisplay) {
	addMsg("\n Clear display.");
	return;
  }
  
  if ((instr & maskCursorHome) == instrCursorHome) {
	addMsg("\n Cursor home. ");
	return;
  }
  
  addMsg("\nThis is not a valid instruction !");;
}

void LCD_SIM::instrpeek(var instr) {
  // debugf("0x%02x", instr);

  // clearMsgs();
  
  if (rwState == 1) {
	return;
  }
  
  if (DL == 0) {
	if (gotUpNib == 1) {
		// instr = (upNib << 4) | parseInt(document.ctrl.lcdpinsHex.value,16);
		// addMsg("LCD is in 4-Bit mode.\n Upper nibble is: " + upNib +",and the lower one is: " + document.ctrl.lcdpinsHex.value +".\n" )
	} else {
	  // addMsg("LCD is in 4-Bit mode.\n Cannot evaluate instruction without getting the upper nibble." )
	  return;
	}
  }
  
  if (rsState == 1) {
	// addMsg("RS is 1, data is: " +  baseConv(document.ctrl.lcdpinsHex.value,16))
	if (lastAdrsSet == ADDR_DDRAM) {
	  addMsg("\n Last address set was DDRAM address.");
	  addMsgf("\n So, if written, data will go to DDRAM address: ", AC);
	} else {
	  addMsg("\n Last address set was CGRAM address.");
	  addMsgf("\n So, if written, data will go to CGRAM address: ", (AC-64));
	}
	
	return;
  }
  
  addMsg("RS is 0, the instruction is: ");
  
  if ((instr & maskSetDDRAMadrs) == instrSetDDRAMadrs) {
	addMsgf("\n Set DDRAM addr to 0x%02x", (instr & 0x7f));
	return;
  }
  
  if ((instr & maskSetCGRAMadrs) == instrSetCGRAMadrs) {
	addMsgf("\n Set CGRAM addr to 0x%02x", (instr & 0x3f));
	return;
  }
  
  if ((instr & maskFuncSet) == instrFuncSet) {
	addMsg("\n Function set cmd: ");
	
	if (instr & eithtBitMode) {
	  addMsg("8 bit mode ON, ");
	} else {
	  addMsg("4 bit mode ON, ");
	}
	
	if (instr & twoLines) {
	  addMsg("2 lines, ");
	} else {
	  addMsg("1 line, ");
	}
	
	if (instr & largeFont) {
	  addMsg("5*10 font, ");
	  addMsg("\nThis LCD supports only 5*7 fonts !!!");
	  addMsg("\nDo not use this cmd!");
	} else {
	  addMsg("5*8 font, ");
	}
	
	return;
  }
  
  if ((instr & maskCursorDisplay) == instrCursorDisplay) {
	addMsg("\n Cursor or display shift cmd: ");
	if (instr & rightLeft) {
	  addMsg("right, ");
	} else {
	  addMsg("left, ");
	}
	
	if (instr & shiftOrCursorMove) {
	  addMsg("shift disp. ");
	} else {
	  addMsg("move cursor ");
	}

	return;
  }
  
  if ((instr & maskEntryMode) == instrEntryMode) {
	addMsg("\n Entry mode set: ");
	
	if (instr & incCursorPos) {
	  addMsg("increase cursor position, ");
	} else {
	  addMsg("decrease cursor position, ");
	}
	
	if (instr & scrollDisp) {
	  addMsg("scroll display ON, ");
	} else {
	  addMsg("scroll display OFF, ");
	}
	
	return;
  }
  
  if ((instr & maskDisplayCtrl) == instrDisplayCtrl) {
	addMsg("\n Display ON/OFF control: ");
	
	if (instr & displayOn) {
	  addMsg("display ON, ");
	} else {
	  addMsg("display OFF, ");
	}
	
	if (instr & cursorOn) {
	  addMsg("cursor ON, ");
	} else {
	  addMsg("cursor OFF, ");
	}
	
	if (instr & blinkOn) {
	  addMsg("blink ON, ");
	} else {
	  addMsg("blink OFF, ");
	}
	
	return;
	
  }
  
  if ((instr & maskClearDisplay) == instrClearDisplay) {
	addMsg("\n Clear display.");
	return;
  }
  
  if ((instr & maskCursorHome) == instrCursorHome) {
	addMsg("\n Cursor home. ");
	return;
  }
  
  addMsg("\nThis is not a valid instruction !");
}

void LCD_SIM::pchr(var chrnum , var _pos) {
  // debugf("%d, %d", chrnum, _pos);
  
  uint16_t pos = _pos * 8;
  
  for (var i = 0; i < 7; i++) {
	doc.p[pos+i] = chrtbl[chrnum][i];
  }
  
  if (chrnum < 8) {
	doc.p[pos+7] = chrtbl[chrnum][7];
  } else {
	doc.p[pos+7] = 0;
  }
}

#ifdef HAVE_SDL

void LCD_SIM::sdl_init(void)
{
}

void LCD_SIM::sdl_draw(SDL_Surface *sf, int x, int y)
{
  SDL_Color bg       = { 0x19, 0x19, 0x19 };
  SDL_Color fg_black = { 0, 0, 0 };
  SDL_Color fg_white = { 255, 255, 255 };
  SDL_Rect rect;
  SDL_Surface *txt_sf;

  char buf[1024];

  SDL_FillRect(sf, NULL, 0x191919);

  rect.w = sf->w;
  rect.h = sf->h;

  for (var l = 0; l < 2; l++) {
	for (int i = 0; i < (range / (N+1)); i++) {
	  rect.x = x + i * 18;
	  
	  int pos = l * ((range / (N+1)) * 8) + (i * 8);

	  for (var j = 0; j < 7; j++) {
		rect.y = y + l * 30 + j * 4;

		int pix = doc.p[pos+j];
		
		for (var k = 0; k <= 5; k++) {
		  SDL_Rect r;

		  r.x = rect.x - k * 3 + 9 - 1 + i;
		  r.y = rect.y - 1;
		  r.h = 3;
		  r.w = 3;
		  SDL_FillRect(sf, &r, 0x0000a0);

		  r.x = rect.x - k * 3 + 9 + 1 - 1 + i;
		  r.y = rect.y + 1 - 1;
		  r.h = 3;
		  r.w = 2;

		  if (pix & (1 << k)) 
			SDL_FillRect(sf, &r, 0xffffff);
		  else
			SDL_FillRect(sf, &r, 0x0000a0);

		}
	  }
	}
  }

  updateStats();

  SDL_Surface *text = sdl_text(sdl_font, messages, fg_white, bg);

  SDL_Rect r;

  r.x = 15;
  r.y = rect.y + 2;

  r.w = text->w;
  r.h = text->h;

  if (text) {
	SDL_BlitSurface(text, NULL, sf, &r);
	SDL_FreeSurface(text);
  }
}

void LCD_SIM::addMsg(const char* msg) {
  messages += msg;
}

void LCD_SIM::addMsgf(const char* fmt, ...) {
  char buf[1024];

  va_list args;

  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);

  messages += buf;
}

std::vector<std::string> tokenise(const std::string & str, const std::string & delim)
{
  using namespace std;
  vector<string> tokens;
  size_t p0 = 0, p1 = string::npos;

  while(p0 != string::npos) {
	p1 = str.find_first_of(delim, p0);
	if (p1 != p0) {
	  string token = str.substr(p0, p1 - p0);
	  tokens.push_back(token);
	}
	
	p0 = str.find_first_not_of(delim, p1);
  }
  return tokens;
}

struct TextGenerator : public std::binary_function<TTF_Font *, std::string, SDL_Surface *>
{
  SDL_Surface *operator()( TTF_Font *font, std::string line ) const {
	const SDL_Color fg = { 0xff, 0xff, 0xff };
	const SDL_Color bg = { 0x19, 0x19, 0x19 };

	return TTF_RenderText_Solid(font, line.c_str(), fg);
  }
};

SDL_Surface *LCD_SIM::sdl_text( TTF_Font *font, const std::string &text, const SDL_Color &fg, const SDL_Color &bg)
{
  vector<string> l = tokenise(text,"\n");

  if ( l.empty() ) { return 0; }

  vector<SDL_Surface *> s(l.size());
  transform(l.begin(), l.end(), s.begin(), bind1st(TextGenerator(), font));

  int w = 0;
  int h = 0;

  for ( int i = 0 ; i < s.size() ; ++i ) {
	if (!s[i]) {
	  // std::cout << TTF_GetError() << std::endl;
	  std::for_each(s.begin(), s.end(), &SDL_FreeSurface);
	  return 0;
	}

	h += s[i]->h;
	w = std::max(w, s[i]->w);
  }

  SDL_PixelFormat *format = s.front()->format;

  SDL_Surface *result =
	SDL_CreateRGBSurface(0, w, h, 32,
						 format->Rmask,
						 format->Gmask,
						 format->Bmask,
						 format->Gmask);
  
  SDL_FillRect(result, NULL, 0x191919);

  SDL_Rect offset;

  for (int i = 0 ; i < s.size() ; ++i ) {
	SDL_BlitSurface(s[i], 0, result, &offset);
	offset.y += s[i]->h;
  }
  
  for_each(s.begin(), s.end(), &SDL_FreeSurface);

  return result;
}
  
#endif
