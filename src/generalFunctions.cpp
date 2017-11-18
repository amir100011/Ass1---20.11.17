//
// Created by amir on 16/11/17.
//

#include "../include/generalFunctions.h"
#include <iostream>

vector<std::string>* pathSplit(string path){//general function returns pointer to a

    vector<std::string> *content = new vector<string>;
    std::size_t found = path.find("/");

    int i = 0;
    while(found != std::string::npos)
    {
        content->push_back(path.substr(0 , found));
        i++;
        path = path.substr(found + 1, path.size());
        found = path.find("/");
    }
    content->push_back(path);
    return content;

}

void jumpToNewWorkingDirectory(FileSystem& fs, string path) {

    string lastPathWord = path.substr(path.find_last_of("/") + 1, path.size());

    if (lastPathWord.compare((fs.getWorkingDirectory().getName())) == 0) {
        cout << "Can’t rename the working directory" << std::endl;
    } else {
        if (path[0] == '/') {//this means from root
            vector<string> *brokenPath = pathSplit(path);
            Directory *rootFolder = &fs.getRootDirectory();
            Directory *isValid = rootFolder->pathValidation(brokenPath, 0);
            if (isValid != nullptr) {
                fs.setWorkingDirectory(isValid);//TODO change name of last expression in path is exists
            }
        } else if (path[0] == '.' && path[1] == '.' && path[2] == '/') {//go up to parent directory
            int i = 0;
            int j = 1;
            int k = 2;
            while (path[i] == '.' && path[j] == '.' && path[k] == '/') {
                fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
                i += 3;
                j += 3;
                k += 3;
                path = path.substr(k + 1, path.size());//cutting the expression "../"
            }
            vector<string> *brokenPath = pathSplit(path);
            Directory *currentDir = &fs.getWorkingDirectory();
            Directory *isValid = currentDir->pathValidation(brokenPath, 0);
            if (isValid != nullptr) {
                fs.setWorkingDirectory(isValid);
            }
        } else if (path[0] == '.' && path[1] == '/') {
            while (path[0] == '.' && path[1] == '/') {
                path = path.substr(2, path.size());//cutting the expression "./"
            }
            vector<string> *brokenPath = pathSplit(path);
            string x = (*brokenPath)[0];
            string y = (*brokenPath)[1];
            Directory *currentDir = &fs.getWorkingDirectory();
            Directory *isValid = currentDir->pathValidation(brokenPath, 0);
            if (isValid != nullptr) {
                fs.setWorkingDirectory(isValid);
            } else {//current directory
                vector<string> *brokenPath = pathSplit(path);
                Directory *currentDir = &fs.getWorkingDirectory();
                Directory *isValid = currentDir->pathValidation(brokenPath, 0);
                if (isValid != nullptr) {
                    fs.setWorkingDirectory(isValid);
                }
            }

        }
    }
}