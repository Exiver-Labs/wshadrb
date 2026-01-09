#!/bin/bash
# Wrapper script to find and run arduino-cli

# Function to find arduino-cli
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
        "$(dirname "$0")/bin/arduino-cli"
        "$(pwd)/bin/arduino-cli"
        "./bin/arduino-cli"
    )
    
    for path in "${possible_paths[@]}"; do
        if [ -f "$path" ] && [ -x "$path" ]; then
            echo "$path"
            return 0
        fi
    done
    
    return 1
}

# Find arduino-cli
ARDUINO_CLI=$(find_arduino_cli)

if [ -z "$ARDUINO_CLI" ] || [ ! -f "$ARDUINO_CLI" ]; then
    echo "Error: arduino-cli not found!" >&2
    echo "Please run ./setup-arduino.sh to install it" >&2
    exit 1
fi

# Add its directory to PATH and run
ARDUINO_CLI_DIR=$(dirname "$ARDUINO_CLI")
export PATH="$PATH:$ARDUINO_CLI_DIR"

# Execute arduino-cli with all arguments
exec "$ARDUINO_CLI" "$@"
