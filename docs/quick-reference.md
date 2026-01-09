# Quick Reference Card

> [!WARNING]
> **CRITICAL:** This project uses **VSPI pins** (GPIO18/23/5). Never use GPIO1 or GPIO10 - they cause boot failures!

## Pin Connections (CORRECTED - VSPI)

**Waveshare 2.13" E-Paper HAT → ESP32 Universal Driver Board**

```
E-Paper HAT    →    ESP32 GPIO       Physical Pin      Function
────────────────────────────────────────────────────────────────
VCC            →    3.3V             Pin 1 (Right)     Power
GND            →    GND              Pin 38 (Right)    Ground
CLK            →    GPIO18 (VSPI)    Pin 30 (Right)    SPI Clock
DIN            →    GPIO23 (VSPI)    Pin 37 (Right)    SPI Data
CS             →    GPIO5  (VSPI)    Pin 29 (Right)    Chip Select
DC             →    GPIO27           Pin 11 (Right)    Data/Command
RST            →    GPIO26           Pin 10 (Right)    Reset
BUSY           →    GPIO25           Pin 9 (Right)     Busy Status
```

### ❌ OLD PINS (DO NOT USE!)
```
CLK  → ~~GPIO1~~  ❌ UART0_TX - Causes boot loops!
DIN  → ~~GPIO19~~ ⚠️ Not VSPI
CS   → ~~GPIO10~~ ❌ Flash pin - System crashes!
```

## Arduino CLI Setup (Quick Steps)

**Recommended Method:**
```bash
./setup-arduino.sh
```

**Manual Method:**
1. **Install Arduino CLI**: Follow `docs/setup-arduino-cli.md`
2. **Add ESP32 Board**: 
   ```bash
   arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   arduino-cli core install esp32:esp32
   ```
3. **Install Libraries**: 
   ```bash
   arduino-cli lib install "GxEPD2"
   arduino-cli lib install "Adafruit GFX Library"
   ```
4. **Compile & Upload**:
   ```bash
   arduino-cli compile --fqbn esp32:esp32:esp32 .
   arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32 .
   ```

## VS Code/Cursor Tasks

Press `Ctrl+Shift+P` → "Tasks: Run Task" → Select:
- **Arduino: Compile** - Build only
- **Arduino: Upload** - Build and upload
- **Arduino: Monitor Serial** - Serial monitor (115200 baud)

Or use keyboard shortcut: `Ctrl+Shift+B` (compile)

## Code Configuration

```cpp
// Pin definitions - CORRECTED for VSPI
#define EPD_CS   5    // GPIO5 (VSPI CS) - Pin 29 Right
#define EPD_DC   27   // GPIO27 - Pin 11 Right
#define EPD_RST  26   // GPIO26 - Pin 10 Right
#define EPD_BUSY 25   // GPIO25 - Pin 9 Right
#define EPD_MOSI 23   // GPIO23 (VSPI MOSI) - Pin 37 Right
#define EPD_SCK  18   // GPIO18 (VSPI SCK) - Pin 30 Right

// Display instance (landscape mode)
GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> 
    display(GxEPD2_213_Z98c(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));
```

## Display Specifications

- **Model**: Waveshare 2.13" E-Paper HAT
- **Resolution**: 250x122 pixels (landscape mode)
- **Colors**: Black, White, Red
- **Refresh Time**: ~15 seconds per full update
- **Display Type**: GxEPD2_213_Z98c

## Serial Monitor

- **Baud Rate**: 115200
- **Use**: Debugging and status messages
- **Command**: `arduino-cli monitor -p /dev/ttyACM0 -c baudrate=115200`

## Update Interval

- **Default**: 30 seconds
- **Change**: Modify `delay(30000)` in `loop()`
- **Reason**: Minimize e-paper wear

## Troubleshooting Quick Fixes

| Problem | Solution |
|---------|----------|
| **ESP32 won't boot** | ❌ Check NOT using GPIO1 or GPIO10! Use GPIO18/23/5 |
| **No display** | Check all 8 wire connections, verify 3.3V power |
| **Garbage on screen** | Verify display model is GxEPD2_213_Z98c |
| **Upload fails** | Hold BOOT button during upload, check port |
| **Library errors** | Run `./setup-arduino.sh` or reinstall libraries |
| **Permission denied** | `sudo usermod -a -G dialout $USER` then logout/login |

## Display Refresh

- **Full Refresh**: ~15 seconds (best quality, no ghosting)
- **Update Frequency**: Only when content changes
- **Power**: Display is bistable (image persists without power)

## Power Consumption

- **Sleep**: < 1µA
- **Active (ESP32)**: 10-50mA
- **Display Refresh**: 50-200mA (peak, ~15 seconds)
- **Idle**: Image persists without power (bistable)

## Connection Method

- **Type**: Individual jumper wires (female-to-female)
- **Count**: 8 wires minimum
- **NOT using**: FPC connector on driver board
- **Wiring**: HAT pin header → ESP32 GPIO pins

## File Locations

- **Code**: `wshadrb.ino`
- **Hardware Docs**: `docs/hardware-connections.md`
- **GPIO Guide**: `docs/gpio-conflicts.md` ⚠️ **Read this!**
- **Setup Guide**: `docs/setup-arduino-cli.md`
- **Specs**: `docs/display-specifications.md`
- **Schematic**: `schematics/connection-diagram.md`
- **License**: `LICENSE` (MIT - completely free!)

## Important Notes

⚠️ **NEVER use these GPIOs for external peripherals:**
- GPIO1 (UART0_TX) - Causes boot loops
- GPIO6-11 (Flash pins) - System crashes

✅ **Safe VSPI pins:**
- GPIO18 (SCK)
- GPIO23 (MOSI)
- GPIO5 (CS)

📖 **See `docs/gpio-conflicts.md` for detailed explanation**
