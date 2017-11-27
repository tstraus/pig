project(pig)
cmake_minimum_required(VERSION 3.0.0)

if(WIN32)
    set(CMAKE_PREFIX_PATH C:/Qt/5.9.3/msvc2017_64)
else()
    set(CMAKE_PREFIX_PATH ~/Qt5.9.3/5.9.3/clang64)
    #set(CMAKE_PREFIX_PATH ~/usr/local/opt/qt5)
endif()

find_package(Qt5 REQUIRED COMPONENTS 
    Core
    Gui
    Widgets
    3DCore
    3DExtras
    3DRender
    3DInput
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE
    src/main.cpp
	src/OrbitTransformController.cpp
)

set(HEADER
	src/OrbitTransformController.h
)

add_executable(${PROJECT_NAME}
    ${SOURCE}
	${HEADER}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
)
