#include "DHT.h"
#include <Arduino.h>
#include <U8g2lib.h>

#define DHTPIN 2     // Pin digital al que está conectado el sensor DHT11
#define DHTTYPE DHT11   // Tipo de sensor DHT

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

DHT dht(DHTPIN, DHTTYPE);

float h;  // Humedad
float tc;  // Temperatura en Celsius
float tf;  // Temperatura en Fahrenheit

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  u8g2.begin(); // Inicializa la pantalla OLED
  dht.begin();  // Inicializa el sensor DHT11
}

void draw(void) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_logisoso30_tf); // tamaño fuente de la temperatura central u8g2_font_ncenB24_tr u8g2_font_logisoso30_tf
    u8g2.drawStr(78, 45, "C");
    u8g2.setCursor(32, 45);
    u8g2.print(tc, 0);
    u8g2.setFont(u8g2_font_chargen_92_tf); // fuente y tamaño de %
    u8g2.drawStr(100, 64, "%");
    u8g2.setCursor(72, 64);
    u8g2.print(h, 0);
    u8g2.setFont(u8g2_font_profont12_tr); // fuente y tamaño de temp y humedad
    u8g2.drawStr(22, 61, "Humedad");
    u8g2.drawStr(34, 8, "Temperatura");  
  } while ( u8g2.nextPage() );
  delay(9000);
}

void loop() {
  h = dht.readHumidity();
  tc = dht.readTemperature();
  tf = dht.readTemperature(true);
  draw();
}
