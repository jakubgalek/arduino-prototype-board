#pragma once
#include <Arduino.h>

void LCD_temperatures() {

   // Zapisanie informacji o tym, że jesteśmy w funkcji do pamięci EEPROM
  lastWasFunction = true;
  EEPROM.write(MEMORY_ADDRESS, 1);

  lcd.clear();
  while (digitalRead(LEFT_BUTTON) == HIGH) {
 //Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 //Serial.println("DONE"); 

 Temp_A = sensors.getTempCByIndex(0) + tempOffset;
 Temp_B = sensors.getTempCByIndex(1) + tempOffset;
 Temp_C = sensors.getTempCByIndex(2) + tempOffset;

 if(Temp_A<-50) Temp_A=0;
 else  {Temp_A = sensors.getTempCByIndex(0) + tempOffset;}
 
  if(Temp_B<-50) Temp_B=0;
 else  {Temp_B = sensors.getTempCByIndex(1) + tempOffset;}
 
 if(Temp_C<-50) Temp_C=0;
 else  {Temp_C = sensors.getTempCByIndex(2) + tempOffset;}
/********************************************************************/
 if(is_sd_inserted_live==1){
lcd.setCursor(0,0); 
 lcd.print("A:"); lcd.print(Temp_A, 1);  lcd.print("  ");
 lcd.print("B:"); lcd.print(Temp_B, 1);  lcd.print("  ");
 lcd.setCursor(0,1); 
 
lcd.print(toStringWithLeadingZeros(dt.day));  lcd.print(".");
lcd.print(toStringWithLeadingZeros(dt.month)); lcd.print(".");
      lcd.print(dt.year);  lcd.setCursor(11,1);  lcd.print("Li:");
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
  myFile.print(Temp_C); myFile.println("");

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
    is_sd_inserted_live=0;  
  }
 }

if(is_sd_inserted_live==0)
{
    lcd.setCursor(0,0); 
    lcd.println("_WLOZ KARTE_");

    lcd.setCursor(0,1); 
    lcd.println("I ZRESETUJ UKLAD");
  
  }

 /********************************************************************/
  if (aktualnyCzas > (co_ile_godzin_reset * 60 * 60 * 1000))
{
  resetFunc(); 
}
 /********************************************************************/
if (digitalRead(LEFT_BUTTON) == LOW) {
      // Wróć do menu
      lcd.clear();
        lastWasFunction = false;
        EEPROM.write(MEMORY_ADDRESS, 0);
      break;
    }
}


}