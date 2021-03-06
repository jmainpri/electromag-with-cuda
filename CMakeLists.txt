#===============================================================================
# CMake declarations for top-level directory
#===============================================================================
project(electromag) 

cmake_minimum_required(VERSION 2.8)

#===============================================================================
# Set flags for GCC.
# credit to kicad project
#
# NOTE: You will most likely want these flags set for any meaningful performance
# The code in electromag is optimized to take advantage of SSE, and avoid use of
# SSE if the extensions are not supported by the runtime CPU
#===============================================================================

if(CMAKE_COMPILER_IS_GNUCXX)

    #This is needed for #include <thread>
    set(CMAKE_CXX_FLAGS "-std=c++0x -D_GLIBCXX_USE_NANOSLEEP")
    
    # Set default flags for Release build.
    set(CMAKE_C_FLAGS_RELEASE "-std=c99 -pedantic -Wall -O3 -DNDEBUG -mfpmath=sse -msse2 -fopenmp -ffast-math -fno-math-errno -ffinite-math-only")
    set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -pedantic -Wall -O3 -DNDEBUG -mfpmath=sse -msse2 -fopenmp -ffast-math -fno-math-errno -ffinite-math-only -D_GLIBCXX_USE_NANOSLEEP")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")

    # Set default flags for Debug build.
    set(CMAKE_C_FLAGS_DEBUG "-std=c99 -pedantic -Wall -g3 -ggdb3 -DDEBUG -mfpmath=sse -msse2 -fopenmp -ffast-math -fno-math-errno -ffinite-math-only")
    set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -pedantic -Wall -g3 -ggdb3 -DDEBUG -mfpmath=sse -msse2 -fopenmp -ffast-math -fno-math-errno -ffinite-math-only -D_GLIBCXX_USE_NANOSLEEP")

endif()

#===============================================================================
# Include directories used by all targets
#===============================================================================
include_directories(include)

#===============================================================================
# Let CMake look in these directories for nested
# 'CMakeLists.txt' files to process
#===============================================================================
add_subdirectory(ElectroMag)
add_subdirectory(GPGPU_Segment)


add_dependencies(ElectroMag
            GPGPU_Segment)

# Path to local CMake modules.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

#===============================================================================
# Find libraries that are needed to build ElectroMag.
#===============================================================================

find_package(OpenGL 1.6)
find_package(GLEW 1.5)
find_package(GLUT 2.6)

IF(OPENGL_FOUND AND OPENGL_GLU_FOUND AND GLEW_FOUND AND GLUT_FOUND)
    add_subdirectory(Graphics)
    add_dependencies(ElectroMag
                Graphics)
ELSE()
    MESSAGE( WARNING
        "Not generating graphics portion due to failed dependencies.")
ENDIF()

