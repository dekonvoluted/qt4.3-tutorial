# Name of the project
project( Qt4.3-Tutorial )

# CMake requirement
cmake_minimum_required( VERSION 3.3 )

# Qt requirement
find_package( Qt4 REQUIRED )

# Qt setup
include( ${QT_USE_FILE} )

# Handle Qt macros
qt4_wrap_cpp( headers_moc lcdRange.h cannonField.h gameBoard.h )

# Create executable
add_executable( qt4.3-tutorial main.cpp gameBoard.cpp lcdRange.cpp cannonField.cpp ${headers_moc} )

# Link libraries
target_link_libraries( qt4.3-tutorial ${QT_LIBRARIES} )

# Install
INSTALL( PROGRAMS ${CMAKE_BINARY_DIR}/qt4.3-tutorial DESTINATION ${CMAKE_SOURCE_DIR} )

