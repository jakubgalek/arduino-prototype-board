#include <Wire.h>
#include <VL53L0X.h>
#include <LiquidCrystal_I2C.h>

int radius = 0;

VL53L0X laser;
LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  laser.init();
  laser.setTimeout(500);
  lcd.begin(16, 2);
  lcd.init();
  lcd.init();
  lcd.backlight();
}

void loop()
{
  radius = laser.readRangeSingleMillimeters();
  Serial.println("Distance");
  Serial.println(String(radius)+"mm");
  lcd.setCursor(4,0);
  lcd.print("Distance");
  lcd.setCursor(5,1);
  lcd.print("      ");
  lcd.setCursor(5,1);
  lcd.print(String(radius)+"mm");
  delay(60);
}
