# Waveshare 2.3" E-Paper Display Project

ESP32 driver code and documentation for the Waveshare 2.3" E-Paper HAT (3-color) with ESP32 Universal Driver Board.

## Overview

This project provides a complete solution for driving the Waveshare 2.3" E-Paper HAT (3-color display) using the Waveshare ESP32 Universal Driver Board. The display supports black, white, and red/yellow colors, making it ideal for information displays, status indicators, and low-power IoT applications.

> [!IMPORTANT]
> **Connection Method:** This setup uses **GPIO pins with jumper wires** to connect the E-Paper HAT to the ESP32 Driver Board, **NOT the FPC (Flexible Printed Circuit) connector**. The HAT's pin header is connected directly to the ESP32's GPIO pins using individual wires, providing more flexibility in pin selection and avoiding potential FPC connector issues.

## Features

- ✅ Complete ESP32 test code with colorful landscape display patterns
- ✅ Support for 3-color e-paper display (black, white, red)
- ✅ **GPIO pin-based connection** (no FPC connector required)
- ✅ **VSPI pins** (GPIO18/23/5) for reliable SPI communication
- ✅ Comprehensive hardware connection documentation
- ✅ Step-by-step setup guide for Arduino CLI
- ✅ Display specifications and technical details
- ✅ GPIO conflicts guide to avoid boot issues
- ✅ Connection schematics and wiring diagrams

## Quick Start

1. **Hardware Setup**: 
   - Connect the E-Paper HAT to ESP32 Driver Board using **jumper wires** (GPIO pins)
   - **Do NOT use the FPC connector** - this setup uses individual wire connections
   - See [Hardware Connections](docs/hardware-connections.md) for detailed wiring diagram

2. **Software Setup**: 
   - **Recommended**: Use Arduino CLI for VS Code/Cursor (see [Arduino CLI Setup](docs/setup-arduino-cli.md))
   - **Alternative**: Use Arduino IDE (see [Setup Guide](docs/setup-guide.md))

3. **Upload Code**: 
   - Compile and upload `wshadrb.ino`
   - Select board: ESP32 Dev Module
   - Select port: /dev/ttyACM0 (or your ESP32 port)

4. **Test**: The display will automatically run 5 colorful test patterns in landscape mode


## Project Structure

```
wshadrb/
├── wshadrb.ino              # Main ESP32 code (landscape mode, VSPI pins)
├── docs/                    # Documentation
│   ├── hardware-connections.md   # VSPI pin configuration
│   ├── gpio-conflicts.md         # GPIO restrictions and best practices
│   ├── setup-guide.md            # Arduino IDE setup
│   ├── setup-arduino-cli.md      # Arduino CLI setup (recommended)
│   ├── display-specifications.md # Display technical specs
│   ├── quick-reference.md        # Quick reference guide
│   └── troubleshooting.md        # Common issues and solutions
├── schematics/              # Schematics and diagrams
│   └── connection-diagram.md
├── .vscode/                 # VS Code/Cursor configuration (Arduino CLI)
│   ├── tasks.json           # Arduino CLI build and upload tasks
│   ├── settings.json        # Arduino CLI settings
│   └── c_cpp_properties.json # IntelliSense configuration
├── setup-arduino.sh         # Automated Arduino CLI setup script
└── Readme.md               # This file
```


## Documentation

### [Hardware Connections](docs/hardware-connections.md)
Complete pin mapping and connection details between the E-Paper HAT and ESP32 Driver Board. Includes pin definitions, power requirements, SPI configuration, and troubleshooting tips.

### [Setup Guide](docs/setup-guide.md)
Step-by-step instructions for:
- Hardware assembly
- Arduino IDE configuration
- Library installation
- Code upload and testing
- Customization options
- Troubleshooting common issues

### [Arduino CLI Setup](docs/setup-arduino-cli.md)
Complete guide for setting up Arduino CLI to compile and upload code directly from Cursor/VS Code:
- Arduino CLI installation
- ESP32 board support setup
- Library installation via CLI
- VS Code/Cursor task configuration
- Compile and upload workflows
- Serial monitor setup

### [Display Specifications](docs/display-specifications.md)
Technical specifications including:
- Physical dimensions and resolution
- Electrical characteristics
- Communication interface details
- Refresh modes and best practices
- Application guidelines

### [Connection Diagram](schematics/connection-diagram.md)
Visual schematics showing:
- Pin connection layout
- SPI bus configuration
- Physical layout diagrams
- Signal flow diagrams
- Power distribution

### [Troubleshooting](docs/troubleshooting.md)
Common issues and solutions:
- Reset loop problems
- Display not working
- Upload issues
- Compilation errors
- Performance problems

### [GPIO Conflicts Guide](docs/gpio-conflicts.md)
Comprehensive guide on ESP32 GPIO pin restrictions:
- Boot-strapping pins and flash pins to avoid
- Safe pins for external peripherals
- Why GPIO1 and GPIO10 caused issues
- VSPI vs HSPI pin assignments
- Best practices for pin selection


## Hardware Requirements

- **Waveshare 2.13" E-Paper HAT** (3-color display)
- **Waveshare ESP32 Universal Driver Board**
- **Jumper wires** (female-to-female, at least 8 wires for connections)
- **USB cable** for programming
- **Computer** with Arduino CLI or Arduino IDE

## Software Requirements

- **Arduino IDE** (1.8.x or 2.x)
- **ESP32 Board Support** (via Arduino Board Manager)
- **GxEPD2 Library** (for e-paper display control)
- **Adafruit GFX Library** (dependency)

## Pin Configuration

The code uses the following pin assignments based on the actual Waveshare pin diagram:

| Function | ESP32 GPIO | Physical Pin | E-Paper Pin |
|----------|-----------|--------------|-------------|
| SPI Clock (SCK) | GPIO18 (P18) | Pin 30 (Right) | CLK |
| SPI Data (MOSI) | GPIO23 (P23) | Pin 37 (Right) | DIN |
| Chip Select | GPIO5 (P5) | Pin 29 (Right) | CS |
| Data/Command | GPIO27 (P27) | Pin 11 (Right) | DC |
| Reset | GPIO26 (P26) | Pin 10 (Right) | RST |
| Busy | GPIO25 (P25) | Pin 9 (Right) | BUSY |
| Power | 3.3V | Pin 1 (Right) | VCC |
| Ground | GND | Pin 38 (Right) | GND |

**Note**: These pins use the ESP32's standard VSPI interface. **Avoid using GPIO1 (UART0_TX) or GPIO6-GPIO11 (flash pins)** as they cause boot failures.

## Code Features

The `wshadrb.ino` sketch includes:

- **Color Fill Test**: Tests white, black, and red fills
- **Shape Tests**: Rectangles, circles, and lines
- **Text Display**: Multiple font sizes and colors
- **Mixed Content**: Combined graphics and text
- **Continuous Updates**: Periodic display refresh with status

## Usage

### Basic Usage

1. Upload the code to your ESP32
2. The display will automatically run test patterns
3. After tests complete, the display updates every 30 seconds

### Customization

Modify the code to:
- Change update interval (modify `delay()` in `loop()`)
- Adjust pin assignments (modify `#define` statements)
- Change display model (modify `GxEPD2_213_Z98c` if needed)
- Add custom content (modify `updateDisplay()` function)

## Troubleshooting

### Display Not Working

1. Check all connections (see [Hardware Connections](docs/hardware-connections.md))
2. Verify power supply (3.3V stable)
3. Check Serial Monitor for error messages
4. Try different display model definitions in code
5. Ensure GxEPD2 library is installed correctly

### Upload Issues

1. Check USB connection and drivers
2. Verify board selection in Arduino IDE
3. Try holding BOOT button during upload
4. Check port selection

### Display Shows Garbage

1. Verify display model matches code
2. Check pin assignments
3. Ensure SPI pins are correct
4. Verify power supply stability

For more detailed troubleshooting, see the [Setup Guide](docs/setup-guide.md).

## Display Characteristics

- **Resolution**: 128 x 250 pixels (portrait) or 250 x 128 pixels (landscape)
- **Colors**: Black, White, Red (or Yellow)
- **Refresh Time**: 1-3 seconds (full refresh)
- **Power**: Very low consumption (only during refresh)
- **Bistable**: Image persists without power

## Best Practices

1. **Refresh Frequency**: Update only when content changes (not suitable for video)
2. **Power Management**: Display can be powered off between updates
3. **Image Quality**: Use full refresh periodically to clear ghosting
4. **Temperature**: Optimal performance at room temperature (0-50°C)

## Resources

- [Waveshare Wiki](https://www.waveshare.com/wiki/E-Paper_ESP32_Driver_Board)
- [GxEPD2 Library](https://github.com/ZinggJM/GxEPD2)
- [ESP32 Arduino Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [Waveshare E-Paper ESP32 Driver Board User Manual](https://files.waveshare.com/upload/4/4a/E-Paper_ESP32_Driver_Board_user_manual_en.pdf)

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

**What this means for you:**
- ✅ **Use freely**: Personal or commercial projects
- ✅ **Modify**: Change anything you want
- ✅ **Distribute**: Share with others
- ✅ **Sell**: Make money from products using this code
- ✅ **No attribution required** (though appreciated!)

**No restrictions, no royalties, completely free!** 🎉


## Support

For issues:
- **Hardware**: Contact Waveshare support
- **Library**: Check GxEPD2 GitHub issues
- **ESP32**: Refer to Espressif documentation

## Changelog

### Version 1.0
- Initial release
- Basic test patterns and display functionality
- Complete documentation
- Connection schematics

## Acknowledgments

- **Waveshare** for the E-Paper HAT and ESP32 Driver Board
- **[GxEPD2 Library](https://github.com/ZinggJM/GxEPD2)** by Jean-Marc Zingg
- **ESP32 Arduino Core** by Espressif Systems


---

**Note**: This code is tested with the Waveshare 2.3" E-Paper HAT (3-color) and ESP32 Universal Driver Board. If you have a different model, you may need to adjust the display class definition in the code (see comments in `wshadrb.ino`).
