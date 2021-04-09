cmake_minimum_required(VERSION 3.14)

project(App VERSION 0.0.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
   options.h
   options.cpp
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
      CXX_STANDARD 11
)

