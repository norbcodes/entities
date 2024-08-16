# entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

# The CMakeLists to build entities2.cpp
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# Set the project
project(entities2 
        LANGUAGES CXX 
        VERSION "1.6.1"
        DESCRIPTION "entities2 is a small silly turn based combat CLI game."
)

include("CheckIncludeFileCXX")

# Options for compilation.
option(STATIC_LIBS              "Statically link against C and C++ standard lib." OFF)
option(OPTIMIZE                 "Enable optimization." OFF)
option(ENABLE_DISCORD_RPC       "Enable Discord RPC." OFF)
option(CUSTOM_DISCORD_ID        "Custom Discord ID." OFF)

# Set search paths
set(
    SEARCH_IN 
    ${CMAKE_SOURCE_DIR}/src/headers
)

# Set sources
set(
    ENTITIES2_SOURCE
    ${CMAKE_SOURCE_DIR}/src/ai.cpp
    ${CMAKE_SOURCE_DIR}/src/discord_rpc.cpp
    ${CMAKE_SOURCE_DIR}/src/energy.cpp
    ${CMAKE_SOURCE_DIR}/src/entity.cpp
    ${CMAKE_SOURCE_DIR}/src/exit_msg.cpp
    ${CMAKE_SOURCE_DIR}/src/gen_moves.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
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
    add_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32)
    list(APPEND NEEDED_EXT_HEADERS windows.h)
    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/Windows/headers")
    list(APPEND ENTITIES2_SOURCE "${CMAKE_SOURCE_DIR}/src/Windows/sleep.cpp")
    list(APPEND DISCORD_RPC_SOURCE "${CMAKE_SOURCE_DIR}/src/discord/connection_win.cpp" "${CMAKE_SOURCE_DIR}/src/discord/discord_register_win.cpp")

    message(STATUS "Windows detected. Adding Windows specific stuff.")

endif()

# Create the main executable
if (ENABLE_DISCORD_RPC)
    add_library(discord-rpc STATIC ${DISCORD_RPC_SOURCE})
    target_include_directories(discord-rpc PUBLIC ${SEARCH_IN})
endif()

add_executable(${PROJECT_NAME} ${ENTITIES2_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_IN})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if (ENABLE_DISCORD_RPC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_RPC__)
    if (NOT CUSTOM_DISCORD_ID)
        target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_CLIENT_ID__="1272918238250008726")
    else()
        target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_CLIENT_ID__=${CUSTOM_DISCORD_ID})
    endif()
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