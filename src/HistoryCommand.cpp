//
// Created by amir on 16/11/17.
//

#include <iostream>
#include "../include/Commands.h"
#include <algorithm>

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> & history)
        : BaseCommand(args), history(history){};

void HistoryCommand::execute(FileSystem & fs){

   // for(vector<BaseCommand*>::iterator it = history.begin(); it != history.end(); it++){

    for (int i = 0; i < history.size(); i++){
        cout<< std::to_string(i) + "  " + (*history[i]).toString() + "\r" << std::endl;
    }

}

string HistoryCommand::toString(){
    return "history";
}