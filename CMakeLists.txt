cmake_minimum_required(VERSION 3.12)
project(my_pgp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O3")

include_directories(include)

add_executable(my_pgp
    src/Main.cpp
    src/Params.cpp
    src/Streams.cpp
    src/Crypto/RsaKeys.cpp
    src/Crypto/Factory.cpp
    src/Crypto/Xor.cpp
    # src/Crypto/Aes.cpp
    src/Crypto/Rsa.cpp
)

target_link_libraries(my_pgp PRIVATE
    gmp
)
