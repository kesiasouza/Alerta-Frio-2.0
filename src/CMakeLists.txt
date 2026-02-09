# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

# Configurações padrão do projeto
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Bloco de código para integração com o VS Code (não precisa editar)
# ====================================================================================
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# Define a placa como Pico W
set(PICO_BOARD "pico_w") # <<< MELHORIA: Forma mais direta de definir a placa

# Inclui o SDK do Pico
include(pico_sdk_import.cmake)

project(AlertaFrio_2.0 C CXX ASM)

# Inicializa o SDK do Pico
pico_sdk_init()

# Adiciona o executável com todos os arquivos fonte (.c)
add_executable(AlertaFrio_2.0
    main.c
    hardware_handler.c
    mqtt_config.c
)

# Configurações do programa
pico_set_program_name(AlertaFrio_2.0 "AlertaFrio_2.0")
pico_set_program_version(AlertaFrio_2.0 "0.1")

# Habilita a saída de terminal via USB
pico_enable_stdio_uart(AlertaFrio_2.0 0)
pico_enable_stdio_usb(AlertaFrio_2.0 1)

# Vincula todas as bibliotecas necessárias em um só lugar
# <<< MELHORIA: Tudo em um único comando para maior clareza
target_link_libraries(AlertaFrio_2.0
    pico_stdlib
    hardware_i2c
    hardware_timer
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mqtt
)

# Adiciona os diretórios de inclusão para os arquivos de cabeçalho (.h)
target_include_directories(AlertaFrio_2.0 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib/ssd1306 # <<< CORREÇÃO: Adicionada a pasta da biblioteca OLED
)

# Adiciona a geração de outros formatos de binário (uf2, etc.)
pico_add_extra_outputs(AlertaFrio_2.0)