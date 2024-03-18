# System Podlewania roślin

**Opis projektu** \
Na podstawie danych z czujnika wilgotności, który jest umieszczony w glebie, mikrokontroler analizuje odczyt i na jego podstawie decyduję o uruchomieniu systemu podlewania. Gdy roślina musi zostać podlana, mikrokontroler wysyła sygnał do przekaźnika, który uruchamia pompkę wodną. Przez rurkę woda jest doprowadzana do gleby. System wyłącza pompkę, gdy odczyt z czujnika wilgotności będzie powyżej poziomu minimalnego. Projekt w celu lepszego dopasowania do potrzeb rośliny posiada 3 różne poziomy wilgotności (Wysoki, średni, niski), które są ustawiane za pomocą przycisku. Informacje o wybranym trybie i o aktualnej wilgotności gleby wyświetlane są na wyświetlaczu LCD. Przy pomocy terminala możemy skalibrować czujniki. System posiada również system alarmowy, który załącza się w wypadku wykrycia awarii. 

**Funkcjonalności**\
    * Wykrywanie zbyt niskiej wilgotności gleby\
    * Ustawienie 3 poziomów progu wilgotności\
    * Informacje o obecnej wilgotności oraz wybranym poziomie \
    * Automatyczne podlewanie\
    * Powiadomienie o zbyt niskim poziomie wody w zbiorniku\
    * Alarm w przypadku awarii\
    * Konfiguracja czujników\

  **Komponenty**\
    * Arduino UNO\
    * Wyświetlacz LCD 2x16 znaków - green - justPi\
    * Przycisk\
    * Potencjometr\
    * Przekaźnik 5V 10A AVR ARM\
    * Bateria 9V\
    * Pompka wodna 3-12V\
    * Czujnik wilgotności FC-28\
    * Płytka stykowa\
    * Rurka silikonowa\
    * Klip na baterie\
    * Przewody połączeniowe\
    * Buzzer\
    * Dioda LED\
    * Czujnik poziomu wody\
    * Kabel do podłączenia Arduino do komputera\

