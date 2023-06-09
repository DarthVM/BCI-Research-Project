cmake_minimum_required(VERSION 3.24)
project(Research)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        REQUIRED)
find_package (Qt5Widgets)
find_package(Qt5Charts)

add_executable(Research main.cpp BCI.cpp BCI.h)
target_link_libraries(Research
        Qt5::Core
        Qt5::Widgets
        Qt5::Charts
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()


set(CMAKE_PREFIX_PATH C:/DevLibs/armadillo-12.4.0/include)
set(OpenBLAS_DIR C:/DevLibs/vcpkg/installed/x64-windows/share/openblas)
set(OpenBLAS_HOME C:/DevLibs/vcpkg/installed/x64-windows)

if(WIN32)
    set(BLAS_INCLUDE_DIRS "C:/DevLibs/vcpkg/installed/x64-windows/include")
    set(BLAS_LIBRARIES "C:/DevLibs/armadillo-12.4.0/examples/lib_win64/libopenblas.lib")
    else()
    set(BLAS_LIBRARIES "-Wl,--no-as-needed ${OpenBLAS_LIB}")
endif()



include_directories(${BLAS_INCLUDE_DIRS})






find_package(OpenBLAS CONFIG REQUIRED)
include_directories(${BLAS_INCLUDE_DIR})
set(BLAS_LIBRARIES "C:/DevLibs/armadillo-12.4.0/examples/lib_win64/libopenblas.dll")
include_directories(${LAPACK_INCLUDE_DIR})

find_package(LAPACK REQUIRED)
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
