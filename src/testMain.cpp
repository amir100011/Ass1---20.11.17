//
// Created by aviran on 08/11/17.
//
#include "../include/Environment.h"
#include <iostream>
int main(int , char **) {

  /*  FileSystem *Temp = new FileSystem();
    BaseCommand* pwd = new PwdCommand("Hi");
    BaseCommand* cd = new CdCommand("Dir111");
    BaseCommand* rename = new RenameCommand("Dir2");
    File File1("File1",3);
    File File2("File2",2);
    File File3("File3",1);
    File File11("File11",4);
    File File12("File12",5);
    File File21("File21",6);
    File File22("File22",7);
    File File111("File111",8);
    File File121("File121",9);
    File File1111("File1111",10);
    File File1112("File1112",0);
    File File5("Something",1000);
    Directory DirRoot("/", nullptr);
    Directory Dir1("Dir1" , &DirRoot);
    Directory Dir2("Dir2" , &DirRoot);
    Directory Dir11("Dir11" , &Dir1);
    Directory Dir12("Dir12" , &Dir1);
    Directory Dir111("Dir111" , &Dir11);
    Temp->setWorkingDirectory(&Dir11);
    pwd->execute(*Temp);
    cd->execute(*Temp);
    cd->setArgs("Nothing");
    pwd->execute(*Temp);
    cd->execute(*Temp);
    pwd->execute(*Temp);


    cout << "BaseFile.cpp Tests starts:"<< endl;

    //Test 1 check - BaseFile.getName()
    if(File1.getName().compare("File1")==0)
        cout << "1 test is OK"<<endl;
    else cout << "Fail at test 1"<< endl;

    //Test 2 check - BaseFile.setName()
    File2.setName("File1");
    if(File2.getName().compare("File1")==0)
        cout << "2 test is OK"<<endl;
    else cout << "Fail at test 2"<< endl;
    File2.setName("File2");

    //Test 3 check - BaseFile.getName()
    if(File1.getName().compare(File2.getName())!=0)
        cout << "3 test is OK"<<endl;
    else cout << "Fail at test 3"<< endl;


    //File.cpp Tests starts

    //Test 4 check - BaseFile.getName()
    if(File1.getSize()==3 && File2.getSize()==2)
        cout << "4 test is OK"<<endl;
    else cout << "Fail at test 4"<< endl;

    //Directory.cpp Tests starts
    //Test 5 check - Directory *getParent()

    if(DirRoot.getParent() == nullptr && Dir111.getParent() == &Dir11)
        cout << "5 test is OK"<<endl;
    else cout << "Fail at test 5"<< endl;

    //Test 6 check - setParent(Directory *newParent)
    Dir12.setParent(&Dir2);
    if(Dir12.getParent() == &Dir2)
        cout << "6 test is OK"<<endl;
    else cout << "Fail at test 6"<< endl;
    Dir12.setParent(&Dir1);

    //Test 7 check - addFile(BaseFile* file)
    DirRoot.addFile(&File1);
    DirRoot.addFile(&File2);
    DirRoot.addFile(&File3);
    Dir1.addFile(&File11);
    Dir1.addFile(&File12);
    Dir2.addFile(&File21);
    Dir2.addFile(&File22);
    Dir11.addFile(&File111);
    Dir12.addFile(&File121);
    Dir111.addFile(&File1111);
    Dir111.addFile(&File1112);
    int numberOfFiles = 0;

    vector<BaseFile*> ChildrenCopy = DirRoot.getChildren();
    vector<BaseFile*>::iterator it = ChildrenCopy.begin();

    for (; it!= ChildrenCopy.end() ; numberOfFiles++, it++) ;
    if(numberOfFiles == 5)
        cout << "7 test is OK"<<endl;
    else cout << "Fail at test 7"<< endl;

    //Test 8 check - void removeFile(string name)
    DirRoot.removeFile("File2");

    ChildrenCopy = DirRoot.getChildren();
    it = ChildrenCopy.begin();

    if( (*it)->getName().compare("Dir1")==0) {
        it++;
        if ((*it)->getName().compare("Dir2")==0)
            cout << "8 test is OK"<<endl;
        else cout << "Fail at test 8"<< endl;
    }else cout << "Fail at test 8"<< endl;

    //Test 9 check - void removeFile(string name)
    DirRoot.removeFile("File3");
    ChildrenCopy = DirRoot.getChildren();
    it = ChildrenCopy.begin();
    if( (*it)->getName().compare("Dir1")==0)
        cout << "9 test is OK"<<endl;
    else cout << "Fail at test 9"<< endl;

    DirRoot.addFile(&File2);
    DirRoot.addFile(&File3);

    //Test 10 check - void removeFile(string name)
    ChildrenCopy = DirRoot.getChildren();
    it = ChildrenCopy.begin();
    numberOfFiles = 0;
    for (; it!= ChildrenCopy.end() ; numberOfFiles++, it++) ;
    if(numberOfFiles == 5)
        cout << "10 test is OK"<<endl;
    else cout << "Fail at test 10"<< endl;


    DirRoot.removeFile(&File2);

    //Test 11 check - void removeFile(BaseFile* file)
    ChildrenCopy = DirRoot.getChildren();
    it = ChildrenCopy.begin();
    if( (*it)->getName().compare("Dir1")==0) {
        it++;
        if ((*it)->getName().compare("Dir2")==0)
            cout << "11 test is OK"<<endl;
        else cout << "Fail at test 11"<< endl;
    }else cout << "Fail at test 11"<< endl;
    DirRoot.removeFile(&File3);
    DirRoot.addFile(&File2);
    DirRoot.addFile(&File3);

    //Test 12 check - void removeFile(BaseFile* file)
      DirRoot.addFile(&Dir1);
      DirRoot.addFile(&Dir2);
      Dir1.addFile(&Dir11);
      Dir1.addFile(&Dir12);
      Dir11.addFile(&Dir111);
    Dir11.removeFile(&Dir111);


      if(DirRoot.getSize()== 55)
          cout << "12 test is OK"<<endl;
      else cout << "Fail at test 12"<< endl;

      //Test 13 check - void removeFile(BaseFile* file)
      if(Dir11.getSize()== 18)
          cout << "13 test is OK"<<endl;
      else cout << "Fail at test 13"<< endl;


    //Test 14 check - string getAbsolutePath();
    string PathDir111 = Dir111.getAbsolutePath();
    string PathDirRoot = DirRoot.getAbsolutePath();
    string PathDir2= Dir2.getAbsolutePath();
    if(PathDir111 == "/Dir1/Dir11/Dir111" && PathDirRoot == "/"&& PathDir2 == "/Dir2")
        cout << "14 test is OK"<<endl;
    else cout << "Fail at test 14"<< endl;

    //Test 15 check - int getSize();
    Directory DirEmpty("DirEmpty", nullptr);
    if(DirEmpty.getSize()==0)
        cout << "15 test is OK"<<endl;
    else cout << "Fail at test 15"<< endl;

    Dir2.addFile(&File5);

    Dir2.removeFile("Something");
    Dir2.removeFile("File21");
    Dir2.removeFile("File22");
    DirRoot.sortBySize();

    DirRoot.sortByName();

/*
    //Test 15 check - rename;
    Temp->setWorkingDirectory(&Dir11);
    rename->setArgs("Dir111/File1112 FileAmir");
    rename->execute(*Temp);

*/
    FileSystem *Temp = new FileSystem();
    Directory* DirRoot = new Directory("/", nullptr);
    Directory* Dir1 = new Directory ("Dir1" , DirRoot);
    Directory* Dir2 = new Directory ("Dir2" , DirRoot);
    Directory* Dir11 = new Directory("Dir11" , Dir1);
    Directory* Dir12 = new Directory("Dir12" , Dir1);
    Directory* Dir111 = new Directory("Dir111" , Dir11);
    Temp->setWorkingDirectory(DirRoot);
    delete(DirRoot);


    return 0;
}
