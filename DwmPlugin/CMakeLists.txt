cmake_minimum_required(VERSION 3.30)

project(hyprfocus
    DESCRIPTION "DWM Plugin for Hyprland"
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 26)

file(GLOB_RECURSE SRC "*.cpp")

add_library(hyprfocus SHARED ${SRC})

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET
    hyprland
    libdrm
    libinput
    libudev
    pangocairo
    pixman-1
    wayland-server
    xkbcommon
)
target_link_libraries(hyprfocus PRIVATE rt PkgConfig::deps)

install(TARGETS hyprfocus)