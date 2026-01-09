/*
 * Waveshare 2.13" E-Paper HAT - ESP32 Driver Test
 * CORRECTED Pin Configuration using VSPI
 *
 * Pin Connections:
 * E-Paper HAT -> ESP32 Driver Board
 * CLK  -> GPIO18 (Pin 30 Right) - VSPI SCK
 * DIN  -> GPIO23 (Pin 37 Right) - VSPI MOSI
 * CS   -> GPIO5  (Pin 29 Right) - VSPI CS
 * DC   -> GPIO27 (Pin 11 Right)
 * RST  -> GPIO26 (Pin 10 Right)
 * BUSY -> GPIO25 (Pin 9 Right)
 * VCC  -> 3.3V   (Pin 1 Right)
 * GND  -> GND    (Pin 38 Right)
 */

// Using built-in default font (no external font files needed)
#include <GxEPD2_3C.h>

// Pin definitions - CORRECTED for VSPI
#define EPD_CS 5    // GPIO5 (VSPI CS) - Pin 29 Right
#define EPD_DC 27   // GPIO27 - Pin 11 Right
#define EPD_RST 26  // GPIO26 - Pin 10 Right
#define EPD_BUSY 25 // GPIO25 - Pin 9 Right
#define EPD_MOSI 23 // GPIO23 (VSPI MOSI) - Pin 37 Right
#define EPD_SCK 18  // GPIO18 (VSPI SCK) - Pin 30 Right

#define LED_PIN 2 // Built-in LED for status indication

// Display instance for 2.13" 3-color e-paper (black, white, red)
// GxEPD2_213_Z98c: 122x250 (portrait), using landscape mode: 250x122
// Landscape mode: WIDTH and HEIGHT are swapped
GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT>
    display(GxEPD2_213_Z98c(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

int updateCount = 0;

void setup() {
  // Initialize LED for status indication
  pinMode(LED_PIN, OUTPUT);

  // Blink 3 times - setup started
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  // Initialize Serial for debugging
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n\n=== Waveshare 2.13\" E-Paper Test ===");
  Serial.println("CORRECTED Pin Configuration (VSPI):");
  Serial.printf("  SCK  = GPIO%d (VSPI SCK)\n", EPD_SCK);
  Serial.printf("  MOSI = GPIO%d (VSPI MOSI)\n", EPD_MOSI);
  Serial.printf("  CS   = GPIO%d (VSPI CS)\n", EPD_CS);
  Serial.printf("  DC   = GPIO%d\n", EPD_DC);
  Serial.printf("  RST  = GPIO%d\n", EPD_RST);
  Serial.printf("  BUSY = GPIO%d\n", EPD_BUSY);

  // Initialize SPI with VSPI pins
  Serial.println("\nInitializing SPI...");
  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  Serial.println("SPI initialized successfully!");

  // Blink 5 times fast - SPI initialized
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  // Initialize display
  Serial.println("\nInitializing display...");
  display.init(115200);
  display.setRotation(1); // Set to landscape mode (0=portrait, 1=landscape,
                          // 2=portrait 180°, 3=landscape 180°)
  Serial.println("Display initialized in LANDSCAPE mode!");
  Serial.printf("Display size: %dx%d pixels\n", display.width(),
                display.height());

  // Run test patterns
  runTests();

  Serial.println("\n=== Setup Complete ===");
  Serial.println("Display will update every 30 seconds\n");
}

void loop() {
  updateDisplay();

  // Blink LED to show activity
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);

  delay(30000); // Update every 30 seconds
}

void runTests() {
  Serial.println("\n--- Running Display Tests (Landscape Mode) ---");

  // Test 1: Color Bars (Horizontal)
  Serial.println("Test 1: Horizontal Color Bars");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Three horizontal color bars
    int barHeight = display.height() / 3;
    display.fillRect(0, 0, display.width(), barHeight, GxEPD_BLACK);
    display.fillRect(0, barHeight, display.width(), barHeight, GxEPD_WHITE);
    display.fillRect(0, barHeight * 2, display.width(), barHeight, GxEPD_RED);

  } while (display.nextPage());
  delay(3000);

  // Test 2: Vertical Color Bars
  Serial.println("Test 2: Vertical Color Bars");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Three vertical color bars
    int barWidth = display.width() / 3;
    display.fillRect(0, 0, barWidth, display.height(), GxEPD_RED);
    display.fillRect(barWidth, 0, barWidth, display.height(), GxEPD_BLACK);
    display.fillRect(barWidth * 2, 0, barWidth, display.height(), GxEPD_WHITE);

  } while (display.nextPage());
  delay(3000);

  // Test 3: Checkerboard Pattern
  Serial.println("Test 3: Checkerboard Pattern");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    int squareSize = 25;
    for (int x = 0; x < display.width(); x += squareSize) {
      for (int y = 0; y < display.height(); y += squareSize) {
        // Alternate between black and red
        if ((x / squareSize + y / squareSize) % 2 == 0) {
          display.fillRect(x, y, squareSize, squareSize, GxEPD_BLACK);
        } else {
          display.fillRect(x, y, squareSize, squareSize, GxEPD_RED);
        }
      }
    }

  } while (display.nextPage());
  delay(3000);

  // Test 4: Geometric Shapes
  Serial.println("Test 4: Geometric Shapes");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Red circles
    display.fillCircle(40, 30, 25, GxEPD_RED);
    display.fillCircle(40, 90, 25, GxEPD_RED);

    // Black rectangles
    display.fillRect(80, 10, 60, 40, GxEPD_BLACK);
    display.fillRect(80, 70, 60, 40, GxEPD_BLACK);

    // Red triangles (using lines)
    display.fillTriangle(160, 20, 190, 60, 130, 60, GxEPD_RED);
    display.fillTriangle(160, 70, 190, 110, 130, 110, GxEPD_BLACK);

    // Mixed color rectangles
    display.fillRect(210, 10, 30, 100, GxEPD_RED);

  } while (display.nextPage());
  delay(3000);

  // Test 5: Colorful Text Demo
  Serial.println("Test 5: Colorful Text Demo");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    display.setTextSize(2); // Larger text

    // Title in black
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 10);
    display.print("Waveshare");

    // Subtitle in red
    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 30);
    display.print("E-Paper 2.13\"");

    display.setTextSize(1); // Normal text

    // Features in black
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 60);
    display.print("250x122 pixels");

    display.setCursor(5, 75);
    display.print("Landscape Mode");

    display.setCursor(5, 90);
    display.print("3 Colors: B/W/R");

    // Status in red
    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 110);
    display.print("VSPI Working!");

  } while (display.nextPage());
  delay(3000);

  Serial.println("--- Tests Complete ---\n");
}

void updateDisplay() {
  updateCount++;

  Serial.printf("Update #%d\n", updateCount);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Red header bar
    display.fillRect(0, 0, display.width(), 20, GxEPD_RED);

    // Title in white (on red background)
    display.setTextColor(GxEPD_WHITE);
    display.setTextSize(2);
    display.setCursor(5, 5);
    display.print("ESP32 Status");

    // Black divider line
    display.fillRect(0, 21, display.width(), 2, GxEPD_BLACK);

    // Status information
    display.setTextSize(1);

    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 35);
    display.printf("Update: #%d", updateCount);

    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 55);
    display.printf("Uptime: %lu sec", millis() / 1000);

    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 75);
    display.print("VSPI: GPIO18/23/5");

    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 95);
    display.print("Landscape 250x122");

    // Decorative corner indicators
    display.fillCircle(230, 105, 8, GxEPD_RED);
    display.fillCircle(240, 105, 8, GxEPD_BLACK);

  } while (display.nextPage());
}
