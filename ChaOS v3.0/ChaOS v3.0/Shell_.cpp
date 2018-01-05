// Shell_.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <conio.h>
#include <cstring>
#include <Windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Headers\Process.h"
#include "Headers\ProcessesManager.h"
#include "Headers\Interpreter.h"
#include "Headers\MemoryManager.h"
#include "Headers\ChaOS_filesystem.h"
#include "Headers\ConditionVariable.h"
#include "Headers\Siec.h"
#include "Headers\ProcessScheduler.h"
#include "Headers\table_maker.h"
#include "locale.h"

using namespace std;

PCB* ActiveProcess;

ProcessScheduler *ps;
ProcessesManager *pm;
MemoryManager *mm;
Siec *s;
ChaOS_filesystem *fs;
std::list<ConditionVariable> cv;
Interpreter *i;

std::vector<std::string> ErrorsTab{

	//Proszę o dopisywanie następnika z własnym opisem błędu. W komentarzu piszcie nr żebyśmy się nie pogubili.
	"Brak błędów w obsłudze.",//(0)
	"Przykładowy błąd który opisuje w tym miejscu jakaś osoba. Możecie go zmienić na własny.", //(1)
	"Brak wolnych sektorów na dysku.",//(2)
	"Obiekt o podanej nazwie już istnieje.",//(3)
	"Obiekt o podanej nazwie nie został odnaleziony.",//(4)
	"Brak otwartego pliku do wykonania operacji.",//(5)
	"Podany plik musi być otwarty, by wykonać operację.", //(6)
	"Aktywny proces ma już otwarty plik.", //(7)
	"Typ pliku, który został podany jest inny niż plik lub folder", //(8)
	"Odwołanie do pamięci z poza obszaru adresowego procesu.", //(9)
	"Brak wolnej pamięci.", //(10)
	"" //(11)
};

class main_loop {
private:
	vector<string> command;
	string line;
	void choose_function();
	void initialize();
	void prepare_string();
	void help();


public:
	main_loop();
	void run();
	void big_letter(vector<string> &pom);
};

void main_loop::big_letter(vector<string> &pom) {
	std::transform(pom[0].begin(), pom[0].end(), pom[0].begin(), ::toupper);
}

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
	ps = new ProcessScheduler();
	pm = new ProcessesManager();
	i = new Interpreter();
	fs = new ChaOS_filesystem();
	s = new Siec();
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
		if (token == "ap" || token == "write") {
			//cout << line << endl;
			command.push_back(line);
			break;
		}
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
		/*
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
	*/
		main_loop::big_letter(command);
		i->DoShellCommand(command);

	}
	else if (command[0] == "rf") {
		/*char tab[1024];
		strcpy_s(tab, command[1].c_str());
		fs->remove(tab);
		*/ 
		main_loop::big_letter(command);
		i->DoShellCommand(command);

		//nie wiemy czy wyrzuca błąd
	}
	else if (command[0] == "ld") {
		//fs->listDirectory(ActiveProcess);
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "cd") {
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		main_loop::big_letter(command);
		i->DoShellCommand(command);
		//fs->changeDirectory(tab);
	}
	else if (command[0] == "rd") {
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "bd") {
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "ren") {
		/*
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		char tab2[1024];
		strcpy_s(tab2, command[2].c_str());
		fs->rename(tab, tab2);
		*/
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "of") {
		/*
		char tab[1024];
		strcpy_s(tab, command[1].c_str());
		fs->openFile(tab);
		*/		
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "clf") {
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "pds") {
		std::cout << fs->printDiskStats() << std::endl;
	}
	else if (command[0] == "pdss") {
		int pom = stoi(command[1]);
		std::cout << fs->printSectorsChain(pom) << std::endl;
	}
	else if (command[0] == "read") {
		//fs->readFile();
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "ap") {
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "write") {
		//fs->writeFile(command[1]);
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "cp") {
		//pm->createProcess(command[1], stoi(command[2]));
		main_loop::big_letter(command);
		i->DoShellCommand(command);
	}
	else if (command[0] == "kp") {
		//pm->killProcess(stoi(command[1]));
		main_loop::big_letter(command);
		i->DoShellCommand(command);
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
			mm->printPCBframes(pm->findPCBbyPID(stoi(command[1])), false);
		}
		else if (command[2] == "-r") {
			mm->printPCBframes(pm->findPCBbyPID(stoi(command[1])), true);
		}
		else if (command[2] == "-f") {
			mm->printFIFO();
		}
		else {
			mm->printMemoryConnetent();
		}
	}
	else if (command[0] == "sms") {
		s->wyswietlwiad();
	}
	else if (command[0] == "go") {
		ps->RunProcess();
	}
	else if (command[0] == "cls") {
		system("cls");
	}
	else {
		throw 1;
	}


}


void main_loop::help() {
	fstream file;
	std::string line;

	TextTable t(196, 179, 197);

	t.add("KOMENDA");
	t.add("OPIS");
	t.endOfRow();
	t.add("help");
	t.add("Wyswietla liste komend");
	t.endOfRow();
	t.add("close");
	t.add("Konczy prace systemu");
	t.endOfRow();
	t.add("cf [nazwa] [typ(plik/folder)]");
	t.add("Tworzy plik/folder");
	t.endOfRow();
	t.add("rf [nazwa]");
	t.add("Usuwa plik/folder");
	t.endOfRow();
	t.add("ld");
	t.add("Wypisuje zawartosc aktualnego folderu");
	t.endOfRow();
	t.add("cd [nazwa]");
	t.add("Przechodzi do podanego folderu(nizszego w hierarchii)");
	t.endOfRow();
	t.add("rd");
	t.add("Przechodzi do folderu ROOT");
	t.endOfRow();
	t.add("bd");
	t.add("Wraca do folderu poprzedniego w hierarchii");
	t.endOfRow();
	t.add("ren [nazwa1] [nazwa2]");
	t.add("Zmienia nazwę podanego pliku/folderu");
	t.endOfRow();
	t.add("of [nazwa]");
	t.add("Otwiera plik");
	t.endOfRow();
	t.add("clf");
	t.add("Zamyka otwarty plik");
	t.endOfRow();
	t.add("pds");
	t.add("Wyświetla statystyki dysku");
	t.endOfRow();
	t.add("pdss [nr_sektora]");
	t.add("Wyświetla zawartość sektora");
	t.endOfRow();
	t.add("read");
	t.add("Wyświetla zawartość pliku");
	t.endOfRow();
	t.add("write [tekst]");
	t.add("Zapisuje tekst do pliku");
	t.endOfRow();
	t.add("ap");
	t.add("Dodaje tekst do pliku");
	t.endOfRow();
	t.add("cp [nazwa_pliku] [nr_grupy]");
	t.add("Tworzy proces");
	t.endOfRow();
	t.add("kp [numer]");
	t.add("Zabija proces");
	t.endOfRow();
	t.add("dap");
	t.add("Wyświetla wszystkie procesy(blok kontrolny)");
	t.endOfRow();
	t.add("dwp");
	t.add("Wyświetla oczekujące procesy");
	t.endOfRow();
	t.add("drp");
	t.add("Wyświetla gotowe procesy");
	t.endOfRow();
	t.add("mem [proces] -r");
	t.add("Wypisze strony procesu które są tylko w ramkach RAM");
	t.endOfRow();
	t.add("mem [proces] -a");
	t.add("Wypisze wszystkie ramki");
	t.endOfRow();
	t.add("mem");
	t.add("Wyświetla RAM");
	t.endOfRow();
	t.add("sms");
	t.add("Wyswietla liste wszystkich wiadomosci");
	t.endOfRow();
	t.add("go");
	t.add("Wykonuje kolejny rozkaz z pliku z aktywnego procesu");
	t.endOfRow();

	t.setAlignment(2, TextTable::Alignment::RIGHT);
	std::cout << t;
}


int main() {
	main_loop m;
	m.run();
	delete ps;
	delete pm;
	delete mm;
	delete s;
	delete fs;
	delete i;
	return EXIT_SUCCESS;
}




