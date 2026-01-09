# VS Code/Cursor Arduino Configuration

This folder contains configuration files to compile and upload Arduino code directly from Cursor/VS Code.

## Quick Start

1. **Run the setup script:**
   ```bash
   ./setup-arduino.sh
   ```

2. **In Cursor/VS Code - Running Tasks:**

   **Option A: Command Palette (Recommended)**
   - Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
   - Type "Tasks: Run Task"
   - Select one of:
     - **Arduino: Compile** - Compile only
     - **Arduino: Upload** - Compile and upload
     - **Arduino: Compile and Upload** - Full workflow
     - **Arduino: Monitor Serial** - Serial monitor

   **Option B: Custom Keyboard Shortcuts**
   - If `Ctrl+Shift+B` opens browser instead of building:
     - Press `Ctrl+Shift+P` → "Preferences: Open Keyboard Shortcuts (JSON)"
     - Add these keybindings:
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
         },
         {
           "key": "ctrl+alt+m",
           "command": "workbench.action.tasks.runTask",
           "args": "Arduino: Monitor Serial"
         }
       ]
       ```
   - Then use:
     - `Ctrl+Alt+B` - Build
     - `Ctrl+Alt+U` - Upload
     - `Ctrl+Alt+M` - Monitor Serial

   **Option C: Terminal Menu**
   - Go to Terminal → Run Task...
   - Select your task

## Available Tasks

- **Arduino: Compile** - Compile the code only
- **Arduino: Upload** - Compile and upload to /dev/ttyACM0
- **Arduino: Compile and Upload** - Full build and upload
- **Arduino: Monitor Serial** - Open serial monitor at 115200 baud

## Fixing Ctrl+Shift+B Conflict

If `Ctrl+Shift+B` opens a browser instead of building:

1. **Use Command Palette** (easiest):
   - `Ctrl+Shift+P` → "Tasks: Run Task" → Select task

2. **Add Custom Keybindings**:
   - Press `Ctrl+Shift+P` → "Preferences: Open Keyboard Shortcuts (JSON)"
   - Add the keybindings shown in Option B above
   - Use `Ctrl+Alt+B` instead of `Ctrl+Shift+B`

3. **Change Browser Shortcut**:
   - Press `Ctrl+Shift+P` → "Preferences: Open Keyboard Shortcuts"
   - Search for the command that opens browser with `Ctrl+Shift+B`
   - Remove or change that keybinding
   - Then `Ctrl+Shift+B` will work for build tasks

## Troubleshooting

### arduino-cli Command Not Found

If you see "arduino-cli: command not found" when running tasks:

1. **The wrapper script should handle this automatically** - `find-arduino-cli.sh` will find arduino-cli in common locations
2. **If it still fails**, make sure you've run the setup script:
   ```bash
   ./setup-arduino.sh
   ```
3. **Or add arduino-cli to your PATH**:
   ```bash
   # Find where arduino-cli is installed
   find ~ -name arduino-cli -type f 2>/dev/null
   
   # Add to PATH (replace with actual path)
   export PATH="$PATH:/path/to/arduino-cli/directory"
   
   # Make permanent by adding to ~/.bashrc or ~/.zshrc
   echo 'export PATH="$PATH:/path/to/arduino-cli/directory"' >> ~/.bashrc
   ```

### Port Permission Denied

```bash
sudo usermod -a -G dialout $USER
# Then log out and back in
```

### Board Not Found

Make sure your ESP32 is connected:
```bash
arduino-cli board list
```

### Compilation Errors

Check if libraries are installed:
```bash
arduino-cli lib list
```

### Upload Fails

1. Press and hold the **BOOT** button on your ESP32
2. Start the upload task
3. Release the BOOT button when upload starts

## Files

- `tasks.json` - Build and upload tasks
- `settings.json` - Arduino and editor settings
- `c_cpp_properties.json` - IntelliSense configuration for code completion
