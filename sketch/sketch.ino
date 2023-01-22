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
int alarmhour = 18;
int alarmmn = 35;
int salarmhour = 23;
int salarmmn = 23;
bool alarmon = true;
bool salarmon = true;
int minutespeed = 6000;
bool isring = false;
bool debugmode = false;
String lang = "fr";
int alarm = 0;

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
String trtoggleactive = "trtoggleactive";
String trchange = "trchange";
String tractive = "tractive";
String trdisactive = "trdisactive";
String trsetmn = "trsetmn";
String trsethour = "trsethour";
String trmn;
String trhour;
int menu = 0;
unsigned long waitime;
unsigned long waitminute;
unsigned long waitloop;
bool ison = false;
unsigned long ontime = 60000;
unsigned long minutime = 60000;
unsigned long looptime = 130;
unsigned long millisprocess;
int buzzerpin = 2;
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
    trtoggleactive = "(des)activer";
    trchange = "configurer";
    tractive = "activer";
    trdisactive = "desactiver";
    trsetmn = "reglage minute";
    trsethour = "reglage heure";
    trmn = "minute";
    trhour = " heure";
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
    trtoggleactive = "(dis)active";
    trchange = "configure";
    tractive = "active";
    trdisactive = "disactive";
    trsetmn = "minute set";
    trsethour = "hour set";
    trmn = "minute";
    trhour = "  hour";
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

void backmenu() {
  if (pressbutton() == 4) {
    menu = menu - 1;
  }
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
        lcd.clear();
      }
    }

    if (pressbutton() == 1) {
      menu = 2;
    }
  }

  if (menu == 2) {
    backmenu();
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
    backmenu();
    if (pressbutton() == 2) {
      canpass = false;
      wantedmenu = 4;
      alarm = 1;
    }
    if (pressbutton() == 3) {
      canpass = false;
      wantedmenu = 4;
      alarm = 2;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+ ");
    lcd.print(tralarm1);
    lcd.setCursor(0, 1);
    lcd.print("- ");
    lcd.print(tralarm2);
  }

  if (menu == 4) {
    backmenu();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+ ");
    lcd.print(trtoggleactive);
    lcd.setCursor(0, 1);
    lcd.print("- ");
    lcd.print(trchange);
    if (pressbutton() == 2) {
      canpass = false;
      wantedmenu = 5;
    }
    if (pressbutton() == 3) {
      canpass = false;
      wantedmenu = 6;
    }
  }
  if (menu == 5) {
    backmenu();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+ ");
    lcd.print(tractive);
    lcd.setCursor(0, 1);
    lcd.print("- ");
    lcd.print(trdisactive);
    if (pressbutton() == 2) {
      if (alarm == 1) {
        alarmon = false;
        Serial.println("alarmon false");
      } else {
        salarmon = false;
        Serial.println("salarmon false");
      }
    }
    if (pressbutton() == 3) {
      if (alarm == 1) {
        alarmon = true;
        Serial.println("alarmon true");
      } else {
        salarmon = true;
        Serial.println("salarmon true");
      }
    }
  }

  if (menu == 6) {
    backmenu();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+ ");
    lcd.print(trsetmn);
    lcd.setCursor(0, 1);
    lcd.print("- ");
    lcd.print(trsethour);
    if (pressbutton() == 2) {
      canpass = false;
      wantedmenu = 7;
    }
    if (pressbutton() == 3) {
      canpass = false;
      wantedmenu = 8;
    }
  }

  if (menu == 7) {
    backmenu();
    if (salarmmn >= 60) {
      salarmmn = 0;
    }
    if (alarmmn >= 60) {
      alarmmn = 0;
    }
    if (salarmmn < 0) {
      salarmmn = 59;
    }
    if (alarmmn < 0) {
      alarmmn = 59;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+     ");
    lcd.print(trmn);
    lcd.print(": ");
    if (alarm == 1) {
      lcd.print(alarmmn);
    } else {
      lcd.print(salarmmn);
    }
    lcd.setCursor(0, 1);
    lcd.print("- ");
  }
  if (pressbutton() == 2) {
    if (alarm == 1) {
      alarmmn++;
    } else {
      salarmmn++;
    }
  }
  if (pressbutton() == 3) {
    if (alarm == 1) {
      alarmmn--;
    } else {
      salarmmn--;
    }
  }

  if (menu == 8) {
    backmenu();
    if (salarmhour >= 24) {
      salarmhour = 0;
    }
    if (alarmhour >= 24) {
      alarmhour = 0;
    }
    if (salarmhour < 0) {
      salarmhour = 23;
    }
    if (alarmhour < 0) {
      alarmhour = 23;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("+     ");
    lcd.print(trhour);
    lcd.print(": ");
    if (alarm == 1) {
      lcd.print(alarmhour);
    } else {
      lcd.print(salarmhour);
    }
    lcd.setCursor(0, 1);
    lcd.print("- ");
  }
  if (pressbutton() == 2) {
    if (alarm == 1) {
      alarmhour++;
    } else {
      salarmhour++;
    }
  }
  if (pressbutton() == 3) {
    if (alarm == 1) {
      alarmhour--;
    } else {
      salarmhour--;
    }
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
      if (alarmon == true) {
        ring();
      }
    }
  }
  if (salarmhour == hour) {
    if (salarmmn == minute) {
      if (salarmon == true) {
        ring();
      }
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