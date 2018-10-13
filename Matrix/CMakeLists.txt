project(libmatrix)

set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/matrix/matrix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/matrix/span.h)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${HEADERS})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} INTERFACE -DTCB_SPAN_NAMESPACE_NAME=std -DTCB_SPAN_THROW_ON_CONTRACT_VIOLATION)
