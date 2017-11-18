//
// Created by amir on 16/11/17.
//

#ifndef ASS1_GENERAL_FUNCTIONS_H
#define ASS1_GENERAL_FUNCTIONS_H

#include <string>
#include <vector>
#include "../include/generalFunctions.h"
#include "../include/FileSystem.h"
#include "../include/Files.h"

using namespace std;

vector<std::string>* pathSplit(string path);

void jumpToNewWorkingDirectory(FileSystem& fs, string path);

#endif //ASS1_GENERAL_FUNCTIONS_H



