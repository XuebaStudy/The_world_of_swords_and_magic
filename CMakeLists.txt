cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置 MinGW-w64 的编译器路径
set(CMAKE_C_COMPILER "${PROJECT_SOURCE_DIR}/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "${PROJECT_SOURCE_DIR}/mingw64/bin/g++.exe")

# 设置 SFML 的 CMake 模块路径
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/External/SFML-2.6.2/lib/cmake/SFML")

# 查找 SFML 库（动态链接）
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

# 添加可执行文件
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Creature.cpp
    src/Summoner.cpp
    src/Event.cpp
    src/Tools.cpp
    src/UserIO.cpp
    src/Mode.cpp
    src/Effect.cpp
    src/SFMLUI.cpp
)

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/include/battle
)

# 链接 SFML 动态库
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# 定义输出目录
set(OUTPUT_BIN_DIR "${PROJECT_SOURCE_DIR}/Project/bin")

# 确保输出目录存在
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_BIN_DIR}")

# 定义一个函数来检查文件是否存在并复制
function(copy_if_not_exists source destination)
    if(NOT EXISTS "${destination}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${source}" "${destination}"
        )
    endif()
endfunction()

# 自动复制 SFML 的 DLL 文件到指定目录
copy_if_not_exists("${PROJECT_SOURCE_DIR}/External/SFML-2.6.2/bin/sfml-graphics-d-2.dll" "${OUTPUT_BIN_DIR}/sfml-graphics-d-2.dll")
copy_if_not_exists("${PROJECT_SOURCE_DIR}/External/SFML-2.6.2/bin/sfml-window-d-2.dll" "${OUTPUT_BIN_DIR}/sfml-window-d-2.dll")
copy_if_not_exists("${PROJECT_SOURCE_DIR}/External/SFML-2.6.2/bin/sfml-system-d-2.dll" "${OUTPUT_BIN_DIR}/sfml-system-d-2.dll")
copy_if_not_exists("${PROJECT_SOURCE_DIR}/External/SFML-2.6.2/bin/sfml-audio-d-2.dll" "${OUTPUT_BIN_DIR}/sfml-audio-d-2.dll")

# 自动复制 MinGW 的 C++ 运行时库 DLL 文件到指定目录
copy_if_not_exists("${PROJECT_SOURCE_DIR}/mingw64/bin/libgcc_s_seh-1.dll" "${OUTPUT_BIN_DIR}/libgcc_s_seh-1.dll")
copy_if_not_exists("${PROJECT_SOURCE_DIR}/mingw64/bin/libstdc++-6.dll" "${OUTPUT_BIN_DIR}/libstdc++-6.dll")
copy_if_not_exists("${PROJECT_SOURCE_DIR}/mingw64/bin/libwinpthread-1.dll" "${OUTPUT_BIN_DIR}/libwinpthread-1.dll")