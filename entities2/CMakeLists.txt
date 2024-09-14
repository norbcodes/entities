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
        LANGUAGES CXX C
        DESCRIPTION "entities2 is a small silly turn based combat CLI game."
)

set(PROJECT_VERSION "v1.8.0-dev")
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "8")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION_IS_DEV 1)

include("CheckIncludeFileCXX")

# Options for compilation.
option(STATIC_LIBS              "Statically link against C and C++ standard lib." OFF)
option(OPTIMIZE                 "Enable optimization." OFF)
option(ENABLE_DISCORD_RPC       "Enable Discord RPC." OFF)
option(CUSTOM_DISCORD_ID        "Custom Discord ID." OFF)
option(DISABLE_COLORS           "Disable colors and styling. ALL of it." OFF)
option(4BIT_COLORS              "Use 4bit colors instead of RGB (ONLY WORKS WHEN COLORS ENABLED)" OFF)
option(4BIT_STYLES              "Enable styling when in 4Bit color mode (ONLY WORKS WHEN 4BIT COLORS ENABLED)" OFF)
option(4BIT_AIXTERM             "Enable bright colors basically (ONLY WORKS WHEN 4BIT COLORS ENABLED)" OFF)
option(DISABLE_TERMINAL_BELL    "Disable terminal bell." OFF)
option(BUILD_DOCS               "Build doxygen documentation." OFF)
option(DISABLE_UNSTABLE_WARN    "Disable warning when starting up a development build of the game." OFF)

# Set search paths
set(
    SEARCH_IN 
    ${CMAKE_SOURCE_DIR}/src/headers
    ${CMAKE_SOURCE_DIR}/src/fmt/include
    ${CMAKE_BINARY_DIR}/headers
)

# Create macro list for Doxygen:
set(
    PREDEFINED_MACROS_DOXY

)

# Set sources
set(
    ENTITIES2_SOURCE
    ${CMAKE_SOURCE_DIR}/src/ai.cpp
    ${CMAKE_SOURCE_DIR}/src/difficulty_picker.cpp
    ${CMAKE_SOURCE_DIR}/src/discord_rpc.cpp
    ${CMAKE_SOURCE_DIR}/src/energy.cpp
    ${CMAKE_SOURCE_DIR}/src/entity.cpp
    ${CMAKE_SOURCE_DIR}/src/exit_msg.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay_info.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay_loop.cpp
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
if(CMAKE_SYSTEM_NAME MATCHES Linux OR CMAKE_SYSTEM_NAME MATCHES Android)
    add_compile_definitions(__linux__)
    list(APPEND PREDEFINED_MACROS_DOXY "__linux__")
    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/linux/headers")
    list(APPEND ENTITIES2_SOURCE "${CMAKE_SOURCE_DIR}/src/linux/sleep.cpp" "${CMAKE_SOURCE_DIR}/src/linux/keyboard.cpp")
    list(APPEND DISCORD_RPC_SOURCE "${CMAKE_SOURCE_DIR}/src/discord/connection_unix.cpp" "${CMAKE_SOURCE_DIR}/src/discord/discord_register_linux.cpp")

    message(STATUS "Linux detected. Adding Linux specific stuff.")

elseif(CMAKE_SYSTEM_NAME MATCHES Windows OR CMAKE_SYSTEM_NAME MATCHES CYGWIN)
    add_compile_definitions(_WIN32 __WIN32__)
    add_compile_definitions(_WIN32 __WIN32__)
    add_compile_options(-mwindows)
    list(APPEND PREDEFINED_MACROS_DOXY "_WIN32" "__WIN32__")
    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/windows/headers")
    list(APPEND ENTITIES2_SOURCE "${CMAKE_SOURCE_DIR}/src/windows/sleep.cpp" "${CMAKE_SOURCE_DIR}/src/windows/keyboard.cpp")
    list(APPEND DISCORD_RPC_SOURCE "${CMAKE_SOURCE_DIR}/src/discord/connection_win.cpp" "${CMAKE_SOURCE_DIR}/src/discord/discord_register_win.cpp")

    # Configure RC script
    configure_file(${CMAKE_SOURCE_DIR}/src/windows/e2_resources.txt ${CMAKE_BINARY_DIR}/e2_resources.rc)

    # Compile RC script
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/e2_resources.res
        COMMAND windres ${CMAKE_BINARY_DIR}/e2_resources.rc -o ${CMAKE_BINARY_DIR}/e2_resources.res
        DEPENDS ${CMAKE_BINARY_DIR}/e2_resources.rc
    )

    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/e2_resources.o
        COMMAND windres ${CMAKE_BINARY_DIR}/e2_resources.res -o ${CMAKE_BINARY_DIR}/e2_resources.o
        DEPENDS ${CMAKE_BINARY_DIR}/e2_resources.res
    )

    list(APPEND ENTITIES2_SOURCE "${CMAKE_BINARY_DIR}/e2_resources.o")

    message(STATUS "Windows detected. Adding Windows specific stuff.")

#elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
#    add_compile_definitions(__APPLE__)
#    list(APPEND SEARCH_IN "${CMAKE_SOURCE_DIR}/src/MacOS/headers")
#    list(APPEND ENTITIES2_SOURCE "${CMAKE_SOURCE_DIR}/src/MacOS/sleep.cpp")
#    list(APPEND DISCORD_RPC_SOURCE "${CMAKE_SOURCE_DIR}/src/discord/connection_unix.cpp" "${CMAKE_SOURCE_DIR}/src/discord/discord_register_osx.m")
#
#    message(STATUS "MacOS detected. Adding MacOS specific stuff.")

else()
    message(FATAL_ERROR "It seems your system is not supported or wasn't detected properly."
                        "CMAKE_SYSTEM_NAME returns ${CMAKE_SYSTEM_NAME}."
                        "If you're on Windows or Linux and you recieved this error, create an issue on the entities2 github repository.")
endif()

if (ENABLE_DISCORD_RPC)
    add_library(discord-rpc STATIC ${DISCORD_RPC_SOURCE})
    target_include_directories(discord-rpc PUBLIC ${SEARCH_IN})
endif()

# Configure version.hpp
configure_file(${CMAKE_SOURCE_DIR}/src/headers/version.txt ${CMAKE_BINARY_DIR}/headers/version.hpp)

# Create the main executable
add_executable(${PROJECT_NAME} ${ENTITIES2_SOURCE})
target_compile_options(${PROJECT_NAME} PUBLIC -Wall)
target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_IN})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add fmt as dependency
add_dependencies(${PROJECT_NAME} fmt)
# Link fmt
target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_BINARY_DIR}/src/fmt")
target_link_libraries(${PROJECT_NAME} PUBLIC fmt)

if (ENABLE_DISCORD_RPC)
    message(STATUS "Enabled Discord RPC.")
    target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_RPC__)
    list(APPEND PREDEFINED_MACROS_DOXY __ENTITIES2_DISCORD_RPC__)
    if (NOT CUSTOM_DISCORD_ID)
        target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_CLIENT_ID__="1272918238250008726")
        list(APPEND PREDEFINED_MACROS_DOXY "__ENTITIES2_DISCORD_CLIENT_ID__=1272918238250008726")
    else()
        target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISCORD_CLIENT_ID__=${CUSTOM_DISCORD_ID})
        list(APPEND PREDEFINED_MACROS_DOXY "__ENTITIES2_DISCORD_CLIENT_ID__=${CUSTOM_DISCORD_ID}")
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
    list(APPEND PREDEFINED_MACROS_DOXY "__ENTITIES2_TERMINAL_BELL__")
    message(STATUS "Compiling with terminal bell enabled.")
else()
    message(STATUS "Compiling with terminal bell disabled.")
endif()

# Color controlling
if (NOT DISABLE_COLORS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_COLORS__)
    list(APPEND PREDEFINED_MACROS_DOXY "__ENTITIES2_COLORS__")

    if (4BIT_COLORS)
        target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_4_BIT_COLORS__)
        list(APPEND PREDEFINED_MACROS_DOXY "__ENTITIES2_4_BIT_COLORS__")
        message(STATUS "Compiling with 4bit colors...")

        if (4BIT_STYLES)
            target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_4_BIT_STYLES__)
            list(APPEND PREDEFINED_MACROS_DOXY "__ENTITIES2_4_BIT_STYLES__")
            message(STATUS "...with styling enabled")
        else()
            message(STATUS "...with styling disabled")
        endif()

        if (4BIT_AIXTERM)
            target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_4_BIT_AIXTERM__)
            list(APPEND PREDEFINED_MACROS_DOXY "__ENTITIES2_4_BIT_AIXTERM__")
            message(STATUS "...with aixterm spec enabled")
        else()
            message(STATUS "...with aixterm spec disabled")
        endif()
    endif()

else()
    message(STATUS "Compiling with no colors :(")
endif()

if (BUILD_DOCS)
    # Get doxygen
    find_package(Doxygen REQUIRED)
    # Configure
    list(JOIN PREDEFINED_MACROS_DOXY " " PREDEFINED_MACROS_DOXY)
    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile ${CMAKE_BINARY_DIR}/Doxyfile)
    # Run!
    add_custom_target(docs COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src COMMENT "Generating Doxygen documentation..." VERBATIM)
    add_dependencies(${PROJECT_NAME} docs)
    message(STATUS "Documentation will be built.")
endif()

# Disable build warn?
if (DISABLE_UNSTABLE_WARN)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __ENTITIES2_DISABLE_UNSTABLE_WARNING__)
endif()