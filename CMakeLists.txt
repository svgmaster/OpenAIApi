cmake_minimum_required(VERSION 3.10)

project(Examples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)

set(PROJECT_NAME OpenAIApi)
set(PROJECT_DESCRIPTION "Community-maintained OpenAI API Library for modern C++")
set(PROJECT_URL "https://github.com/svgmaster/OpenAIApi")
set(OPENAIAPI_VERSION 0.3.1)

project(${PROJECT_NAME}
	VERSION ${OPENAIAPI_VERSION}
        DESCRIPTION ${PROJECT_DESCRIPTION}
        HOMEPAGE_URL ${PROJECT_URL})

set(CMAKE_PROJECT_NAME ${PROJECT_NAME})

enable_language(CXX)

if(WIN32)
add_definitions("-DWIN32")
add_definitions("-DCURL_WIN32")
add_link_options("Ws2_32.lib" "Wldap32.lib" "Crypt32.lib")
endif()

set(OPENAIAPI_VERSION 0.3.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(src ${CMAKE_CURRENT_SOURCE_DIR}/src/ApiHelper.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/OpenAIApi.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ApiHelper.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/EndPoints.h)

find_package(CURL REQUIRED)

include(CheckIncludeFileCXX)
include(TestForSTDNamespace)

add_library(OpenAIApi STATIC ${src})

set_property(TARGET OpenAIApi PROPERTY VERSION ${OPENAIAPI_VERSION})
set_property(TARGET OpenAIApi APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING OPENAIAPI_VERSION
)

target_include_directories(OpenAIApi PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)
target_link_libraries(OpenAIApi CURL::libcurl)

install(TARGETS OpenAIApi EXPORT OpenAIApiTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
)

install(
  FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/OpenAIApi/Client.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/OpenAIApi/Response.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/OpenAIApi/OpenAIException.h
  DESTINATION
    include/OpenAIApi
  COMPONENT
    Devel
)

install(
  FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json_fwd.hpp
  DESTINATION
    include/nlohmann
  COMPONENT
    Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/src/OpenAIApiConfigVersion.cmake"
  VERSION ${OPENAIAPI_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT OpenAIApiTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/src/OpenAIApiTargets.cmake"
  NAMESPACE OpenAIApi::
)

configure_file(src/OpenAIApiConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/src/OpenAIApiConfig.cmake"
  COPYONLY
)
  
set(ConfigPackageLocation lib/cmake/OpenAIApi)
install(EXPORT OpenAIApiTargets
  FILE
    OpenAIApiTargets.cmake
  NAMESPACE
    OpenAIApi::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/src/OpenAIApiConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/src/OpenAIApiConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)

add_custom_target(uninstall
     COMMAND xargs rm < install_manifest.txt
)

include(CPack)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT ${PROJECT_URL})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
