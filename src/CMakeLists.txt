add_subdirectory(mycalc)

add_executable(calc main.cpp)
target_link_libraries(calc mycalc)