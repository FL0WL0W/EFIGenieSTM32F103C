cmake_minimum_required ( VERSION 3.9 )
project ( EFIGenie C CXX ASM )

include_directories(Drivers/CMSIS/Device/ST/STM32F1xx/Include)
include_directories(Drivers/CMSIS/Include)
include_directories(Drivers/STM32F1xx_HAL_Driver/Inc)
include_directories(Drivers/STM32F1xx_HAL_Driver/Inc/Legacy)
include_directories(Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc)
include_directories(Middlewares/ST/STM32_USB_Device_Library/Core/Inc)
include_directories(Inc)

file(GLOB_RECURSE USER_CSOURCES Src/*.c)
file(GLOB_RECURSE USER_CXXSOURCES Src/*.cpp)
file(GLOB_RECURSE USB_CDC_SOURCES Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/*.c)
file(GLOB_RECURSE USB_CORE_SOURCES Middlewares/ST/STM32_USB_Device_Library/Core/Src/*.c)
file(GLOB_RECURSE HAL_SOURCES Drivers/STM32F1xx_HAL_Driver/Src/*.c)

set(SOURCE_FILES ${USER_CSOURCES} ${USER_CXXSOURCES} ${HAL_SOURCES} ${USB_CDC_SOURCES} ${USB_CORE_SOURCES} startup_stm32f103xb.s STM32F103CBTx_FLASH.ld)
add_executable(firmware.elf ${SOURCE_FILES})

#set(LIBRARIES	libs)
#add_subdirectory (${LIBRARIES}/EmbeddedIOServices)
#add_subdirectory (${LIBRARIES}/Reluctor)
#add_subdirectory (${LIBRARIES}/EngineControl)
#target_link_libraries(firmware.elf EmbeddedIOServices)
#target_link_libraries(firmware.elf Reluctor)
#target_link_libraries(firmware.elf EngineControl)

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/firmware.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/firmware.bin)
add_custom_command(TARGET firmware.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex $<TARGET_FILE:firmware.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary $<TARGET_FILE:firmware.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
