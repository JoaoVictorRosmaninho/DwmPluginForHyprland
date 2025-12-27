# DWM Layout Plugin for Hyprland

A Hyprland plugin that implements the classic **dwm (Dynamic Window Manager)** tiling layout behavior with proper master/stack window management.

## 🎯 Overview

This plugin provides a layout that faithfully reproduces the window management behavior of [dwm](https://dwm.suckless.org/), the minimalist dynamic window manager. Unlike Hyprland's built-in Master layout, this plugin implements the authentic dwm swap logic where stack windows properly shift when promoted to master.

## 🚀 Features

- **True DWM Behavior**: When swapping a stack window with master, the old master becomes the first stack window and all other stack windows shift down
- **Multiple Orientations**: Support for left, right, top, bottom, and center master orientations
- **Dynamic Resizing**: Adjust master/stack ratio on the fly
- **Smart Window Placement**: New windows intelligently placed based on configuration
- **Full Master Layout Compatibility**: Uses all master layout configuration options

## 👥 Target Audience

This plugin is perfect for:
- **dwm users** transitioning to Hyprland who want familiar window management
- **Tiling enthusiasts** who prefer traditional master-stack layouts
- **Workflow optimizers** who want predictable window positioning
- Users who find Hyprland's default Master layout swap behavior unintuitive

## 📦 Installation

### Prerequisites

- Hyprland 0.49.0 or later
- CMake 3.30+
- C++26 compatible compiler
- Hyprland development headers

### Building

```bash
cd DwmPlugin
mkdir -p build
cd build
cmake ..
make
```

### Installing

```bash
# Copy the compiled plugin to Hyprland's plugin directory
mkdir -p ~/.config/hypr/plugins
cp build/libhyprfocus.so ~/.config/hypr/plugins/
```

## ⚙️ Configuration

Add to your `~/.config/hypr/hyprland.conf`:

```conf
# Load the plugin
exec-once = hyprctl plugin load ~/.config/hypr/plugins/libhyprfocus.so

# Set DWM as the default layout
general {
    layout = dwm
}

# Key bindings (optional - uses standard master layout bindings)
bind = SUPER, RETURN, layoutmsg, swapwithmaster
bind = SUPER, J, layoutmsg, cyclenext
bind = SUPER, K, layoutmsg, cycleprev
bind = SUPER, H, splitratio, -0.05
bind = SUPER, L, splitratio, +0.05
bind = SUPER SHIFT, RETURN, layoutmsg, focusmaster
bind = SUPER SHIFT, J, layoutmsg, swapnext
bind = SUPER SHIFT, K, layoutmsg, swapprev

# DWM Layout uses all master layout options
master {
    # New windows behavior
    new_status = slave           # New windows go to stack
    new_on_top = false           # Add new windows at bottom
    new_on_active = none         # Don't position relative to active window
    
    # Master area configuration
    mfact = 0.5                  # Master area factor (50% of screen)
    orientation = left           # Master on left side
    
    # Advanced options
    allow_small_split = false    # Prevent splits smaller than minimum
    always_keep_position = false # Don't maintain master position when alone
    smart_resizing = true        # Intelligent window resizing
    drop_at_cursor = false       # Disable cursor-based window placement
}
```

## 🔄 DWM Behavior Explained

### The Key Difference

**Standard Master Layout:**
- 3 windows: Master(1), Stack(2), Stack(3)
- Select window 3 → Press SUPER+ENTER
- Result: Master(3), Stack(2), Stack(1) ❌ (Windows swap positions)

**DWM Layout (This Plugin):**
- 3 windows: Master(1), Stack(2), Stack(3)
- Select window 3 → Press SUPER+ENTER
- Result: Master(3), Stack(1), Stack(2) ✅ (Stack windows shift down)

### Why This Matters

In dwm's philosophy, the master position is special and stable. When a stack window is promoted:
1. It becomes the new master
2. The old master moves to the top of the stack
3. Other stack windows maintain their relative order

This creates more predictable and intuitive window management, especially when frequently switching focus between master and specific stack windows.

## 🎮 Usage Examples

### Basic Window Management

```bash
# Open windows - first is automatically master
alacritty &           # Master
firefox &             # Stack 1
code &                # Stack 2

# Promote Stack 2 (code) to master
# Focus code window, then press SUPER+RETURN
# Result: code (Master), alacritty (Stack 1), firefox (Stack 2)
```

### Layout Messages

```bash
# Swap focused window with master
hyprctl dispatch layoutmsg swapwithmaster

# Focus master window
hyprctl dispatch layoutmsg focusmaster

# Cycle through windows
hyprctl dispatch layoutmsg cyclenext
hyprctl dispatch layoutmsg cycleprev

# Change orientation
hyprctl dispatch layoutmsg orientationleft
hyprctl dispatch layoutmsg orientationtop
hyprctl dispatch layoutmsg orientationright
hyprctl dispatch layoutmsg orientationbottom
hyprctl dispatch layoutmsg orientationcenter

# Cycle through orientations
hyprctl dispatch layoutmsg orientationnext
hyprctl dispatch layoutmsg orientationprev

# Add/remove master windows (for multi-master layouts)
hyprctl dispatch layoutmsg addmaster
hyprctl dispatch layoutmsg removemaster
```

## 📋 Supported Layout Messages

- `swapwithmaster [master|child|auto]` - Swap focused window with master (DWM behavior)
- `focusmaster [master|auto]` - Focus the master window
- `cyclenext [noloop]` - Focus next window in stack
- `cycleprev [noloop]` - Focus previous window in stack
- `swapnext [noloop]` - Swap with next window
- `swapprev [noloop]` - Swap with previous window
- `addmaster` - Promote focused window to master
- `removemaster` - Demote focused master to stack
- `orientationleft|top|right|bottom|center` - Change master orientation
- `orientationnext|orientationprev` - Cycle orientations
- `orientationcycle [orientations...]` - Cycle through specific orientations
- `mfact <value>` - Set master factor (0.05-0.95)

## 🐛 Troubleshooting

### Plugin won't load

```bash
# Check plugin status
hyprctl plugin list

# Check logs
hyprctl log
```

### Layout not available

```bash
# List available layouts
hyprctl layouts

# Verify plugin loaded successfully
hyprctl plugin list | grep -i dwm
```

### Crashes or unexpected behavior

```bash
# Unload and reload plugin
hyprctl plugin unload ~/.config/hypr/plugins/libhyprfocus.so
hyprctl plugin load ~/.config/hypr/plugins/libhyprfocus.so

# Check Hyprland version
hyprland --version
```

## 🔧 Development

### Building with Debug Symbols

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Running Tests

The plugin follows Hyprland's window management API. Test by:
1. Opening 3+ windows
2. Testing swap behavior with SUPER+RETURN
3. Verifying window order after swaps

## 📝 License

This plugin follows the same license as Hyprland (BSD-3-Clause).

## 🙏 Acknowledgments

- [Hyprland](https://hyprland.org/) - The amazing Wayland compositor
- [dwm](https://dwm.suckless.org/) - The inspiration for this layout
- [hyprNStack](https://github.com/zakk4223/hyprNStack) - Reference plugin implementation

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

### Areas for Improvement

- [ ] Additional layout customization options
- [ ] Performance optimizations
- [ ] Extended multi-master support
- [ ] Integration with Hyprland's workspace rules

## 📧 Contact

For issues and feature requests, please use the GitHub issue tracker.

---

**Note**: This plugin is specifically designed to replicate dwm's window management behavior. If you prefer Hyprland's default Master layout swap logic, use the built-in master layout instead.
