cmake_minimum_required(VERSION 3.10)
project(${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

if(WIN32)
add_definitions("-DWIN32")
add_definitions("-DCURL_WIN32")
add_link_options("Ws2_32.lib" "Wldap32.lib" "Crypt32.lib")
endif()

add_definitions("-D_CONSOLE")

set(src Examples.cpp)

find_package(CURL REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} ${src})

target_link_libraries(${CMAKE_PROJECT_NAME} OpenAIApi CURL::libcurl)
