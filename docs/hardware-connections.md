# Hardware Connections

## Waveshare 2.13" E-Paper HAT to ESP32 Universal Driver Board

> [!IMPORTANT]
> **Connection Method:** This setup uses **individual jumper wires** to connect the E-Paper HAT's pin header to the ESP32 Driver Board's GPIO pins. **Do NOT use the FPC (Flexible Printed Circuit) connector** on the driver board. We are connecting via the GPIO pin headers using female-to-female jumper wires.

This document describes the pin connections between the Waveshare 2.13" E-Paper HAT (3-color display) and the Waveshare ESP32 Universal Driver Board using VSPI pins.

### Pin Mapping

**IMPORTANT**: These are the actual pin assignments based on the Waveshare pin diagram:

| E-Paper HAT Pin | ESP32 GPIO | Physical Pin | Function | Notes |
|----------------|------------|--------------|----------|-------|
| VCC            | 3.3V       | Pin 1 (Right) | Power    | 3.3V power supply |
| GND            | GND        | Pin 38 (Right) | Ground   | Common ground |
| DIN (MOSI)     | GPIO23 (P23) | Pin 37 (Right) | SPI Data | VSPI MOSI |
| CLK (SCK)      | GPIO18 (P18) | Pin 30 (Right) | SPI Clock| VSPI SCK |
| CS             | GPIO5 (P5) | Pin 29 (Right) | Chip Select | VSPI CS |
| DC             | GPIO27 (P27) | Pin 11 (Right) | Data/Command | Data/Command control |
| RST            | GPIO26 (P26) | Pin 10 (Right) | Reset    | Display reset pin |
| BUSY           | GPIO25 (P25) | Pin 9 (Right) | Busy     | Display busy status |

### Connection Diagram

```
E-Paper HAT          ESP32 Driver Board
┌─────────────┐      ┌──────────────────┐
│   VCC       │──────│  3.3V (Pin 1 R)   │
│   GND       │──────│  GND (Pin 38 R)   │
│   DIN       │──────│  GPIO23 (P23)     │
│             │      │  Pin 37 (Right)   │
│   CLK       │──────│  GPIO18 (P18)     │
│             │      │  Pin 30 (Right)   │
│   CS        │──────│  GPIO5 (P5)       │
│             │      │  Pin 29 (Right)   │
│   DC        │──────│  GPIO27 (P27)     │
│             │      │  Pin 11 (Right)   │
│   RST       │──────│  GPIO26 (P26)     │
│             │      │  Pin 10 (Right)   │
│   BUSY      │──────│  GPIO25 (P25)     │
│             │      │  Pin 9 (Right)    │
└─────────────┘      └──────────────────┘
```

### Physical Connection

1. Align the E-Paper HAT connector with the ESP32 Driver Board header
2. Ensure proper orientation (check for pin 1 markers or keying)
3. Press down firmly to ensure all pins make contact
4. Verify connections are secure before powering on

### Power Requirements

- **Voltage**: 3.3V
- **Current**: Varies during refresh (typically 10-50mA, up to 200mA during refresh)
- **Power Source**: ESP32 Driver Board 3.3V regulator

### SPI Configuration

The display uses SPI (Serial Peripheral Interface) communication:
- **SPI Mode**: Mode 0 (CPOL=0, CPHA=0)
- **Clock Speed**: Up to 10MHz (display dependent)
- **Bit Order**: MSB first

### Important Notes

1. **Power Sequence**: Always power on the ESP32 board before connecting the display
2. **Static Protection**: Handle the E-Paper HAT carefully to avoid static discharge
3. **Refresh Rate**: E-paper displays have a slow refresh rate (1-3 seconds). Avoid frequent updates
4. **Temperature**: E-paper displays work best at room temperature (0-50°C)
5. **Orientation**: The display can be rotated in software (see code comments)

### Troubleshooting

If the display doesn't work:

1. **Check Connections**: Verify all pins are properly connected according to the pin diagram
2. **Power**: Ensure 3.3V is present and stable
3. **SPI Pins**: Verify SPI pins match the code configuration (GPIO1 for SCK, GPIO19 for MOSI)
4. **GPIO1 Conflict**: GPIO1 is also UART0_TX. If you experience issues:
   - On most ESP32 dev boards, Serial uses USB pins, not GPIO1, so this shouldn't be a problem
   - If Serial conflicts occur, try commenting out Serial.begin() and Serial.print() statements
   - Or use Serial1 on different pins for debugging
5. **Display Model**: Confirm your display model matches the code (see code comments for alternatives)
6. **Library**: Ensure GxEPD2 library is installed correctly
7. **Serial Monitor**: Check Serial Monitor (115200 baud) for error messages and pin confirmation
8. **SPI Initialization**: The code initializes SPI with custom pins - ensure this happens before display.init()

### Alternative Pin Configurations

The pin definitions in `wshadrb.ino` match the Waveshare pin diagram:

```cpp
#define EPD_CS    5   // P5 (Pin 29 right side) - VSPI CS
#define EPD_DC    27  // P27 (Pin 11 right side)
#define EPD_RST   26  // P26 (Pin 10 right side)
#define EPD_BUSY  25  // P25 (Pin 9 right side)
#define EPD_MOSI  23  // P23 (Pin 37 right side) - VSPI MOSI
#define EPD_SCK   18  // P18 (Pin 30 right side) - VSPI SCK
```

**Important Notes:**
- These pins use the ESP32's standard VSPI interface (GPIO18=SCK, GPIO23=MOSI, GPIO5=CS)
- **AVOID GPIO1 (UART0_TX)** and **GPIO10 (flash pin)** - they cause boot failures and system crashes
- **AVOID GPIO6-GPIO11** - these are connected to internal flash memory
- The code initializes SPI with VSPI pins: `SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS)`

If you need to use different pins, modify the pin definitions in `wshadrb.ino` and ensure SPI is initialized with the correct pins.
