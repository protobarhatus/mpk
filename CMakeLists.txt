cmake_minimum_required(VERSION 3.16)
project(mpk C)

set(CMAKE_C_STANDARD 11)



#include(gen_lib/vector/CMakeLists.txt)
#include (gen_lib/user_interacts/CMakeLists.txt)
#include (gen_lib/linear_algebra_elements/CMakeLists.txt)


include (gen_lib/CMakeLists.txt)
include (Polynom/CMakeLists.txt)
message(${LIB})
add_executable(karatsuba
        mpk1.c ${LIB} ${POLYNOM} mpk1.c)
add_executable(naive naive.c ${LIB} ${POLYNOM} naive.c)
add_executable(toom_cook mpk_lvl2.c ${LIB} ${POLYNOM} mpk_lvl2.c)
add_executable(fourier ${LIB} ${POLYNOM} fourier.c)
add_executable(inverse ${LIB} ${POLYNOM} inverse.c)
add_executable(schonhage_strassen ${LIB} ${POLYNOM} schonhage_strassen.c)
add_executable(time_comparison ${LIB} ${POLYNOM} time_comparisong.c)
add_executable(matrixes_mult ${LIB} matrixes_mult.c)

include_directories(gen_lib)

target_link_libraries(karatsuba m)
target_link_libraries(naive m)
target_link_libraries(toom_cook m)
target_link_libraries(fourier m)
target_link_libraries(inverse m)
target_link_libraries(schonhage_strassen m)
target_link_libraries(time_comparison m)
target_link_libraries(matrixes_mult m)