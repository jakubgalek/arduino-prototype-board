/********************************************************************/
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
/********************************************************************/ 
// SD CARD
#include <SPI.h>
#include <SD.h>
/********************************************************************/ 
// RTC DS3231
#include <DS3231.h>
/********************************************************************/ 
#include <EEPROM.h>
/********************************************************************/ 

#include "global_vars.hpp"
#include "setdate.hpp"
#include "settime.hpp"
#include "lcdtemperatures.hpp"



const int numOptions = 4;
const char *options[] = {"1.Temperatury", "2.Ustaw date", "3.Ustaw czas", "4.Reset"};
int option = 0;



void setup() {
 // start serial port 
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
/********************************************************************/
 // Start up the library 
 sensors.begin();
/********************************************************************/
 // Odczytanie wartości bitu z pamięci EEPROM
  lastWasFunction = EEPROM.read(MEMORY_ADDRESS);
/********************************************************************/ 
 lcd.init();   
 lcd.backlight(); // zalaczenie podwietlenia 
/********************************************************************/ 
 if (!SD.begin(53)) {
    Serial.println("initialization SD failed!");
    lcd.println("_BRAK KARTY_");
    lcd.setCursor(0,1); 
    lcd.println("_PRZY STARCIE_");
    while (1);
  }
    dt = clock.getDateTime();
   print_time();
  Serial.println("initialization SD done.");
 /********************************************************************/
 // Initialize DS3231
  print_time();
  Serial.print("Initialize DS3231 ");;
  clock.begin();
  Serial.println("done.");;
  // Set sketch compiling time
   // clock.setDateTime(__DATE__, __TIME__);

 /********************************************************************/   
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);


  sensors.requestTemperatures(); // Send the command to get temperature readings 
 //Serial.println("DONE"); 

 Temp_A = sensors.getTempCByIndex(0);
 Temp_B = sensors.getTempCByIndex(1);
 Temp_C = sensors.getTempCByIndex(2);
 
  myFile = SD.open("LOGS.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {

       print_time();
       licznik_zapisow++;

    Serial.print("Writing to logs.txt... ");

  myFile.print(dt.year);   myFile.print("-");
  myFile.print(dt.month);  myFile.print("-");
  myFile.print(dt.day);    myFile.print("|");
  myFile.print(dt.hour);   myFile.print(":");
  myFile.print(dt.minute); myFile.print(":");
  myFile.print(dt.second); myFile.print("      ");
    
  myFile.print(Temp_A); myFile.print("      ");     
  myFile.print(Temp_B); myFile.print("      ");
  myFile.print(Temp_C); myFile.print("      ");
  myFile.print(Temp_D); myFile.print("      ");
  myFile.print(Temp_E); myFile.print("      ");
  myFile.print(Temp_F); myFile.println("");

      Serial.print("File size: ");
      Serial.print(myFile.size());

      myFile.close();
      Serial.println(" - done.");
  }
 
}

/********************************************************************/
void loop() {
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 if (lastWasFunction) {
    // Jeśli ostatnio byliśmy w funkcji, to uruchamiamy ją
    LCD_temperatures();
 }

delay(200);

 // Wyświetlamy nazwę opcji na pierwszej linii wyświetlacza
  lcd.setCursor(0, 0);
  lcd.print(options[option]);

  // Obsługujemy nawigację za pomocą przycisków
 if (digitalRead(LEFT_BUTTON) == LOW)
{
    // Przesuwamy się do poprzedniej opcji
    lcd.clear();
    option--;
    if (option < 0) {
      option = numOptions - 1;
    }
}
if (digitalRead(RIGHT_BUTTON) == LOW)
{
    // Przesuwamy się do następnej opcji
    lcd.clear();
    option++;
    if (option >= numOptions) {
        option = 0;
    }
}
if (digitalRead(SELECT_BUTTON) == LOW)
{
    // Wybieramy bieżącą opcję
    lcd.clear();
    selectOption(option);
}
    // Odczytaj aktualną godzinę z zegara DS3231
  dt = clock.getDateTime();
  int hour = dt.hour;
  int minute = dt.minute;

 // Odświeżamy wyświetlacz
lcd.setCursor(0, 1);
lcd.print(" ");
lcd.setCursor(0, 1);
lcd.print("^ Wybierz  ");
      lcd.print(toStringWithLeadingZeros(dt.hour));   lcd.print(":");
      lcd.print(toStringWithLeadingZeros(dt.minute)); 
      

}

void selectOption(int option)
{
    // Wykonujemy odpowiednią akcję dla wybranej opcji
    switch (option)
    {
    case 0:
        LCD_temperatures();
        break;
    case 1:
        setDate();
        break;
    case 2:
        setTime();
        break;
    case 3:
        resetFunc();
        break;
    }
}







