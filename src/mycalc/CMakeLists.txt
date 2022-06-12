find_package(Boost COMPONENTS system REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

file(GLOB_RECURSE CPPFILES *.cpp ast/*.cpp)
add_library(mycalc ${CPPFILES})
target_link_libraries(mycalc ${REQUIRED_LLVM_LIBS} ${Boost_LIBRARIES})