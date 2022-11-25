//   ____ ___ __  __ ____  _     _____      _                       ____ _     ___   ____ _  __
//  / ___|_ _|  \/  |  _ \| |   | ____|__ _| | __ _ _ __ _ __ ___  / ___| |   / _ \ / ___| |/ /
//  \___ \| || |\/| | |_) | |   |  _| / _` | |/ _` | '__| '_ ` _ \| |   | |  | | | | |   | ' /
//   ___) | || |  | |  __/| |___| |__| (_| | | (_| | |  | | | | | | |___| |__| |_| | |___| . \ 
//  |____/___|_|  |_|_|   |_____|_____\__,_|_|\__,_|_|  |_| |_| |_|\____|_____\___/ \____|_|\_\



#include <EEPROM.h>
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int day = 7;
int hour = 23;
int minute = 58;
int week = 2;
int minutespeed = 60000;
bool debugmode = false;
String lang = "fr";

String day1 = "day1";
String day2 = "day2";
String day3 = "day3";
String day4 = "day4";
String day5 = "day5";
String day6 = "day6";
String day7 = "day7";
String trweek = "defweek";
String startscrl1 = "blank line 1";
String startscrl2 = "blank line 2";


int config = 1;

void setup() {

  if (debugmode == true) {
    day = 1;
    hour = 1;
    minute = 1;
    week = 1;
    minutespeed = 10;
    startscrl1 = "debugmode don't";
    startscrl2 = "use as it is";
  }

  pinMode(A4, OUTPUT);
  digitalWrite(A4, HIGH);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print(startscrl1);
  lcd.setCursor(0, 1);
  lcd.print(startscrl2);
  delay(10000);
  lcd.clear();
  if (debugmode == true) {
    Serial.println("debugmode");
    day = 1;
    hour = 1;
    minute = 1;
    week = 1;
    minutespeed = 10;
    String startscrl1 = "debugmode don't";
    String startscrl2 = "use as an alarmclock";
  }

  //while(config < 10){}

  if (lang == "fr") {
    day1 = "Lundi";
    day2 = "Mardi";
    day3 = "Mercredi";
    day4 = "Jeudi";
    day5 = "Vendredi";
    day6 = "Samedi";
    day7 = "Dimanche";
    trweek = "semaine: ";
    if (debugmode == true) {
      Serial.println("lang = fr");
    }
  }

  if (lang == "en") {
    day1 = "Monday";
    day2 = "Tuesday";
    day3 = "Wednesday";
    day4 = "Thursday";
    day5 = "Friday";
    day6 = "Saturday";
    day7 = "Sunday";
    trweek = "  week : ";
    if (debugmode == true) {
      Serial.println("lang = en");
    }
  }
}

void loop() {

  minute = minute + 1;
  if (minute == 60) {
    hour = hour + 1;
    minute = 00;

    if (hour == 24) {
      day = day + 1;
      hour = 00;

      if (day == 8) {
        if (week == 1) {
          week = 2;
          day = 1;
        }
        if (week == 2) {
          week = 1;
          day = 1;
        }
      }
    }
  }

  lcd.clear();
  lcd.setCursor(11, 0);
  lcd.print(":");
  if (hour < 10) {
    lcd.setCursor(9, 0);
    lcd.print("0");
    lcd.setCursor(10, 0);  // put your main code here, to run repeatedly:
    lcd.print(hour);
  } else {
    lcd.setCursor(9, 0);
    lcd.print(hour);
  }
  if (minute < 10) {
    lcd.setCursor(12, 0);
    lcd.print("0");
    lcd.setCursor(13, 0);
    lcd.print(minute);
  } else {
    lcd.setCursor(12, 0);
    lcd.print(minute);
  }
  lcd.setCursor(0, 0);

  if (day == 1) {
    lcd.print(day1);
  }
  if (day == 2) {
    lcd.print(day2);
  }
  if (day == 3) {
    lcd.print(day3);
  }
  if (day == 4) {
    lcd.print(day4);
  }
  if (day == 5) {
    lcd.print(day5);
  }
  if (day == 6) {
    lcd.print(day6);
  }
  if (day == 7) {
    lcd.print(day7);
  }

  lcd.setCursor(0, 1);
  lcd.print(trweek);
  lcd.print(week);

  delay(minutespeed);
}