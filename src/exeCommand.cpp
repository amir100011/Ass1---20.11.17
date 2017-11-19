//
// Created by dor on 19/11/17.
//

#include "../include/Commands.h"
#include <iostream>
ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history):BaseCommand(args), history(history) {}

void ExecCommand::execute(FileSystem &fs) {
    string number = this->getArgs();
    int B;
    try {
        B = std::stoi(number);
    } catch (std::invalid_argument) {
        cout << "Command not found" << endl;
        return;
    }
    if(B >= this->history.size()){
        cout << "Command not found" << endl;
        return;
    }
    this->history[B]->execute(fs);
}
string ExecCommand::toString() {return "exec";}