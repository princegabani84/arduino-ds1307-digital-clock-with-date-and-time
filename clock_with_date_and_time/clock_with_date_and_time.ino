#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // change 0x27 to 0x3F if needed

// Button pins
const int btnSet  = 2;
const int btnUp   = 3;
const int btnDown = 4;

int setMode = 0; // 0=normal, 1=hour, 2=minute, 3=day, 4=month, 5=year
unsigned long lastBlink = 0;
bool blinkState = true;

DateTime now;

unsigned long lastButtonPress = 0;
unsigned long buttonRepeatDelay = 500; // first repeat delay
unsigned long buttonFastDelay = 150;   // faster repeat on hold

const char* daysOfTheWeek[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

void setup() {
  pinMode(btnSet, INPUT_PULLUP);
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC NOT found!");
    while (1);
  }

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set RTC at compile time
  }
}

void loop() {
  now = rtc.now();

  // Button handling
  if (digitalRead(btnSet) == LOW) {
    delay(300); 
    setMode++;
    if (setMode > 5) setMode = 0;
  }

  if (setMode != 0) handleSetMode();

  // Blink timing
  if (millis() - lastBlink > 500) {
    blinkState = !blinkState;
    lastBlink = millis();
  }

  // --- Display Time (12-hour with AM/PM) ---
  int hour12 = now.hour();
  String ampm = "AM";
  if (hour12 >= 12) {
    ampm = "PM";
    if (hour12 > 12) hour12 -= 12;
  }
  if (hour12 == 0) hour12 = 12;

  lcd.setCursor(0, 0);

  if (setMode == 1 && !blinkState) lcd.print("  "); 
  else print2digits(hour12);
  lcd.print(":");

  if (setMode == 2 && !blinkState) lcd.print("  "); 
  else print2digits(now.minute());
  lcd.print(":");
  print2digits(now.second());

  lcd.print(" ");
  lcd.print(ampm);

  // --- Display Date + Day ---
  lcd.setCursor(0, 1);

  if (setMode == 3 && !blinkState) lcd.print("  "); 
  else print2digits(now.day());
  lcd.print("/");

  if (setMode == 4 && !blinkState) lcd.print("  "); 
  else print2digits(now.month());
  lcd.print("/");

  if (setMode == 5 && !blinkState) lcd.print("    "); 
  else lcd.print(now.year());

  lcd.print(" ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
}


void handleSetMode() {
  int hour = now.hour();
  int minute = now.minute();
  int day = now.day();
  int month = now.month();
  int year = now.year();

  if (digitalRead(btnUp) == LOW) {
    delay(200); // small delay to avoid bouncing
    if (setMode == 1) hour = (hour + 1) % 24;
    if (setMode == 2) minute = (minute + 1) % 60;
    if (setMode == 3) day = (day % daysInMonth(month, year)) + 1;
    if (setMode == 4) month = (month % 12) + 1;
    if (setMode == 5) year++;
    rtc.adjust(DateTime(year, month, day, hour, minute, now.second()));
  }

  if (digitalRead(btnDown) == LOW) {
    delay(200); // small delay to avoid bouncing
    if (setMode == 1) hour = (hour - 1 + 24) % 24;
    if (setMode == 2) minute = (minute - 1 + 60) % 60;
    if (setMode == 3) day = (day - 1 < 1) ? daysInMonth(month, year) : day - 1;
    if (setMode == 4) month = (month - 1 < 1) ? 12 : month - 1;
    if (setMode == 5) year--;
    rtc.adjust(DateTime(year, month, day, hour, minute, now.second()));
  }
}

// --- Utility: Days in Month ---
int daysInMonth(int month, int year) {
  if (month == 2) {
    // Leap year check
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return 29;
    else return 28;
  }
  if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
  return 31;
}

void print2digits(int number) {
  if (number < 10) lcd.print("0");
  lcd.print(number);
}
