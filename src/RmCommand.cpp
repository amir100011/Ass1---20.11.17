//
// Created by amir on 16/11/17.
//

#include <iostream>
#include "../include/Commands.h"
#include <algorithm>

RmCommand::RmCommand(string args) : BaseCommand(args){};


void RmCommand::execute(FileSystem & fs) {

    string path = this->getArgs();
    path = path.substr(path.find_first_not_of(" "), path.find_last_not_of(" ") + 1);//space cutter

    Directory *lastDir = &fs.getWorkingDirectory();

    if (path[0] == '/' && path.size() == 1) {
        cout << "can't remove directory" << std::endl;
        return;
    }
    else
        lastDir = jumpToNewWorkingDirectory(fs, path);

    if (lastDir != nullptr && (*lastDir).getChildren().size() > 0) {
        bool okToDelete = false;
        string oldName = path.substr(path.find_last_of("/") + 1,
                                     path.size());//last argument of the path + name to change to
        bool found = false;
        BaseFile *X = nullptr;
        for (unsigned int i = 0; i < (*lastDir).getChildren().size(); i++) {
            X = (*lastDir).getChildren()[i];
            if (X->getName().compare(oldName) == 0) {
                if (X->getName().compare(oldName) == 0) {
                    if (&(*X) == (&fs.getWorkingDirectory())) {
                        cout << "Can’t remove the working directory" << std::endl;
                        found = true;
                        break;
                    } else if (X->isDirectory(X))//check if it is ok to delete X
                        okToDelete = lastDir->checkSubTree(&fs.getWorkingDirectory(), dynamic_cast<Directory *>(X));
                    if (okToDelete) {
                        (lastDir)->removeFile(X);
                        found = true;
                    } else {//working directory is in the subtree of the path can't delete
                        cout << "Can’t remove the working directory" << std::endl;
                        found = true;
                    }
                }
            }
        }
            if (!found)
                cout << "No such file or directory" << std::endl;
        //}
    }
    else if (lastDir != nullptr)
        cout << "No such file or directory" << std::endl;

}


string RmCommand::toString(){
    return "rm";
}