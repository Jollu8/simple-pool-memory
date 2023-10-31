CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(MY_PROJECT_NAME example)
project(${MY_PROJECT_NAME} VERSION ${PROJECT_VERSION})
SET(
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

add_subdirectory(../src ${CMAKE_CURRENT_BINARY_DIR}/src)

file(GLOB SOURCE "*.cpp")
#add_library(lib_src)
ADD_EXECUTABLE(example ${SOURCE} )
TARGET_LINK_LIBRARIES(example PRIVATE pool_lib)


if (MSVC)
    target_compile_options(example PRIVATE
            /W4
    )


else ()
    target_compile_options(example PRIVATE
            -Wall -Wextra -pedantic -Werror
    )


endif()