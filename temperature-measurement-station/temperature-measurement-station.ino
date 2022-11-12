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
DS3231 clock;
RTCDateTime dt;

File myFile;
/********************************************************************/ 
 // TIMER DO ROBIENIA ZAPISOW DO PLIKU
unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;
/********************************************************************/ 
 //FLAGA INFORMUJACA WYSWIETLACZ CZY KARTA JEST WLOZONA
 int flaga = 0;
/********************************************************************/     
 float Temp_A = 0;
 float Temp_B = 0;
 float Temp_C = 0;
 float Temp_D = 0;
 float Temp_E = 0;
 float Temp_F = 0;
/********************************************************************/ 

 unsigned long co_ile_minut_zapis = 5;
 int ile_dni_do_kasacji = 2;
 unsigned long co_ile_godzin_reset = 4;

 
 int rozmiar_jedna_linijka = 84;
 int ile_linii_na_dobe = (1440/co_ile_minut_zapis);

 int rozmiarpoczasie =  rozmiar_jedna_linijka * ile_linii_na_dobe * ile_dni_do_kasacji; 

unsigned int licznik_zapisow;

/********************************************************************/
 void godzina()
 {
      Serial.print(dt.hour);   Serial.print(":");
      Serial.print(dt.minute); Serial.print(":");
      Serial.print(dt.second); Serial.print("  ");
 }

String toStringWithLeadingZeros(byte number) {
  String result = String(number);
  if(number < 10) {
    result = "0" + result;
  }
  return result;
}
void setup() {

 // start serial port 
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
/********************************************************************/
 // Start up the library 
 sensors.begin();
/********************************************************************/

/********************************************************************/ 
 lcd.init();   
 lcd.backlight(); // zalaczenie podwietlenia 
/********************************************************************/ 
 if (!SD.begin(10)) {
    Serial.println("initialization SD failed!");
    lcd.println("_BRAK KARTY_");
    lcd.setCursor(0,1); 
    lcd.println("_PRZY STARCIE_");
    while (1);
  }
    dt = clock.getDateTime();
   godzina();
  Serial.println("initialization SD done.");
 /********************************************************************/
 // Initialize DS3231
  godzina();
  Serial.print("Initialize DS3231 ");;
  clock.begin();
  Serial.println("done.");;
  // Set sketch compiling time
   // clock.setDateTime(__DATE__, __TIME__);

 /********************************************************************/   



  sensors.requestTemperatures(); // Send the command to get temperature readings 
 //Serial.println("DONE"); 

 Temp_A = sensors.getTempCByIndex(0)-1;
 Temp_B = sensors.getTempCByIndex(1)-1;
 Temp_C = sensors.getTempCByIndex(2)-1;
 
  myFile = SD.open("LOGS.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {

       godzina();
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
 void(* resetFunc) (void) = 0; //declare reset function @ address 0
/********************************************************************/
void loop() {
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 //Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 //Serial.println("DONE"); 

 Temp_A = sensors.getTempCByIndex(0)-1;
 Temp_B = sensors.getTempCByIndex(1)-1;
 Temp_C = sensors.getTempCByIndex(2)-1;

 if(Temp_A<-50) Temp_A=0;
 else  {Temp_A = sensors.getTempCByIndex(0)-1;}
 
  if(Temp_B<-50) Temp_B=0;
 else  {Temp_B = sensors.getTempCByIndex(1)-1;}
 
 if(Temp_C<-50) Temp_C=0;
 else  {Temp_C = sensors.getTempCByIndex(2)-1;}
/********************************************************************/
 if(flaga==0){
lcd.setCursor(0,0); 
 lcd.print("A:"); lcd.print(Temp_A, 0);  lcd.print("  ");
 lcd.print("B:"); lcd.print(Temp_B, 0);  lcd.print("  ");
 lcd.print("C:"); lcd.print(Temp_C, 0);  
 lcd.setCursor(0,1); 
 //lcd.print("D:"); lcd.print(Temp_D, 0);  lcd.print("  "); 
 //lcd.print("E:"); lcd.print(Temp_E, 0);  lcd.print("  ");
// lcd.print("F:"); lcd.print(Temp_F, 0);  
lcd.print(toStringWithLeadingZeros(dt.hour));   lcd.print(":");
      lcd.print(toStringWithLeadingZeros(dt.minute)); lcd.print(":");
      lcd.print(toStringWithLeadingZeros(dt.second));  lcd.setCursor(10,1);  lcd.print("Li:");
     lcd.print(licznik_zapisow) ;
}

/********************************************************************/
// Odczytujemy date
  dt = clock.getDateTime();
 
  //Pobierz liczbe milisekund od startu
  aktualnyCzas = millis();
  roznicaCzasu = aktualnyCzas - zapamietanyCzas;
  //Jeśli różnica wynosi ponad minute
  if (roznicaCzasu >= (co_ile_minut_zapis*60*1000)) 
  {
      zapamietanyCzas = aktualnyCzas;
    
     licznik_zapisow++;
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("LOGS.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
    Serial.print("Writing to logs.txt...");


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
        Serial.println(myFile.size());


      myFile.close();
      Serial.println("close file done.");
    
         if (myFile.size()>=rozmiarpoczasie)
      {
         Serial.println("REMOVE LOGS");
         SD.remove("LOGS.txt");
         myFile.close();
      } 
      
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening logs.txt");
    flaga=1;  
  }
 }

if(flaga==1)
{
    lcd.setCursor(0,0); 
    lcd.println("_WLOZ KARTE_");

    lcd.setCursor(0,1); 
    lcd.println("I ZRESETUJ UKLAD");
  
  }

 /********************************************************************/
  if (aktualnyCzas>3600000)
{
  resetFunc(); 
}
 /********************************************************************/

}
