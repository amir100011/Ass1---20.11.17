#include "../include/Files.h"/*
 * Directory.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: amir
 */


#include "../include/Files.h"
#include <string.h>
#include <algorithm>
#include "iostream"

using namespace std;

Directory::Directory(string name, Directory *parent) : BaseFile(name) , parent(parent){
    if(parent != nullptr)
        parent->addFile(this);
}

Directory* Directory::getParent() const {
    return parent;
}

void Directory::setParent(Directory *newParent){

    parent = newParent;
}


void Directory::addFile(BaseFile* file){ // Add the file to children

    bool isFile = file->isDirectory(file);
    bool shouldInsert = true;
    for(vector<BaseFile*>::iterator it = children.begin(); it < children.end();it++){
        if((*it)->getName().compare((*file).getName()) == 0){
            cout << "Folder/Directory with same name already exists" << std::endl;
            shouldInsert = false;
        }
    }
    if (shouldInsert == true) {
        children.push_back(file);
        if(isFile == true)
            static_cast<Directory*> (file)->setParent(this);
    }

}

void Directory::removeFile(string name) { // Remove the file with the specified name from children

    int numOfChildrenStart = this->getChildren().size();
    int numOfChildrenEnd;
    int i; //vector start at index 1
//TODO --if we have same name for a file and a directory which one to delete? currently we delete both
    for (i = 0; i < children.size() + 1; i++) {

        if (name.compare(children[i]->getName()) == 0) {//if the name are the same
            removeFile(children[i]);//remove by a pointer
        }
    }
        numOfChildrenEnd = this->getChildren().size();
        if (numOfChildrenEnd == numOfChildrenStart) {
            cout << "File doesn't exist" << std::endl;
        }
}


void Directory::removeFile(BaseFile* file) {// Remove the file from children


    //TODO possible problem - the pointer doesn't belong to this directory but has same name like one of the directory's files

   /* bool shouldDelete = false;
    for (int i = 0; !shouldDelete && i < children.size(); i++) {
        if ((file->isDirectory(file) && static_cast<Directory *>(children[i]) == static_cast<Directory *>(file))
            || (static_cast<File *>(children[i]) == static_cast<File *>(file))) { shouldDelete = true; }

        if (shouldDelete) {
            children.erase(std::remove(children.begin(), children.end(), file), children.end());
        }
    }

    if (!shouldDelete) {
        cout << "File not found in current folder" << endl;
    }*/

    vector<BaseFile*>::iterator it;

    if(isDirectory(file))//can delete only directories
        delete(file);//TODO recursive deletion at the ~Directory
    else {//file
        for (it = children.begin(); it < children.end(); it++) {
            if (&(**it) ==
                &(*file)) {//only if the pointer is not null or the value (address that he points)is on this directory children
                children.erase(std::remove(children.begin(), children.end(), file), children.end());
                break;
            }
        }
    }
}


void Directory::sortByName() { // Sort children by name alphabetically (not recursively)


    std::sort(children.begin(), children.end(),
              [](const BaseFile* baseFileA, const BaseFile* baseFileB) {
                  return (baseFileA->getName() < baseFileB->getName()); });

}

void Directory::sortBySize() { // Sort children by size (not recursively) if sizes are equal sort by name

    std::sort(children.begin(), children.end(),
              [](BaseFile *baseFileA, BaseFile *baseFileB) {
                   if((baseFileA->getSize() < baseFileB->getSize()))
                        return true;
              else if (baseFileA->getSize() == baseFileB->getSize())
                     return baseFileA->getName() < baseFileB->getName();
                   else
                        return false;});
}

vector<BaseFile*> Directory::getChildren() { // Return children

    return children;
}

int Directory::getSize(){ // Return the size of the directory (recursively)

    int directorySize = 0;

    for_each(children.begin(), children.end(),
             [&](BaseFile* baseFile) {
                 directorySize += baseFile->getSize(); });

    return directorySize;

    //TODO-Better?
    /*for(int i = 1; i < children.Size() + 1; i++){
     * directorySize += children[i]->getSize();}*/

}

string Directory::getAbsolutePath() {//Return the path from the root to this

    std::string path = this->getAbsolutePath(0);
    return path;
}

string Directory::getAbsolutePath(int i) {//Return the path from the root to this

    if (parent == nullptr && i == 0)
        return "/";
    else if (parent == nullptr && i > 0)
        return "";

    return  this->parent->getAbsolutePath(i+1) + ('/' + this->getName());
}

bool Directory::isDirectory(BaseFile* file){

    return true;
}

int Directory::getChild(string child){//return the index of "child" in the children vector if doesn't exists returns -1
    string temp;
    unsigned int i = 1;
    if(children.size() == 0)
        return -1;
    for(i = 0; i< children.size(); i++) {
        temp =children[i]->getName();
        if(!child.compare(temp)){
            if (children[i]->isDirectory(children[i])) {
                return i;
            }
            else
                return -1;
        }
    }
    return -1;

}
Directory* Directory::getDirectory(string path) {
    if(children.size()==0)
        return nullptr;
    bool fag = false;//this is to split the string
    string directory= "";
    int i;
    int location=0;
    string::iterator it;
    for(it = path.begin();it < path.end(); it++) {
        if ('/' == *it && fag){//end sequence of /.../
            fag = false;
            i = getChild(directory);//looking for /".."/ directory
            if (i != -1) {//-1 if we haven't found a directory resembling the name given
                std::cout << "path not valid" << endl;
                return nullptr;
            } else {
                /* if path was /dir1/dir2 and this directory is /
                 * then the next recursive move of the function
                 * will be with path /dir2 and this directory will be at dir1
                 */
                return static_cast<Directory *>(children[i])->getDirectory(path.substr(location,path.length()));
            }
        } else if ('/' == *it && fag == false)//begin sequence of /.../
            fag = true;

        if (fag && '/' != *it) {//Appending the /"..."/
            directory += *it;
            location++;
        }
    }
    i = getChild(directory);
    if(it == path.end() && i>=0){//reached end of path
        return  static_cast<Directory *>(children[i]);

    }else return nullptr;

}


 Directory::~Directory(){
      BaseFile* ptr = nullptr;
     if(children.size() > 0) {
         for (vector<BaseFile *>::iterator it = children.begin(); it < children.end(); it++) {
             ptr = *it;
             delete (ptr);
             cout << "delete" << endl;
         }
         children.erase(children.begin(), children.end());
     }
     parent = nullptr;

}

Directory* Directory::pathValidation(vector<string>* name, int index) {//checks if the path enterd exists and returns a pointer to the new working directory

    Directory* tmpFldr = this;
    bool valid = true;
    string x = (*name)[index];
    string y = this->getName();
    if((*name).size() == index + 1  && (*name)[index - 1] == (this->getName()))//current dir
        return tmpFldr;
    else if ((*name).size() == index + 1)//dir is not the current dir
        return nullptr;
    else {
        for (vector<string>::iterator it = (*name).begin() + index; it < (*name).end() && valid == true; it++) {//next subdriectory/subfile
            string tmp = *it;
            int i = 0;
            for (vector<BaseFile*>::iterator itChildren = this->children.begin(); itChildren != this->children.end() && valid == true; itChildren++) {//TODO last elemnet comparison
                string tmp2 = (**itChildren).getName();
                if ((**itChildren).getName().compare((*it)) == 0){
                    valid = false;
                    tmpFldr = dynamic_cast <Directory*>(this->children[i]);
                }
               else if (itChildren == this->children.end() && (**itChildren).getName().compare((*it)) != 0) {
                    valid = false;
                    cout << "path is not valid" << std::endl;
                    return nullptr;
                }
                i++;
            }
        }
    }
    return tmpFldr->pathValidation(name,index+1);
}