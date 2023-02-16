#pragma once
#include <Arduino.h>


void setTime() {

 delay(200);

  int hour = dt.hour;
  int minute = dt.minute;
  int second = dt.second;

  // Ustawiamy tryb edycji godziny
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Godzina -> ");
  lcd.setCursor(11, 0);
  lcd.print(toStringWithLeadingZeros(hour));

  int edit = 0;
  
  while (edit == 0) {
    if (digitalRead(LEFT_BUTTON) == LOW) {
      // Zmniejszamy godzine
      hour--;
      if (hour == -1) hour = 23;
      lcd.setCursor(11, 0);
      lcd.print(toStringWithLeadingZeros(hour));
      delay(DEBOUNCE_DELAY);
    }
    if (digitalRead(RIGHT_BUTTON) == LOW) {
      // Zwiększamy godzine
      hour++;
      if (hour == 24) hour = 0;
      lcd.setCursor(11, 0);
      lcd.print(toStringWithLeadingZeros(hour));
      delay(DEBOUNCE_DELAY);
    }
    if (digitalRead(SELECT_BUTTON) == LOW) {
      // Kończymy edycję godziny
      edit = 1;
      delay(DEBOUNCE_DELAY);
    }
  }

    // Ustawiamy tryb edycji miesiąca
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Minuta -> ");
    lcd.setCursor(10, 0);
    lcd.print(toStringWithLeadingZeros(minute));
    edit = 0;

  while (edit == 0) {

    if (digitalRead(LEFT_BUTTON) == LOW) {
      // Zmniejszamy minute
      minute--;
      if (minute == -1) minute = 59;
      lcd.setCursor(10, 0);
      lcd.print(toStringWithLeadingZeros(minute));
      delay(DEBOUNCE_DELAY);
    }

    if (digitalRead(RIGHT_BUTTON) == LOW) {
      // Zwiększamy minute
      minute++;

      if (minute == 60) minute = 0;
      lcd.setCursor(10, 0);
      lcd.print(toStringWithLeadingZeros(minute));
      delay(DEBOUNCE_DELAY);
      }

      if (digitalRead(SELECT_BUTTON) == LOW) {
      // Kończymy edycję minut
      edit = 1;
      delay(DEBOUNCE_DELAY);
      }
  }
  // Zatwierdzamy datę i zapisujemy ją w zegarze DS3231
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ustawiam...");
  lcd.setCursor(0, 1);
  lcd.print(toStringWithLeadingZeros(hour));
  lcd.print(":");
  lcd.print(toStringWithLeadingZeros(minute));
  clock.setDateTime(dt.year, dt.month, dt.day, hour, minute, second);
  delay(2000);
  }