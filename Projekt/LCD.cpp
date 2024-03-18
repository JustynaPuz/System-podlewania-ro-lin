#include <Arduino.h>
#include <LCD.h>

LCD::LCD(int a, int b, int c, int d, int e, int f)
: _lcd(a,b,c,d,e,f) {
  int _a =a;
  int _b =b;
  int _c =c;
  int _d =d;
  int _e =e;
  int _f =f;
  
}
void LCD::PrintHumidityAndLevel(int humidity, String level) { 
  _lcd.clear();
   _lcd.setCursor(0, 0);        //Ustawienie kursora
   _lcd.print("Wilgotnosc: ");  //Wyświetlenie tekstu
   _lcd.setCursor(0, 1);        //Ustawienie kursora
  _lcd.print("Poziom: ");      //Wyświetlenie tekstu
 _lcd.setCursor(12, 0);
  _lcd.print(humidity);
  _lcd.print("   ");
  _lcd.setCursor(15, 0);
  _lcd.print("%");
  _lcd.setCursor(8, 1);
  _lcd.print(level);
  _lcd.print("        ");
}

void LCD::begin() {
  _lcd.begin(16,2);
  _lcd.setCursor(3,0);
  _lcd.print("Rozpoczynam");
  _lcd.setCursor(4,1);
  _lcd.print("Dzialanie");
  delay(3000);
}
void LCD::clear() {
  _lcd.clear();
}

void LCD::alarm() {
  _lcd.clear();
  _lcd.setCursor(6,0);
  _lcd.print("ALARM!");

}