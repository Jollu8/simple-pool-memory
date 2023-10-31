CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(MY_PROJECT_NAME pool_lib)
project(${MY_PROJECT_NAME} VERSION ${PROJECT_VERSION})
SET(
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

file(GLOB SOURCE "*.cpp")
file(GLOB HEADER "*.h")
ADD_LIBRARY(${PROJECT_NAME} ${SOURCE} ${HEADER})


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
    )


else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
    )

endif()

