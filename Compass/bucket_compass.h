#include <SoftwareSerial.h>

#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15

// The following digital pins can be used for RX on MEGA2560
// 10, 11, 12, 13, 14, 15, 50, 51, 52, 53
#define CMPS_RX_PIN 10
#define CMPS_TX_PIN 11

SoftwareSerial CMPS12 = SoftwareSerial(CMPS_RX_PIN,CMPS_TX_PIN);

unsigned char high_byte, low_byte, angle8;
char pitch, roll;
unsigned int angle16;
float startingHeading;

float getRawHeading() {//get raw compass reading from cmps12 sensor
  CMPS12.write(CMPS_GET_ANGLE16);  // Request and read 16 bit angle
  while (CMPS12.available() < 2);
  high_byte = CMPS12.read();
  low_byte = CMPS12.read();
  angle16 = high_byte;                // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;

  float angleDecimal = angle16;
  angleDecimal /= 10;

  return angleDecimal;
}

float transferHeading(float heading) { //translate compass reading into coordinateMotion.h facingAngle format
  float newHeading = 360 - heading; //convert from clockwise to counter-clockwise format
  return newHeading;
}

float getAbsoluteHeading() { //get angle from cmps12 sensor in facingAngle format
  float heading = transferHeading(getRawHeading());
  return heading;
}

float getHeading() { //creates new heading that centers the bot at 0 degrees

  float calibratedHeading = getAbsoluteHeading() - startingHeading;

  if (calibratedHeading < 0) {
    calibratedHeading = 360 + calibratedHeading;
  }
  return calibratedHeading;
}
