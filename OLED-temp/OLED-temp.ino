
#include <U8glib.h>
#include <Adafruit_BMP085.h>

// The OLED display.
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

// The BMP180 sensor.
Adafruit_BMP085 bmp;

// Draw temperature to the OLED display.
void drawTemp(char* buf) {
  u8g.setFont(u8g_font_fub25);
  u8g.drawStr(0, 50, buf);
}

// Read temperature sensor.
double readTemp() {
  // Read BMP180 sensor.
  return bmp.readTemperature();
}

void setup(void) {
  // Start serial log.
  Serial.begin(9600);

  // Start BMP180 sensor.
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }
}

void loop(void) {
  // Read temperature sensor.
  double temp = readTemp();

  // Create temp display buffer.
  char buf[20];

  // Fill in buffer for displaying.
  dtostrf(temp, 6, 1, buf);

  // Picture loop.
  u8g.firstPage();  
  do {
    drawTemp(buf);
  } while (u8g.nextPage());
  
  // Rebuild the picture after some delay.
  delay(1000);
}

