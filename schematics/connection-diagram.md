# Connection Diagram

## Waveshare 2.3" E-Paper HAT to ESP32 Driver Board

### Pin Connection Schematic

```
┌─────────────────────────────────────────────────────────────┐
│                    ESP32 Driver Board                        │
│                                                              │
│  ┌────────────────────────────────────────────────────┐    │
│  │              ESP32 Microcontroller                  │    │
│  │                                                      │    │
│  │  IO13 ────┐                                         │    │
│  │  IO14 ────┤                                         │    │
│  │  IO15 ────┤                                         │    │
│  │  IO25 ────┤                                         │    │
│  │  IO26 ────┤                                         │    │
│  │  IO27 ────┤                                         │    │
│  │  3.3V ────┤                                         │    │
│  │  GND  ────┤                                         │    │
│  └───────────┼─────────────────────────────────────────┘    │
│              │                                               │
│              │ Header Connector                              │
│              │                                               │
└──────────────┼───────────────────────────────────────────────┘
               │
               │ 8-pin Connection
               │
┌──────────────┼───────────────────────────────────────────────┐
│              │                                               │
│              │ Header Connector                              │
│              │                                               │
│  ┌───────────┼─────────────────────────────────────────┐    │
│  │           │          E-Paper HAT                     │    │
│  │           │                                          │    │
│  │  CLK  ◄───┼─── IO13 (SCK)                           │    │
│  │  DIN  ◄───┼─── IO14 (MOSI)                          │    │
│  │  CS   ◄───┼─── IO15                                 │    │
│  │  BUSY ────┼─── IO25                                 │    │
│  │  RST  ◄───┼─── IO26                                 │    │
│  │  DC   ◄───┼─── IO27                                 │    │
│  │  VCC  ◄───┼─── 3.3V                                 │    │
│  │  GND  ◄───┼─── GND                                  │    │
│  │           │                                          │    │
│  │  ┌──────────────────────────────────────┐           │    │
│  │  │   2.3" E-Paper Display               │           │    │
│  │  │   (128x250 pixels)                   │           │    │
│  │  │   Colors: Black, White, Red          │           │    │
│  │  └──────────────────────────────────────┘           │    │
│  └──────────────────────────────────────────────────────┘    │
│                                                              │
└──────────────────────────────────────────────────────────────┘
```

### Connection Table

| Signal | E-Paper HAT | ESP32 GPIO | Physical Pin | Function |
|--------|-------------|-----------|--------------|----------|
| Power  | VCC         | 3.3V      | Pin 1 (Right) | Power supply |
| Ground | GND         | GND       | Multiple     | Common ground |
| Clock  | CLK         | GPIO1 (P1) | Pin 15 (Right) | SPI clock |
| Data   | DIN         | GPIO19 (P19) | Pin 12 (Right) | SPI data (MOSI) |
| Select | CS          | GPIO10 (P10) | Pin 16 (Left) | Chip select |
| Control| DC          | GPIO27 (P27) | Pin 11 (Right) | Data/Command |
| Reset  | RST         | GPIO26 (P26) | Pin 10 (Right) | Reset signal |
| Status | BUSY        | GPIO25 (P25) | Pin 9 (Right) | Busy indicator |

### SPI Bus Configuration

```
ESP32 (Master)                    E-Paper Display (Slave)
─────────────────                 ──────────────────────
GPIO1 (P1, SCK)  ────────────────►  CLK  (Clock)
GPIO19 (P19, MOSI) ──────────────►  DIN  (Data In)
GPIO10 (P10, CS) ─────────────────►  CS   (Chip Select)
GPIO27 (P27, DC) ─────────────────►  DC   (Data/Command)
GPIO26 (P26, RST) ────────────────►  RST  (Reset)
GPIO25 (P25, BUSY) ◄──────────────  BUSY (Status)
3.3V              ────────────────►  VCC  (Power)
GND               ────────────────►  GND  (Ground)
```

### Physical Layout (Top View)

```
                    E-Paper HAT
        ┌──────────────────────────────┐
        │                              │
        │    ┌──────────────────┐     │
        │    │                  │     │
        │    │  2.3" Display    │     │
        │    │   (128x250)      │     │
        │    │                  │     │
        │    └──────────────────┘     │
        │                              │
        │  [Connector Pins]            │
        └──────────┬───────────────────┘
                   │
                   │ 8-pin header
                   │
        ┌──────────▼───────────────────┐
        │   ESP32 Driver Board         │
        │                              │
        │  ┌──────────────────────┐   │
        │  │     ESP32 Module     │   │
        │  └──────────────────────┘   │
        │                              │
        │  [Header Connector]          │
        │                              │
        │  [USB Connector]             │
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
    │
    └──► ESP32 Module (3.3V)
    │
    └──► GND ────────────────► GND (E-Paper HAT)
```

### Signal Flow

**Write Operation (ESP32 → Display):**
1. ESP32 sets CS low (select display)
2. ESP32 sets DC high (data mode) or low (command mode)
3. ESP32 sends clock pulses on SCK
4. ESP32 sends data bits on MOSI
5. Display receives data on DIN
6. ESP32 sets CS high (deselect)

**Status Check (Display → ESP32):**
1. ESP32 reads BUSY pin
2. High = Display is busy (refreshing)
3. Low = Display is ready

### Notes

- All signals are 3.3V logic levels
- SPI communication is unidirectional for data (MOSI only)
- BUSY is an output from display, input to ESP32
- RST and DC are control signals from ESP32
- CS is active low (low = selected)
- Display draws power only during refresh operations
