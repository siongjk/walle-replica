/**
 * oLED Display
 *
 * @file      display.ino
 * @brief     Draw battery level on the oLED display
 * @author    Hans Vandamme
 * @copyright MIT license
 * @version   1.0
 *
 * Code to draw the battery level indicator onto an oLED
 * display. For instructions of how to wire up the display,
 * see the README file included in this repository.
 */

#ifdef OLED

/**
 * Draw battery level on the display
 * 
 * @param  batlevel The current battery percentage
 */

void intDisplayLevel (void){
	u8g2.clearBuffer();
	displayLevel(55);
	solarSound01();
	delay(1000);
	displayLevel(60);
	solarSound01();
	delay(800);
	displayLevel(65);
	solarSound01();
	delay(800);
	displayLevel(70);
	solarSound02();
	delay(600);
	displayLevel(75);
	solarSound02();
	delay(600);
	displayLevel(80);
	solarSound02();
	delay(600);
	displayLevel(85);
	solarSound02();
	delay(400);
	displayLevel(90);
	solarSound02();
	delay(400);
	displayLevel(95);
	solarSound02();
	delay(400);
	displayLevel(100);
	solarSound03();
	delay(1000);
}

void displayLevel(int batlevel) {
	u8g2.clearBuffer();
	u8g2.firstPage();
	do {
		u8g2.setDrawColor(1);
		/**Text Title*/
		//u8g2.setFont(u8g2_font_squeezed_r7_tr);
		//u8g2.setFontDirection(3);
		//u8g2.drawStr(7,63,"SOLAR CHARGE LEVEL");
		//drawSun();
    sun_animation();
		
		// Scale to 50% as the battery should not drop bellow that anyway
		drawBatt10();
		if (batlevel > 55) drawBatt20();
		if (batlevel > 60) drawBatt30();
		if (batlevel > 65) drawBatt40();
		if (batlevel > 70) drawBatt50();
		if (batlevel > 75) drawBatt60();
		if (batlevel > 80) drawBatt70();
		if (batlevel > 85) drawBatt80();
		if (batlevel > 90) drawBatt90();
		if (batlevel > 95) drawBatt100();
	} while ( u8g2.nextPage() );
	u8g2.sendBuffer();
}


/**
 * Functions to draw each of the battery level bars
 */
void drawBatt10() {
	u8g2.drawBox(114, 0, 12, 38);
}

void drawBatt20() {
	u8g2.drawBox(103, 0, 7, 34);
}

void drawBatt30() {
	u8g2.drawBox(92, 0, 7, 34);
}

void drawBatt40() {
	u8g2.drawBox(81, 0, 7, 34);
}

void drawBatt50() {
	u8g2.drawBox(70, 0, 7, 34);
}

void drawBatt60() {
	u8g2.drawBox(59, 0, 7, 30);
}

void drawBatt70() {
	u8g2.drawBox(48, 0, 7, 30);
}

void drawBatt80() {
	u8g2.drawBox(37, 0, 7, 30);
}

void drawBatt90() {
	u8g2.drawBox(26, 0, 7, 30);
}

void drawBatt100() {
	u8g2.drawBox(15, 0, 7, 30);
}

/**
 * Draw the sun icon on the display
 */
void drawSun() {
	/** New Sun Draw */
	u8g2.drawCircle(25, 52, 5, U8G2_DRAW_ALL);
	u8g2.drawDisc(25, 52, 3, U8G2_DRAW_ALL);
	u8g2.drawLine(25, 45, 25, 41);
	u8g2.drawLine(25, 59, 25, 63);
	u8g2.drawLine(18, 52, 14, 52);
	u8g2.drawLine(32, 52, 36, 52);
	// ------------------------------
	u8g2.drawLine(28, 46, 31, 42);
	u8g2.drawLine(31, 49, 35, 46);
	// ------------------------------
	u8g2.drawLine(29, 58, 31, 62);
	u8g2.drawLine(31, 55, 35, 58);
	// ------------------------------
	u8g2.drawLine(21, 58, 19, 62);
	u8g2.drawLine(19, 55, 15, 58);
	// ------------------------------
	u8g2.drawLine(22, 46, 19, 42);
	u8g2.drawLine(19, 49, 15, 46);
}

#endif /* OLED */