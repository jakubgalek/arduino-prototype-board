#pragma once
#include <Arduino.h>

DS3231 clock;
RTCDateTime dt;

File myFile;

int LEFT_BUTTON = 9;
int RIGHT_BUTTON = 8;
int SELECT_BUTTON = 7;

#define DEBOUNCE_DELAY 200  // Opóźnienie debouncingu (w milisekundach)


String toStringWithLeadingZeros(byte number) {
  String result = String(number);
  if(number < 10) {
    result = "0" + result;
  }
  return result;
}

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
 /********************************************************************/
 void(* resetFunc) (void) = 0; //declare reset function @ address 0
