/*
 * BaseFile.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: amir
 */


#include "../include/Files.h"


using namespace std;

BaseFile::BaseFile(string name) : name(name)
{}//sets the name of BaseFile to the inserted (presumably) file's name


string BaseFile::getName() const{//returns current file name
	return name;
}
void BaseFile::setName(string newName){
	name = newName;
}

