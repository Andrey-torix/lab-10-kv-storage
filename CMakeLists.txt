cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
  SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

#имя проекта
project(lab10 VERSION 0.1.0)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
hunter_add_package(rocksdb)
find_package(RocksDB CONFIG REQUIRED)
hunter_add_package(Boost COMPONENTS regex system filesystem log program_options thread)
find_package(Boost 1.72.0 CONFIG REQUIRED regex system filesystem thread log log_setup program_options date_time)



add_library(menu STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/menu.cpp
)
add_executable(main
 ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
)

add_executable(tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)


target_include_directories(menu
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(main
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(tests
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(tests GTest::gtest_main)
target_link_libraries(menu Boost::program_options Boost::regex Boost::system Boost::filesystem Boost::log Boost::thread RocksDB::rocksdb)
target_link_libraries(main menu)
# TODO: change template word to project name and delete this comment

#исправить


#file(COPY misc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_test(NAME unit_tests COMMAND tests)

#file(COPY misc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_COVERAGE)
  function(ENABLE_PROJECT_COVERAGE PROJECT)
    target_compile_options(${PROJECT} PRIVATE --coverage)
    target_link_libraries(${PROJECT} --coverage)
    add_coverage(${PROJECT})
  endfunction()

  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  # TODO: change template word to project name and delete this comment
  #enable_project_coverage(main)
  enable_project_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()
