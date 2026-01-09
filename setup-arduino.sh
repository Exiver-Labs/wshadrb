#!/bin/bash
# Setup script for Arduino CLI on Linux

set -e

echo "=========================================="
echo "Arduino CLI Setup for ESP32"
echo "=========================================="
echo ""

# Function to find arduino-cli executable
find_arduino_cli() {
    # First check if it's in PATH
    if command -v arduino-cli &> /dev/null; then
        echo "arduino-cli"
        return 0
    fi
    
    # Check common installation locations
    local possible_paths=(
        "$HOME/bin/arduino-cli"
        "$HOME/.local/bin/arduino-cli"
        "./bin/arduino-cli"
        "$(pwd)/bin/arduino-cli"
    )
    
    for path in "${possible_paths[@]}"; do
        if [ -f "$path" ] && [ -x "$path" ]; then
            echo "$path"
            return 0
        fi
    done
    
    return 1
}

# Find or install arduino-cli
ARDUINO_CLI=$(find_arduino_cli)

if [ -z "$ARDUINO_CLI" ] || [ ! -f "$ARDUINO_CLI" ]; then
    echo "❌ arduino-cli not found. Installing..."
    echo ""
    echo "Installing arduino-cli..."
    
    # Install arduino-cli
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
    
    # Try to find it after installation
    ARDUINO_CLI=$(find_arduino_cli)
    
    if [ -z "$ARDUINO_CLI" ] || [ ! -f "$ARDUINO_CLI" ]; then
        echo "❌ Error: arduino-cli installation failed or not found"
        echo "Please install arduino-cli manually:"
        echo "  curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh"
        echo "  export PATH=\"\$PATH:\$HOME/bin\""
        exit 1
    fi
    
    echo "✅ arduino-cli installed at: $ARDUINO_CLI"
    
    # Add to PATH for this session
    ARDUINO_CLI_DIR=$(dirname "$ARDUINO_CLI")
    export PATH="$PATH:$ARDUINO_CLI_DIR"
    
    echo "✅ Added $ARDUINO_CLI_DIR to PATH for this session"
    echo "   To make it permanent, add this to your ~/.bashrc or ~/.zshrc:"
    echo "   export PATH=\"\$PATH:$ARDUINO_CLI_DIR\""
else
    echo "✅ arduino-cli found at: $ARDUINO_CLI"
    # Add its directory to PATH
    ARDUINO_CLI_DIR=$(dirname "$ARDUINO_CLI")
    export PATH="$PATH:$ARDUINO_CLI_DIR"
fi

# Verify it works
echo ""
echo "Verifying arduino-cli..."
"$ARDUINO_CLI" version

echo ""
echo "Initializing Arduino CLI config..."
"$ARDUINO_CLI" config init 2>/dev/null || echo "Config already exists"

echo ""
echo "Adding ESP32 board support URL..."
"$ARDUINO_CLI" config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json 2>/dev/null || echo "URL already added"

echo ""
echo "Updating board index..."
"$ARDUINO_CLI" core update-index

echo ""
echo "Installing ESP32 core..."
"$ARDUINO_CLI" core install esp32:esp32

echo ""
echo "Installing required libraries..."
"$ARDUINO_CLI" lib install "GxEPD2"
"$ARDUINO_CLI" lib install "Adafruit GFX Library"

echo ""
echo "Checking for connected boards..."
"$ARDUINO_CLI" board list

echo ""
echo "=========================================="
echo "Setup Complete!"
echo "=========================================="
echo ""
echo "Next steps:"
echo "1. Make sure your ESP32 is connected to /dev/ttyACM0"
echo "2. If you get permission errors, run:"
echo "   sudo usermod -a -G dialout $USER"
echo "   (then log out and back in)"
echo ""
echo "3. In Cursor/VS Code:"
echo "   - Press Ctrl+Shift+B to build"
echo "   - Press Ctrl+Shift+P → 'Tasks: Run Task' → 'Arduino: Upload'"
echo ""
echo "4. Test compilation:"
echo "   arduino-cli compile --fqbn esp32:esp32:esp32 wshadrb.ino"
echo ""
