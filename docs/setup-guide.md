# Setup Guide

## Getting Started with Waveshare 2.3" E-Paper Display on ESP32

This guide will help you set up and test your Waveshare 2.3" E-Paper HAT (3-color) with the ESP32 Universal Driver Board.

### Prerequisites

- Waveshare 2.3" E-Paper HAT (3-color display)
- Waveshare ESP32 Universal Driver Board
- USB cable for programming
- Computer with Arduino IDE installed

### Step 1: Hardware Assembly

1. **Connect the E-Paper HAT to the Driver Board**
   - Align the HAT connector with the driver board header
   - Ensure proper orientation (check pin 1 markers)
   - Press down firmly to secure the connection
   - Refer to [Hardware Connections](hardware-connections.md) for detailed pin mapping

2. **Connect USB Cable**
   - Connect the ESP32 Driver Board to your computer via USB
   - Ensure the board is powered (LED should indicate power)

### Step 2: Software Installation

#### Install Arduino IDE

1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the IDE following the platform-specific instructions

#### Add ESP32 Board Support

1. Open Arduino IDE
2. Go to `File` > `Preferences`
3. In "Additional Board Manager URLs", add:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
4. Click "OK"
5. Go to `Tools` > `Board` > `Boards Manager`
6. Search for "esp32"
7. Install "esp32 by Espressif Systems" (latest version)

#### Install Required Libraries

1. In Arduino IDE, go to `Sketch` > `Include Library` > `Manage Libraries`
2. Search for and install:
   - **GxEPD2** by Jean-Marc Zingg (this is the main e-paper library)
   - **Adafruit GFX Library** (dependency, usually installed automatically)

### Step 3: Configure Arduino IDE

1. **Select Board**:
   - Go to `Tools` > `Board` > `ESP32 Arduino`
   - Select your ESP32 board model (typically "ESP32 Dev Module")

2. **Select Port**:
   - Go to `Tools` > `Port`
   - Select the COM port for your ESP32 (e.g., COM3 on Windows, /dev/ttyUSB0 on Linux)

3. **Configure Upload Settings** (if needed):
   - Upload Speed: 115200
   - CPU Frequency: 240MHz (default)
   - Flash Frequency: 80MHz
   - Flash Size: 4MB (or match your board)

### Step 4: Upload Code

1. Open `wshadrb.ino` in Arduino IDE
2. Review the pin definitions to ensure they match your hardware
3. Click the "Upload" button (arrow icon) or press `Ctrl+U` (Windows/Linux) or `Cmd+U` (Mac)
4. Wait for compilation and upload to complete
5. The display should start showing test patterns

### Step 5: Verify Operation

After uploading:

1. **Serial Monitor**:
   - Open Serial Monitor (`Tools` > `Serial Monitor`)
   - Set baud rate to 115200
   - You should see test messages

2. **Display Test**:
   - The display will cycle through several test patterns:
     - Color fill test (white, black, red)
     - Rectangle test
     - Circle test
     - Line test
     - Text test
     - Mixed content test
   - Each test runs for 2-5 seconds

3. **Continuous Operation**:
   - After tests complete, the display updates every 30 seconds
   - Shows uptime and status information

### Step 6: Customize (Optional)

#### Change Display Model

If your display model is different, modify the display initialization in `wshadrb.ino`:

```cpp
// Current: GxEPD2_213_Z98c (2.3" 3-color)
// Alternatives to try:
// GxEPD2_213_Z19c
// GxEPD2_213_Z98c
// GxEPD2_213_Z19c
```

#### Adjust Pin Assignments

If using different pins, modify the pin definitions:

```cpp
#define EPD_CS    15  // Your CS pin
#define EPD_DC    27  // Your DC pin
#define EPD_RST   26  // Your RST pin
#define EPD_BUSY  25  // Your BUSY pin
```

#### Change Update Interval

Modify the delay in `loop()`:

```cpp
void loop()
{
  delay(30000);  // Change 30000 to your desired interval (milliseconds)
  updateDisplay();
}
```

### Troubleshooting

#### Display Not Working

1. **Check Connections**: Verify all pins are properly connected (see [Hardware Connections](hardware-connections.md))
2. **Power**: Ensure board is powered and 3.3V is stable
3. **Serial Output**: Check Serial Monitor for error messages
4. **Display Model**: Try different display model definitions in code
5. **Library Version**: Ensure GxEPD2 library is up to date

#### Upload Errors

1. **Port Not Found**: 
   - Check USB cable connection
   - Install USB drivers if needed (CP2102 or CH340 drivers)
   - Try different USB port

2. **Upload Failed**:
   - Hold BOOT button while clicking Upload
   - Check board selection matches your hardware
   - Reduce upload speed in Tools menu

3. **Compilation Errors**:
   - Verify all libraries are installed
   - Check for typos in code
   - Ensure ESP32 board package is installed

#### Display Shows Garbage

1. **Wrong Display Model**: Try different model definitions
2. **Pin Mismatch**: Verify pin assignments match hardware
3. **SPI Issues**: Check SPI pin connections
4. **Power Issues**: Ensure stable 3.3V supply

### Next Steps

- Customize the display content for your application
- Add sensors and display their readings
- Implement low-power modes for battery operation
- Create custom graphics and fonts
- Add WiFi connectivity for remote updates

### Additional Resources

- [Waveshare Wiki](https://www.waveshare.com/wiki/E-Paper_ESP32_Driver_Board)
- [GxEPD2 Library Documentation](https://github.com/ZinggJM/GxEPD2)
- [ESP32 Arduino Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)

### Support

For issues specific to:
- **Hardware**: Contact Waveshare support
- **Library**: Check GxEPD2 GitHub issues
- **ESP32**: Refer to Espressif documentation
