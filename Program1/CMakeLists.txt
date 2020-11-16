# CMakeList.txt : CMake project for CMakeProject3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Program1")

# Add source to this project's executable.
add_executable (Program1 "main.cpp" "main.h")
set_target_properties(Program1 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
# TODO: Add tests and install targets if needed.
