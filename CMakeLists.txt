# CMake Version Check
cmake_minimum_required(VERSION 3.20)

# Project Setup
project("Main" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build Output Path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Build)

# Global Compiler Flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# External Libraries Setup
include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# OpenGL - GLFW
ExternalProject_Add(GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND ""
)

# SOIL2
ExternalProject_Add(SOIL2
    GIT_REPOSITORY https://github.com/SpartanJ/SOIL2.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND ""
)

# GLM
ExternalProject_Add(GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND ""
)

# FreeType2
ExternalProject_Add(FreeType2
    GIT_REPOSITORY https://github.com/freetype/freetype
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND ""
)

# Find System Libraries
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

# Source Files
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)
include_directories(${PROJECT_SOURCE_DIR}/inc/)

# Define Library Target for External Usage
add_library(MainLib STATIC ${SRC})

# macOS Specific Setup
if(APPLE)
    target_link_libraries(MainLib
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework QuartzCore" # Required for CAMetalLayer
    )
else()
    if(MSVC)
        message(STATUS "Using MSVC compiler")
        # Add MSVC specific compiler flags
    else()
        message(STATUS "Using non-MSVC compiler")
        # Set flags for other compilers
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++20 -fpermissive")
    endif()
endif()

# Link Dependencies to Library
add_dependencies(MainLib GLFW SOIL2 GLM FreeType2)
target_include_directories(MainLib PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include)
target_link_libraries(MainLib freetype soil2 glfw3 ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Define Executable Target for Standalone Builds
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_executable(${PROJECT_NAME} ${SRC})

    # macOS Specific Setup for Executable
    if(APPLE)
        target_link_libraries(${PROJECT_NAME}
            "-framework Cocoa"
            "-framework OpenGL"
            "-framework IOKit"
            "-framework CoreFoundation"
            "-framework QuartzCore" # Required for CAMetalLayer
        )
    endif()

    # Link Library to Executable
    target_link_libraries(${PROJECT_NAME} MainLib)
endif()

# Install Targets
install(TARGETS MainLib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
    )
endif()

# Install Headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
