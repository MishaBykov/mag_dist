cmake_minimum_required(VERSION 2.8)

#--- имя проекта совпадает с именем каталога проекта
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#--- имя главной цели. CXX значает, что проект на с++
project( ${PROJECT_NAME} C CXX )

set(source_code src)
set(headers ${source_code}/headers)
set(implementation ${source_code}/implementation)

message(
"
config:
    source_code: ${source_code}
    headers: ${headers}
    implementation: ${implementation}
"
)

########################################################################

#--- обработка хедеров
if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${headers})
    list(APPEND PATH_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${headers})
    FILE (GLOB_RECURSE FILES_HEADERS ${PATH_HEADERS}/*)
else()
    message(SEND_ERROR "headers not found")
endif()

if (FILES_HEADERS)
    message("FILES_HEADERS not empty")
else()
    message(WARNING "FILES_HEADERS empty")
endif()

########################################################################

#--- обработка cpp-файлов
if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${implementation})
    list(APPEND PATH_IMPLEMENTATION ${CMAKE_CURRENT_SOURCE_DIR}/${implementation})
    FILE (GLOB_RECURSE FILES_IMPLEMENTATION ${CMAKE_CURRENT_SOURCE_DIR}/${implementation}/*)
else()
    message(SEND_ERROR "implementation not found")
endif()

if (FILES_IMPLEMENTATION)
    message("FILES_IMPLEMENTATION not empty")
else()
    message(WARNING "FILES_IMPLEMENTATION empty")
endif()

########################################################################

add_executable(
    ${PROJECT_NAME}
    ${FILES_HEADERS}
    ${FILES_IMPLEMENTATION}
    ${source_code}/main.cpp
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PATH_HEADERS}
)

message("")