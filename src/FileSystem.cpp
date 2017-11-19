//
// Created by amir on 11/11/17.
//

#include "../include/FileSystem.h"
#include "../include/GlobalVariables.h"
#include <iostream>


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

    if (verbose==1 || verbose==3)
        cout << "~FileSystem()" << std::endl;

}

// Move Assignment
FileSystem& FileSystem::operator=(FileSystem &&other){
    if (this != &other){

        rootDirectory = other.rootDirectory;
        workingDirectory = other.workingDirectory;
        other.rootDirectory = nullptr;
        other.workingDirectory = nullptr;

        if (verbose==1 || verbose==3)
            cout << "FileSystem& operator=(FileSystem &&other)" << std::endl;

    }

}

// Move Constructor
FileSystem::FileSystem(FileSystem &&other):rootDirectory(other.rootDirectory), workingDirectory(other.workingDirectory) {

    other.workingDirectory = nullptr;
    other.rootDirectory = nullptr;
    if (verbose==1 || verbose==3)
        cout << "FileSystem(FileSystem &&other)" << std::endl;


}

FileSystem& FileSystem::operator=(const FileSystem &other){//copy assignment

    if (this != &other) {
        rootDirectory = &other.getRootDirectory();
        workingDirectory = &other.getWorkingDirectory();

        if (verbose==1 || verbose==3)
            cout << "FileSystem& operator=(const FileSystem &other)" << std::endl;

    }

    return *this;
}

FileSystem::FileSystem(const FileSystem &other){// Copy Constructor

    rootDirectory = new Directory(other.rootDirectory->getName(),other.rootDirectory->getParent());
    for (int i = 0; i < other.rootDirectory->getChildren().size(); i++){
        rootDirectory->ToCopy(other.rootDirectory->getChildren()[i]);
    }
    string path = other.workingDirectory->getAbsolutePath();
    workingDirectory = rootDirectory->getDirectory(path);//root Directory is an ancestor of working directory

    if (verbose==1 || verbose==3)
        cout << "FileSystem(const FileSystem &other)" << std::endl;

}


