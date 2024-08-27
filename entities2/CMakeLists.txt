# entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

# The CMakeLists to build entities2.cpp
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# Do not make install rules pls
# and disable other stuff
set(FMT_INSTALL OFF)
set(FMT_DOC OFF)
set(FMT_TEST OFF)
add_subdirectory("${CMAKE_SOURCE_DIR}/src/fmt")

# Set the project
project(entities2 
        LANGUAGES CXX OBJC
        VERSION "1.7.0.0"
        DESCRIPTION "entities2 is a small silly turn based combat CLI game."
)

include("CheckIncludeFileCXX")

# Options for compilation.
option(STATIC_LIBS              "Statically link against C and C++ standard lib." OFF)
option(OPTIMIZE                 "Enable optimization." OFF)
option(ENABLE_DISCORD_RPC       "Enable Discord RPC." OFF)
option(CUSTOM_DISCORD_ID        "Custom Discord ID." OFF)
option(DISABLE_COLORS           "Disable colors and styling. ALL of it." OFF)
option(DISABLE_TERMINAL_BELL    "Disable terminal bell." OFF)

# Set search paths
set(
    SEARCH_IN 
    ${CMAKE_SOURCE_DIR}/src/headers
    ${CMAKE_SOURCE_DIR}/src/fmt/include
)

# Set sources
set(
    ENTITIES2_SOURCE
    ${CMAKE_SOURCE_DIR}/src/ai.cpp
    ${CMAKE_SOURCE_DIR}/src/discord_rpc.cpp
    ${CMAKE_SOURCE_DIR}/src/energy.cpp
    ${CMAKE_SOURCE_DIR}/src/entity.cpp
    ${CMAKE_SOURCE_DIR}/src/exit_msg.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay_info.cpp
    ${CMAKE_SOURCE_DIR}/src/gen_moves.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/pick_move.cpp
    ${CMAKE_SOURCE_DIR}/src/rng.cpp
    ${CMAKE_SOURCE_DIR}/src/status.cpp
    ${CMAKE_SOURCE_DIR}/src/utils.cpp
)
set(
    DISCORD_RPC_SOURCE
    ${CMAKE_SOURCE_DIR}/src/discord/discord_rpc.cpp
    ${CMAKE_SOURCE_DIR}/src/discord/rpc_connection.cpp
    ${CMAKE_SOURCE_DIR}/src/discord/serialization.cpp
)

# Check if compiling for Linux
message(STATUS "Checking OS...")
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    add_compile_definitions(${PROJECT_NAME} PUBLIC __linux__)
    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/Linux/headers")
    list(APPEND ENTITIES2_SOURCE "${CMAKE_SOURCE_DIR}/src/Linux/sleep.cpp")
    list(APPEND DISCORD_RPC_SOURCE "${CMAKE_SOURCE_DIR}/src/discord/connection_unix.cpp" "${CMAKE_SOURCE_DIR}/src/discord/discord_register_linux.cpp")

    message(STATUS "Linux detected. Adding Linux specific stuff.")

elseif(CMAKE_SYSTEM_NAME MATCHES Windows)
    add_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32 __WIN32__)
    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/Windows/headers")
    list(APPEND ENTITIES2_SOURCE "${CMAKE_SOURCE_DIR}/src/Windows/sleep.cpp" "${CMAKE_SOURCE_DIR}/src/Windows/keyboard.cpp")
    list(APPEND DISCORD_RPC_SOURCE "${CMAKE_SOURCE_DIR}/src/discord/connection_win.cpp" "${CMAKE_SOURCE_DIR}/src/discord/discord_register_win.cpp")

    message(STATUS "Windows detected. Adding Windows specific stuff.")

#elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
#    add_compile_definitions(${PROJECT_NAME} PUBLIC __APPLE__)
#    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/MacOS/headers")
#    list(APPEND ENTITIES2_SOURCE "${CMAKE_SOURCE_DIR}/src/MacOS/sleep.cpp")
#    list(APPEND DISCORD_RPC_SOURCE "${CMAKE_SOURCE_DIR}/src/discord/connection_unix.cpp" "${CMAKE_SOURCE_DIR}/src/discord/discord_register_osx.m")
#
#    message(STATUS "MacOS detected. Adding MacOS specific stuff.")

endif()

# Create the main executable
if (ENABLE_DISCORD_RPC)
    add_library(discord-rpc STATIC ${DISCORD_RPC_SOURCE})
    target_include_directories(discord-rpc PUBLIC ${SEARCH_IN})
endif()

add_executable(${PROJECT_NAME} ${ENTITIES2_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_IN})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add fmt as dependency
add_dependencies(${PROJECT_NAME} fmt)
# Link fmt
target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_BINARY_DIR}/src/fmt")
target_link_libraries(${PROJECT_NAME} PUBLIC fmt)

if (ENABLE_DISCORD_RPC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_RPC__)
    if (NOT CUSTOM_DISCORD_ID)
        target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_CLIENT_ID__="1272918238250008726")
    else()
        target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_CLIENT_ID__=${CUSTOM_DISCORD_ID})
    endif()
    # Add the discord-rpc as dependency
    add_dependencies(${PROJECT_NAME} discord-rpc)
    target_link_libraries(${PROJECT_NAME} PUBLIC discord-rpc)
endif()

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

# Terminal bell
if (NOT DISABLE_TERMINAL_BELL)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_TERMINAL_BELL__)
    message(STATUS "Compiling with terminal bell enabled.")
else()
    message(STATUS "Compiling with terminal bell disabled.")
endif()

# Color controlling
if (NOT DISABLE_COLORS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_COLORS__)
    message(STATUS "Compiling with colors enabled.")
else()
    message(STATUS "Compiling with colors disabled.")
endif()