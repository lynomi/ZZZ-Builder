cmake_minimum_required(VERSION 3.10)
project(ZZZBuilder)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6Widgets REQUIRED)

qt_add_resources(RESOURCES fonts/fonts.qrc)

add_executable(ZZZBuilder
 src/main.cpp
 src/AgentList.cpp
 ${RESOURCES}
)

target_link_libraries(ZZZBuilder Qt6::Widgets)

