#All Targets
all: fs

#Tool invocations

fs: bin/BaseFile.o bin/Files.o bin/FileSystem.o bin/Directory.o bin/Environment.o bin/Directory.o bin/generalFunctions.o bin/BaseCommand.o bin/Commands.o bin/RmCommand.o bin/rename.o bin/HistoryCommand.o bin/Main.o bin/exeCommand.o bin/Verbose.o
		@echo 'Building target: fs'
		@echo 'Invoking: C++ Linker'
		g++ -o bin/fs bin/BaseFile.o bin/Files.o bin/FileSystem.o bin/Directory.o bin/Environment.o bin/generalFunctions.o bin/BaseCommand.o bin/Commands.o bin/RmCommand.o bin/rename.o bin/HistoryCommand.o bin/Main.o bin/exeCommand.o bin/Verbose.o
	@echo 'Finished building target: fs'
	@echo ' '

bin/Verbose.o: src/Verbose.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Verbose.o src/Verbose.cpp

bin/exeCommand.o: src/exeCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/exeCommand.o src/exeCommand.cpp

bin/FileSystem.o: src/FileSystem.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp

# Depends on the source and header files
bin/BaseCommand.o: src/BaseCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseCommand.o src/BaseCommand.cpp

# Depends on the source and header files
bin/BaseFile.o: src/BaseFile.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseFile.o src/BaseFile.cpp

# Depends on the source and header files
bin/Commands.o: src/Commands.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Commands.o src/Commands.cpp


# Depends on the source and header files
bin/Directory.o: src/Directory.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Directory.o src/Directory.cpp

# Depends on the source and header files
bin/Environment.o: src/Environment.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Environment.o src/Environment.cpp

# Depends on the source and header files
bin/generalFunctions.o: src/generalFunctions.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/generalFunctions.o src/generalFunctions.cpp

# Depends on the source and header files
bin/Files.o: src/Files.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Files.o src/Files.cpp

# Depends on the source and header files
bin/HistoryCommand.o: src/HistoryCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/HistoryCommand.o src/HistoryCommand.cpp


# Depends on the source and header files
bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp


# Depends on the source and header files
bin/RmCommand.o: src/RmCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RmCommand.o src/RmCommand.cpp

# Depends on the source and header files
bin/rename.o: src/rename.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/rename.o src/rename.cpp

#Clean the build directory
clean:
	rm -f bin/*
