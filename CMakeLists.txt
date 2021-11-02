cmake_minimum_required(VERSION 3.16)
project(mpk C)

set(CMAKE_C_STANDARD 11)



#include(gen_lib/vector/CMakeLists.txt)
#include (gen_lib/user_interacts/CMakeLists.txt)
#include (gen_lib/linear_algebra_elements/CMakeLists.txt)


include (gen_lib/CMakeLists.txt)
message(${LIB})
add_executable(karatsuba
        mpk1.c ${LIB} Polynom/polynom.c Polynom/polynom.h)
add_executable(naive naive.c ${LIB} Polynom/polynom.h Polynom/polynom.c)
add_executable(toom_cook mpk_lvl2.c ${LIB} Polynom/polynom.h Polynom/polynom.c)


add_executable(______metatemp gen_lib/linear_algebra_elements/matrix.c gen_lib/linear_algebra_elements/matrix.h gen_lib/linear_algebra_elements/rational.c gen_lib/linear_algebra_elements/rational.h)