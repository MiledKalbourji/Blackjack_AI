cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BlackjackAI)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the static library
add_library(blackjack_lib STATIC
    src/blackjack.cpp
    # Add other source files here
)

# Include directories
include_directories(include)

# Add the main executable
add_executable(blackjack_ai
    src/main.cpp
)

# Link the main executable with the static library
target_link_libraries(blackjack_ai blackjack_lib)

# Add test executable
add_executable(run_tests
    src/test_dealer.cpp
)

# Link the test executable with the static library
target_link_libraries(run_tests blackjack_lib)



