#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include "FileSystem.h"
#include "generalFunctions.h"

using namespace std;

class BaseCommand {
private:
	string args;

public:
	virtual ~BaseCommand() = default;
	BaseCommand(string args);
	string getArgs();
	virtual void execute(FileSystem & fs) = 0;
	virtual string toString() = 0;
    void setArgs(string newargs);
};

class PwdCommand : public BaseCommand {
private:
public:
	PwdCommand(string args);
	void execute(FileSystem & fs); // Every derived class should implement this function according to the document (pdf)
	virtual string toString();
};

class CdCommand : public BaseCommand {
private:
public:
	CdCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class LsCommand : public BaseCommand {
private:
public:
	LsCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class MkdirCommand : public BaseCommand {
private:
public:
	MkdirCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class MkfileCommand : public BaseCommand {
private:
public:
	MkfileCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class CpCommand : public BaseCommand {
private:
public:
	CpCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class MvCommand : public BaseCommand {
private:
public:
	MvCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class RenameCommand : public BaseCommand {
private:
public:
	RenameCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class RmCommand : public BaseCommand {
private:
public:
	RmCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class HistoryCommand : public BaseCommand {
private:
	const vector<BaseCommand *> & history;
public:
	HistoryCommand(string args, const vector<BaseCommand *> & history);
	void execute(FileSystem & fs);
	virtual string toString();
};


class VerboseCommand : public BaseCommand {
private:
public:
	VerboseCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class ErrorCommand : public BaseCommand {
private:
public:
	ErrorCommand(string args);
	void execute(FileSystem & fs);
	virtual string toString();
};

class ExecCommand : public BaseCommand {
private:
	const vector<BaseCommand *> & history;
public:
	ExecCommand(string args, const vector<BaseCommand *> & history);
	void execute(FileSystem & fs);
	virtual string toString();
};


#endif
