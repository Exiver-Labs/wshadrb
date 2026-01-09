/**
 * @file wshadrb.ino
 * @brief Waveshare 2.13" E-Paper HAT Driver for ESP32 Universal Driver Board
 * @author Your Name
 * @date 2026-01-09
 * @version 1.0
 *
 * @details
 * This sketch drives a Waveshare 2.13" 3-color E-Paper HAT (black, white, red)
 * using the Waveshare ESP32 Universal Driver Board. The display is connected
 * via GPIO pins using jumper wires (NOT the FPC connector).
 *
 * Display Features:
 * - Resolution: 250x122 pixels (landscape mode)
 * - Colors: Black, White, Red
 * - Refresh time: ~15 seconds per full update
 * - Low power consumption when idle
 *
 * Connection Method:
 * - Uses VSPI hardware SPI pins for reliable communication
 * - Individual jumper wires from HAT pin header to ESP32 GPIO pins
 * - No FPC connector used
 *
 * Pin Connections (E-Paper HAT -> ESP32 Driver Board):
 * ┌─────────────┬──────────────┬─────────────────┬──────────────────┐
 * │ HAT Pin     │ ESP32 GPIO   │ Physical Pin    │ Function         │
 * ├─────────────┼──────────────┼─────────────────┼──────────────────┤
 * │ CLK         │ GPIO18       │ Pin 30 (Right)  │ VSPI SCK         │
 * │ DIN (MOSI)  │ GPIO23       │ Pin 37 (Right)  │ VSPI MOSI        │
 * │ CS          │ GPIO5        │ Pin 29 (Right)  │ VSPI CS          │
 * │ DC          │ GPIO27       │ Pin 11 (Right)  │ Data/Command     │
 * │ RST         │ GPIO26       │ Pin 10 (Right)  │ Reset            │
 * │ BUSY        │ GPIO25       │ Pin 9 (Right)   │ Busy Status      │
 * │ VCC         │ 3.3V         │ Pin 1 (Right)   │ Power            │
 * │ GND         │ GND          │ Pin 38 (Right)  │ Ground           │
 * └─────────────┴──────────────┴─────────────────┴──────────────────┘
 *
 * IMPORTANT: Why VSPI Pins?
 * - GPIO1 (UART0_TX) causes boot loops if used for SPI
 * - GPIO6-11 are flash pins and will crash the system
 * - VSPI pins (GPIO18/23/5) are dedicated hardware SPI pins
 * - See docs/gpio-conflicts.md for detailed explanation
 *
 * Libraries Required:
 * - GxEPD2 (for e-paper display control)
 * - Adafruit GFX Library (dependency of GxEPD2)
 *
 * @see https://github.com/ZinggJM/GxEPD2
 * @see docs/hardware-connections.md for wiring details
 * @see docs/gpio-conflicts.md for GPIO pin restrictions
 */

#include <GxEPD2_3C.h> // E-paper display library (3-color support)

// ============================================================================
// PIN DEFINITIONS - VSPI Configuration
// ============================================================================
// Using ESP32's VSPI hardware SPI pins for reliable communication
// These pins are specifically designed for SPI peripherals

#define EPD_CS 5    ///< Chip Select - GPIO5 (VSPI CS) - Pin 29 Right
#define EPD_DC 27   ///< Data/Command - GPIO27 - Pin 11 Right
#define EPD_RST 26  ///< Reset - GPIO26 - Pin 10 Right
#define EPD_BUSY 25 ///< Busy Status - GPIO25 - Pin 9 Right
#define EPD_MOSI 23 ///< Master Out Slave In - GPIO23 (VSPI MOSI) - Pin 37 Right
#define EPD_SCK 18  ///< Serial Clock - GPIO18 (VSPI SCK) - Pin 30 Right

#define LED_PIN 2 ///< Built-in LED for visual status indication

// ============================================================================
// DISPLAY CONFIGURATION
// ============================================================================
/**
 * Display instance for Waveshare 2.13" 3-color e-paper
 * Model: GxEPD2_213_Z98c
 * Native resolution: 122x250 (portrait)
 * Configured for: 250x122 (landscape) via setRotation(1)
 *
 * Note: The template parameter uses HEIGHT to swap dimensions for landscape
 */
GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT>
    display(GxEPD2_213_Z98c(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================
int updateCount = 0; ///< Counter for periodic display updates

// ============================================================================
// SETUP FUNCTION
// ============================================================================
/**
 * @brief Initialize hardware and display, run initial tests
 *
 * This function:
 * 1. Initializes LED for status indication
 * 2. Starts serial communication for debugging
 * 3. Initializes SPI with VSPI pins
 * 4. Initializes the e-paper display in landscape mode
 * 5. Runs comprehensive display test patterns
 *
 * LED Blink Patterns:
 * - 3 slow blinks: Setup started
 * - 5 fast blinks: SPI initialized successfully
 * - Continuous 1-second blinks: Normal operation in loop()
 */
void setup() {
  // Initialize LED for status indication
  pinMode(LED_PIN, OUTPUT);

  // Visual feedback: Setup started (3 slow blinks)
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  // Initialize Serial for debugging output
  Serial.begin(115200);
  delay(1000); // Allow serial to stabilize

  // Print configuration information
  Serial.println("\n\n=== Waveshare 2.13\" E-Paper Test ===");
  Serial.println("CORRECTED Pin Configuration (VSPI):");
  Serial.printf("  SCK  = GPIO%d (VSPI SCK)\n", EPD_SCK);
  Serial.printf("  MOSI = GPIO%d (VSPI MOSI)\n", EPD_MOSI);
  Serial.printf("  CS   = GPIO%d (VSPI CS)\n", EPD_CS);
  Serial.printf("  DC   = GPIO%d\n", EPD_DC);
  Serial.printf("  RST  = GPIO%d\n", EPD_RST);
  Serial.printf("  BUSY = GPIO%d\n", EPD_BUSY);

  // Initialize SPI with VSPI pins
  // Parameters: SCK, MISO (not used), MOSI, CS
  Serial.println("\nInitializing SPI...");
  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  Serial.println("SPI initialized successfully!");

  // Visual feedback: SPI initialized (5 fast blinks)
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  // Initialize e-paper display
  Serial.println("\nInitializing display...");
  display.init(115200); // Initialize with serial debug baud rate

  // Set display to landscape mode
  // Rotation values: 0=portrait, 1=landscape, 2=portrait 180°, 3=landscape 180°
  display.setRotation(1);

  Serial.println("Display initialized in LANDSCAPE mode!");
  Serial.printf("Display size: %dx%d pixels\n", display.width(),
                display.height());

  // Run comprehensive test patterns
  runTests();

  Serial.println("\n=== Setup Complete ===");
  Serial.println("Display will update every 30 seconds\n");
}

// ============================================================================
// MAIN LOOP
// ============================================================================
/**
 * @brief Main loop - updates display every 30 seconds
 *
 * Continuously updates the display with current status information
 * including update count and uptime. The LED blinks briefly to indicate
 * activity.
 *
 * Update interval: 30 seconds (to minimize e-paper wear)
 */
void loop() {
  updateDisplay();

  // Brief LED blink to show activity
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);

  delay(30000); // Wait 30 seconds before next update
}

// ============================================================================
// TEST PATTERNS FUNCTION
// ============================================================================
/**
 * @brief Run comprehensive display test patterns
 *
 * Executes 5 different test patterns to verify display functionality:
 * 1. Horizontal color bars (black, white, red)
 * 2. Vertical color bars (red, black, white)
 * 3. Checkerboard pattern (alternating black and red squares)
 * 4. Geometric shapes (circles, rectangles, triangles)
 * 5. Colorful text demo (multi-colored text at different sizes)
 *
 * Each test runs for 3 seconds before transitioning to the next.
 * Total test duration: ~15 seconds + display refresh time per test
 *
 * @note E-paper displays have slow refresh rates (~15s per full update)
 */
void runTests() {
  Serial.println("\n--- Running Display Tests (Landscape Mode) ---");

  // -------------------------------------------------------------------------
  // Test 1: Horizontal Color Bars
  // -------------------------------------------------------------------------
  Serial.println("Test 1: Horizontal Color Bars");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Divide display into three equal horizontal sections
    int barHeight = display.height() / 3;
    display.fillRect(0, 0, display.width(), barHeight, GxEPD_BLACK);
    display.fillRect(0, barHeight, display.width(), barHeight, GxEPD_WHITE);
    display.fillRect(0, barHeight * 2, display.width(), barHeight, GxEPD_RED);

  } while (display.nextPage());
  delay(3000);

  // -------------------------------------------------------------------------
  // Test 2: Vertical Color Bars
  // -------------------------------------------------------------------------
  Serial.println("Test 2: Vertical Color Bars");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Divide display into three equal vertical sections
    int barWidth = display.width() / 3;
    display.fillRect(0, 0, barWidth, display.height(), GxEPD_RED);
    display.fillRect(barWidth, 0, barWidth, display.height(), GxEPD_BLACK);
    display.fillRect(barWidth * 2, 0, barWidth, display.height(), GxEPD_WHITE);

  } while (display.nextPage());
  delay(3000);

  // -------------------------------------------------------------------------
  // Test 3: Checkerboard Pattern
  // -------------------------------------------------------------------------
  Serial.println("Test 3: Checkerboard Pattern");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Create alternating pattern of black and red squares
    int squareSize = 25;
    for (int x = 0; x < display.width(); x += squareSize) {
      for (int y = 0; y < display.height(); y += squareSize) {
        // Alternate colors based on grid position
        if ((x / squareSize + y / squareSize) % 2 == 0) {
          display.fillRect(x, y, squareSize, squareSize, GxEPD_BLACK);
        } else {
          display.fillRect(x, y, squareSize, squareSize, GxEPD_RED);
        }
      }
    }

  } while (display.nextPage());
  delay(3000);

  // -------------------------------------------------------------------------
  // Test 4: Geometric Shapes
  // -------------------------------------------------------------------------
  Serial.println("Test 4: Geometric Shapes");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Red circles (left side)
    display.fillCircle(40, 30, 25, GxEPD_RED);
    display.fillCircle(40, 90, 25, GxEPD_RED);

    // Black rectangles (center)
    display.fillRect(80, 10, 60, 40, GxEPD_BLACK);
    display.fillRect(80, 70, 60, 40, GxEPD_BLACK);

    // Triangles (center-right)
    display.fillTriangle(160, 20, 190, 60, 130, 60, GxEPD_RED);
    display.fillTriangle(160, 70, 190, 110, 130, 110, GxEPD_BLACK);

    // Vertical bar (right side)
    display.fillRect(210, 10, 30, 100, GxEPD_RED);

  } while (display.nextPage());
  delay(3000);

  // -------------------------------------------------------------------------
  // Test 5: Colorful Text Demo
  // -------------------------------------------------------------------------
  Serial.println("Test 5: Colorful Text Demo");
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Large title text
    display.setTextSize(2);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 10);
    display.print("Waveshare");

    // Large subtitle in red
    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 30);
    display.print("E-Paper 2.13\"");

    // Normal size text for specifications
    display.setTextSize(1);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 60);
    display.print("250x122 pixels");

    display.setCursor(5, 75);
    display.print("Landscape Mode");

    display.setCursor(5, 90);
    display.print("3 Colors: B/W/R");

    // Status message in red
    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 110);
    display.print("VSPI Working!");

  } while (display.nextPage());
  delay(3000);

  Serial.println("--- Tests Complete ---\n");
}

// ============================================================================
// PERIODIC UPDATE FUNCTION
// ============================================================================
/**
 * @brief Update display with current status information
 *
 * Creates a status dashboard showing:
 * - Red header bar with title
 * - Update counter
 * - System uptime in seconds
 * - VSPI pin configuration
 * - Display resolution
 * - Decorative corner indicators
 *
 * This function is called every 30 seconds from loop()
 *
 * @note Each call increments the global updateCount variable
 */
void updateDisplay() {
  updateCount++;

  Serial.printf("Update #%d\n", updateCount);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // Red header bar at top
    display.fillRect(0, 0, display.width(), 20, GxEPD_RED);

    // Title text in white (appears white on red background)
    display.setTextColor(GxEPD_WHITE);
    display.setTextSize(2);
    display.setCursor(5, 5);
    display.print("ESP32 Status");

    // Black divider line below header
    display.fillRect(0, 21, display.width(), 2, GxEPD_BLACK);

    // Status information in normal text size
    display.setTextSize(1);

    // Update counter in black
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 35);
    display.printf("Update: #%d", updateCount);

    // Uptime in red
    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 55);
    display.printf("Uptime: %lu sec", millis() / 1000);

    // VSPI pin info in black
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(5, 75);
    display.print("VSPI: GPIO18/23/5");

    // Display resolution in red
    display.setTextColor(GxEPD_RED);
    display.setCursor(5, 95);
    display.print("Landscape 250x122");

    // Decorative corner indicators (bottom right)
    display.fillCircle(230, 105, 8, GxEPD_RED);
    display.fillCircle(240, 105, 8, GxEPD_BLACK);

  } while (display.nextPage());
}
