cmake_minimum_required(VERSION 3.12)
project(RandomMap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_CXX_FLAGS}")

# BEGIN SDL
### https://ccavusoglu.github.io/posts/Setting-up-SDL2-and-SDL_gpu-on-Windows-using-CMake/
set(SDL2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2-2.0.9/i686-w64-mingw32/include)
set(SDL2_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2-2.0.9/i686-w64-mingw32)

### Find the SDL2 library
find_package(SDL2 REQUIRED)

#### SDL2_INCLUDE_DIR variable set by the FindSDL2 module (if it finds directory).
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_GPU_INCLUDE_PATH})

### Copies SDL2 DLL to build
configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.9/i686-w64-mingw32/bin/SDL2.dll" SDL2.dll COPYONLY)

## SDL Image
set(SDL2_IMAGE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_image-2.0.4/i686-w64-mingw32/include)
set(SDL2_IMAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_image-2.0.4/i686-w64-mingw32)

find_package(SDL2_Image REQUIRED)

### SDL2_IMAGE_INCLUDE_DIR variable set by the FindSDL2 module (if it finds directory).
include_directories(${SDL2_IMAGE_INCLUDE_DIR} )

configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.4/i686-w64-mingw32/bin/SDL2_image.dll" SDL2_image.dll COPYONLY)

### Copies SDL2 PNG IMAGE DLL to build
configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.4/i686-w64-mingw32/bin/libpng16-16.dll" libpng16-16.dll COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.4/i686-w64-mingw32/bin/zlib1.dll" zlib1.dll COPYONLY)

### Copies SDL2 PNG IMAGE DLL to build
configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.4/i686-w64-mingw32/bin/libpng16-16.dll" libpng16-16.dll COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.4/i686-w64-mingw32/bin/zlib1.dll" zlib1.dll COPYONLY)

## SDL TTF
set(SDL2_TTF_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_ttf-2.0.14/i686-w64-mingw32/include)
set(SDL2_TTF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_ttf-2.0.14/i686-w64-mingw32)

find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_TTF_INCLUDE_DIR} )

configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.14/i686-w64-mingw32/bin/SDL2_ttf.dll" SDL2_ttf.dll COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.14/i686-w64-mingw32/bin/libfreetype-6.dll" libfreetype-6.dll COPYONLY)

## SDL Mixer SDL2_mixer-2.0.4
set(SDL2_MIXER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/i686-w64-mingw32/include)
set(SDL2_MIXER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/i686-w64-mingw32)

find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_MIXER_INCLUDE_DIR} )

### Copy all SDL mixer DLLs

file(COPY ${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/i686-w64-mingw32/bin/ DESTINATION /)

# END SDL
file(COPY resources DESTINATION /)

add_executable(RandomMap main.cpp)
target_link_libraries(RandomMap ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} mingw32  )


