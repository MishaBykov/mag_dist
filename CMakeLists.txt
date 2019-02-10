cmake_minimum_required(VERSION 2.8)

#--- имя проекта совпадает с именем каталога проекта
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#--- имя главной цели. CXX значает, что проект на с++
project( ${PROJECT_NAME} C CXX )

########################################################################

#--- обработка хедеров
if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/headers)
    list(APPEND PATH_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/headers)
    FILE (GLOB_RECURSE  HEADERS ${PATH_INCLUDES}/*)
else()
    message(FATAL_ERROR "headers not found")
endif()

########################################################################

#--- обработка cpp-файлов
FILE (GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/implementation/*)

########################################################################

#--- создание цели проекта
#add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} )

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    main.cpp
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PATH_INCLUDES}
)
