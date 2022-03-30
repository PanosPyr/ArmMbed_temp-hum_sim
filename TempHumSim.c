#include "mbed.h"
#include "C12832.h"
#include "Sht31.h"

C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);
Sht31 sht31(I2C_SDA, I2C_SCL);
DigitalOut led(p5);
DigitalOut led1(p6);
PwmOut speaker(p21);

void play_tone(float frequency, float volume, int interval, int rest) {
    speaker.period(1.0 / frequency);
    speaker = volume;
    wait(interval);
    speaker = 0.0;
    wait(rest);
}

int main() {

    while (1) {
        lcd.cls();

        float temp = sht31.readTemperature();
        float humidity = sht31.readHumidity();

        if(temp>35 && humidity<15){
            lcd.cls();
            led1=0;
            led=1;
            lcd.locate(3,3);
            lcd.printf("FIRE ALARM!!!");
            play_tone(800.0, 0.5, 1, 0);
            wait(0.5);
            led=0;
            lcd.cls();
            wait(0.5);
        }
        
        else if(temp<15 && humidity<15){
            lcd.cls();
            led=0;
            led1=1;
            lcd.locate(3,3);
            lcd.printf("FIRE ALARM!!!");
            play_tone(400.0, 0.5, 1, 0);
            wait(0.5);
            led1=0;
            lcd.cls();
            wait(0.5); 
        }
        
        else{
            lcd.cls();
            led=0;
            led1=0;
            lcd.locate(3,3);
            lcd.printf("Normal Conditions");
        }

        wait(0.5f);
    }
}
