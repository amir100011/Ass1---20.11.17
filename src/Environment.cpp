//
// Created by amir on 11/11/17.
//

#include "../include/Environment.h"
#include <iostream>
#include "../include/GlobalVariables.h"

using namespace std;

Environment::Environment(){

    commandsHistory = *new vector<BaseCommand*>;
    FileSystem fs;

}

void Environment::start(){//TODO send to command only paths --> delete the command name from the input

    Directory* Root = new Directory ("/",nullptr);
    fs.setWorkingDirectory(Root);
    std::string input;

    while(input != "exit"){

        cout << fs.getWorkingDirectory().getAbsolutePath() + ">  ";
        std::getline(std::cin,input);
        while (input.size() == 0) {
            cout << fs.getWorkingDirectory().getAbsolutePath() + ">  ";
            std::getline(std::cin, input);
        }

        input = input.substr(input.find_first_not_of(" "),input.find_last_not_of(" ") + 1);//space cutter

            if(!input.compare("pwd")) {
                BaseCommand* pwd = new PwdCommand(input);
                pwd->execute(fs);
                this->addToHistory(pwd);

                input = "";
            }
        else if (!input.substr(0,input.find(" ")).compare("cd")){//substring is for the address - we need to cut it
                BaseCommand* cd = new CdCommand((input.substr(2,input.size())));
                cd->execute(fs);
                this->addToHistory(cd);// equivalent to commandsHistory.push_back(cd);
                input = "";
            }
        else if(!input.substr(0,input.find(" ")).compare("ls")) {
                BaseCommand* ls = new LsCommand ((input.substr(2,input.size())));
                ls->execute(fs);
                this->addToHistory(ls);
                input = "";
            }
        else if (!input.substr(0,5).compare("mkdir")){
                BaseCommand* mkdir = new MkdirCommand ((input.substr(6,input.size())));
                mkdir->execute(fs);
                this->addToHistory(mkdir);
                input = "";
            }
            else if (!input.substr(0,input.find(" ")).compare("mkfile")){
                BaseCommand* mkfile = new MkfileCommand ((input.substr(7,input.size())));
                mkfile->execute(fs);
                addToHistory(mkfile);
                this->addToHistory(mkfile);
                input = "";
            }
            else if (!input.substr(0,input.find(" ")).compare("cp")){
                BaseCommand* cp = new CpCommand ((input.substr(3,input.size())));
                cp->execute(fs);
                this->addToHistory(cp);
                input = "";
            }
            else if (!input.substr(0,input.find(" ")).compare("mv")){
               BaseCommand* mv = new MvCommand ((input.substr(3,input.size())));
                mv->execute(fs);
                this->addToHistory(mv);
                input = "";
            }
            else if (!input.substr(0,input.find(" ")).compare("rename")){
                BaseCommand* rename = new RenameCommand ((input.substr(7,input.size())));
                rename->execute(fs);
                this->addToHistory(rename);
                input = "";
            }
            else if(!input.substr(0,input.find(" ")).compare("rm")){
                BaseCommand* rm = new RmCommand ((input.substr(3,input.size())));
                rm->execute(fs);
                this->addToHistory(rm);
                input = "";
            }
            else if (!input.substr(0,input.find(" ")).compare("history")){
                BaseCommand* history = new HistoryCommand (input, commandsHistory);
                history->execute(fs);
                this->addToHistory(history);
                input = "";
            }

             else if (!input.substr(0,input.find(" ")).compare("verbose")){
                BaseCommand* verbose = new VerboseCommand((input.substr(7,input.size())));
                verbose->execute(fs);
                addToHistory(verbose);
                input = "";
            }
            else if(!input.substr(0,input.find(" ")).compare("exec")){
                BaseCommand* exeCom = new ExecCommand ((input.substr(5,input.size())), commandsHistory);
                exeCom->execute(fs);
                addToHistory(exeCom);

            }
            else {
                BaseCommand* errorCmd = new ErrorCommand (input);
                errorCmd->execute(fs);
                addToHistory(errorCmd);
                input = "";
            }


    }

}

void Environment::addToHistory(BaseCommand *command) {
    commandsHistory.push_back(command);
}

FileSystem& Environment::getFileSystem() {

    return fs;
}

const vector<BaseCommand*>& Environment:: getHistory() const{

    return this->commandsHistory;
}

Environment::~Environment(){//destructor
    for (int i = 0; i < commandsHistory.size(); i++) {
        delete commandsHistory.at(i);
        commandsHistory.~vector();

        if (verbose==1 || verbose==3)
            cout << "~Environment()" << endl;
    }
}

Environment::Environment(const Environment &other): commandsHistory(other.commandsHistory), fs(other.fs){

    if (verbose==1 || verbose==3)
        cout << "Environment(const Environment &other)" << endl;

}//copy constructor

Environment& Environment::operator=(const Environment &other){//copy assignment

    fs = other.fs;
    commandsHistory = other.commandsHistory;

    if (verbose==1 || verbose==3)
        cout << "Environment& operator=(const Environment &other)" << endl;
    return *this;
}

Environment& Environment::operator=(Environment &&other) {//Move assignment

    if (this != &other) {//Environment has no pointers data members only shifting ownership
        commandsHistory = other.commandsHistory;
        fs = other.fs;
    }

    if (verbose==1 || verbose==3)
        cout << "Environment& operator=(Environment &&other)" << endl;

    return *this;

}

Environment::Environment(Environment &&other):commandsHistory(other.commandsHistory),fs(other.fs){

    if (verbose==1 || verbose==3)
        cout << "Environment(Environment &&other)" << endl;
}//move constructor
//Environment has no pointers data members only placing values