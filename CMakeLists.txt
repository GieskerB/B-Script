cmake_minimum_required(VERSION 3.28)
project(B_Sharp)

set(CMAKE_CXX_STANDARD 26)

add_executable(B_Sharp main.cpp
        DataTypes/Operators.cpp
        DataTypes/Integer.cpp
        DataTypes/Decimal.cpp
        DataTypes/Number.cpp
        DataTypes/NumberPrinter.cpp
)
