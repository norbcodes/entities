# entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

# The CMakeLists to build entities2.cpp
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# Set the project
project(entities2 
        LANGUAGES CXX 
        VERSION "1.3.0"
        DESCRIPTION "entities2 is a small silly turn based combat CLI game."
)

include("CheckIncludeFileCXX")

# Options for compilation.
option(STATIC_LIBS "Statically link against C and C++ standard lib." OFF)
option(OPTIMIZE    "Enable optimization." OFF)

# Set search paths
set(
    SEARCH_IN 
    ${CMAKE_SOURCE_DIR}/src/headers
)

# Set sources
set(
    SOURCES
    ${CMAKE_SOURCE_DIR}/src/ai.cpp
    ${CMAKE_SOURCE_DIR}/src/energy.cpp
    ${CMAKE_SOURCE_DIR}/src/entity.cpp
    ${CMAKE_SOURCE_DIR}/src/exit_msg.cpp
    ${CMAKE_SOURCE_DIR}/src/gen_moves.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/rng.cpp
    ${CMAKE_SOURCE_DIR}/src/status.cpp
    ${CMAKE_SOURCE_DIR}/src/utils.cpp
)

set(NEEDED_EXT_HEADERS cstdint string vector iostream math.h random iomanip)

# Check if compiling for Linux
message(STATUS "Checking OS...")
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    add_compile_definitions(${PROJECT_NAME} PUBLIC __linux__)
    list(APPEND NEEDED_EXT_HEADERS unistd.h)
    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/linux/headers")
    list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/src/linux/sleep.cpp")
    message(STATUS "Linux detected. Adding Linux specific stuff.")

elseif(CMAKE_SYSTEM_NAME MATCHES Windows)
    add_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32)
    list(APPEND NEEDED_EXT_HEADERS windows.h)
    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/windows/headers")
    list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/src/windows/sleep.cpp")
    message(STATUS "Windows detected. Adding Windows specific stuff.")

else()
    message(WARNING "Unrecognized system ${CMAKE_SYSTEM_NAME}")

endif()

# Check for headers
# Because paranoia
foreach(header ${NEEDED_EXT_HEADERS})
CHECK_INCLUDE_FILE_CXX(${header} FILE_EXISTS)
if(NOT FILE_EXISTS)
    message(FATAL_ERROR "Header ${header} not found")
endif()
unset(FILE_EXISTS CACHE)
endforeach()
# Yep

# Create target
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_IN})

# Check if STATIC_LIBS
if (STATIC_LIBS)
    target_link_options(${PROJECT_NAME} PUBLIC -static-libgcc -static-libstdc++)
    message(STATUS "Statically linking against C and C++ standard lib. Expect increase in file size!")
endif()

# Check if OPTIMIZATION
if (OPTIMIZE)
    target_compile_options(${PROJECT_NAME} PUBLIC -O2 -g0 -ggdb0 -s)
    message(STATUS "Enabled optimization.")
endif()