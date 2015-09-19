# Name of the project
project( Qt5-Tutorial )

# CMake requirement
cmake_minimum_required( VERSION 3.3 FATAL_ERROR )

# Qt requirement
find_package( Qt5 COMPONENTS Widgets REQUIRED )

set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Create executable
add_executable( qt5-tutorial main.cpp gameBoard.cpp lcdRange.cpp cannonField.cpp )

# Link libraries
target_link_libraries( qt5-tutorial Qt5::Widgets )

# Install
INSTALL( PROGRAMS ${CMAKE_BINARY_DIR}/qt5-tutorial DESTINATION ${CMAKE_SOURCE_DIR} )

