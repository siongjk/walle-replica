/*------------------------------------
// Function: This is car control demo code for Wireless Joystick Remote 
	to control the smart car.
// IDE: Arduinio-1.8.7
// Author: OPEN-SMART Team
// Buy from: https://open-smart.aliexpress.com/store/1199788

-------------------------------------*/
#include <String.h>
#include <VirtualWire.h>

int RF_RX_PIN = A3;           //the RF433 or RF315 receiver module connect with D9 pin of Easy IO Shield pro.
void (*resetFunc)(void) = 0;  //software reset when the RF receiver can not respond

//Remote control code macro
#define CMD_INVALID 0
#define CMD_FORWARD 1
#define CMD_K2 2
#define CMD_RIGHT 3
#define CMD_BACKWARD 4
#define CMD_K4 5
#define CMD_LEFT 6
#define CMD_STOP 7
#define CMD_K1 8
#define CMD_K3 9


#define XY_TOLERANCE 30
#define X0 510  //Initial value of X-asix of the Joystick
#define Y0 510  //Initial value of Y-asix of the Joystick

#define SPEED_STEPS 20
uint8_t speed0 = 200;  //Initial value of speed, value should 0~255.


void receiversetup() {
  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  vw_setup(2000);            // Transmission speed in bits per second.
  vw_rx_start();             // Start the PLL receiver.
  Serial.println(F("Receiver Connected"));
}

uint8_t command;
uint8_t buff[VW_MAX_MESSAGE_LEN];  // buffer array for data recieve over serial port
uint8_t buflen = VW_MAX_MESSAGE_LEN;

void receiverloop() {
  if (vw_get_message(buff, &buflen))  // non-blocking I/O
  {
    command = decode();
    if (command != CMD_INVALID) {
      controlCar(command);
      delay(200);
    }
  }
}
void J_action() {
  evaluateSerial();
  delay(200);
}

void controlCar(uint8_t cmd) {
  switch (cmd) {
    case CMD_FORWARD:
      number = 0;
      //Serial.println(F("Forward"));
      //Serial.print(F("Controller Value:"));
      //Serial.print(firstChar);
      //Serial.println(number);
      Serial3.print(F("Controller Value:"));
      Serial3.print(firstChar);
      Serial3.println(number);
      J_action();
      break;

    case CMD_BACKWARD:
      //motordriver.goBackward();
      number = 0;
      // Serial.println(F("Backward"));
      // Serial.print(F("Controller Value:"));
      // Serial.print(firstChar);
      // Serial.println(number);
      Serial3.println(F("Controller Value:"));
      Serial3.print(firstChar);
      Serial3.println(number);
      J_action();
      break;

    case CMD_RIGHT:
      //motordriver.slideRight();
      number = 0;
      // Serial.println(F("Turn right"));
      // Serial.print(F("Controller Value:"));
      // Serial.print(firstChar);
      // Serial.println(number);
      Serial3.println(F("Controller Value:"));
      Serial3.print(firstChar);
      Serial3.println(number);
      J_action();
      break;

    case CMD_LEFT:
      //motordriver.slideLeft();
      number = 0;
      // Serial.println(F("Turn left \t"));
      // Serial.print(F("Controller Value:"));
      // Serial.print(firstChar);
      // Serial.println(number);
      Serial3.println(F("Controller Value:"));
      Serial3.print(firstChar);
      Serial3.println(number);
      J_action();
      delay(200);
      break;

    case CMD_STOP:
      number = 0;
      //firstChar = 'q';
      Serial.println(F("Stop \t"));
      break;

    case CMD_K4:

      Serial.println(F("K4 button \t"));
      delay(200);

      break;

    case CMD_K2:

      Serial.println(F("K2 button \t"));
      delay(200);

      break;

    case CMD_K1:

      Serial.println(F("K1 button \t"));
      delay(200);
      break;

    case CMD_K3:

      Serial.println(F("K3 button \t"));
      delay(200);
      break;
    default: break;
  }
}


uint8_t decode() {

  command = 0;
  if ((buff[0] != 0x7E) || (buff[4] != 0xEF)) {
    resetFunc();  //software reset
    return 0;
  }
  int x, y;
  int xh, xl, yh, yl;
  uint8_t z;
  uint8_t button;

  x = buff[1] << 2;
  y = buff[2] << 2;
  z = buff[3] >> 3;
  button = buff[3] & 0x07;

  if ((x < (X0 + XY_TOLERANCE)) && (x > (X0 - XY_TOLERANCE))) {
    if (y > (Y0 + XY_TOLERANCE)) {
      number = (float)(y - Y0) / Y0 * 100;
      firstChar = 'Y';
      delay(200);
      J_action();
      command = CMD_FORWARD;

    } else if (y < (Y0 - XY_TOLERANCE)) {
      number = (float)(y - Y0) / Y0 * 100;
      firstChar = 'Y';
      delay(200);
      J_action();
      command = CMD_BACKWARD;
    } else {
      command = CMD_STOP;
    }
  } else if (x < (X0 - XY_TOLERANCE)) {

    if ((y < (Y0 + XY_TOLERANCE)) && (y > (Y0 - XY_TOLERANCE))) {
      number = (float)(x - X0) / X0 * 100;
      firstChar = 'X';
      delay(200);
      J_action();
      command = CMD_LEFT;
    }

  } else {

    if ((y < (Y0 + XY_TOLERANCE)) && (y > (Y0 - XY_TOLERANCE))) {
      number = (float)(x - X0) / X0 * 100;
      firstChar = 'X';
      delay(200);
      J_action();
      command = CMD_RIGHT;
    }
  }
  switch (button) {
    case 1: command = CMD_K1; break;  //K1 button;
    case 2: command = CMD_K2; break;  //K2 button;
    case 3: command = CMD_K3; break;  //K3 button;
    case 4: command = CMD_K4; break;  //K4 button;
    default: break;
  }
  clearBufferArray();
  return command;

  /*decode End*/
}


void clearBufferArray()  // function to clear buffer array
{
  for (int i = 0; i < VW_MAX_MESSAGE_LEN; i++) { buff[i] = 0; }  // clear all index of array with 0
}
