add_library(libmatrix INTERFACE)
target_sources(libmatrix INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Matrix.h ${CMAKE_CURRENT_SOURCE_DIR}/Common.h)
target_include_directories(libmatrix INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(matrix_test Source.cpp)
target_link_libraries(matrix_test PUBLIC libmatrix)