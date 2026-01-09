# Troubleshooting Guide

## Reset Loop Issues

### Problem: ESP32 Keeps Resetting

**Symptoms:**
- ESP32 continuously resets/reboots
- Serial Monitor shows reset messages repeatedly
- Display doesn't initialize

**Causes and Solutions:**

#### 1. GPIO1 (SCK) Conflict with Serial

**Cause:** GPIO1 is used for SPI SCK but is also UART0_TX. When `Serial.begin()` is called, it conflicts with SPI.

**Solution:**
- Serial is disabled by default in the code (`ENABLE_SERIAL = false`)
- If you enabled Serial and get reset loops, set `ENABLE_SERIAL` back to `false` in `wshadrb.ino`
- The code will work without Serial debugging

**To enable Serial (if needed):**
1. Open `wshadrb.ino`
2. Change `#define ENABLE_SERIAL false` to `#define ENABLE_SERIAL true`
3. Be aware this may cause reset loops on some boards
4. If reset loops occur, disable Serial again

#### 2. GPIO10 (CS) Issues

**Cause:** Some ESP32 boards have restrictions on GPIO10.

**Solution:**
- GPIO10 should work for SPI CS on most ESP32 boards
- If you experience issues, you may need to use a different pin (requires hardware modification)

#### 3. Power Supply Issues

**Cause:** Insufficient or unstable power supply.

**Solution:**
- Use a high-quality USB cable (not a charging-only cable)
- Ensure USB port provides adequate power (500mA+)
- Try a powered USB hub
- Check for voltage drops during display refresh (can draw 50-200mA)

#### 4. Watchdog Timer

**Cause:** Long display operations (1-3 seconds) may trigger watchdog timer.

**Solution:**
- The code includes delays to prevent this
- If issues persist, you can disable watchdog (not recommended):
  ```cpp
  disableCore0WDT();
  disableCore1WDT();
  ```

#### 5. Incorrect Pin Connections

**Cause:** Pins not connected according to the pin diagram.

**Solution:**
- Verify all connections match the pin diagram exactly
- Check for loose connections
- Verify pin numbers (GPIO numbers, not physical pin positions)

## Display Not Working

### Problem: Display Shows Nothing

**Solutions:**
1. **Check Power:**
   - Verify 3.3V is present
   - Check GND connection
   - Measure voltage at VCC pin

2. **Check Connections:**
   - Verify all 8 pins are connected correctly
   - Check for loose connections
   - Verify pin assignments match code

3. **Check Display Model:**
   - Try different display model in code:
     ```cpp
     // Try these alternatives:
     GxEPD2_213_Z98c  // Current
     GxEPD2_213_Z19c  // Alternative 1
     GxEPD2_213_Z98c  // Alternative 2
     ```

4. **Check Library:**
   - Ensure GxEPD2 library is installed
   - Try reinstalling the library
   - Check library version compatibility

### Problem: Display Shows Garbage/Corrupted Image

**Solutions:**
1. **Wrong Display Model:**
   - Try different display model class (see above)

2. **SPI Issues:**
   - Verify SPI pins are correct (GPIO1 for SCK, GPIO19 for MOSI)
   - Check SPI initialization

3. **Power Issues:**
   - Ensure stable 3.3V supply
   - Check for voltage drops during refresh

4. **Partial Refresh Ghosting:**
   - Use full refresh periodically
   - Clear screen before major updates

## Upload Issues

### Problem: Code Won't Upload

**Solutions:**
1. **Port Selection:**
   - Check Tools > Port in Arduino IDE
   - Try different USB port
   - Reconnect USB cable

2. **Board Selection:**
   - Verify correct ESP32 board is selected
   - Try "ESP32 Dev Module" if unsure

3. **Upload Mode:**
   - Hold BOOT button while clicking Upload
   - Release BOOT button after upload starts
   - Some boards require this for first upload

4. **Drivers:**
   - Install USB-to-Serial drivers (CP2102, CH340, etc.)
   - Check Device Manager (Windows) for unrecognized devices

5. **Upload Speed:**
   - Try reducing upload speed in Tools menu
   - Use 115200 baud or lower

## Compilation Errors

### Problem: Library Not Found

**Solutions:**
1. Install GxEPD2 library:
   - Sketch > Include Library > Manage Libraries
   - Search "GxEPD2"
   - Install by Jean-Marc Zingg

2. Install Adafruit GFX Library:
   - Usually installed automatically with GxEPD2
   - If not, install manually

3. Install ESP32 Board Support:
   - File > Preferences > Additional Board Manager URLs
   - Add: `https://dl.espressif.com/dl/package_esp32_index.json`
   - Tools > Board > Boards Manager > Search "esp32" > Install

### Problem: Pin Definition Errors

**Solutions:**
- Verify pin numbers are valid GPIO pins
- Check for typos in pin definitions
- Ensure pin numbers match your hardware

## Performance Issues

### Problem: Display Updates Very Slowly

**Cause:** E-paper displays are inherently slow (1-3 seconds per refresh).

**Solutions:**
- This is normal behavior
- Use partial refresh for faster updates (may cause ghosting)
- Update only when content changes
- Don't update more than once every few seconds

### Problem: Display Flickers or Shows Partial Updates

**Solutions:**
1. **Use Full Refresh:**
   - Call `display.display(false)` for full refresh
   - Use periodically to clear ghosting

2. **Clear Before Update:**
   - Call `display.fillScreen(GxEPD_WHITE)` before new content

3. **Wait for Busy:**
   - Ensure display finishes previous update before starting new one

## Still Having Issues?

1. **Check Serial Output:**
   - Enable Serial (`ENABLE_SERIAL = true`) if possible
   - Look for error messages
   - Note: May cause reset loops on some boards

2. **Verify Hardware:**
   - Test with known-good components
   - Check for damaged pins or connections
   - Verify display model number

3. **Try Minimal Code:**
   - Start with simplest possible code
   - Add features one at a time
   - Isolate the problem

4. **Check Documentation:**
   - Review [Hardware Connections](hardware-connections.md)
   - Check [Setup Guide](setup-guide.md)
   - Review [Display Specifications](display-specifications.md)

5. **Community Resources:**
   - Waveshare Wiki
   - GxEPD2 GitHub Issues
   - ESP32 Forums

## Common Mistakes

1. **Using Wrong Pin Numbers:**
   - Confusing GPIO numbers with physical pin positions
   - Using default SPI pins instead of custom pins

2. **Serial Conflict:**
   - Enabling Serial when GPIO1 is used for SPI SCK
   - Forgetting to disable Serial when experiencing reset loops

3. **Power Issues:**
   - Using insufficient power supply
   - Long or thin USB cables causing voltage drops

4. **Library Issues:**
   - Wrong version of GxEPD2 library
   - Missing dependencies
   - Incompatible ESP32 board package version

5. **Display Model Mismatch:**
   - Using wrong display class in code
   - Not checking actual display model number
