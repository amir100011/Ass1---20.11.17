//
// Created by dor on 11/11/17.
//
//not to self   "Class::.." means that we are in the body of Class

#include "../include/Commands.h"

BaseCommand::BaseCommand(string Args) :args(Args){}//BaseCommand Constructor

/*BaseCommand::~BaseCommand(){//Destructor
   // args.clear();
    this->args = nullptr;
}*/
string BaseCommand::getArgs() {//returns string
    return this->args;
}
void BaseCommand::setArgs(string Name) {
    this->args=Name;
}
