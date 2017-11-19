//
// Created by amir on 11/11/17.
//

#include "../include/FileSystem.h"


FileSystem::FileSystem(){//Initialize FileSystem

    Directory root =  Directory("/", nullptr);

    workingDirectory = nullptr;
    rootDirectory = nullptr;

}

Directory& FileSystem::getRootDirectory() const {// Return reference to the root directory

    return *rootDirectory;
}

Directory& FileSystem::getWorkingDirectory() const{// Return reference to the working directory
    return *workingDirectory;
}

void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory){ // Change the working directory of the file system

    workingDirectory = newWorkingDirectory;
    if(rootDirectory == nullptr)//only if we are talking about the root - first initalization
    {
        rootDirectory = newWorkingDirectory;
    }
}
FileSystem::~FileSystem(){
    workingDirectory = nullptr;
    delete(rootDirectory);
    rootDirectory = nullptr;
}