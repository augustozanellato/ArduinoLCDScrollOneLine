#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

int screenWidth = 16;
int screenHeight = 2;

// line1 = scrolling
String line1 = "This is a very long scrolling line";
// line2 = static
String line2 = "Fixed Line";

int stringStart, stringStop = 0;
int scrollCursor = screenWidth;


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (Serial.available()){
    line1 = Serial.readString();
    Serial.println(line1);
    stringStart = line1.length();
    scrollCursor = 16;
    lcd.setCursor(16, 0);
  }
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(scrollCursor, 0);
  lcd.print(line1.substring(stringStart,stringStop));
  lcd.setCursor(0, 1);
  lcd.print(line2);
  if(stringStart == 0 && scrollCursor > 0){
    scrollCursor--;
    stringStop++;
  } else if (stringStart == stringStop){
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;
  } else if (stringStop == line1.length() && scrollCursor == 0) {
    stringStart++;
  } else if (stringStart == line1.length()) {
    stringStart = 0;
    stringStop = 0;
    scrollCursor = 16;
  } else {
    stringStart++;
    stringStop++;
  } 
  delay(400);
}

