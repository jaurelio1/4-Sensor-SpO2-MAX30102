#include <rtc.h>           // biblioteca RTC
#include <SPI.h>              // caso utilize comunicação SPI
#include <Wire.h>             // biblioteca requerida para I2C
#include <Adafruit_GFX.h>     // biblioteca OLED
#include <display.h> // biblioteca OLED

DS3231 rtc(SDA, SCL); // cria o objeto rtc

// configuração do display OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaração para um display SSD1306 conectado a I2C (pinos SDA, SCL)
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(9600); // inicializa o monitor serial (usado para testes)

  rtc.begin(); // inicializa o RTC
  // **** Altere as linhas abaixo para ajustar a hora e data do RTC ********
  rtc.setDOW(TUESDAY);      // Altere o dia da semana SUNDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY e SATURDAY
  rtc.setTime(11, 29, 40);  // Altere o tempo: hora, minutos, segundos (formato de 24 horas)
  rtc.setDate(27, 9, 2021); // Dia, mês, Ano

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa a comunicação I2C do OLED end 0X3C

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // teste RTC - exibir no monitor serial
  Serial.println(rtc.getDateStr());
  Serial.println(rtc.getDOWStr());
  Serial.print(rtc.getTemp());
  Serial.println(" ºC");
  Serial.print("Hora: ");
  Serial.print(rtc.getTimeStr());
}

void loop()
{

  String time = rtc.getTimeStr();

  if (time.charAt(0) == '1' && time.charAt(1) == '1' && time.charAt(3) == '3' && time.charAt(4) == '0')
  {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(13, 0);
    display.print(rtc.getTimeStr());
    display.setTextColor(WHITE);
    display.setCursor(0, 27);
    display.print("HORA DO REMEDIO!!!!");
  }
  else
  {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Despertador para remedio: todo dia 11h30");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(13, 37);
    display.print(rtc.getTimeStr());
  }

  // exibe no display
  display.display();

  // limpa o display
  display.clearDisplay();
}