cmake_minimum_required(VERSION 3.26)
project(lacaze_lespagnol)

set(CMAKE_CXX_STANDARD 17)

add_executable(lacaze_lespagnol main.cpp
        Algo_PRIM/PrimL.cpp
        Algo_PRIM/PrimL.h
        Algo_PRIM/PrimM.cpp
        Algo_PRIM/PrimM.h)
