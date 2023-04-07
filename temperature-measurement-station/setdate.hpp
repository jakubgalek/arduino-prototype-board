#pragma once
#include <Arduino.h>


void setDate() {

    delay(200);

    // Pobieramy aktualną datę z zegara DS3231
    int day = dt.day;
    int month = dt.month;
    int year = dt.year;

    // Ustawiamy tryb edycji dnia
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dzien -> ");
    lcd.setCursor(9, 0);
    lcd.print(toStringWithLeadingZeros(day));
    int edit = 0;

    while (edit == 0)
    {
        if (digitalRead(LEFT_BUTTON) == LOW)
        {
            // Zmniejszamy dzień
            day--;
            if (day == 0) day = 31;
            lcd.setCursor(9, 0);
            lcd.print(toStringWithLeadingZeros(day));
            delay(DEBOUNCE_DELAY);
        }
        if (digitalRead(RIGHT_BUTTON) == LOW)
        {
            // Zwiększamy dzień
            day++;
            if (day == 32) day = 1;
            lcd.setCursor(9, 0);
            lcd.print(toStringWithLeadingZeros(day));
            delay(DEBOUNCE_DELAY);
        }
        if (digitalRead(SELECT_BUTTON) == LOW)
        {
            // Kończymy edycję dnia
            edit = 1;
            delay(DEBOUNCE_DELAY);
        }
    }

    // Ustawiamy tryb edycji miesiąca
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Miesiac -> ");
    lcd.setCursor(11, 0);
    lcd.print(toStringWithLeadingZeros(month));
    edit = 0;
    while (edit == 0)
    {
        if (digitalRead(LEFT_BUTTON) == LOW)
        {
            // Zmniejszamy miesiąc
            month--;
            if (month == 0) month = 12;
            lcd.setCursor(11, 0);
            lcd.print(toStringWithLeadingZeros(month));
            delay(DEBOUNCE_DELAY);
        }
        if (digitalRead(RIGHT_BUTTON) == LOW)
        {
            // Zwiększamy miesiąc
            month++;
            if (month == 13) month = 1;
            lcd.setCursor(11, 0);
            lcd.print(toStringWithLeadingZeros(month));
            delay(DEBOUNCE_DELAY);
        }
        if (digitalRead(SELECT_BUTTON) == LOW)
        {
            // Kończymy edycję miesiąca
            edit = 1;
            delay(DEBOUNCE_DELAY);
        }
    }

    // Ustawiamy tryb edycji roku
    year=2023;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rok -> ");
    lcd.setCursor(7, 0);
    lcd.print(year);
    edit = 0;
    while (edit == 0)
    {
        if (digitalRead(LEFT_BUTTON) == LOW)
        {
            // Zmniejszamy rok
            year--;
            lcd.setCursor(7, 0);
            lcd.print(year);
            delay(DEBOUNCE_DELAY);
        }
        if (digitalRead(RIGHT_BUTTON) == LOW)
        {
            // Zwiększamy rok
            year++;
            lcd.setCursor(7, 0);
            lcd.print(year);
            delay(DEBOUNCE_DELAY);
        }
        if (digitalRead(SELECT_BUTTON) == LOW)
        {
            // Kończymy edycję roku
            edit = 1;
            delay(DEBOUNCE_DELAY);
        }
    }

    // Zatwierdzamy datę i zapisujemy ją w zegarze DS3231
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ustawiam...");
    lcd.setCursor(0, 1);
    lcd.print(toStringWithLeadingZeros(day));
    lcd.print(".");
    lcd.print(toStringWithLeadingZeros(month));
    lcd.print(".");
    lcd.print(year);
    clock.setDateTime(year, month, day,dt.hour,dt.minute,dt.second);
    delay(2000);
}
