#include <EEPROM.h>
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int day = 4;
int hour = 18;
int minute = 43;
int week = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("  # UNLOCKED #  ");
  lcd.setCursor(0,1);
  lcd.print("--> FIRST START  ");
  delay (2000);
  lcd.clear();

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
    week = week + 1;
    day= 0;
  }
  if (week == 2) {
    week = week - 1;
    day = 0;
  }
 }
 }
}
lcd.clear();
lcd.setCursor(2,0);
lcd.print(":");
if (hour < 10){
  lcd.setCursor(0,0);
  lcd.print("0");
  lcd.setCursor(1,0);
  lcd.print(hour);
}
else {
  lcd.setCursor(0,0);
  lcd.print(hour); 
}
if (minute < 10){
  lcd.setCursor(3,0);
  lcd.print("0");
  lcd.setCursor(4,0);
  lcd.print(minute);
}
else {
  lcd.setCursor(3,0);
  lcd.print(minute); 
}
lcd.setCursor(1,1);
if (day == 1){
 lcd.print("Lundi");
}
if (day == 2){
 lcd.print("Mardi");
}
if (day == 3){
 lcd.print("Mercredi");
}
if (day == 4){
 lcd.print("Jeudi");
}
if (day == 5){
 lcd.print("Vendredi");
}
if (day == 6){
 lcd.print("Samedi");
}
if (day == 7){
 lcd.print("Dimanche");
}
 delay (60000);
}
