#include <SoftwareSerial.h>

#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15

SoftwareSerial CMPS12 = SoftwareSerial(2, 3);

unsigned char high_byte, low_byte, angle8;
char pitch, roll;
unsigned int angle16;

float getHeading() {
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
