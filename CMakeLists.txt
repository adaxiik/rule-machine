cmake_minimum_required(VERSION 3.0.0)
project(rule-machine VERSION 1.0)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -flto -ftree-vectorize -march=native -O3 -mtune=generic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -fsanitize=address")



#https://stackoverflow.com/questions/58107854/cmake-is-unable-to-find-sdl2-ttf-im-trying-to-link-it-the-same-way-i-would-wit
#change it if it doesn't work, but find_package(SDL2_TTF) doesn't work for me
#INCLUDE(FindPkgConfig)  
find_package(SDL2)
#find_package(SDL2_TTF)
#find_package(SDL2_IMAGE)


#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)



include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/Application/*.cpp")
add_executable(rule-machine src/main.cpp ${SOURCES})
#target_include_directories(rule-machine PRIVATE /include)

target_link_libraries(rule-machine ${SDL2_LIBRARIES} m)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/rules DESTINATION ${CMAKE_CURRENT_BINARY_DIR})