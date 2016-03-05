# After installation of libgtest-dev, cd /usr/src/gtest, sudo cmake CMakeLists.txt, sudo make, sudo cp libgtest_main.a libgtest.a /usr/lib
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${DATA_STRUCTURES_SOURCE_DIR}/heap)
include_directories(${DATA_STRUCTURES_SOURCE_DIR}/trie)

file(GLOB SRCS *.cpp)
add_executable(tests ${SRCS})

target_link_libraries(tests heap trie ${GTEST_BOTH_LIBRARIES} pthread)