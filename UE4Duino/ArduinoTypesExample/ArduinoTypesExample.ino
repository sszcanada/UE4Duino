#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String Display = "   SSZ Canada   ";
String Command = "";
String str = "";

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Display = "Waiting 4 Unreal";
  lcd.setCursor(0, 0);
  lcd.print(Display);
  Serial.begin(9600);
  Serial.setTimeout(5);
}

void loop()
{
  if (!Serial.available()) return;

  str = Serial.readString();
  
  // command to send a float
  if (str.startsWith("SSZ"))
  {
    lcd.clear();
    Display = "Command Recieved";
    lcd.setCursor(0, 0);
    lcd.print(Display);
    str.remove(0, 4);
    Command = str;
    lcd.setCursor(0, 1);
    lcd.print(Command);


    delay(2000);
    lcd.clear();
    Display = "Waiting 4 Unreal";
    lcd.setCursor(0, 0);
    lcd.print(Display);
  }
  else
  {
    lcd.clear();
    Display = "Command Failed";
    lcd.setCursor(0, 0);
    lcd.print(Display);
    delay(2000);
    lcd.clear();
    Display = "Waiting 4 Unreal";
    lcd.setCursor(0, 0);
    lcd.print(Display);
  }
}
