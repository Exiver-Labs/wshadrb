# Arduino CLI Setup for VS Code/Cursor

This guide will help you set up Arduino CLI to compile and upload code directly from Cursor/VS Code.

## Step 1: Install Arduino CLI

### On Linux (Ubuntu/Debian):

```bash
# Download and install arduino-cli
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

# Add to PATH (add this to your ~/.bashrc or ~/.zshrc)
export PATH="$PATH:$HOME/bin"

# Or install via package manager (if available)
# sudo apt-get update
# sudo apt-get install arduino-cli
```

### Verify Installation:

```bash
arduino-cli version
```

## Step 2: Initialize Arduino CLI

```bash
# Create Arduino CLI config directory
mkdir -p ~/.arduino15

# Initialize config
arduino-cli config init

# Add ESP32 board support
arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

# Update board index
arduino-cli core update-index

# Install ESP32 core
arduino-cli core install esp32:esp32
```

## Step 3: Install Required Libraries

```bash
# Install GxEPD2 library
arduino-cli lib install "GxEPD2"

# Install Adafruit GFX Library (dependency)
arduino-cli lib install "Adafruit GFX Library"

# Verify libraries are installed
arduino-cli lib list
```

## Step 4: Verify Board and Port

```bash
# List available boards
arduino-cli board list

# Should show /dev/ttyACM0 if your ESP32 is connected
# If not, check:
# - USB cable is connected
# - Board is powered on
# - You have permissions (may need to add user to dialout group)
```

### Fix Permissions (if needed):

```bash
# Add your user to dialout group
sudo usermod -a -G dialout $USER

# Log out and log back in, or run:
newgrp dialout
```

## Step 5: Test Compilation

```bash
# Navigate to your project directory
cd /home/oem/projects/electronics/wshadrb

# Compile the sketch
arduino-cli compile --fqbn esp32:esp32:esp32 wshadrb.ino

# If successful, you should see "Sketch uses X bytes" message
```

## Step 6: Test Upload

```bash
# Upload to ESP32
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32 wshadrb.ino

# You may need to press BOOT button on ESP32 during upload
```

## Step 7: Using in Cursor/VS Code

### Option A: Use Tasks (Recommended)

1. Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
2. Type "Tasks: Run Task"
3. Select one of:
   - **Arduino: Compile** - Just compile the code
   - **Arduino: Upload** - Upload (will compile first)
   - **Arduino: Compile and Upload** - Full build and upload
   - **Arduino: Monitor Serial** - Open serial monitor

### Option B: Keyboard Shortcuts

Add to your `keybindings.json`:

```json
[
  {
    "key": "ctrl+alt+b",
    "command": "workbench.action.tasks.build"
  },
  {
    "key": "ctrl+alt+u",
    "command": "workbench.action.tasks.runTask",
    "args": "Arduino: Upload"
  }
]
```

### Option C: Command Palette

1. `Ctrl+Shift+P`
2. Type "Tasks: Run Task"
3. Select your task

## Troubleshooting

### Port Not Found (/dev/ttyACM0)

```bash
# Check if device exists
ls -l /dev/ttyACM*

# Check permissions
ls -l /dev/ttyACM0

# If permission denied, add user to dialout group (see Step 4)
```

### Compilation Errors

```bash
# Check if ESP32 core is installed
arduino-cli core list

# Check if libraries are installed
arduino-cli lib list

# Update everything
arduino-cli core update-index
arduino-cli core upgrade esp32:esp32
arduino-cli lib upgrade
```

### Upload Fails

1. **Press BOOT button** on ESP32 before/during upload
2. Check USB cable (use data cable, not charging-only)
3. Try different USB port
4. Check if another program is using the port:
   ```bash
   sudo lsof /dev/ttyACM0
   ```

### Board Not Recognized

```bash
# List all boards
arduino-cli board listall | grep esp32

# Check installed cores
arduino-cli core list
```

## Quick Reference Commands

```bash
# Compile
arduino-cli compile --fqbn esp32:esp32:esp32 wshadrb.ino

# Upload
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32 wshadrb.ino

# Monitor Serial (115200 baud)
arduino-cli monitor -p /dev/ttyACM0 -c baudrate=115200

# List installed libraries
arduino-cli lib list

# Search for libraries
arduino-cli lib search GxEPD2
```

## Alternative: Using Arduino IDE

If you prefer using Arduino IDE:

1. Install Arduino IDE
2. Add ESP32 board support (same URL as above)
3. Install libraries via Library Manager
4. Open `wshadrb.ino` in Arduino IDE
5. Select board: Tools → Board → ESP32 Arduino → ESP32 Dev Module
6. Select port: Tools → Port → /dev/ttyACM0
7. Upload

## Next Steps

Once setup is complete:
1. Use `Ctrl+Shift+B` to build
2. Use `Ctrl+Shift+P` → "Tasks: Run Task" → "Arduino: Upload" to upload
3. Use "Arduino: Monitor Serial" to view output at 115200 baud

**Note:** Serial debugging is fully functional! The code uses VSPI pins (GPIO18/23/5) which don't conflict with UART0 (GPIO1/3).

