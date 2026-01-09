# Quick Reference Card

## Pin Connections (At a Glance)

**Based on actual Waveshare pin diagram:**

```
E-Paper HAT    →    ESP32 GPIO    Physical Pin
──────────────────────────────────────────────
VCC            →    3.3V          Pin 1 (Right)
GND            →    GND          Multiple
DIN            →    GPIO19 (P19)  Pin 12 (Right)
CLK            →    GPIO1 (P1)   Pin 15 (Right)
CS             →    GPIO10 (P10) Pin 16 (Left)
DC             →    GPIO27 (P27) Pin 11 (Right)
RST            →    GPIO26 (P26) Pin 10 (Right)
BUSY           →    GPIO25 (P25) Pin 9 (Right)
```

## Arduino IDE Setup (Quick Steps)

1. **Add ESP32 Board URL**: `https://dl.espressif.com/dl/package_esp32_index.json`
2. **Install ESP32 Board**: Tools → Board → Boards Manager → "esp32"
3. **Install Libraries**: 
   - GxEPD2
   - Adafruit GFX (auto-installed)
4. **Select Board**: ESP32 Dev Module
5. **Upload**: Open `wshadrb.ino` → Upload

## Code Configuration

```cpp
// Pin definitions (based on Waveshare pin diagram)
#define EPD_CS    10  // P10 (Pin 16 left side)
#define EPD_DC    27  // P27 (Pin 11 right side)
#define EPD_RST   26  // P26 (Pin 10 right side)
#define EPD_BUSY  25  // P25 (Pin 9 right side)
#define EPD_MOSI  19  // P19 (Pin 12 right side) - DIN
#define EPD_SCK   1   // P1 (Pin 15 right side) - CLK

// Display model (try alternatives if needed)
GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> display(...);
```

## Common Display Models

- `GxEPD2_213_Z98c` - Most common 2.3" 3-color
- `GxEPD2_213_Z19c` - Alternative model
- Check your HAT label for exact model number

## Serial Monitor

- **Baud Rate**: 115200
- **Use**: Debugging and status messages

## Update Interval

Default: 30 seconds
Change: Modify `delay(30000)` in `loop()`

## Troubleshooting Quick Fixes

| Problem | Solution |
|---------|----------|
| No display | Check connections, verify power |
| Garbage on screen | Try different display model |
| Upload fails | Hold BOOT button, check port |
| Library errors | Reinstall GxEPD2 library |

## Display Refresh

- **Full Refresh**: 1-3 seconds (best quality)
- **Partial Refresh**: 0.5-1 second (faster, may ghost)
- **Update Frequency**: Only when content changes

## Power Consumption

- **Sleep**: < 1µA
- **Active**: 10-50mA
- **Refresh**: 50-200mA (peak)
- **Bistable**: Image persists without power

## File Locations

- **Code**: `wshadrb.ino`
- **Hardware Docs**: `docs/hardware-connections.md`
- **Setup Guide**: `docs/setup-guide.md`
- **Specs**: `docs/display-specifications.md`
- **Schematic**: `schematics/connection-diagram.md`
