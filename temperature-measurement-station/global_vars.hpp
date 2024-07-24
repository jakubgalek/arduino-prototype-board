#pragma once
#include <Arduino.h>

DS3231 clock;
RTCDateTime dt;

File myFile;

int LEFT_BUTTON = 9;
int RIGHT_BUTTON = 8;
int SELECT_BUTTON = 7;

#define DEBOUNCE_DELAY 200  // Opóźnienie debouncingu (w milisekundach)

bool lastWasFunction;
#define MEMORY_ADDRESS 0

String toStringWithLeadingZeros(byte number)
{
    String result = String(number);
    if(number < 10)
    {
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
int is_sd_inserted_live = 1;
/********************************************************************/
float Temp_A = 0;
float Temp_B = 0;
float Temp_C = 0;
float Temp_D = 0;
float Temp_E = 0;
float Temp_F = 0;


float tempOffset = -0.6;

/********************************************************************/

unsigned long co_ile_minut_zapis = 5;
int ile_dni_do_kasacji = 20;
unsigned long co_ile_godzin_reset = 12;


int rozmiar_jedna_linijka = 84;
int ile_linii_na_dobe = (1440/co_ile_minut_zapis);

int rozmiarpoczasie =  rozmiar_jedna_linijka * ile_linii_na_dobe * ile_dni_do_kasacji;

unsigned int licznik_zapisow;

/********************************************************************/
void print_time()
{
    Serial.print(dt.hour);
    Serial.print(":");
    Serial.print(dt.minute);
    Serial.print(":");
    Serial.print(dt.second);
    Serial.print("  ");
}
/********************************************************************/
void(* resetFunc) (void) = 0; //declare reset function @ address 0
