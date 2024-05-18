#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
bool IsCalled = false;
bool IsDebug = false;
bool IsExit = true;

static short ErrorExitSeq(bool IsExit, short exitcode, string reason) {// Main Script
	if (IsExit) {
		if (IsCalled) {
		}
		else {
			IsCalled = true;
			if (exitcode == 0) { return 0; }
			else {
				cout << "The program is unsastified of your wrongdoings. Giving you code " << exitcode << " as a penalty." << endl << "Reason: " << reason << endl;
				return exitcode;
			}
		}
	}
	else {
		cout << "The program slightly hates the way you do. Giving you code " << exitcode << " as a reminder." << endl << "Reason: " << reason << endl;
	}
	
}

int main(int argc, char* argv[]) {
	cout << endl;
	// Check if help request is being called
	/*
	string IsHelp = argv[1];
	if (IsHelp == "/?" || IsHelp == "-help") {
		cout << "Usage: <size> <size unit> [Append] <file path>" << endl << "Where:" << endl << endl << "<size>: Ranging from 0 - 1024 for each unit." << endl << "<size unit>: B, KB, MB, GB and TB." << endl << "[Append]: Add append to continue filling the file." << endl << "<file path>: Path to the target file to fill. Typically uses a empty file for that." << endl;
		return 0;
	}
	*/
	// Check debug request
	if (filesystem::exists("Debug")) {
		IsDebug = true;
	}
	unsigned short count;
	// Command Check
	if (argc < 2) {
		cout << "Usage: <size> <size unit> [Append] <file path>" << endl << "Where:" << endl << endl << "<size>: Ranging from 0 - 1024 for each unit." << endl << "<size unit>: B, KB, MB, GB and TB." << endl << "[Append]: Add append to continue filling the file." << endl << "<file path>: Path to the target file to fill. Typically uses a empty file for that." << endl;
		return 0;
	}
	if (argc > 3) {
		try {
			count = stoi(argv[1]);
		}
		catch (const invalid_argument) {
			return ErrorExitSeq(true, 1, "There exist input of character other than number.");
		}
		if (count > 1024) {
			return ErrorExitSeq(true, 1, "If you want size larger than 1024, you better off choosing a larger size unit. (The max possible value is 1024 TB.)");
		}
	}
	else {
		string IsHelp = argv[1];
		if (IsHelp == "/?" || IsHelp == "-help") {
			cout << "Usage: <size> <size unit> [Append] <file path>" << endl << "Where:" << endl << endl << "<size>: Ranging from 0 - 1024 for each unit." << endl << "<size unit>: B, KB, MB, GB and TB." << endl << "[Append]: Add append to continue filling the file." << endl << "<file path>: Path to the target file to fill. Typically uses a empty file for that." << endl;
			return 0;
		}
		else {
			return ErrorExitSeq(true, 1, "Arg incomplete");
		}
	}
	// Size And Var Setup
	unsigned long long index = 0;
	unsigned short OuterIndex = 0;
	unsigned long long TargetIndex = 0;
	const unsigned int bindex = 1;
	const unsigned short kbindex = 1024;
	const unsigned int mbindex = 1048576;
	const unsigned int gbindex = 1073741824;
	const unsigned long long tbindex = 1099511627776;
	string ArgContent = argv[2];
	string IfAppendEnabled = argv[3];
	// Append arg.check
	string FilePath;
	if (IfAppendEnabled == "Append" || IfAppendEnabled == "append") {
		if (argc < 5) {
			return ErrorExitSeq(true, 1, "Append enabled, but no file path.");
		}
		FilePath = argv[4];
	}
	else {
		FilePath = argv[3];
		if (argc > 4) {
			ErrorExitSeq(false, 1, "Append is not found, but there is more than 3 arguments. Therefore, ignoring arguments after the third argument. Check if you have mistype the word Append, or else the mistype word Append is used as the file name, which you might not want to.");
		}
	}
	ofstream file(FilePath, ios::app);
	if (IfAppendEnabled == "Append" || IfAppendEnabled == "append") {
		ofstream file(FilePath, ios::app);
	}
	else {
		ofstream file(FilePath);
	}
	// Check if file exist. If not, create it.
	/*
	if (filesystem::exists(FilePath)) {
		string IsCreateFile;
		cout << "The file exist. Overwrite file? [Y,N] ";
		cin >> IsCreateFile;
		if (IsCreateFile == "Y" || IsCreateFile == "y") {
			//Append.enable/disable
			if (IfAppendEnabled == "Append") {
				ofstream file(FilePath, ios::app);
			}
			else {
				ofstream file(FilePath);
			}
		}
		else if (IsCreateFile == "N" || IsCreateFile == "n") {
			return ErrorExitSeq(1, "File not overwritten because user cancelled the operation.");
		}
		else {
			return ErrorExitSeq(1, "Invalid option.");
		}
	}
	else {
		if (IfAppendEnabled == "Append") {
			ofstream file(FilePath, ios::app);
		}
		else {
			ofstream file(FilePath);
		}
	}
	*/
	// Map size to preset size
	if (ArgContent == "B") { TargetIndex = bindex; }
	else if (ArgContent == "KB") { TargetIndex = kbindex; }
	else if (ArgContent == "MB") { TargetIndex = mbindex; }
	else if (ArgContent == "GB") { TargetIndex = gbindex; }
	else if (ArgContent == "TB") { TargetIndex = tbindex; }
	else { return ErrorExitSeq(true, 1, "Invalid size unit."); };
	// Debug output
	if (IsDebug) {
		cout << "Current TargetIndex: " << TargetIndex << endl;
		cout << "Count: " << count << endl;
		cout << "FilePath: " << FilePath << endl;
		cout << "IfAppendEnabled: " << IfAppendEnabled << endl;
	}
	// Main filling loop
	while (OuterIndex != count) {
		index = 0;
		while (index != TargetIndex) {
			index = index + 1;
			if (IsDebug) { cout << index << " Bytes written" << endl; }
			file << " ";
			if (file.fail()) {
				return ErrorExitSeq(true, 1, "^Ignore the upper text. No offense.^ Disk is full");
			}
		}
		OuterIndex = OuterIndex + 1;
		cout << "Pass " << OuterIndex << " complete"  << endl;
	}
	return 0;
}