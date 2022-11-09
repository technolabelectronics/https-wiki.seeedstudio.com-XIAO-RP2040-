#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int Flasher = 3;
int Siren = 7;
int buzzer = 2;
int smokeA0 = A1;
// My threshold value
int sensorThres = 400;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(Flasher, OUTPUT);
  pinMode(Siren, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(Flasher, HIGH);
    digitalWrite(Siren, HIGH);
    tone(buzzer, 1000, 200);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(" GAS/SMOKE DETECTOR ");
    display.print("Sensor Reading :");
    display.print(analogSensor);
    display.println("Gas Leakage Detected");
    display.display();
  }
  else
  {
    digitalWrite(Flasher, LOW);
    digitalWrite(Siren, LOW);
    noTone(buzzer);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(" GAS/SMOKE DETECTOR ");
    display.print("Sensor Reading :");
    display.print(analogSensor);
    display.println("No Leakage");
    display.display();
  }
  delay(100);
}
