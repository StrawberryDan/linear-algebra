add_library(linear-algebra INTERFACE Matrix.hpp Vector.hpp Orientation.hpp)
target_include_directories(linear-algebra INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(linear-algebra-test Test.cpp)
target_link_libraries(linear-algebra-test PRIVATE linear-algebra)

add_test(NAME linear-algebra-test COMMAND linear-algebra-test)