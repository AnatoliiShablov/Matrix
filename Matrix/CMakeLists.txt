add_library(libmatrix Matrix.cpp Matrix.h)

add_executable(matrix_test Source.cpp)
target_link_libraries(matrix_test PUBLIC libmatrix)