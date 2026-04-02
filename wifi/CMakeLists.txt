cmake_minimum_required(VERSION 3.12)
project(wifi C CXX ASM)

add_executable(wifi src/wifi.c)

# Tell the compiler to look in the include folder for lwipopts.h
target_include_directories(wifi PRIVATE include)

pico_enable_stdio_usb(wifi 1)

target_compile_definitions(wifi PRIVATE
    WIFI_SSID="${WIFI_SSID}"
    WIFI_PASSWORD="${WIFI_PASSWORD}"
)

# Link the correct Wi-Fi and Networking libraries
target_link_libraries(wifi 
    pico_stdlib 
    pico_cyw43_arch_lwip_poll
)

pico_add_extra_outputs(wifi)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/wifi.uf2 DESTINATION /firmware)
