//
// Created by amir on 15/11/17.
//

#include <iostream>
#include "../include/Commands.h"
#include <algorithm>


RenameCommand::RenameCommand(string args) : BaseCommand(args){};

void RenameCommand::execute(FileSystem & fs) {

    string Command = this->getArgs();
    int length = Command.size();
    std::size_t pathIndex = Command.find(" ");//return index of the letter after " " in command
    string newName = Command.substr(pathIndex + 1, length);//from start of path to the end of string
    pathIndex = Command.find(" ");
    string path = Command.substr(0, pathIndex); //the path

    Directory* lastDir = jumpToNewWorkingDirectory(fs,path);

          if( lastDir != nullptr && (*lastDir).getChildren().size() > 0) {
                  string oldName = path.substr(path.find_last_of("/") + 1,
                                               path.size());//last argument of the path + name to change to
                  bool found = false;
                  bool foundWithSameName = false;
                  BaseFile *X = nullptr;
                  BaseFile *y = nullptr;
                  for (unsigned int i = 0; i < (*lastDir).getChildren().size(); i++) {
                      X = (*lastDir).getChildren()[i];
                      if (X->getName().compare(oldName) == 0) {
                          if (&(*X) == (&fs.getWorkingDirectory())) {
                              cout << "Can’t rename the working directory" << std::endl;
                              foundWithSameName = true;
                          }
                          for (unsigned int j = 0;
                               j < (*lastDir).getChildren().size() && !foundWithSameName && !foundWithSameName; j++) {
                              y = (*lastDir).getChildren()[j];
                              if (y->getName().compare(newName) == 0) {
                                  foundWithSameName = true;
                                  cout << "File/Directory with same name already exists at the target location"
                                       << std::endl;
                              }
                          }
                          if (!foundWithSameName)
                              X->setName(newName);

                          found = true;
                      }
                  }
                  if (!found)
                      cout << "File/Directory not found in specified path" << std::endl;
              }
    else if (lastDir != nullptr)
              cout << "File/Directory not found in specified path" << std::endl;
          }
   // }
string RenameCommand::toString(){
    return "rename";
}


