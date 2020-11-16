# CMakeList.txt : CMake project for CMakeProject2, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

project ("Program2")
set(Program2_SRCS
    "bitmap_image.hpp" 
    "drawer.hpp" 
    "cmd_discovery.hpp" 
    "cmd_executor.hpp" 
    "custom_exceptions.hpp"
)

# Add source to this project's executable.
add_executable (Program2 
"main.cpp" 
${Program2_SRCS}

)
set_target_properties(Program2 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
