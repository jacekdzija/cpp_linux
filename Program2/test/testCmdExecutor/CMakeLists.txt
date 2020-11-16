file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testCmdExecutor ${SRCS})

TARGET_LINK_LIBRARIES(testCmdExecutor
    libgmock 
    libgtest
)
include_directories(${PROJECT_SOURCE_DIR}/src)
add_test(NAME testCmdExecutor
         COMMAND testCmdExecutor)