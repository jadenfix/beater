cmake_minimum_required(VERSION 3.10)
project(beater-cpp-conformance CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the generated cpp-restsdk client as a subproject and link against it.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../clients/cpp
                 ${CMAKE_CURRENT_BINARY_DIR}/beater-client-build)

find_package(cpprestsdk REQUIRED)
find_package(Boost REQUIRED)

# The generated client links 'crypto' for static builds; OpenSSL is keg-only on
# Homebrew, so resolve it explicitly and add its lib dir for the bare -lcrypto.
find_package(OpenSSL REQUIRED)
get_filename_component(_openssl_libdir "${OPENSSL_CRYPTO_LIBRARY}" DIRECTORY)
link_directories(${_openssl_libdir})

add_executable(beater_cpp_conformance main.cpp)
target_link_libraries(beater_cpp_conformance
    PRIVATE beater-client cpprestsdk::cpprest Boost::headers OpenSSL::Crypto)
