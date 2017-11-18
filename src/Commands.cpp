//
// Created by amir on 11/11/17.
//

#include <iostream>
#include "../include/Commands.h"
#include <algorithm>

string delSpace(string &str)
{
    int size = str.length();
    for(int j = 0; j<=size; j++)
    {
        for(int i = 0; i <=j; i++)
        {
            if(str[i] == ' ' && str[i+1] == ' ')
            {
                str.erase(str.begin() + i);
            }
            else if(str[0]== ' ')
            {
                str.erase(str.begin());
            }
            else if(str[i] == '\0' && str[i-1]== ' ')
            {
                str.erase(str.end() - 1);
            }
        }
    }
    return str;
}
///////////Pwd Command////////////////
PwdCommand::PwdCommand(string args):BaseCommand(args){}

void PwdCommand::execute(FileSystem &fs) {
    std::cout<<fs.getWorkingDirectory().getAbsolutePath() << endl;
}

string PwdCommand::toString() {
    return "pwd";
}
///////////CD Command////////////////
CdCommand::CdCommand(string args):BaseCommand(args){}


void CdCommand::execute(FileSystem &fs) {
    string path = this->getArgs();
    Directory* temp;
    if (path[0] == '/')//absoulte path
        temp = &fs.getRootDirectory();
    else {
        temp = &fs.getWorkingDirectory();//RelativePath
        path = "/"+path;
    }
    temp = temp->getDirectory(path);
    if(temp == nullptr){//no such path exists
        std::cout << "path not valid" << endl;
        return;
    }
    fs.setWorkingDirectory(temp);
    return;


}
string CdCommand::toString() {
    return "cd";
}
////////Ls Command/////////////
LsCommand::LsCommand(string args) :BaseCommand(args){}

void LsCommand::execute(FileSystem &fs) {
    string Command = this->getArgs();
    Directory* WorkDir;
    int loc = Command.find("-s");
    bool SortBySize = false;
    if(loc != - 1)///-s  found meaning that we sort by Size
        SortBySize = true;
    if(Command.length() != 0 && loc != -1) //there is a path
        Command = Command.substr(loc+2,Command.length());//if loc is -1 then command remains untouched else it give us the path...if exists

    if(Command.length() != 0){
        Command = delSpace(Command);
        if(Command[0] == '/')//Absoulote path
            WorkDir = &fs.getRootDirectory();
        else{
            WorkDir = &fs.getWorkingDirectory();
            Command = "/"+ Command;
        }//Relative path
        WorkDir = WorkDir->getDirectory(Command);
        if(WorkDir==nullptr)
            return;
    }else WorkDir = &fs.getWorkingDirectory();//there isn't a path ls is activated on Working Direcotry
    if (SortBySize)
        WorkDir->sortBySize();
    else WorkDir->sortByName();//By default the children vector is sorted Alphabticly
    vector<BaseFile*> Children = WorkDir->getChildren();
    vector<BaseFile*>::iterator it;
    int size;
    for(it =Children.begin();it != Children.end() ;it++ ){

        if(dynamic_cast<BaseFile*>(*it)->isDirectory(*it))
            std::cout << "DIR  ";
        else    std:: cout<< "FILE  ";
        size = dynamic_cast<BaseFile*>(*it)->getSize();
        std::cout << dynamic_cast<BaseFile*>(*it)->getName()+"  "+to_string(size) << endl;//print name
    }
}
string LsCommand::toString() {
    return "ls";
}
/*
/////////mkir Command////////////

MkdirCommand::MkdirCommand(string args) : BaseCommand(args){}

void MkdirCommand::execute(FileSystem &fs) {
    string path = this->getArgs();
    string directory = "";
    path = delSpace(path);
    bool fag = false;
    if (path.length() == 0) {
        std::cout << "path not valid" << endl;
        return;
    }
    Directory *Point;
    if (path[0] == '/') //Absouloute path
        Point = &fs.getRootDirectory();
    else {
        Point = &fs.getWorkingDirectory();///Relative path--mean we go an order to build a directory here
        BaseFile *newDir = new Directory(path, Point);
        Point->addFile(newDir);
        return;
    }
    while(path.length() != 0) {
        directory = path.substr(0,)
    }



}*/





