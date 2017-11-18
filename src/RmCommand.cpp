//
// Created by amir on 16/11/17.
//

#include <iostream>
#include "../include/Commands.h"
#include <algorithm>

RmCommand::RmCommand(string args) : BaseCommand(args){};


void RmCommand::execute(FileSystem & fs){

    string path = this->getArgs();

    if (path[0] == '/')
        cout << "can't remove Root directory" << std::endl;
    else
        jumpToNewWorkingDirectory(fs,path);
    /*string lastPathWord = path.substr(path.find_last_of("/"), path.size());


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
            int i = 0;
            int j = 1;
            while (path[i] == '.' && path[j] == '/') {
                i += 2;
                j += 2;
                path = path.substr(j + 1, path.size());//cutting the expression "./"
            }
            vector<string> *brokenPath = pathSplit(path);
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
            }*/
            path = path.substr(path.find_last_of("/"),path.size());//last argument of the path + name to change to
            string oldName = path.substr(path.find_last_of("/") + 1,path.find(" ") - 1);
            string newName = path.substr(path.find(" ") + 1,path.size());
            bool found = false;
            for(vector<BaseFile*>::iterator it = fs.getWorkingDirectory().getChildren().begin();it < fs.getWorkingDirectory().getChildren().end() && !found;it++){
                if((**it).getName().compare(oldName) == 0) {
                    delete *it;
                    found = true;
                }
            }
            if(!found)
                cout << "File/Directory not found in specified path" << std::endl;
      //  }
    //}
}


string RmCommand::toString(){
    return "rm";
}