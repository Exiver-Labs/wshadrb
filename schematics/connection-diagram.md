# Connection Diagram

## Waveshare 2.13" E-Paper HAT to ESP32 Driver Board

> [!IMPORTANT]
> **Connection Method:** This diagram shows **GPIO pin connections using jumper wires**, NOT the FPC connector. Individual wires connect the HAT's pin header to ESP32 GPIO pins.

> [!WARNING]
> **CRITICAL:** This uses **VSPI pins** (GPIO18/23/5). The old configuration (GPIO1/10/19) caused boot failures and is **NOT SAFE**. See `docs/gpio-conflicts.md` for details.

### Pin Connection Schematic

```
┌─────────────────────────────────────────────────────────────┐
│                    ESP32 Driver Board                        │
│                                                              │
│  ┌────────────────────────────────────────────────────┐    │
│  │              ESP32 Microcontroller                  │    │
│  │                                                      │    │
│  │  IO18 ────┐  (VSPI SCK)                            │    │
│  │  IO23 ────┤  (VSPI MOSI)                           │    │
│  │  IO5  ────┤  (VSPI CS)                             │    │
│  │  IO25 ────┤  (BUSY)                                │    │
│  │  IO26 ────┤  (RST)                                 │    │
│  │  IO27 ────┤  (DC)                                  │    │
│  │  3.3V ────┤                                         │    │
│  │  GND  ────┤                                         │    │
│  └───────────┼─────────────────────────────────────────┘    │
│              │                                               │
│              │ Jumper Wire Connections                       │
│              │ (8 individual wires)                          │
└──────────────┼───────────────────────────────────────────────┘
               │
               │ Female-to-Female Jumper Wires
               │
┌──────────────┼───────────────────────────────────────────────┐
│              │                                               │
│              │ Pin Header (PH2.0 connector)                  │
│              │                                               │
│  ┌───────────┼─────────────────────────────────────────┐    │
│  │           │          E-Paper HAT                     │    │
│  │           │                                          │    │
│  │  CLK  ◄───┼─── GPIO18 (VSPI SCK)                    │    │
│  │  DIN  ◄───┼─── GPIO23 (VSPI MOSI)                   │    │
│  │  CS   ◄───┼─── GPIO5  (VSPI CS)                     │    │
│  │  DC   ◄───┼─── GPIO27                               │    │
│  │  RST  ◄───┼─── GPIO26                               │    │
│  │  BUSY ────┼─── GPIO25                               │    │
│  │  VCC  ◄───┼─── 3.3V                                 │    │
│  │  GND  ◄───┼─── GND                                  │    │
│  │           │                                          │    │
│  │  ┌──────────────────────────────────────┐           │    │
│  │  │   2.13" E-Paper Display              │           │    │
│  │  │   (250x122 pixels - Landscape)       │           │    │
│  │  │   Colors: Black, White, Red          │           │    │
│  │  └──────────────────────────────────────┘           │    │
│  └──────────────────────────────────────────────────────┘    │
│                                                              │
└──────────────────────────────────────────────────────────────┘
```

### Connection Table (CORRECTED - VSPI Pins)

| Signal | E-Paper HAT | ESP32 GPIO | Physical Pin | Function | Notes |
|--------|-------------|-----------|--------------|----------|-------|
| Power  | VCC         | 3.3V      | Pin 1 (Right) | Power supply | 3.3V only! |
| Ground | GND         | GND       | Pin 38 (Right) | Common ground | |
| Clock  | CLK         | **GPIO18** | **Pin 30 (Right)** | **VSPI SCK** | ✅ Safe |
| Data   | DIN         | **GPIO23** | **Pin 37 (Right)** | **VSPI MOSI** | ✅ Safe |
| Select | CS          | **GPIO5**  | **Pin 29 (Right)** | **VSPI CS** | ✅ Safe |
| Control| DC          | GPIO27 | Pin 11 (Right) | Data/Command | ✅ Safe |
| Reset  | RST         | GPIO26 | Pin 10 (Right) | Reset signal | ✅ Safe |
| Status | BUSY        | GPIO25 | Pin 9 (Right) | Busy indicator | ✅ Safe |

### ❌ OLD CONFIGURATION (DO NOT USE!)

| Signal | OLD GPIO | Why It Failed |
|--------|----------|---------------|
| CLK    | ~~GPIO1~~  | ❌ UART0_TX - Causes boot loops |
| DIN    | ~~GPIO19~~ | ⚠️ Works but not VSPI |
| CS     | ~~GPIO10~~ | ❌ Flash pin - System crashes |

**Never use GPIO1, GPIO6-11 for external peripherals!**

### VSPI Bus Configuration (CORRECTED)

```
ESP32 (Master)                    E-Paper Display (Slave)
─────────────────                 ──────────────────────
GPIO18 (VSPI SCK)  ──────────────►  CLK  (Clock)
GPIO23 (VSPI MOSI) ──────────────►  DIN  (Data In)
GPIO5  (VSPI CS)   ──────────────►  CS   (Chip Select)
GPIO27 (DC)        ──────────────►  DC   (Data/Command)
GPIO26 (RST)       ──────────────►  RST  (Reset)
GPIO25 (BUSY)      ◄──────────────  BUSY (Status)
3.3V               ──────────────►  VCC  (Power)
GND                ──────────────►  GND  (Ground)
```

### Physical Wiring Diagram

```
ESP32 Driver Board (Right Side)          E-Paper HAT
─────────────────────────────            ────────────
Pin 1  (3.3V)    ═══════════════════════► VCC
Pin 9  (GPIO25)  ═══════════════════════► BUSY
Pin 10 (GPIO26)  ═══════════════════════► RST
Pin 11 (GPIO27)  ═══════════════════════► DC
Pin 29 (GPIO5)   ═══════════════════════► CS
Pin 30 (GPIO18)  ═══════════════════════► CLK
Pin 37 (GPIO23)  ═══════════════════════► DIN
Pin 38 (GND)     ═══════════════════════► GND

Legend: ═══ = Female-to-Female Jumper Wire
```

### Physical Layout (Top View)

```
                    E-Paper HAT
        ┌──────────────────────────────┐
        │                              │
        │    ┌──────────────────┐     │
        │    │                  │     │
        │    │  2.13" Display   │     │
        │    │   (250x122)      │     │
        │    │   Landscape      │     │
        │    └──────────────────┘     │
        │                              │
        │  [8-Pin Header]              │
        └──────────┬───────────────────┘
                   │
                   │ 8 Jumper Wires
                   │ (Female-Female)
                   │
        ┌──────────▼───────────────────┐
        │   ESP32 Driver Board         │
        │                              │
        │  ┌──────────────────────┐   │
        │  │     ESP32 Module     │   │
        │  │   (30-pin headers)   │   │
        │  └──────────────────────┘   │
        │                              │
        │  [GPIO Pin Headers]          │
        │   (Right side: Pins 1-38)    │
        │                              │
        │  [USB-C Connector]           │
        └──────────────────────────────┘
```

### Power Distribution

```
USB Power (5V)
    │
    ▼
ESP32 Driver Board
    │
    ├──► 3.3V Regulator ────► VCC (E-Paper HAT)
    │                          │
    │                          └──► Display Controller
    │                          │
    │                          └──► E-Ink Panel (during refresh)
    │
    └──► ESP32 Module (3.3V)
    │
    └──► GND ────────────────► GND (E-Paper HAT)
```

### Signal Flow

**Write Operation (ESP32 → Display):**
1. ESP32 sets CS low (select display)
2. ESP32 sets DC high (data mode) or low (command mode)
3. ESP32 sends clock pulses on GPIO18 (SCK)
4. ESP32 sends data bits on GPIO23 (MOSI)
5. Display receives data on DIN
6. ESP32 sets CS high (deselect)

**Status Check (Display → ESP32):**
1. ESP32 reads BUSY pin (GPIO25)
2. High = Display is busy (refreshing)
3. Low = Display is ready for next command

**Display Refresh Cycle:**
1. Send image data via SPI
2. Send refresh command
3. Wait for BUSY to go LOW (~15 seconds)
4. Display update complete

### Hardware SPI vs Software SPI

This configuration uses **Hardware SPI (VSPI)**:
- ✅ **Faster**: Hardware-accelerated SPI transfers
- ✅ **Reliable**: Dedicated SPI peripheral
- ✅ **Lower CPU usage**: DMA support available
- ✅ **No boot conflicts**: Safe GPIO pins

### Notes

- **All signals are 3.3V logic levels** - Do NOT use 5V!
- **SPI communication is unidirectional** for data (MOSI only, no MISO)
- **BUSY is an output** from display, input to ESP32
- **RST and DC are control signals** from ESP32
- **CS is active low** (LOW = selected, HIGH = deselected)
- **Display draws power** only during refresh operations (~15 seconds)
- **Connection method**: Individual jumper wires, NOT FPC connector
- **Wire type**: Female-to-Female jumper wires (8 wires minimum)

### Troubleshooting

**If ESP32 won't boot:**
- ❌ Check you're NOT using GPIO1, GPIO6-11
- ✅ Verify GPIO18, GPIO23, GPIO5 are connected correctly
- ✅ Ensure no shorts between wires

**If display doesn't work:**
- Check BUSY pin connection (GPIO25)
- Verify 3.3V power supply is stable
- Check all 8 wires are firmly connected
- Verify display model matches code (GxEPD2_213_Z98c)

### References

- See `docs/hardware-connections.md` for detailed pin descriptions
- See `docs/gpio-conflicts.md` for GPIO restrictions
- See `wshadrb.ino` for pin definitions in code

