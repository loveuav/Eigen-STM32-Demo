cmake_minimum_required(VERSION 3.5)
project(Eigen-STM32-Demo)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

add_definitions(
-DSTM32F405xx
-DUSE_HAL_DRIVER
)

#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Release")

set(MCU_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

set(CMAKE_C_FLAGS "${MCU_FLAGS} -w -Wno-unknown-pragmas -std=c99 -ffunction-sections -fdata-sections")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g2 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -w -Wno-unknown-pragmas -std=c++11 -fno-rtti -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories(
    Driver/STM32F4xx_HAL_Driver
    Driver/STM32F4xx_HAL_Driver/Inc
    Driver/STM32F4xx_HAL_Driver/Inc/Legacy
    Driver/CMSIS/Device/ST/STM32F4xx/Include
    Driver/CMSIS/Include
    Eigen
    ${CMAKE_CURRENT_BINARY_DIR}
)

set_property(SOURCE Driver/STM32F4xx_HAL_Driver/Startup/GCC/startup_stm32f405xx.s PROPERTY LANGUAGE C)

add_library(stm32f4_lib
    Driver/STM32F4xx_HAL_Driver/Startup/GCC/startup_stm32f405xx.s
    Driver/STM32F4xx_HAL_Driver/system_stm32f4xx.c
    Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32F4xx_HAL_Driver/STM32F405RGTx_FLASH.ld)
set(CMAKE_EXE_LINKER_FLAGS
"--specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref -Wl,--gc-sections"
)

add_executable(${PROJECT_NAME}.elf Src/main.cpp)
target_link_libraries(${PROJECT_NAME}.elf
    stm32f4_lib
)

set(ELF_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET "${PROJECT_NAME}.elf" POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Oihex  ${ELF_FILE} ${HEX_FILE}
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"

    COMMAND ${CMAKE_COMMAND} -E copy ${HEX_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex"
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin"

    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Invoking: Cross ARM GNU Print Size"
)
