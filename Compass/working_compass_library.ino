#include "bucket_compass.h"


void setup()
{
  Serial.begin(9600);              // Start serial ports
  CMPS12.begin(9600);

  startingHeading = getHeading();
}

void loop()
{
  float heading = getCalibratedHeading();

  Serial.print("Heading: ");       // Display 16 bit angle with decimal place
  Serial.println(heading);

  Serial.print("Starting Heading: ");       // Display 16 bit angle with decimal place
  Serial.println(startingHeading);
  delay(1000);                           // Short delay before next loop
}
