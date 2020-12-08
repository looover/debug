

add_compile_options(-fPIC)

# compile project

#add_executable(Demo ${DIR_SRCS})
add_library (ddebug SHARED debug.cpp)
target_link_libraries(ddebug)
