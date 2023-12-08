#include <M5Core2.h>
#include <M5_PbHub.h>
#include <Wire.h>
#include <Unit_Sonic.h>

M5_PbHub myPbHub;
SONIC_IO sensor;

#define PIR_UNIT_CHANNEL_1 2
#define PIR_UNIT_CHANNEL_2 3

void displaySensorStatus(int sensorNumber, int value);

void setup() {
  M5.begin();
  sensor.begin(32, 33);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  // M5.Lcd.setCursor(40, 0);
  // M5.Lcd.println("Dual PIR example with M5_PbHub");
  M5.Lcd.setCursor(35, 10);
  M5.Lcd.setTextColor(WHITE);

  myPbHub.begin();
  myPbHub.setPixelCount(PIR_UNIT_CHANNEL_1, 1);
  myPbHub.setPixelCount(PIR_UNIT_CHANNEL_2, 1);
}

int point      = 0;
int last_point = 0;

void loop() {
  M5.Lcd.setCursor(0, 25);
  M5.Lcd.print("Status PIR 1: ");
  M5.Lcd.setCursor(0, 45);
  M5.Lcd.print("Value PIR 1: ");

  M5.Lcd.setCursor(0, 75);
  M5.Lcd.print("Status PIR 2: ");
  M5.Lcd.setCursor(0, 95);
  M5.Lcd.print("Value PIR 2: ");

  M5.Lcd.fillRect(180, 25, 200, 25, BLACK);
  M5.Lcd.fillRect(180, 45, 200, 25, BLACK);
  M5.Lcd.fillRect(180, 75, 200, 25, BLACK);
  M5.Lcd.fillRect(180, 95, 200, 25, BLACK);

  int pirValue1 = myPbHub.digitalRead(PIR_UNIT_CHANNEL_1);
  int pirValue2 = myPbHub.digitalRead(PIR_UNIT_CHANNEL_2);

  //ultrasonic
  float Distance = sensor.getDistance();
    Serial.printf("Distance: %.2fmm\r\n", Distance);
    point = map((int)Distance, 20, 4500, 10, 180);
    last_point = point;

  displaySensorStatus(1, pirValue1);
  displaySensorStatus(2, pirValue2);

  delay(50);
  M5.update();
}

void displaySensorStatus(int sensorNumber, int value) {
  M5.Lcd.setCursor(180, (sensorNumber - 1) * 50 + 25);
  if (value == 1) {
    M5.Lcd.print("Sensing");
    Serial.printf("PIR %d Status: Sensing\n", sensorNumber);
  } else {
    M5.Lcd.print("Not Sensed");
    Serial.printf("PIR %d Status: Not Sensed\n", sensorNumber);
  }
  M5.Lcd.setCursor(180, (sensorNumber - 1) * 50 + 45);
  M5.Lcd.print(value);
  Serial.printf(" PIR %d value: %d\n", sensorNumber, value);
}

