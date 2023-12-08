#include <M5Core2.h>
#include <M5_PbHub.h>

M5_PbHub myPbHub;

#define PIR_UNIT_CHANNEL_1 2

void displaySensorStatus(int sensorNumber, int value);

void setup() {
  M5.begin();

  myPbHub.begin();
  myPbHub.setPixelCount(PIR_UNIT_CHANNEL_1, 1);
}

void loop() {
    
  int pirValue1 = myPbHub.digitalRead(PIR_UNIT_CHANNEL_1);
  Serial.printf("%d", pirValue1);

  delay(50);
  M5.update();
}



