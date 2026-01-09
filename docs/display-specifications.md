# Display Specifications

## Waveshare 2.3" E-Paper HAT (3-Color)

### General Information

- **Model**: 2.3 inch E-Paper HAT (B) / 2.3 inch E-Paper HAT (C)
- **Display Type**: E-Ink / E-Paper
- **Colors**: Black, White, Red (or Yellow depending on model)
- **Interface**: SPI
- **Driver IC**: Typically IL3895 or similar

### Physical Specifications

- **Active Area**: 2.3 inches diagonal
- **Resolution**: 128 x 250 pixels (portrait) or 250 x 128 pixels (landscape)
- **Pixel Pitch**: ~0.45mm
- **Viewing Angle**: 180°
- **Weight**: ~15-20g (HAT only)

### Electrical Specifications

- **Operating Voltage**: 3.3V
- **Operating Current**: 
  - Sleep: < 1µA
  - Standby: ~10µA
  - Active: 10-50mA
  - Refresh: 50-200mA (peak)
- **Power Consumption**: Very low (only consumes power during refresh)
- **Operating Temperature**: 0°C to 50°C
- **Storage Temperature**: -20°C to 60°C

### Display Characteristics

- **Refresh Time**: 1-3 seconds (full refresh)
- **Partial Refresh**: Supported (faster, ~0.5-1 second)
- **Contrast Ratio**: High (paper-like appearance)
- **Reflectance**: ~40% (similar to paper)
- **Bistable**: Yes (image persists without power)
- **Memory**: Built-in frame buffer

### Communication Interface

- **Protocol**: SPI (Serial Peripheral Interface)
- **SPI Mode**: Mode 0 (CPOL=0, CPHA=0)
- **Clock Speed**: Up to 10MHz
- **Data Width**: 8-bit
- **Bit Order**: MSB first

### Pin Functions

| Pin Name | Function | Description |
|----------|----------|-------------|
| VCC      | Power    | 3.3V power supply |
| GND      | Ground   | Common ground |
| DIN      | SPI Data | Master Out Slave In (MOSI) |
| CLK      | SPI Clock| Serial Clock (SCK) |
| CS       | Chip Select | SPI chip select (active low) |
| DC       | Data/Command | High = Data, Low = Command |
| RST      | Reset    | Display reset (active low) |
| BUSY     | Busy     | High = Busy, Low = Ready |

### Display Models

Common model numbers for 2.3" 3-color displays:
- **GDEW023Z10**: 2.3" 3-color (Black/White/Red)
- **GDEW023Z19**: 2.3" 3-color variant
- **GDEW023Z98**: 2.3" 3-color variant

Note: Model numbers may vary. Check your HAT label for the exact model.

### GxEPD2 Library Support

The GxEPD2 library supports various display models. For 2.3" 3-color displays, common class names include:
- `GxEPD2_213_Z98c` (most common)
- `GxEPD2_213_Z19c`
- `GxEPD2_213_Z98c`

### Refresh Modes

1. **Full Refresh**: 
   - Complete screen update
   - Takes 1-3 seconds
   - Best image quality
   - Use for major content changes

2. **Partial Refresh**:
   - Updates only changed areas
   - Takes 0.5-1 second
   - Faster but may leave ghosting
   - Use for small updates

### Best Practices

1. **Refresh Frequency**: 
   - E-paper is not suitable for video or fast animations
   - Update only when content changes
   - Typical use: Update every few seconds to minutes

2. **Power Management**:
   - Display consumes power only during refresh
   - Can remain powered off between updates
   - Ideal for battery-powered applications

3. **Image Quality**:
   - Use full refresh periodically to clear ghosting
   - Avoid too many partial refreshes in sequence
   - Clear screen before major content changes

4. **Temperature**:
   - Refresh time increases at low temperatures
   - Display may not work below 0°C
   - Optimal performance at room temperature

5. **Storage**:
   - Store in a dry environment
   - Avoid direct sunlight
   - Handle carefully to avoid damage

### Limitations

- **Refresh Speed**: Slow compared to LCD/OLED (1-3 seconds)
- **Color**: Limited to 3 colors (black, white, red/yellow)
- **Temperature Sensitivity**: Performance degrades at extreme temperatures
- **Ghosting**: May occur with partial refresh (cleared with full refresh)
- **Not for Video**: Not suitable for moving images or video

### Applications

Ideal for:
- Information displays
- Status indicators
- Weather stations
- Data loggers
- E-readers
- Price tags
- Smart labels
- Low-power IoT displays

Not suitable for:
- Video playback
- Fast animations
- Real-time graphics
- High refresh rate applications

### Additional Notes

- The display is bistable: once an image is written, it remains visible without power
- Power consumption is extremely low, making it ideal for battery-powered devices
- The red/yellow color is typically used for highlighting or important information
- Display orientation can be changed in software (0°, 90°, 180°, 270°)
