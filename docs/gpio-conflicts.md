# ESP32 GPIO Conflicts and Boot-Strapping Pins

## Overview

The ESP32 has several GPIO pins with special functions that **cannot be used freely** for external peripherals. Using these pins incorrectly will cause boot failures, system crashes, or unpredictable behavior.

This document explains which pins to avoid and why.

## Critical Pins to AVOID

### 1. Flash Memory Pins (GPIO6-GPIO11)

**Status**: ❌ **NEVER USE FOR EXTERNAL PERIPHERALS**

These pins are internally connected to the SPI flash memory chip that stores your program:

- **GPIO6**: Flash CLK
- **GPIO7**: Flash D0
- **GPIO8**: Flash D1
- **GPIO9**: Flash D2
- **GPIO10**: Flash D3
- **GPIO11**: Flash CMD

**Why avoid**: Using any of these pins for external devices will disrupt the ESP32's ability to read its own program from flash memory, causing immediate system crashes or boot failures.

**Impact**: System crash, boot loop, corrupted program execution

---

### 2. UART0 Pins (GPIO1, GPIO3)

**Status**: ⚠️ **AVOID FOR SPI/I2C** (can be used with caution)

- **GPIO1**: UART0_TX (transmit)
- **GPIO3**: UART0_RX (receive)

**Why avoid**: These pins are used for:
- USB serial communication (Serial Monitor)
- Bootloader communication during firmware upload
- Debug output

**Impact**: 
- Using GPIO1 for SPI CLK causes conflicts with serial debugging
- Boot failures if pins are pulled LOW during startup
- Garbled serial output
- Upload failures

**When you can use them**: Only if you completely disable Serial communication and don't need USB debugging.

---

### 3. Boot-Strapping Pins

These pins determine the ESP32's boot mode and must be in specific states during power-on:

#### GPIO0 (Boot Mode Selection)
- **Boot requirement**: Must be HIGH for normal boot
- **LOW during boot**: Enters firmware download mode
- **Impact**: If pulled LOW by external device, ESP32 won't boot normally
- **Usage**: Can be used after boot, but avoid pull-down resistors

#### GPIO2 (Boot Mode Selection)
- **Boot requirement**: Must be LOW or floating during boot
- **Impact**: Some boot modes require this pin to be LOW
- **Usage**: Can be used after boot, but be careful with pull-up resistors

#### GPIO12 (Flash Voltage Selection)
- **Boot requirement**: Must be LOW during boot (for 3.3V flash)
- **Impact**: If HIGH during boot, sets flash voltage to 1.8V → **BOOT FAILURE**
- **Usage**: ❌ **AVOID** - very dangerous if pulled HIGH

#### GPIO15 (Boot Mode Selection)
- **Boot requirement**: Must be HIGH during boot
- **Impact**: If LOW during boot, enters silent boot mode
- **Usage**: Can be used after boot, but avoid pull-down resistors

#### GPIO5 (Boot Mode Selection)
- **Boot requirement**: Should be HIGH during boot
- **Impact**: Outputs PWM signal during boot sequence
- **Usage**: ✅ **SAFE** for VSPI CS (standard SPI chip select)

---

## Safe GPIO Pins for External Peripherals

### ✅ Recommended for SPI (VSPI Interface)

The ESP32 has two hardware SPI buses: **VSPI** (recommended) and **HSPI**.

**VSPI Pins** (use these for e-paper display):
- **GPIO18**: VSPI SCK (SPI Clock)
- **GPIO23**: VSPI MOSI (Master Out Slave In)
- **GPIO19**: VSPI MISO (Master In Slave Out)
- **GPIO5**: VSPI CS (Chip Select)

**HSPI Pins** (alternative):
- **GPIO14**: HSPI SCK
- **GPIO13**: HSPI MOSI
- **GPIO12**: HSPI MISO ⚠️ (be careful - boot pin!)
- **GPIO15**: HSPI CS ⚠️ (be careful - boot pin!)

### ✅ Safe General Purpose GPIO Pins

These pins are safe for general use (no boot conflicts):

- **GPIO4**: Safe
- **GPIO13**: Safe (HSPI MOSI)
- **GPIO14**: Safe (HSPI SCK)
- **GPIO16**: Safe
- **GPIO17**: Safe
- **GPIO18**: Safe (VSPI SCK)
- **GPIO19**: Safe (VSPI MISO)
- **GPIO21**: Safe (I2C SDA)
- **GPIO22**: Safe (I2C SCL)
- **GPIO23**: Safe (VSPI MOSI)
- **GPIO25**: Safe (DAC1)
- **GPIO26**: Safe (DAC2)
- **GPIO27**: Safe
- **GPIO32**: Safe (ADC1_CH4)
- **GPIO33**: Safe (ADC1_CH5)
- **GPIO34**: Input only (ADC1_CH6)
- **GPIO35**: Input only (ADC1_CH7)
- **GPIO36**: Input only (ADC1_CH0)
- **GPIO39**: Input only (ADC1_CH3)

---

## Summary Table

| GPIO Pin(s) | Function | Safe for External Use? | Notes |
|-------------|----------|------------------------|-------|
| GPIO6-11 | Flash Memory | ❌ **NEVER** | System crash if used |
| GPIO1 | UART0_TX | ⚠️ **AVOID** | Serial conflicts, boot issues |
| GPIO3 | UART0_RX | ⚠️ **AVOID** | Serial conflicts, boot issues |
| GPIO0 | Boot Mode | ⚠️ **CAUTION** | Must be HIGH during boot |
| GPIO2 | Boot Mode | ⚠️ **CAUTION** | Must be LOW/floating during boot |
| GPIO12 | Flash Voltage | ❌ **AVOID** | Must be LOW during boot |
| GPIO15 | Boot Mode | ⚠️ **CAUTION** | Must be HIGH during boot |
| GPIO5 | Boot Mode | ✅ **SAFE** | VSPI CS - safe for SPI |
| GPIO18 | VSPI SCK | ✅ **SAFE** | Recommended for SPI clock |
| GPIO23 | VSPI MOSI | ✅ **SAFE** | Recommended for SPI data |
| GPIO19 | VSPI MISO | ✅ **SAFE** | Recommended for SPI data in |
| GPIO4, 13, 14, 16, 17, 21, 22, 25-27, 32-33 | General Purpose | ✅ **SAFE** | No boot conflicts |
| GPIO34-39 | Input Only | ✅ **SAFE** | ADC inputs, no pull-up/down |

---

## Best Practices

1. **Always use VSPI pins for SPI peripherals** (GPIO18, GPIO23, GPIO19, GPIO5)
2. **Never use GPIO6-GPIO11** - they're connected to internal flash
3. **Avoid GPIO1 and GPIO3** unless you disable Serial communication
4. **Be careful with boot-strapping pins** (GPIO0, GPIO2, GPIO12, GPIO15)
5. **Test boot behavior** after connecting external hardware
6. **Use pull-up/pull-down resistors carefully** on boot pins

---

## For E-Paper Display

**Recommended Pin Configuration**:

```cpp
#define EPD_CS    5   // VSPI CS
#define EPD_DC    27  // General purpose GPIO
#define EPD_RST   26  // General purpose GPIO
#define EPD_BUSY  25  // General purpose GPIO
#define EPD_MOSI  23  // VSPI MOSI
#define EPD_SCK   18  // VSPI SCK
```

This configuration:
- ✅ Uses standard VSPI interface
- ✅ Avoids all boot-strapping conflicts
- ✅ Avoids flash memory pins
- ✅ Allows Serial debugging
- ✅ Ensures reliable boot behavior

---

## References

- [ESP32 Datasheet - GPIO Matrix](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [Random Nerd Tutorials - ESP32 Pinout Reference](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
