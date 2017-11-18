cmake_minimum_required(VERSION 3.8)
project(Ass1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/Commands.h
        include/Environment.h
        include/Files.h
        include/FileSystem.h
        include/GlobalVariables.h
        src/BaseFile.cpp
        src/Directory.cpp
        src/Files.cpp
        src/FileSystem.cpp
        src/BaseCommand.cpp
        src/Commands.cpp
        #src/Main.cpp
        #src/Environment.cpp
        src/testMain.cpp
        #src/FilesTest1.cpp
        #src/FilesTest2.cpp
        src/rename.cpp
        src/RmCommand.cpp
        "include/generalFunctions.h"
        "src/generalFunctions.cpp"
        src/HistoryCommand.cpp)



add_executable(Ass1 ${SOURCE_FILES})