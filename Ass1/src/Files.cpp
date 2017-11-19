/*
 * Files.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: amir
 */

#include "../include/Files.h"

using namespace std;

File::File(std::string name, int size): BaseFile(name) , size(size){}


int File::getSize(){
	return size;
}

bool File::isDirectory(BaseFile* file){

	return false;
}
