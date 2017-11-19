//
// Created by amir on 16/11/17.
//

#include "../include/generalFunctions.h"
#include <iostream>

vector<std::string> pathSplit(string path){//general function returns pointer to a

    vector<std::string> content;
    std::size_t found = path.find("/");

    while(found != std::string::npos) {
        string tmp =path.substr(0, 2);
        if (path.substr(0, 2).compare("..") == 0) {
            if (content.size() > 0)
                content.pop_back();
            else {

                content.~vector();
                content.clear();
                vector<std::string> content(1,"invalid path");
                return content;
            }
            path = path.substr(found + 1, path.size());//jump over X/../something
            found = path.find("/");
        } else if (path.substr(0, 1).compare(".") == 0){
            path = path.substr(found + 1, path.size());//jump over X/../something
            found = path.find("/");
        } else {
            content.push_back(path.substr(0, found));
            path = path.substr(found + 1, path.size());
            found = path.find("/");
        }
    }
    content.push_back(path);
    vector<std::string> content1 (content.size(),"1");
    for (unsigned int i = 0; i < content1.size(); i++)
        content1[i] = content[i];
    for (unsigned int i = 0; i < content.size(); i++)
        content[i] = "";
    return content1;

}

Directory* jumpToNewWorkingDirectory(FileSystem& fs, string path) {

    string lastPathWord = path.substr(path.find_last_of("/") + 1, path.size());

        Directory* currentDir = &fs.getWorkingDirectory();
        if (path[0] == '/') {//this means from root
            path = path.substr(1,path.size());
            vector<string> brokenPath = pathSplit(path);
            if (brokenPath.size() == 1 && brokenPath[0] == "invalid path")
                return nullptr;
            Directory *rootFolder = &fs.getRootDirectory();
            Directory *isValid = rootFolder->pathValidation(brokenPath, 0);
            if (isValid != nullptr) {
                currentDir = isValid;//TODO change name of last expression in path is exists
                return currentDir;
            }else {
                cout << "path is not valid" << endl;
                return nullptr;
            }
        } else if (path[0] == '.' && path[1] == '.' && path[2] == '/') {//go up to parent directory
            currentDir = ((*currentDir).getParent());//go to father worst case nullptr
            path = path.substr(3, path.size());//cutting the expression "../"
            if (currentDir == nullptr) {//changing root or above
                cout << "trying to change folder that doesn't exist (above root)" << std::endl;;
                return currentDir;
            }
            else
                currentDir = ((*currentDir).getParent());//go to grandpa worst case nullptr
            path = path.substr(3, path.size());//cutting the expression "../"
            if (currentDir == nullptr) {//changing root or above
                cout << "can't change root or above folders" << std::endl;
                return currentDir;
            }
            while (path[0] == '.' && path[1] == '.' && path[2] == '/' && currentDir != nullptr) {
                currentDir = ((*currentDir).getParent());
                path = path.substr(3, path.size());//cutting the expression "../"
            }
            if (currentDir == nullptr) {//changing root or above
                cout << "trying to change folder that doesn't exist (above root)" << std::endl;
                return currentDir;
            }
            vector<string> brokenPath = pathSplit(path);
            if (brokenPath.size() == 1 && brokenPath[0] == "invalid path"){
                return nullptr;
            }
            Directory *isValid = currentDir->pathValidation(brokenPath, 0);
            if (isValid != nullptr) {
                currentDir = isValid;
                return currentDir;
            }else{
                cout << "path is not valid" <<endl;

                return nullptr;
            }
        } else if (path[0] == '.' && path[1] == '/') {
            while (path[0] == '.' && path[1] == '/') {
                path = path.substr(2, path.size());//cutting the expression "./"
            }
            vector<string> brokenPath = pathSplit(path);
            if (brokenPath.size() == 1 && brokenPath[0] == "invalid path"){
                return nullptr;
            }
            Directory *isValid = currentDir->pathValidation(brokenPath, 0);
            if (isValid != nullptr) {
                currentDir = isValid;
                return currentDir;
            } else{
                cout << "path is not valid" <<endl;
                return nullptr;
            }
        }
        else {//current directory
            vector<string> brokenPath = pathSplit(path);
            if (brokenPath.size() == 1 && brokenPath[0] == "invalid path"){
                return nullptr;
            }
            Directory *isValid = currentDir->pathValidation(brokenPath, 0);
            if (isValid != nullptr) {
                currentDir = isValid;
                return currentDir;
            } else{
                cout << "path is not valid" <<endl;
                return nullptr;
            }
        }
    }
