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
boolean mode = false;

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

  // Read BMP180 temperature sensor.
  double temp = bmp.readTemperature();

  // Read BMP180 pressure sensor.
  double pressure = bmp.readPressure();

  // Toggle display mode.
  if (buttonState) {
    mode = !mode;
  }

  if (mode) {
    draw(pressure);
  }
  else {
    draw(temp);
  }

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
  //u8g.setFont(u8g_font_7x14);
  //u8g.setFont(u8g_font_robot_de_niro);
  //u8g.setFont(u8g_font_lucasfont_alternate);
  //u8g.setFont(u8g_font_helvR10);
  u8g.setFont(u8g_font_helvR08);
  u8g.drawStr(0, 15, mode ? "Pressure (Pa)" : "Temperature (" "\xb0" "C)");

  //u8g.setFont(u8g_font_fub25);
  //u8g.setFont(u8g_font_timB24);
  u8g.setFont(u8g_font_helvR24n);
  u8g.drawStr(0, 50, buf);
}

