project(MoveSolver)
cmake_minimum_required(VERSION 3.0)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

set ( CMAKE_C_FLAGS "-fshort-enums")

add_executable(moveS moveS.c)

add_executable(moveS2 moveS2.c)
target_include_directories(moveS2 PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(moveS2 PUBLIC ${GLIB_LDFLAGS})