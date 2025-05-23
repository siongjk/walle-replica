/************************************************* ************************************************** ******
* OPEN-SMART Red Serial MP3 Player Lesson 1: Play a song
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/1Y8CYgHcJfa3CxeA_H6ugRz-e4OMmWQ_G?usp=sharing


Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 

* You can learn how to play a song with its index in the TF card.
*
* The following functions are available:
*
/--------basic operations---------------/
mp3.play();
mp3.pause();
mp3.nextSong();
mp3.previousSong();
mp3.volumeUp();
mp3.volumeDown();
mp3.forward();    //fast forward
mp3.rewind();     //fast rewind
mp3.stopPlay();  
mp3.stopInject(); //when you inject a song, this operation can stop it and come back to the song befor you inject
mp3.singleCycle();//it can be set to cycle play the currently playing song 
mp3.allCycle();   //to cycle play all the songs in the TF card
/--------------------------------/

mp3.playWithIndex(int8_t index);//play the song according to the physical index of song in the TF card

mp3.injectWithIndex(int8_t index);//inject a song according to the physical index of song in the TF card when it is playing song.

mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level

mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...099

mp3.playWithVolume(int8_t index, int8_t volume);//play the song according to the physical index of song in the TF card and the volume set

mp3.cyclePlay(int16_t index);//single cycle play a song according to the physical index of song in the TF

mp3.playCombine(int16_t folderAndIndex[], int8_t number);//play combination of the songs with its folder name and physical index
      //folderAndIndex: high 8bit is folder name(01 02 ...09 10 11...99) , low 8bit is index of the song
      //number is how many songs you want to play combination

About SoftwareSerial library:
The library has the following known limitations:
If using multiple software serial ports, only one can receive data at a time.

Not all pins on the Mega and Mega 2560 support change interrupts, so only the following can be used for RX: 
10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69).

Not all pins on the Leonardo and Micro support change interrupts, so only the following can be used for RX: 
8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
On Arduino or Genuino 101 the current maximum RX speed is 57600bps.
On Arduino or Genuino 101 RX doesn't work on Pin 13.

Product link: 

USB MP3 + TF card + Speaker:
https://www.aliexpress.com/item/1005003274011049.html
Easy IO Shield:
https://www.aliexpress.com/item/4000022518637.html
OPEN-SMART ONE R3 C board:
https://www.aliexpress.com/item/1005002536184038.html
************************************************** **************************************************/
#include <SoftwareSerial.h>
#include "RedMP3.h"

#define MP3_RX 6  //RX of Serial MP3 module connect to D4 of Arduino
#define MP3_TX 7  //TX to D2, note that D2 can not be used as RX on Mega2560, you should modify this if you donot use Arduino UNO
MP3 mp3(MP3_RX, MP3_TX);

int8_t index = 0x01;       //the first song in the TF card
int8_t volume = 0x1a;      //0~0x1e (30 adjustable level)
int8_t folderName = 0x01;  //folder name must be 01 02 03 04 ...
int8_t fileName = 0x01;    // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
int8_t folder02 = 2;       //folder name must be 01 02 03 04 ...
int8_t beep01 = 52;        // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
int8_t beep02 = 51;        // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
int8_t charged = 53;       // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...

const int buttonOne = 48;
const int buttonTwo = 49;
unsigned long buttonDebounce;
bool buttonState = false;

void soundSetup() {
  delay(500);  //Requires 500ms to wait for the MP3 module to initialize
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  //mp3.playWithVolume(index,volume);
  //mp3.playWithFileName(folderName,fileName);
  delay(50);  //you should wait for >=50ms between two commands
}

void solarSound01(void) {
  mp3.stopPlay();
  mp3.playWithFileName(folder02, beep01);
  delay(50);  //you should wait for >=50ms between two commands
}
void solarSound02(void) {
  mp3.stopPlay();
  mp3.playWithFileName(folder02, beep02);
  delay(50);  //you should wait for >=50ms between two commands
}
void solarSound03(void) {
  mp3.stopPlay();
  mp3.playWithFileName(folder02, charged);
  delay(50);  //you should wait for >=50ms between two commands
}

void buttonSound()  //button music
{
  int buttonPressed;
  if (millis() > buttonDebounce) {
    buttonPressed = digitalRead(buttonOne);
    if (buttonPressed > 0) {
      buttonDebounce = millis() + 200;
      mp3.stopPlay();  //stop any existing sounds
      delay(500);
      //playSoundAtVolume(15, 1);//play sound at volume 15, track 1...drill
      mp3.playWithFileName(folderName, fileName);
      Serial.println("Play");
    }
  }
  if (millis() > buttonDebounce) {
    buttonPressed = digitalRead(buttonTwo);
    if (buttonPressed > 0) {
      buttonDebounce = millis() + 200;
      mp3.stopPlay();  //stop any existing sounds
      delay(500);
      //mp3.allCycle();
      Serial.print(F("number: \t"));
      Serial.println(number);
      Serial.println("Play Cycle");
    }
  }

  // buttonState = digitalRead(buttonOne);
  // if (buttonState == true) {
  //   //buttonDebounce = millis() + 200;
  //   mp3.stopPlay();  //stop any existing sounds
  //   delay(500);
  //   //playSoundAtVolume(15, 1);//play sound at volume 15, track 1...drill
  //   mp3.playWithFileName(folderName, fileName);
  //   Serial.println("Play");
  // }
}



/*********************************************************************************************************
The end of file
*********************************************************************************************************/
