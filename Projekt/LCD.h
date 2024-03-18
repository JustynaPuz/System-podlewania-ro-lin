#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h> 
class LCD {
  public:
  LCD(int a, int b, int c, int d, int e, int f);
  void begin();
  void clear();
  void alarm();
  void PrintHumidityAndLevel(int humidity, String level);
  private:
  int _a, _b, _c, _d, _e, _f;
  LiquidCrystal _lcd;

};



#endif