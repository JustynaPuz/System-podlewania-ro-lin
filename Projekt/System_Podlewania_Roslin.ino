#include <LiquidCrystal.h>  //Dołączenie bilbioteki LCD
#include <stdio.h>
#include <LCD.h>
LCD lcd(3, 4, 5, 6, 7, 9);
int FC28_pin = A5;                    //pin do czujnika wilgonosci
int FC28_output_value;                //wartosc z czujnika wilgotnosci
int WaterSensorValue;
int Relay = 12;                       //przekaznik
int CompareHumidity;                  //wartosc do porownywania odczytu
int LowLevel, MediumLevel, HighLevel;
int button = 2;
int LED =13;
int Buzzer = A1;
int WaterLevelSensor = A4;
int WaterTreshold = 300; 
bool alarmInterrput = false;
char RecivedSerialChar ='\0';
String LevelHumidity;
volatile unsigned long buttonLastInterruptTime = 0;
const unsigned long debounceTime = 300;
const unsigned long interval = 2000;  //do millis 1 sek
unsigned long previousMillis = 0;
int button_counter;
int HumiditySensorMin = 280; // Minimum sensor value
int HumiditySensorMax = 1030; // Maximum sensor value

enum mode {
  Low,
  Medium,
  High
};
//wybrany obecny poziom
mode CurrentMode;

void setup() {

  digitalWrite(Relay, HIGH);
  lcd.begin();
  Serial.begin(9600);
  button_counter = 0;
  //ustawianie poziomów
  LowLevel = 30;
  MediumLevel = 60;
  HighLevel = 90;
  LevelHumidity = "Wysoki";
  
  pinMode(button, INPUT_PULLUP);  //przycisk
  pinMode(Relay, OUTPUT);         //przekaznik
  pinMode(Buzzer,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button), SetLevel, FALLING);
}

void SetLevel() {
  //debouncing
  unsigned long interruptTime = millis();
  if ((interruptTime - buttonLastInterruptTime) > debounceTime) {
    button_counter = (button_counter + 1) % 3;
    alarmInterrput = 1;
  }

  buttonLastInterruptTime = interruptTime;
}

void loop() {
  unsigned long currentMillis = millis();

  //zczytywanie z czujnika co 2 sek
  if (currentMillis - previousMillis >= interval) {
    FC28_output_value = analogRead(FC28_pin);
    WaterSensorValue = analogRead(WaterLevelSensor);
    FC28_output_value = map(FC28_output_value, HumiditySensorMax,HumiditySensorMin , 0, 100);
  //   Serial.print("Wilgotnosc: ");
  //  Serial.println(FC28_output_value);
  //  Serial.print("Poziom wody: ");
  //  Serial.println(WaterSensorValue);
    previousMillis = currentMillis;
    lcd.PrintHumidityAndLevel(FC28_output_value, LevelHumidity);
  }
    if(Serial.available() > 0) {
      RecivedSerialChar = Serial.read();
      switch(RecivedSerialChar) {
        case 'M':
        case 'm':
        Serial.println();
        Serial.println("Menu: ");
        Serial.println("H - humidity sensor configuration");
        Serial.println("W - water level sensor configuration");
        Serial.println("M - menu");
        break;

        case 'H': {
        Serial.println("Put your sensor in air");
        delay(5000);
        int check = 2000;
        int tempCheck = 0;
        for(int i = 0; i < 10; i++) {
          tempCheck = analogRead(FC28_pin);
          Serial.print("Min value: ");
          Serial.println(tempCheck);
          if(tempCheck < check) {
            check = tempCheck;
          }
          delay(1000);
        }
        Serial.println(check);
        HumiditySensorMax = check;
        check =0;
         Serial.println("Put your sensor in water");
         delay(5000);
          for(int i =0; i < 10; i++) {
          tempCheck = analogRead(FC28_pin);
          Serial.print("Max value: ");
          Serial.println(tempCheck);
            if(tempCheck > check) {
            check = tempCheck;
          }
          delay(1000);
        }
        Serial.println(check);
        HumiditySensorMin = check ;
         Serial.println("End of configuration");
        break;
        }
      case 'W': {
        Serial.println("Place water level sensor at the minimum level");
        delay(5000);
        int newTreshold=10000;
        int tempTreshold;
        for(int i = 0; i < 10; i++) {
           tempTreshold = analogRead(WaterLevelSensor);
           Serial.print("Value: ");
           Serial.println(tempTreshold);
           if(tempTreshold < newTreshold) {
            newTreshold = tempTreshold;
           }
           delay(1000);
        }
        Serial.println(newTreshold);
        Serial.println("End of configuration");
        WaterTreshold = newTreshold;
       break;
      }
      }
    }

  if (alarmInterrput) {
    switch (button_counter) {
      case 0:
        {
          CurrentMode = High;
          CompareHumidity=HighLevel;
          LevelHumidity = "Wysoki";
          break;
        }
      case 1:
        {
          CurrentMode = Low;
          CompareHumidity=LowLevel;
          LevelHumidity = "Niski";
          break;
        }
      case 2:
        {
          CurrentMode = Medium;
          CompareHumidity = MediumLevel;
          LevelHumidity = "Sredni";
        }
    }
    alarmInterrput = false;
  }

  if(WaterSensorValue < WaterTreshold) {
    digitalWrite(LED,HIGH);
  }else {
    digitalWrite(LED,LOW);
  }



  //ustawianie pompki
  if (FC28_output_value < CompareHumidity) {
     digitalWrite(Relay,LOW);  //włączenie pompki
  }

  if (FC28_output_value > CompareHumidity) {
    digitalWrite(Relay,HIGH);  //wyłączenie pompki
  }
    if(digitalRead(Relay) == LOW && FC28_output_value >  CompareHumidity || digitalRead(Relay) == HIGH && FC28_output_value <  CompareHumidity ) {
    lcd.alarm();
    // digitalWrite(Buzzer, HIGH);
  }else {
    // digitalWrite(Buzzer, LOW);
  }
}