/**
 * Read temperature from a BMP180 sensor and print it on a OLED
 * 128x64 display.
 */

#include <U8glib.h>
#include <Adafruit_BMP085.h>

// The OLED display.
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

// The BMP180 sensor.
Adafruit_BMP085 bmp;

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

  // Update display.
  draw(temp);
  
  // Rebuild the picture after some delay.
  delay(1000);
}

// Update display information.
void draw(double temp) {
  // Picture loop.
  u8g.firstPage();  
  do {
    drawTemp(temp);
  } while (u8g.nextPage());
}

// Draw temperature to the OLED display.
void drawTemp(double temp) {
  // Create temp display buffer.
  char buf[20];

  // Fill in buffer for displaying.
  dtostrf(temp, 6, 1, buf);

  // Set font and draw the string.
  u8g.setFont(u8g_font_fub25);
  u8g.drawStr(0, 50, buf);
}

// Read temperature sensor.
double readTemp() {
  // Read BMP180 sensor.
  return bmp.readTemperature();
}

