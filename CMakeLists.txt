cmake_minimum_required(VERSION 3.12)
project(my_pgp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Ofast")

include_directories(include)

add_executable(my_pgp
    src/Main.cpp
    src/Params.cpp
    src/Crypto.cpp
    src/Crypto/Factory.cpp
    src/Crypto/Xor.cpp
)

target_link_libraries(my_pgp PRIVATE
)
