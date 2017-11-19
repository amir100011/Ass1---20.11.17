/*
 * Directory.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: amir
 */


#include "../include/Files.h"
#include <string.h>
#include <algorithm>
#include "iostream"
#include "../include/GlobalVariables.h"

using namespace std;

Directory::Directory(string name, Directory *parent) : BaseFile(name) , children() , parent(parent){
    if(verbose == 1 || verbose == 3)
        cout<< "Directory::Directory(string name, Directory *parent)"<<endl;
    if(parent != nullptr)
        parent->addFile(this);
}
Directory::~Directory(){
    if(verbose == 1 || verbose == 3)
        cout<< "Directory::~Directory()"<<endl;
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

Directory :: Directory(const Directory &other) :BaseFile(other.getName()) , children(), parent(other.getParent()) {//copy constructor
    if(verbose == 1 || verbose == 3)
        cout<< "Directory :: Directory(const Directory &other)"<<endl;
    for(unsigned int i = 0;i < other.children.size();i++)
        this->ToCopy(other.children[i]);
}
Directory& Directory:: operator=(const Directory& other) {//copy assignment operator
    if(verbose == 1 || verbose == 3)
        cout<< "Directory& Directory:: operator=(const Directory& other)"<<endl;
    if(this == &other)//the two Directory are the same
        return *this;
    if(this->getParent() != nullptr)
        this->getParent()->removePtr(this);//remove this directory from parent directory
    this->setParent(other.getParent());
    for(unsigned int i = 0 ; i < this->children.size() ; i++)
        this->removeFile(children[i]);
    this->children.clear();//clearing the children vector.
    for(unsigned int i = 0 ; i < other.children.size() ; i++)
        this->ToCopy(other.children[i]);//this deeps copy the new children to this directory
    return *this;

}
Directory ::Directory(Directory &&other):BaseFile(other.getName()) , children(), parent(other.getParent())  {//move constructor
    if(verbose == 1 || verbose == 3)
        cout<< "Directory ::Directory(Directory &&other)"<<endl;
    for (unsigned int i = 0; i < other.children.size(); i++)
        this->children.push_back(other.children[i]);
    other.children.clear();//clears the other's children vector now this Directory stole this resource from him
    other.setName("");
    other.getParent()->removePtr(&other);
    other.setParent(nullptr);
    delete (&other);
}
Directory& Directory :: operator=(Directory&& other){//move operator
    if(verbose == 1 || verbose == 3)
        cout<< "Directory& Directory :: operator=(Directory&& other)"<<endl;
    if(this != &other){
        this->setName(other.getName());
        this->getParent()->removePtr(this);
        this->setParent(other.getParent());
        for(unsigned int i = 0 ; i < this->children.size() ; i++)
            this->removeFile(children[i]);
        this->children.clear();//clearing the children vector.
        for(unsigned int i = 0 ; i < other.children.size() ; i++)
            this->children.push_back(other.children[i]);
        other.children.clear();//clear pointers
        other.getParent()->removePtr(&other);
        other.setParent(nullptr);
        delete(&other);
    }
    return *this;

}

Directory* Directory::getParent() const {
    return parent;
}

void Directory::setParent(Directory *newParent){
    parent = newParent;
}


void Directory::addFile(BaseFile* file){ // Add the file to children

    bool isDirectory = file->isDirectory(file);
    bool shouldInsert = true;
    for(vector<BaseFile*>::iterator it = children.begin(); it < children.end();it++){
        if((*it)->getName().compare((*file).getName()) == 0 ){
            cout << "File already exists" << std::endl;
            shouldInsert = false;
        }
    }
    if (shouldInsert == true) {
        children.push_back(file);
        if(isDirectory == true)
            static_cast<Directory*> (file)->setParent(this);
    }

}


void Directory::removeFile(string name) { // Remove the file with the specified name from children

    int numOfChildrenStart = this->getChildren().size();
    int numOfChildrenEnd;
    for (unsigned int i = 0; i < children.size() + 1; i++) {

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

    vector<BaseFile*>::iterator it;
    for(it = children.begin(); it < children.end(); it++){
        if(&(**it) == &(*file)){//only if the pointer is not null or the value (address that he points)is on this directory children
            children.erase(std::remove(children.begin(), children.end(), file), children.end());
            break;
        }
    }
    delete(file);
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
    if(children.size() == 0)
        return -1;
    for(unsigned int i = 0; i< children.size(); i++) {
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
BaseFile* Directory::getChildModified(string child){
    string temp;
    if(children.size() == 0 )
        return nullptr;
    for(unsigned int i = 0 ; i< children.size() ; i++){
        temp = children[i]->getName();
        if(!child.compare(temp)){
            return children[i];
        }
    }
    return nullptr;

}
Directory* Directory::getDirectory(string path) {
    bool fag = false;//this is to split the string
    string directory= "";
    int i = 0;
    int location=0;
    string::iterator it;
    for(it = path.begin();it != path.end(); it++) {
        if ('/' == *it && fag){//end sequence of /.../
            fag = false;
            if(directory.length() == 0) {//first check if there is a statement between the /
                std::cout << "path not valid" << endl;
                return nullptr;
            }
            if( directory.length() == 2 && directory[0] == '.' && directory[1] == '.' ) {//next check if there's dots that means we need to go up
                if (this->getParent() == nullptr) {
                    std::cout << "path not valid" << endl;
                    return nullptr;
                }
                path = path.substr(location+1,path.length());
                if(path.length()==1)//this deals with ../ after substr we get /
                    return this->getParent();
                else return static_cast<Directory *>(this->getParent()->getDirectory(path));//next recursive move is from the parent and we have a case of ../moreChars
            }
            if(directory.length() == 1 && directory[0]== '.' ){
                path = path.substr(location+1 , path.length());
                if(path.length()==1)
                    return this;
                else return this->getDirectory(path);
            }
            //if we passed the above we need to check if the next Dir is one of the children
            if(children.size()==0)
                return nullptr;
            i = getChild(directory);//looking for /".."/ directory
            if (i == - 1 ) {//-1 if we haven't found a directory resembling the name given
                std::cout << "path not valid" << endl;
                return nullptr;
            } else {
                /* if path was /dir1/dir2 and this directory is /
                 * then the next recursive move of the function
                 * will be with path /dir2 and this directory will be at dir1
                 */
                return static_cast<Directory *>(children[i])->getDirectory(path.substr(location+1,path.length()));
            }
        } else if ('/' == *it && fag == false)//begin sequence of /.../
            fag = true;

        if (fag && '/' != *it) {//Appending the /"..."/
            directory += *it;
            location++;
        }
    }
    i = getChild(directory);
    if(it == path.end() && i>=0)//reached end of path
        return  static_cast<Directory *>(children[i]);
    if(i == -1 && directory.compare("..") == 0 )
        return this->getParent();
    if(i== -1 && directory.compare(".") == 0)
        return this;
    else
        return nullptr;
}

/*
 * this function deeps copy file to this directory making a new copy of the file notice that it doesnt delete the original file
 */
void Directory:: ToCopy(BaseFile* file){
    Directory* CopyDir;
    if(file->isDirectory(file)){//to be copied file is directory so we need to recursive copy everything in it
        CopyDir = new Directory(file->getName(),this);//ToDo why this and not file.getParent?
        vector <BaseFile*> CopyChildren = static_cast<Directory*>(file)->getChildren();
        for(unsigned int i = 0 ; i < CopyChildren.size(); i++)
            CopyDir->ToCopy(CopyChildren[i]);
    }else{//file is just a file
        BaseFile* CopyFile = new File(file->getName(),file->getSize());
        this->addFile(CopyFile);
        CopyFile = nullptr;
        return;
    }
     CopyDir = nullptr;


    return;
}

void Directory::removePtr(BaseFile* file){
    vector<BaseFile*>::iterator it;
    for(it = children.begin(); it < children.end(); it++) {
        if (&(**it) == &(*file)) //only if the pointer is not null or the value (address that he points)is on this directory children
            children.erase(std::remove(children.begin(), children.end(), file), children.end());// only deletes pointer

    }
}

Directory* Directory::pathValidation(vector<string>* name, int index) {//checks if the path enterd exists and returns a pointer to the new working directory

    Directory* tmpFldr = this;
    bool valid = true;
    string x = (*name)[index];
    string y = this->getName();
    if (name->size() == 1){
        return tmpFldr;
    }
   else if((*name).size() == (unsigned int)(index + 1) && (*name)[index - 1 ] == (this->getName()))//current dir
        return tmpFldr;
    else if ((*name).size() ==(unsigned int) (index + 1))//dir is not the current dir
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

bool Directory::checkSubTree(Directory* file, Directory* directoryToDelete) {//checks if working dir is in sub-tree of deleted candidate

    Directory* tmp = file->getParent();
        if (file->getParent() == nullptr)
            return true;
        else if (&(*tmp) == &(*directoryToDelete))
            return false;
        else
            return file->checkSubTree(file->getParent(), directoryToDelete);


}