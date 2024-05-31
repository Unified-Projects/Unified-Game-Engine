#Cmake Version Check (Should Decrease to open up more compiler versions)
cmake_minimum_required(VERSION "3.20.0")

# Global Compiler Flags
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Allow external libraries
include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# Open-GL setups
ExternalProject_Add(OpenGL # Using 4.6 So no macOS support RN (They dont really like OpenGl anyways)
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND  ""
)

# SOIL2 setups
ExternalProject_Add(SOIL2
    GIT_REPOSITORY https://github.com/SpartanJ/SOIL2.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND  ""
)

# GLM OpenGL Mathematics
ExternalProject_Add(GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND  ""
)

# FreeType2 font library
ExternalProject_Add(FreeType2
    GIT_REPOSITORY https://github.com/freetype/freetype
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    UPDATE_COMMAND  ""
)

# TODO: Port to a library

#Main Project Init
project("Main" LANGUAGES CXX C)

#Build Output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build)

#For Include referencing
include_directories()

#For Threading Find and use
find_package (Threads REQUIRED)
add_compile_options()

#Console Hiding
#-mwindows

#Search for files
file(GLOB_RECURSE SRC
${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c*
)
file(GLOB_RECURSE SRC
${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*
)

#Attach Main Files
add_executable(${PROJECT_NAME} ${SRC}) 

if(MSVC)
    message(STATUS "Using MSVC compiler")
    # Add MSVC specific compiler flags
else()
    message(STATUS "Using non-MSVC compiler")
    # Set flags for other compilers
    target_compile_options(Main PRIVATE "-O3 -std=c++20 -fpermissive")
endif()

# Find the OpenGL library depening on compiler
find_package(OpenGL REQUIRED)

# Link libraries and require exteral first
add_dependencies(${PROJECT_NAME} SOIL2 GLM FreeType2 OpenGL)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/include/freetype)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc/)
target_link_libraries(${PROJECT_NAME} freetype soil2 glfw3 ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})