#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() 
{
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.init();
  lcd.init();
  lcd.backlight();
}
void loop() {
    bool buttonState1 = digitalRead(9);
    bool buttonState2 = digitalRead(8);
    bool buttonState3 = digitalRead(7);
    lcd.setCursor(0,0);
    lcd.print(buttonState1);
    lcd.setCursor(3,0);
    lcd.print(buttonState2); 
    lcd.setCursor(6,0);
    lcd.print(buttonState3);
}