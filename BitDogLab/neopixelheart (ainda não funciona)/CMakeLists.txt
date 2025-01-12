# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# Defina o caminho correto para o SDK do Raspberry Pi Pico
# Evite espaços no caminho, caso contrário, coloque o caminho entre aspas
set(PICO_SDK_PATH "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/pico-sdk")

# Inicializa o Raspberry Pi Pico SDK
pico_sdk_init()

set(PICO_BOARD pico_w CACHE STRING "Board type")

project(neopixelheart C CXX ASM)

# Adiciona o executável
add_executable(neopixelheart neopixelheart.c)

pico_set_program_name(neopixelheart "neopixelheart")
pico_set_program_version(neopixelheart "0.1")

# Modifica as configurações para habilitar/desabilitar a saída UART/USB
pico_enable_stdio_uart(neopixelheart 0)
pico_enable_stdio_usb(neopixelheart 1)

# Adiciona a biblioteca padrão à construção
target_link_libraries(neopixelheart
        pico_stdlib)

# Adiciona os diretórios de inclusão
target_include_directories(neopixelheart PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/libs/ws2812   # Certifique-se de que ws2812.pio.h está aqui
  ${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include  # Dependendo de onde o PIO SDK está
)

# Adiciona as bibliotecas necessárias
target_link_libraries(neopixelheart
        hardware_pio
        hardware_clocks
        hardware_gpio
)

# Adiciona saídas extras (binário, etc)
pico_add_extra_outputs(neopixelheart)
