# CMakeList.txt : CMake project for JXS_21122_LAB, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (JXS_21122_LAB "JXS_21122_LAB.cpp" "JXS_21122_LAB.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET JXS_21122_LAB PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
