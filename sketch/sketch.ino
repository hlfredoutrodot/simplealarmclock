#include <EEPROM.h>
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int day = 7;
int hour = 23;
int minute = 58;
int week = 2;


String lang = "fr";

String day1 = "day1";
String day2 = "day2";
String day3 = "day3";
String day4 = "day4";
String day5 = "day5";
String day6 = "day6";
String day7 = "day7";
String trweek = "defweek";


int config = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("  # UNLOCKED #  ");
  lcd.setCursor(0, 1);
  lcd.print("--> FIRST START  ");
  delay(2000);
  lcd.clear();

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
  }
}

void loop() {
  // put your main code here, to run repeatedly:
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
  lcd.setCursor(10, 0);
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

delay(60000);
}