cmake_minimum_required(VERSION 3.4)
project(AircraftSim)

find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText)
find_package(GTest REQUIRED)
find_package(Eigen3 3.3 REQUIRED)

find_library(OSGQOPENGL_DEBUG_LIBRARIES NAMES osgQOpenGLd PATHS ${OSG_ROOT})
find_library(OSGQOPENGL_OPTIMIZED_LIBRARIES NAMES osgQOpenGL PATHS ${OSG_ROOT})

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(PHYSICS_NAME AircraftPhysics)
set(TEST_NAME ${PROJECT_NAME}_UnitTests)

add_library(${PHYSICS_NAME} STATIC
        AircraftPhysics.hpp
        AircraftPhysics.cpp
        Vehicle.hpp
        FixedWing.hpp
        FixedWing.cpp
        FixedWingParameters.hpp
        FixedWingEMBParameters.hpp
        FixedWingEMBParameters.cpp
        FixedWingF16Parameters.hpp
        FixedWingF16Parameters.cpp
        FixedWingMQ9Parameters.hpp
        FixedWingMQ9Parameters.cpp
        MathTools.hpp
        MathTools.cpp
        )

add_executable(${TEST_NAME}
    AircraftPhysicsUnitTests.cpp
    FixedWingUnitTests.cpp
    FixedWingParametersUnitTests.cpp
    MathToolsUnitTests.cpp
    UnitTestUtils.cpp
    UnitTestUtils.hpp
    )

set(MYRESOURCES
    resources/command_icons/command_icons.qrc
    )

add_executable(${PROJECT_NAME}
    Main.cpp
    MainWindow.cpp
    MainWindow.hpp
    MainWindowForm.ui
    KeyboardCommandWindow.cpp
    KeyboardCommandWindow.hpp
    KeyboardCommandWindow.ui
    VehicleUpdateCallback.cpp
    VehicleUpdateCallback.hpp
    WindUpdateCallback.cpp
    WindUpdateCallback.hpp
    ${MYRESOURCES}
    )

target_link_libraries(${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    debug ${OSGQOPENGL_DEBUG_LIBRARIES}
    optimized ${OSGQOPENGL_OPTIMIZED_LIBRARIES}
    ${PHYSICS_NAME}
    Eigen3::Eigen
    )

target_link_libraries(${TEST_NAME}
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    ${PHYSICS_NAME}
    Eigen3::Eigen
    )

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
    )

