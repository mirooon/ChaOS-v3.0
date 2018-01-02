// Shell_.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include "Headers\Process.h"
#include "Headers\ProcessesManager.h"
#include "Headers\Interpreter.h"
#include "Headers\MemoryManager.h"
#include "Headers\ChaOS_filesystem.h"
#include "Headers\ConditionVariable.h"
#include "Headers\Siec.h"
#include "Headers\ProcessScheduler.h"

using namespace std;

PCB* ActiveProcess;

ProcessScheduler *ps;
ProcessesManager *pm;
MemoryManager *mm;
Siec *s;
ChaOS_filesystem *fs;
ConditionVariable *cv;
Interpreter *i;



class main_loop {
private:
	vector<string> command;
	string line;
	void choose_function();
	void initialize();
	void prepare_string();
	void help();
	PCB* ActiveProcess;

public:
	main_loop();
	void run();
};



void main_loop::initialize() {
	//uruchmienie logo

	//cout << "________/\\\\\\\\\\\\\\\\\\__/\\\\\\______________________________/\\\\\\\\\__________/\\\\\\\\\\\\\\\\\\\\\\___        " << endl
	//	 << " _____/\\\\\\////////__\\/\\\\\\____________________________/\\\\\\///\\\\\\______/\\\\\\/////////\\\\\\_       " << endl
	//	 << "  ___/\\\\\\/___________\\/\\\\\\__________________________/\\\\\\/__\\///\\\\\\___\\//\\\\\\______\\///__      " << endl
	//	 << "   __/\\\\\\_____________\\/\\\\\\__________/\\\\\\\\\\\\\\\\\\_____/\\\\\\______\\//\\\\\\___\\////\\\\\\_________     " << endl
	//	 << "    _\\/\\\\\\_____________\\/\\\\\\\\\\\\\\\\\\\\__\\////////\\\\\\___\\/\\\\\\_______\\/\\\\\\______\\////\\\\\\______    " << endl
	//	 << "     _\\//\\\\\\____________\\/\\\\\\/////\\\\\\___/\\\\\\\\\\\\\\\\\\\\__\\//\\\\\\______/\\\\\\__________\\////\\\\\\___   "<<endl
	//	 << "      __\\///\\\\\\__________\\/\\\\\\___\\/\\\\\\__/\\\\\\/___\\\\\\___\\///\\\\\\__/\\\\\\_____/\\\\\\______\\//\\\\\\__  "<<endl
	//	 << "       ____\\////\\\\\\\\\\\\\\\\\\_\\/\\\\\\___\\/\\\\\\_\\//\\\\__\\\\\\/\\\\____\\///\\\\\\\\\\/_____\\///\\\\\\\\\\\\\\\\\\\\\\/___ "<<endl
	//	 << "        _______\\/////////__\\///____\\///___\\////////\\//_______\\/////_________\\///////////_____" << endl;

	mm = new MemoryManager();
	//uruchamiam tutaj moduły innych osób
	pm = new ProcessesManager();
	i = new Interpreter();
	fs = new ChaOS_filesystem();
	cv = new ConditionVariable();
	s = new Siec();

	//procesor, planista, ram, interpreter, system plików, ?????
}


void main_loop::prepare_string() {
	command.clear();
	size_t pos = 0;
	string delimiter = " ";
	string token;
	int pom = 0;
	while (((pos = line.find(delimiter)) != string::npos + 1) && pom < 3) {
		token = line.substr(0, pos);
		command.push_back(token);
		line.erase(0, pos + delimiter.length());
		pom++;
	}
}

void main_loop::run() {
	initialize();
	while (true) {
		try {
			cout << "> ";
			getline(cin, line);
			if (line == "close")break;
			else {
				prepare_string();
				choose_function();
			}
		}
		catch (...) {
			cout << "Bledna nazwa rozkazu. \nWpisz \"help\" zeby zobaczyc liste rozkazow\n";
		}
	}
}

main_loop::main_loop() {

}



void main_loop::choose_function() {
	//cout << command[0] << " " << command[1] << " " << command[2] << endl;
	if (command[0] == "help") {
		help();
	}
	else if (command[0] == "xD") {
		cout << "           /$$$$$$$ " << endl
			<< "          | $$__  $$" << endl
			<< " /$$   /$$| $$  \\ $$" << endl
			<< "|  $$ /$$/| $$  | $$" << endl
			<< " \\  $$$$/ | $$  | $$" << endl
			<< "  >$$  $$ | $$  | $$" << endl
			<< " /$$/\\  $$| $$$$$$$/" << endl
			<< "|__/  \\__/|_______/ " << endl;

	}
	else if (command[0] == "cf") {
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		if (command[2] == "plik") {
			fs->create(tab, ChaOS_filesystem::type::file);
		}
		else if (command[2] == "folder") {
			fs->create(tab, ChaOS_filesystem::type::dir);
		}
		else {
			throw 1;
		}
	}
	else if (command[0] == "rf") {
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		fs->remove(tab);
	}
	else if (command[0] == "ld") {
		fs->listDirectory();
	}
	else if (command[0] == "cd") {
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		fs->changeDirectory(tab);
	}
	else if (command[0] == "rd") {
		fs->rootDirectory();
	}
	else if (command[0] == "bd") {
		fs->backDirectory();
	}
	else if (command[0] == "ren") {
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		char tab2[1024];
		strcpy_s(tab2, command[2].c_str());
		fs->rename(tab, tab2);
	}
	else if (command[0] == "of") {
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		fs->openFile(tab);
	}
	else if (command[0] == "sf") {
		fs->saveFile();
	}
	else if (command[0] == "clf") {
		fs->closeFile();
	}
	else if (command[0] == "pds") {
		fs->printDiskStats();
	}
	else if (command[0] == "pdss") {
		int pom = stoi(command[1]);
		fs->printSector(pom);
	}
	else if (command[0] == "read") {
		fs->readFile();
	}
	else if (command[0] == "write") {
		fs->writeFile(command[1]);
	}
	else if (command[0] == "cp") {
		pm->createProcess(command[1], stoi(command[2]));
	}
	else if (command[0] == "kp") {
		pm->killProcess(stoi(command[1]));
	}
	else if (command[0] == "dap") {
		pm->displayAllProcesses();
	}
	else if (command[0] == "dwp") {
		pm->displayWaitingProcesses();
	}
	else if (command[0] == "drp") {
		pm->displayReadyProcesses();
	}
	else if (command[0] == "mem") {
		if (command[2] == "-a") {
			mm->printPCBframes(ActiveProcess, false);
		}
		else if (command[2] == "-r") {
			mm->printPCBframes(ActiveProcess, true);
		}
		else {
			mm->printMemoryConnetent();
		}
	}
	else if (command[0] == "sms") {
		s->wyswietlwiad();
	}
	else if (command[0] == "go") {
		i->DoCommand();
	}
	else {
		throw 1;
	}


}


void main_loop::help() {
	fstream file;
	std::string line;
	file.open("help.txt", ios::in);
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			cout << line << endl;
		}
	}
	else {
		cout << "Nie można otworzyć pliku pomocy!";
	}
	file.close();
}


int main() {
	main_loop m;
	m.run();
	return EXIT_SUCCESS;
}




