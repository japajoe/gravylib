cmake_minimum_required(VERSION 3.5.1)

project(gravy)

set(CMAKE_BUILD_TYPE Release)

find_package(OpenSSL REQUIRED)

# Will add __FILENAME__ macros for all source files, which is the filename without full find_path
function(define_file_basename_for_sources targetname)
    get_target_property(source_files "${targetname}" SOURCES)
    foreach(sourcefile ${source_files})
        # Get source file's current list of compile definitions.
        get_property(defs SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS)
        # Add the FILE_BASENAME=filename compile definition to the list.
        get_filename_component(basename "${sourcefile}" NAME)
        list(APPEND defs "__FILENAME__=\"${basename}\"")
        # Set the updated compile definitions on the source file.
        set_property(
            SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS ${defs})
    endforeach()
endfunction()

# Add sources
file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/System/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/System/Collections/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/System/IO/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/System/Net/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/System/Runtime/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/System/Security/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/System/Text/*.cpp"
    #"${PROJECT_SOURCE_DIR}/examples/*.cpp"
)

# Specify include Directory
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/System"
    "${PROJECT_SOURCE_DIR}/include/System/Collections"
    "${PROJECT_SOURCE_DIR}/include/System/IO"
    "${PROJECT_SOURCE_DIR}/include/System/Net"
    "${PROJECT_SOURCE_DIR}/include/System/Runtime"
    "${PROJECT_SOURCE_DIR}/include/System/Security"
    "${PROJECT_SOURCE_DIR}/include/System/Text"
)

#add_executable(${PROJECT_NAME} ${SOURCES})
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} -lpthread -lstdc++fs ${OPENSSL_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

define_file_basename_for_sources(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION /usr/local/include/Gravy)
