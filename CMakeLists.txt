cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME MJSGadget_dB_meter)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/Core/Src/*.c)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
    ${SRC_FILES}
#../Core/Src/EEProm.c
#../Core/Src/efficient_10log10.c
#../Core/Src/ESP.c
# ../Core/Src/I2CSensors.c
# ../Core/Src/measurement.c
# ../Core/Src/microphone.c
# ../Core/Src/PC_Config.c
# ../Core/Src/PowerUtils.c
# ../Core/Src/print_functions.c
# ../Core/Src/RealTimeClock.c
# ../Core/Src/sen5x_i2c.c
# ../Core/Src/sen5x.c
# ../Core/Src/sensirion_common.c
# ../Core/Src/sensirion_gas_index_algorithm.c
# ../Core/Src/sensirion_i2c.c
# ../Core/Src/sgp40.c
# ../Core/Src/sound_LUTs.c
# ../Core/Src/sound_measurement.c
# ../Core/Src/sound_utilities.c
# ../Core/Src/statusCheck.c
# ../Core/Src/utils.c
# ../Core/Src/wsenHIDS.c
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

target_link_options(${CMAKE_PROJECT_NAME}  PRIVATE 
    -u _printf_float
)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/DSP/Lib
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/DSP/Include
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    ARM_MATH_CM0PLUS
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    #cmsis_dsp
    #arm_cortexM0l_math
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Lib/GCC/libarm_cortexM0l_math.a
    # Add user defined libraries
)