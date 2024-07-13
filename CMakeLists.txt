cmake_minimum_required(VERSION 3.16)
project(Atlas_Preview LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Atlas_Preview source/main.cpp
                             source/vec2.cpp)
target_link_libraries(Atlas_Preview PRIVATE sfml-graphics)

if(WIN32)
    add_custom_command(
        TARGET Atlas_Preview
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Atlas_Preview>
        VERBATIM)
endif()
