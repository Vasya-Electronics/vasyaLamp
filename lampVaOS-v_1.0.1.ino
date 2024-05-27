/*
 Вася Лампа - Версия 1.0.1 от 02.02.2024
 Разрабодчик: Вася Электронника 
 Telegram: https://t.me/va_elektro
 Дзен: https://dzen.ru/va_ru_electro
 Ссылка на Яндекс Диск: https://disk.yandex.ru/d/659tUWQeh8T0TQ
 Поддрержка: info-va-ru@yandex.ru
*/

//А тут должны были быть настройки, а их нет, потому что они все в приложении - Вася Лампа//

//Библиотеки// 
#include <LedControl.h>              //Библиотека матрицы 
#include <SoftwareSerial.h>          //Библиотека блютуз 
#include <RTClib.h>                  //Библиотека модуля реального времени 
#include <EEPROM.h>                  //Библиотека Епром 
//Подключения//
LedControl lclm=LedControl(4,6,5,1); //Подключаем матрицу 
SoftwareSerial mySerialBT(8,9);      //Подключаем блютуз 
RTC_DS3231 rtc;                      //Подключение модуля времени
DateTime t;                          //Подключение модуля времени
String daysOfTheWeek[7]={"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
String monthsNames[12]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
//Переменные//
int BT;                              //Переменая блютуз
int X;                               //Переменая Х
int Y;                               //Переменая Y 
char time1;                          //Таймер
int flag1;                           //Флаг1
int hour2;                           //Час
int minute2;                         //Минуты
long random_int(int a,int b) {       //Рандом
 if (a > b) {
    int c = a;
    a = b;
    b = c;
  }
  return random(a,b);
}
void ok(){                           //Галочка
  lclm.setIntensity(0,15);
  lclm.shutdown(0,false);
  lclm.setRow(0,0,B00000000);lclm.setRow(0,1,B00000001);lclm.setRow(0,2,B00000010);lclm.setRow(0,3,B00000100);lclm.setRow(0,4,B10001000);lclm.setRow(0,5,B01010000);lclm.setRow(0,6,B00100000);lclm.setRow(0,7,B00000000);
  delay(1000);
  lclm.setIntensity(0,15);
  lclm.shutdown(0,false);
  lclm.setRow(0,0,B00000000);lclm.setRow(0,1,B00000000);lclm.setRow(0,2,B00000000);lclm.setRow(0,3,B00000000);lclm.setRow(0,4,B00000000);lclm.setRow(0,5,B00000000);lclm.setRow(0,6,B00000000);lclm.setRow(0,7,B00000000);
}
void no(){                           //Крестик
  lclm.setIntensity(0,15);
  lclm.shutdown(0,false);
  lclm.setRow(0,0,B10000001);lclm.setRow(0,1,B01000010);lclm.setRow(0,2,B00100100);lclm.setRow(0,3,B00011000);lclm.setRow(0,4,B00011000);lclm.setRow(0,5,B00100100);lclm.setRow(0,6,B01000010);lclm.setRow(0,7,B10000001);
  delay(1000);
  lclm.setIntensity(0,15);
  lclm.shutdown(0,false);
  lclm.setRow(0,0,B00000000);lclm.setRow(0,1,B00000000);lclm.setRow(0,2,B00000000);lclm.setRow(0,3,B00000000);lclm.setRow(0,4,B00000000);lclm.setRow(0,5,B00000000);lclm.setRow(0,6,B00000000);lclm.setRow(0,7,B00000000);
}
void serial(){                       //Главная функция
  BT =  mySerialBT.read();           //Чтение блютуз
  if(t.hour() == hour2 - 1){         //Будильник
    if(t.minute() == minute2){  
      X = 0;
      Y = 0;
      modeB();
    }
  }
  if(BT == 98){                      //Запись будильника
    BT =  mySerialBT.read();
    minute2  = BT;
    EEPROM.write(5,minute2);
    if (hour2 > -1) {
      if(minute2 > -1){
        ok();
      }else{
        no();    
      }
    }else{
      no();
    }
  }
  if(BT == 99){                      //Запись будильника
      BT =  mySerialBT.read();
      hour2 = BT;
      EEPROM.write(10,hour2);       
  }
  if(BT == 61){                      //Режим 1
    flag1 = 1;
  }
  if(BT == 62){                      //Режим 2
    flag1 = 2;
  }
  if(BT == 63){                      //Режим 3
    flag1 = 3;
  }
  if(BT == 64){                      //Режим 4
    flag1 = 4;
  }
  if(BT == 65){                      //Режим 5
    X = 0;
    Y = 0;
    flag1 = 5;
  }
}
void mode0(){                        //Режим Загрузка
     for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,true);
      X = X + 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,true);
      Y = Y + 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    X = 7;
    for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,true);
      X = X - 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    Y = 7;
    for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,true);
      Y = Y - 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,false);
      X = X + 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,false);
      Y = Y + 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    X = 7;
    for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,false);
      X = X - 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    Y = 7;
    for (int count = 0; count < 7; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,false);
      Y = Y - 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
}
void mode2(){                        //Режим Дождь или Снег
   X = random_int(0, 8);
    for (int count = 0; count < 9; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,(Y - 1),false);
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,true);
      Y = Y + 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    Y = 0;
}
void mode3(){                        //Режим Два пикселя
    X = random_int(0, 8);
    for (int count = 0; count < 9; count++) {
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,(Y - 1),false);
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,(Y - 1),X,false);
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,X,Y,true);
      lclm.setIntensity(0,15);
      lclm.shutdown(0,false);
      lclm.setLed(0,Y,X,true);
      Y = Y + 1;
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
    }
    Y = 0;
}
void mode4(){                        //Режим Бешеный пиксель
   X = random_int(0, 7);
   Y = random_int(0, 7);
   lclm.setIntensity(0,15);
   lclm.shutdown(0,false);
   lclm.setLed(0,X,Y,true);
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
   lclm.setIntensity(0,15);
   lclm.shutdown(0,false);
   lclm.setLed(0,X,Y,false);
      for (int count = 0; count < time1; count++) {
        delay(1);
        serial();
      }
}
void mode5(){                        //Режим Автоматическое приложение 
  for (int count = 0; count < 10; count++) {
  serial();
   mode0();
   X == 0;
   Y == 0;
 }
 for (int count = 0; count < 20; count++) { 
   serial();
   mode2();
   X == 0;
   Y == 0;
 }
 for (int count = 0; count < 20; count++) { 
  serial();
   mode3();
   X == 0;
   Y == 0;
 }
 for (int count = 0; count < 100; count++) {
   serial();
   mode4();
   X == 0;
   Y == 0;
 }
 X = 0;
 Y = 0;
}
void modeB(){                        //Режим будильника
  lclm.setIntensity(0,15);
  lclm.shutdown(0,false);
  lclm.setRow(0,0,B00000000);lclm.setRow(0,1,B00000000);lclm.setRow(0,2,B00000000);lclm.setRow(0,3,B00000000);lclm.setRow(0,4,B00000000);lclm.setRow(0,5,B00000000);lclm.setRow(0,6,B00000000);lclm.setRow(0,7,B00000000);
   for (int count = 0; count < 8; count++) {
      for (int count = 0; count < 8; count++) {
         lclm.setIntensity(0,15);
           lclm.shutdown(0,false);
          lclm.setLed(0,X,Y,true);
         X = X + 1;
        delay(56256);
      }
      X = 0;
       lclm.setIntensity(0,15);
         lclm.shutdown(0,false);
        lclm.setLed(0,X,Y,true);
       Y = Y + 1;
    }
      for (int count = 0; count < 20; count++) {
        tone(7,2000,500);
        delay(500);
        noTone(3);
        delay(500);
        tone(7,2000,500);
        delay(500);
        noTone(3);
        delay(500);
     }
    X = 0;
    Y = 0;
    for (int count = 0; count < 8; count++) {
      for (int count = 0; count < 8; count++) {
        lclm.setIntensity(0,15);
           lclm.shutdown(0,false);
          lclm.setLed(0,X,Y,false);
         X = X + 1;
          delay(100);
      }
      X = 0;
      lclm.setIntensity(0,15);
         lclm.shutdown(0,false);
        lclm.setLed(0,X,Y,false);
       Y = Y + 1;
    }
    X = 0;
    Y = 0;
    void(* resetFunc) (void) = 0;
    resetFunc();
}
void setup() {
  rtc.begin();                       //Запуск времени
  Serial.begin(9600);                //Запуск Сериал
  mySerialBT.begin(9600);            //Запуск блютуз
  time1 = 50;                        //Скорость режима 
  minute2 = EEPROM.read(5);          //Чтение из памяти
  hour2 = EEPROM.read(10);           //Чтение из памяти
}
void loop() {
  serial();                          //Функция записи
  t=rtc.now();                       //Разрешение чтение модуля
  Serial.println((String(hour2) + String(":") + String(minute2) + String("-") + String(t.hour()) + String(":") + String(t.minute()))); 
  if(flag1 == 1){                    //Загрузка
    X = 0;
    Y = 0;
    mode0();
  }
  if(flag1 == 2){                    //Дождь
    mode2();
  }
  if(flag1 == 3){                    //Два пикселя
    mode3();
  }
  if(flag1 == 4){                    //Бешеный пиксель
    mode4();
  }
  if(flag1 == 5){                    //Авиоматическое переключение
    mode5();
  }
  if(t.hour() == hour2 - 1){         //Будильник
    Serial.println((String(hour2) + String(":") + String(minute2) + String("-") + String(t.hour()) + String(":") + String(t.minute())));
    if(t.minute() == minute2){
      X = 0;
      Y = 0;
      modeB();
    }
  }
}
