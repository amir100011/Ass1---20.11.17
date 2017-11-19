#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>

using namespace std;

class BaseFile {
private:
	string name;
	
public:

    virtual	~BaseFile() = default;
	BaseFile(std::string name);
	std::string getName() const;
	void setName(string newName);
	virtual int getSize() = 0;
	//Added functions
	virtual bool isDirectory(BaseFile* file) =0;//checks if this is a file

};

class File : public BaseFile {
private:
	int size;
		
public:
	~File() = default;
	File(std::string name, int size); // Constructor
	int getSize(); // Return the size of the file

	//Added functions
	virtual bool isDirectory(BaseFile* file);
};

class Directory : public BaseFile {
private:
	vector<BaseFile*> children;
	Directory *parent;
    //Added functions
    string getAbsolutePath(int i);//Return the path from the root to this

public:
	Directory(string name, Directory *parent); // Constructor
	Directory *getParent() const; // Return a pointer to the parent of this directory
	void setParent(Directory *newParent); // Change the parent of this directory
	void addFile(BaseFile* file); // Add the file to children
	void removeFile(string name); // Remove the file with the specified name from children
	void removeFile(BaseFile* file); // Remove the file from children
	void sortByName(); // Sort children by name alphabetically (not recursively)
	void sortBySize(); // Sort children by size (not recursively)
	vector<BaseFile*> getChildren(); // Return children
	int getSize(); // Return the size of the directory (recursively)
	string getAbsolutePath();  //Return the path from the root to this

    //added functions
	virtual bool isDirectory(BaseFile* file);
	int getChild(string child);//return the index of "child" in the children vector if doesn't exists returns -1
    Directory* getDirectory(string path);//Returns a pointer to a specipic sub-directory in this directory
	virtual ~Directory();//destructor
	Directory* pathValidation(vector<string>* name, int index);//checks if the path enterd exists and returns a pointer to the new working directory
	void removePtr(BaseFile* file);//remove the pointer from the vector without removing the data from the heap
	void ToCopy(BaseFile*);//creates deep copy of a file or directory that we need to copy
	BaseFile* getChildModified(string child);//returns a pointer to last directory in path
	bool checkSubTree(Directory* file, Directory* directoryToDelete);
	Directory(const Directory& other);//copy constructor
    Directory& operator=(const Directory& other);//copy assignment operator
    Directory(Directory&& other);//move constructor
    Directory& operator=(const Directory&& other);//move operator

};

#endif
