
#include <LiquidCrystal_I2C.h>

void printSmraza() {
    lcd.init();                      
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("Welcome to Smraza!");
}
