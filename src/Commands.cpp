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

void MakeDir(string path,Directory* Point){//we can assume that path is a Relative path meaning it doesnt start with a /
    int loc = path.find("/",0);
    string directory="";
    Directory *temp;
    if(loc == -1) {//create a directory in Point
        if(Point->getChild(path) != -1) {
            cout << "The directory already exists" << std::endl;
            return;
        }
            Directory *newDir = new Directory(path, Point);
            directory = newDir->getName();
            newDir = nullptr;
            return;

    }else{///has intermediate fDIR
        directory = path.substr(0,loc);//now directory hold the name of the  intermediate  directory
        path = path.substr(loc+1,path.length());///now we have our next Dir objective
        temp = Point->getDirectory("/"+directory);
        if(temp == nullptr){// no such Dir exist
            BaseFile* newDir = new Directory(directory,Point);
            MakeDir(path ,static_cast<Directory*>(newDir));//next Recursive call
            newDir = nullptr;
        }else//Directory exist
            MakeDir(path,temp);
    }
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
    Directory *temp;
    path = delSpace(path);
    if (path[0] == '/') {//absoulte path
        temp = &fs.getRootDirectory();
        if (path.length() == 1) {
            fs.setWorkingDirectory(temp);
            return;
        }
    }else {
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
    Command = delSpace(Command);
    if(Command.length() != 0){
        if(Command[0] == '/')//Absoulote path
            WorkDir = &fs.getRootDirectory();
        else{
            WorkDir = &fs.getWorkingDirectory();
            Command = "/"+ Command;
        }//Relative path
        WorkDir = WorkDir->getDirectory(Command);
        if(WorkDir==nullptr) {
            cout << "The system cannot find the path specified"<< endl;
            return;
        }
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

/////////mkir Command////////////

MkdirCommand::MkdirCommand(string args) : BaseCommand(args){}

void MkdirCommand::execute(FileSystem &fs) {
    string path = this->getArgs();
    path = delSpace(path);
    if (path.length() == 0) {
        std::cout << "path not valid" << endl;
        return;
    }
    Directory *Point;
    if (path[0] == '/') { //Absouloute path
        Point = &fs.getRootDirectory();
        path = path.substr(1,path.length());
    }else
        Point = &fs.getWorkingDirectory();///Relative path--mean we go an order to build a directory here
    MakeDir(path,Point);
}


string MkdirCommand::toString() {return "mkdir";}



/////////MkFile/////////////
MkfileCommand::MkfileCommand(string args) :BaseCommand(args){}

void MkfileCommand::execute(FileSystem &fs) {
    string path = this->getArgs();
    string Size = "";
    string FileName = "";
    BaseFile *newFile;
    int loc;
    bool fag = false;
    Directory* WorkDir;
    while(!fag){
        loc = path.find_last_of(" ");
        if(loc == -1){
            std::cout << "Command not Valid" << endl;
            return;
        }

        if(loc+1 == (int) path.length())
            path =  path.substr(0,path.length() -1);
        else {
            Size = path.substr(loc + 1, path.length());
            path = path.substr(0, loc);
            fag = true;
        }
    }//now Size hold the size integer
    path = delSpace(path);
    loc = path.find_last_of("/");
    if(loc == -1){///Make file in this Directory
        WorkDir = &fs.getWorkingDirectory();
        if (WorkDir->getChild(path) != -1){//ckecks if file exists
            cout << "File already exists" << std::endl;
            return;
        }
        try {
            newFile= new File(path, std::stoi(Size));
        }catch(std::invalid_argument&){    cout << "Invalid Command please enter a valid size integer "<<endl;return; }
        WorkDir->addFile(newFile);
        return;
    }else {
        FileName = path.substr(loc + 1,path.length());
        path = path.substr(0,loc);
    }//TODO now we have the file size in Size the file name in FileName and the path in path so from here is just to get the workDir to the last dir in path and initializing the file
    if(path[0] == '/')
        WorkDir = &fs.getRootDirectory();
    else {

        WorkDir = &fs.getWorkingDirectory();
        path = '/' + path;
    }
    WorkDir = WorkDir->getDirectory(path);
    if(WorkDir == nullptr){
        std::cout << "The system cannot find the path specified" << endl;
        return;
        if (WorkDir->getChild(path) != -1){//ckecks if file exists
            cout << "File already exists" << std::endl;
            return;
        }
    }
    try {
        newFile = new File(FileName, std::stoi(Size));
    }catch(std::invalid_argument){ cout<< "Invalid Command please enter a valid size integer"<<endl;return;}
    WorkDir->addFile(newFile);
}


string MkfileCommand::toString() {return "mkfile";}


//////Cp Command///////

CpCommand::CpCommand(string args) :BaseCommand(args){}

void CpCommand::execute(FileSystem &fs) {
    string path = this->getArgs();
    string Dest = "";
    string src = "";
    int loc;
    bool fag = false;
    while (!fag) {
        loc = path.find_last_of(" ");
        if (loc == -1) {
            std::cout << "Command not Valid" << endl;
            return;
        }

        if (loc + 1 == (int) path.length())
            path = path.substr(0, path.length() - 1);
        else {
            Dest = path.substr(loc + 1, path.length());
            path = path.substr(0, loc);
            fag = true;
        }

    }///now we have a destination path in Dest and Source in path
    BaseFile* temp;
    Directory* Destination;
    Directory* Source;
    Dest = delSpace(Dest);
    if(Dest[0]=='/')
        Destination = &fs.getRootDirectory();
    else{
        Destination = &fs.getWorkingDirectory();
        Dest = '/' + Dest;
    }
    Destination = Destination->getDirectory(Dest);///Destination directory is here
    if(Destination == nullptr){
        cout << "No such file or directory" << endl;
        return;
    }
    path = delSpace(path);
    loc = path.find_last_of('/');
    if(loc != -1) {//means we have an intermediate directories
        src = path.substr(loc+1,path.length());
        path = path.substr(0,loc);
        if(path.length() == 0){//this means src is a file in root
            temp = fs.getRootDirectory().getChildModified(src);
            if(temp == nullptr){
                cout << "No such file or directory" << endl;
                return;
            }
            Destination->ToCopy(temp);
            return;
        }
        if(path[0] == '/')
            Source = &fs.getRootDirectory();
        else {
            Source = &fs.getWorkingDirectory();
            path = '/' + path;
        }
        Source = Source->getDirectory(path);
        if(Source == nullptr) {
            cout << "No such file or directory" << endl;
            return;
        }
        temp = Source->getChildModified(src);
    }else  temp = fs.getWorkingDirectory().getChildModified(path);//file in this working directory

    if(temp == nullptr){
        cout << "No such file or directory" << endl;
        return;
    }
    /*
     * If we got this far this means we have our source to be copied in temp and our destination in Dest
     */
    Destination->ToCopy(temp);
}
string CpCommand::toString() {return "cp";}





//////Mv Command///////////
MvCommand::MvCommand(string args) :BaseCommand(args){}

void MvCommand::execute(FileSystem &fs) {
    string path = this->getArgs();
    string Dest = "";
    string src = "";
    int loc;
    bool fag = false;
    while (!fag) {
        loc = path.find_last_of(" ");
        if (loc == -1) {
            std::cout << "Command not Valid" << endl;
            return;
        }

        if (loc + 1 == (int) path.length())
            path = path.substr(0, path.length() - 1);
        else {
            Dest = path.substr(loc + 1, path.length());
            path = path.substr(0, loc);
            fag = true;
        }

    }///now we have a destination path in Dest and Source in path
    BaseFile *temp;
    Directory *Destination;
    Directory *Source;
    Dest = delSpace(Dest);
    if (Dest[0] == '/')
        Destination = &fs.getRootDirectory();
    else {
        Destination = &fs.getWorkingDirectory();
        Dest = '/' + Dest;
    }
    Destination = Destination->getDirectory(Dest);///Destination directory is here
    if (Destination == nullptr) {
        cout << "No such file or directory" << endl;
        return;
    }
    path = delSpace(path);
    loc = path.find_last_of('/');
    if (loc != -1) {//means we have an intermediate directories
        src = path.substr(loc + 1, path.length());
        path = path.substr(0, loc);


        if (path.length() == 0) {//this means src is a file in root
            temp = fs.getRootDirectory().getChildModified(src);
            if (temp == nullptr) {
                cout << "No such file or directory" << endl;
                return;
            }
            if (temp->isDirectory(temp)) {
                static_cast<Directory *>(temp)->getParent()->removePtr(temp);
                static_cast<Directory *>(temp)->setParent(Destination);

            }else{///temp is a file whose parent is Root
                fs.getRootDirectory().removePtr(temp);//the idea is to deletea pointer and switch to other pointer
                Destination->addFile(temp);

            }
            Destination->addFile(temp);
            return;
        }//end of stupid loop
        if(path[0] == '/')//absoulote path
            Source = &fs.getRootDirectory();
        else {
            Source = &fs.getWorkingDirectory();
            path = '/' + path;
        }
        Source = Source->getDirectory(path);///parent Directory
        temp = Source->getChildModified(src);//file or Directory to be moved

    }else {//from relative folder file or dir in workingdirectory
        Source = &fs.getWorkingDirectory();
        temp = Source->getChildModified(path);
    }   if(temp == nullptr) {
        cout << "No such file or directory" << endl;
        return;
    }
    if(temp->isDirectory(temp))
        static_cast<Directory *>(temp)->setParent(Destination);//need to update parent if Dir

    Source->removePtr(temp);
    Destination->addFile(temp);
    return;
}
string MvCommand::toString() {return "mv";}



//////Error Commmand///////

ErrorCommand::ErrorCommand(string args): BaseCommand(args) {}


string ErrorCommand::toString() {return "Error Command";}

void ErrorCommand::execute(FileSystem &fs) {
    string A = this->getArgs();
   // unsigned long first = A.find_first_not_of(" ",0);
    //unsigned long  second =A.find_first_not_of(" ",first);
   // if//((int)second != -1)
       // A = A.substr(first,second);
    cout << A  + ":Unknown command " << endl;
}
