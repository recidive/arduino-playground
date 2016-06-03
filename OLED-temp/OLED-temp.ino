
#include <U8glib.h>
#include <Adafruit_BMP085.h>




// The OLED display.
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

// The BMP180 sensor.
Adafruit_BMP085 bmp;

void drawTemp(void) {
  u8g.setFont(u8g_font_fub25);

  char buf[20];
  double temp = bmp.readTemperature();

  dtostrf(temp, 6, 1, buf);
  
  u8g.drawStr(0, 50, buf);
}

void setup(void) {
  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }
}

void loop(void) {
  // Picture loop.
  u8g.firstPage();  
  do {
    drawTemp();
  } while (u8g.nextPage());
  
  // Rebuild the picture after some delay.
  delay(1000);
}

