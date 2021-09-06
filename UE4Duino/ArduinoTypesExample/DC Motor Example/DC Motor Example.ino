#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialization
LiquidCrystal_I2C lcd(0x27, 16, 2);
String Display = "";
String Command = "";
String str = "";
const int motor1A = 10;
const int motor2A = 9;

void setup()
{
  // Setup Display
  lcd.init();
  lcd.backlight();
  ClearDisplay();
  Serial.begin(9600);
  Serial.setTimeout(5);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
}

void loop()
{
  // Check Serial
  if (!Serial.available()) return;
  str = Serial.readString();

  // Recieved Command
  if (str.startsWith("SSZ"))
  {
    str.remove(0, 4);
    Command = str;
    VerifyCommand(Command);
  }
}

void ClearDisplay()
{
  lcd.clear();
  Display = " SSZ UE4 BRIDGE";
  lcd.setCursor(0, 0);
  lcd.print(Display);
  Display = " COMMAND  READY";
  lcd.setCursor(0, 1);
  lcd.print(Display);
}

void InvalidCommand()
{
  lcd.clear();
  Display = Command;
  lcd.setCursor(0, 1);
  lcd.print(Display);
  Display = "Invalid  Command";
  lcd.setCursor(0, 0);
  lcd.print(Display);
}

void LastCommand(String LastCom)
{
  lcd.clear();
  Display = "  LAST COMMAND";
  lcd.setCursor(0, 0);
  lcd.print(Display);
  Display = LastCom;
  lcd.setCursor(0, 1);
  lcd.print(Display);
}

void VerifyCommand(String InputCommand)
{
  if (InputCommand == String("Left"))
  {
    LastCommand(InputCommand);
    Left();
    return;
  }
  if (InputCommand == String("Right"))
  {
    LastCommand(InputCommand);
    Right();
    return;
  }
  if (InputCommand == String("StopMotor"))
  {
    LastCommand(InputCommand);
    StopMotor();
    return;
  }
  InvalidCommand();
}

void Left()//
{
  analogWrite(motor1A, 0);
  analogWrite(motor2A, 255);
}

void Right()//
{
  analogWrite(motor1A, 255);
  analogWrite(motor2A, 0);
}

void StopMotor()
{
  analogWrite(motor1A, 0);
  analogWrite(motor2A, 0);
}