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
int hour = 18;
int minute = 34;
int week = 2;
int alarmhour = 24;
int alarmmn = 35;
int minutespeed = 6000;
bool isring = false;
bool debugmode = false;
String lang = "fr";

int milliscount;
String day1 = "day1";
String day2 = "day2";
String day3 = "day3";
String day4 = "day4";
String day5 = "day5";
String day6 = "day6";
String day7 = "day7";
String trweek = "defweek";
String tralarm = "tralarm";
String tralarm1 = "tralarm1";
String tralarm2 = "tralarm2";
String trsettings = "trsettings";
String startscrl1 = "SIMPLEalarmCLOCK";
String startscrl2 = "   @Stbretzel   ";
String trpress = "trpress";

int menu = 0;
unsigned long waitime;
unsigned long waitminute;
unsigned long waitloop;
bool ison = false;
unsigned long ontime = 60000;
unsigned long minutime = 60000;
unsigned long looptime = 100;
unsigned long millisprocess;
int buzzerpin = 2;
int almledpin = 5;
bool canpass = true;
int wantedmenu = 0;



enum {
  release_buttons,
  menu_button,
  up_button,
  down_button,
  select_button
};

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
  pinMode(buzzerpin, OUTPUT);
  pinMode(almledpin, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  digitalWrite(A4, HIGH);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print(startscrl1);
  lcd.setCursor(0, 1);
  lcd.print(startscrl2);
  delay(10000);
  lcd.clear();
  analogWrite(10, 0);
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
  if (lang == "fr") {
    day1 = "Lundi";
    day2 = "Mardi";
    day3 = "Mercredi";
    day4 = "Jeudi";
    day5 = "Vendredi";
    day6 = "Samedi";
    day7 = "Dimanche";
    trweek = "semaine: ";
    tralarm = "alarmes";
    trsettings = "parametres";
    tralarm1 = "alarme 1";
    tralarm2 = "alarme 2";
    trpress = "pressez 'menu'";
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
    tralarm = "alarms";
    trsettings = "settings";
    tralarm1 = "alarm 1";
    tralarm2 = "alarm 2";
    trpress = "press 'menu'";
  }
  millisprocess = millis();
  waitminute = millisprocess;
  waitloop = millisprocess;
}

byte pressbutton() {
  int val = analogRead(A0);

  if (val < 50)
    return menu_button;
  else if (val < 250)
    return up_button;
  else if (val < 450)
    return down_button;
  else if (val < 850) {
    return select_button;
  } else
    return release_buttons;
}

void hourpass() {
  minute++;
  if (minute == 60) {
    hour++;
    minute = 00;

    if (hour == 24) {
      day++;
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
}

void hourshow() {

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
}
void inloop() {
  if (pressbutton() >= 1) {
    if (isring == true) {
      isring = false;
      digitalWrite(buzzerpin, LOW);
    }
    if (menu == 0) {
      analogWrite(10, 225);
      ison = true;
      menu = 1;
      millisprocess = millis();
      waitime = millisprocess;
    }
  }
  if (menu == 1) {
    if (ison) {
      millisprocess = millis();
      hourshow();
      if (millisprocess - waitime >= ontime) {
        menu = 0;
        ison = false;
        analogWrite(10, 0);
        digitalWrite(almledpin, LOW);
        lcd.clear();
      }
    }

    if (pressbutton() == 1) {
      menu = 2;
    }
  }

  if (menu == 2) {
    if (pressbutton() == 4) {
      menu = 1;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+ ");
    lcd.print(tralarm);
    lcd.setCursor(0, 1);
    lcd.print("- ");
    lcd.print(trsettings);
    if (pressbutton() == 2) {
      canpass = false;
      wantedmenu = 3;
    }
  }
  if (menu == 3) {
    if (pressbutton() == 4) {
      menu = 1;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+ ");
    lcd.print(tralarm1);
    lcd.setCursor(0, 1);
    lcd.print("- ");
    lcd.print(tralarm2);
  }
}

void ring() {
  isring = true;
  digitalWrite(buzzerpin, HIGH);
  Serial.println("ring");
}

void alm() {
  if (alarmhour == hour) {
    if (alarmmn == minute) {
      ring();
    }
  }
}

void wantedchoose() {
  if (wantedmenu >= 1) {
    waitscreen();
  }
}

void waitscreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(trpress);
  if (canpass == false) {
    if (pressbutton() == 1) {
      canpass = true;
      menu = wantedmenu;
      wantedmenu = 0;
    }
  }
}

void loop() {
  millisprocess = millis();
  if (millisprocess - waitminute >= minutime) {
    millisprocess = millis();
    waitminute = millisprocess;
    hourpass();
    alm();
  }

  if (millisprocess - waitloop >= looptime) {
    millisprocess = millis();
    waitloop = millisprocess;

    inloop();
    wantedchoose();
  }
}