//
// Created by dor on 19/11/17.
//
#include "../include/Commands.h"
#include "../include/GlobalVariables.h"
#include <iostream>

VerboseCommand ::VerboseCommand(string args):BaseCommand(args) {}

void VerboseCommand::execute(FileSystem &fs) {
    string A = this->getArgs();
    unsigned  int B;
    try {
        B = std::stoi(A);
    } catch (std::invalid_argument&) {
        cout << "Wrong verbose input" << endl;
        return;
    }
    if(B == 1||B == 2 || B == 3) {
        verbose = B;
    }else  cout << "Wrong verbose input" << endl;
}
string VerboseCommand::toString() {return "verbose";}