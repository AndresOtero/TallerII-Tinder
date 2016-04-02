cmake_minimum_required(VERSION 3.5.0)
#Nombre del proyecto
project (tindertaller)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing ()
add_test (NAME MyTest COMMAND Test)
