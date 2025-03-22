cmake_minimum_required(VERSION 3.18)

project(web_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(web_app)

find_package(Boost REQUIRED COMPONENTS system thread)
target_link_libraries(web_app Boost::system Boost::thread)

target_sources(web_app PRIVATE
    Application.cpp
    ButtonHandler.h
    RequestHandler.h
    Server.cpp
    Server.h
)