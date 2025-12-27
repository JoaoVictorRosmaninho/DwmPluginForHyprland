
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/includes.hpp>
#include "DwmLayout.hpp"

// Global handle
HANDLE PHANDLE = nullptr;

// Global layout instance
inline std::unique_ptr<CHyprDwmLayout> g_pDwmLayout;

// Define the plugin name and a brief description
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    // Create the layout instance
    g_pDwmLayout = std::make_unique<CHyprDwmLayout>();

    // Register the layout with Hyprland
    HyprlandAPI::addLayout(handle, "dwm", g_pDwmLayout.get());

    HyprlandAPI::addNotification(handle, "[DwmPlugin] DWM Layout registered successfully!", 
                                  CHyprColor{0.0f, 1.0f, 0.0f, 1.0f}, 5000);
    
    Debug::log(LOG, "[DwmPlugin] DWM Layout plugin initialized successfully!");
    
    return PLUGIN_DESCRIPTION_INFO{
        .name = "DwmPlugin",
        .description = "DWM-style tiling layout for Hyprland with proper master/stack behavior",
        .author = "Your Name",
        .version = "1.0"
    };
}

APICALL EXPORT void PLUGIN_EXIT() {
    HyprlandAPI::removeLayout(PHANDLE, g_pDwmLayout.get());
    g_pDwmLayout.reset();
}


