cmake_minimum_required(VERSION 3.16)
project(mpk C)

set(CMAKE_C_STANDARD 11)



#include(gen_lib/vector/CMakeLists.txt)
#include (gen_lib/user_interacts/CMakeLists.txt)
#include (gen_lib/linear_algebra_elements/CMakeLists.txt)


include (gen_lib/CMakeLists.txt)
message(${LIB})
add_executable(karatsuba
        mpk1.c ${LIB} Polynom/polynom.c Polynom/polynom.h gen_lib/linear_algebra_elements/complex.c gen_lib/linear_algebra_elements/complex.h)
add_executable(naive naive.c ${LIB} Polynom/polynom.h Polynom/polynom.c)
add_executable(toom_cook mpk_lvl2.c ${LIB} Polynom/polynom.h Polynom/polynom.c)
add_executable(fourier ${LIB} Polynom/polynom.h Polynom/polynom.c Polynom/fourier.c Polynom/fourier.h fourier.c)

include_directories(gen_lib)

target_link_libraries(karatsuba m)
target_link_libraries(naive m)
target_link_libraries(toom_cook m)
target_link_libraries(fourier m)