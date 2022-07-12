#Cmake Version Check (Should Decrease to open up more compiler versions)
cmake_minimum_required(VERSION "3.16.3")

#C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Main Project Init
project("Main")

#Build Output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build)

#For Include referencing
include_directories(${PROJECT_SOURCE_DIR}/inc/)

#Compiler Type Windows
if (WIN32)
    #Windows Specific Libraries
    LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/Windows)

    #Auido Library
    # file(COPY ${PROJECT_SOURCE_DIR}/lib/OpenAL32.dll DESTINATION ${PROJECT_SOURCE_DIR}/build/)
endif (WIN32)

#For Threading Find and use
find_package (Threads REQUIRED)
add_compile_options()

#Main Compile Flags for C++
list(APPEND CMAKE_CXX_FLAGS "-O3 -pthread ${CMAKE_CXX_FLAGS} -static -fpermissive")

#Console Hiding
#-mwindows

#Search for files
file(GLOB_RECURSE SOURCES_CPP RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE SOURCES_C RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

#Attach Main Files
add_executable("${PROJECT_NAME}" ${SOURCES_CPP} ${SOURCES_C})

#Compiler Type Windows
if (WIN32)
    #Windows Specific Libraries
    LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/Windows)

    #Auido Library
    # file(COPY ${PROJECT_SOURCE_DIR}/lib/OpenAL32.dll DESTINATION ${PROJECT_SOURCE_DIR}/build/)

    #Link Main Libraries OpenAL32 Needed later
    TARGET_LINK_LIBRARIES("${PROJECT_NAME}" stdc++ soil2 freetype glfw3 opengl32 gdi32 gdiplus pthread ${CMAKE_THREAD_LIBS_INIT})
endif (WIN32)