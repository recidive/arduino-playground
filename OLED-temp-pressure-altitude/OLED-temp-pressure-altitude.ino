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

// The number of the pushbutton pin.
const int buttonPin = 4;

// The display mode 0: temperature, 1: pressure, 2: altitude.
int mode = 0;

// Control if display mode has changed for better UX.
boolean modeChanged = false;

void setup(void) {
  // Start serial log.
  Serial.begin(9600);

  // Start BMP180 sensor.
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }

  // Initialize the pushbutton pin as an input.
  pinMode(buttonPin, INPUT);
}

void loop(void) {
  // Read the state of the pushbutton value.
  boolean buttonState = digitalRead(buttonPin);

  // Hold data from the sensor.
  double data;

  // Toggle display mode.
  if (buttonState) {
    if (!modeChanged) {
      mode++;
  
      // Reset if mode is greater 2.
      if (mode > 2) {
        mode = 0;
      }
      modeChanged = true;
    }
  }
  else {
    modeChanged = false;
  }

  // Draw data from sensor to the display.
  switch (mode) {
    case 0:
      // Read BMP180 temperature sensor.
      data = bmp.readTemperature();
      draw(data, "Temperature (" "\xb0" "C)");
      break;

    case 1:
      // Read BMP180 pressure sensor.
      data = bmp.readPressure();
      draw(data, "Pressure (Pa)");
      break;

    case 2:
      // Read calculated altitude.
      data = bmp.readAltitude();
      draw(data, "Altitude (m)");
      break;
  }

  // Rebuild the picture after some delay.
  delay(100);
}

// Update display information.
void draw(double data, char* label) {
  // Picture loop.
  u8g.firstPage();  
  do {
    drawData(data, label);
  } while (u8g.nextPage());
}

// Draw data to the OLED display.
void drawData(double data, char* label) {
  // Create data display buffer.
  char buf[10];

  // Fill in buffer for displaying.
  dtostrf(data, 6, 1, buf);

  // Set font and draw the label.
  u8g.setFont(u8g_font_helvR08);
  u8g.drawStr(0, 15, label);

  // Set font and draw the data.
  u8g.setFont(u8g_font_helvR24n);
  u8g.drawStr(0, 50, buf);
}

