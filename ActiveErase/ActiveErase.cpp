#include <iostream>
//#include <fstream>
#include <string>
#include <filesystem>
#include <windows.h>
using namespace std;
bool IsCalled = false;
bool IsDebug = false;
bool IsExit = true;

static short ErrorExitSeq(bool IsExit, short exitcode, string reason) {
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

static short ShowHelp() {
	cout << "Usage: <size> <size unit> [Append] <file path>" << endl << "Where:" << endl << endl << "<size>: Ranging from 0 - 1024 for each unit." << endl << "<size unit>: B, KB, MB, GB and TB. (Upper/Lower is OK)" << endl << "[Append]: Add append to continue filling the file." << endl << "<file path>: Path to the target file to fill. Typically uses a empty file for that." << endl << "Note:" << endl << "For unit \"B\", range restriction is not enforced." << endl << "Append does call the handle to open the file as append, but apparently does not work." << endl;
	return 0;
}

int main(int argc, char* argv[]) {
	// Check debug request
	if (filesystem::exists("Debug")) {
		IsDebug = true;
		cout << "Debug is ON" << endl << "Debug status is " << IsDebug << endl;
	}
	unsigned long long TargetSize;
	// Command Check
	if (argc < 2) {
		ShowHelp();
		return 0;
	}
	if (argc > 3) {
		try {
			TargetSize = stoull(argv[1]);
		}
		catch (const invalid_argument) {
			return ErrorExitSeq(true, 1, "There exist input of character other than number.");
		}
		catch (const out_of_range) {
			return ErrorExitSeq(true, 1, "Number too large.");
		}
	}
	else {
		string IsHelp = argv[1];
		if (IsHelp == "/?" || IsHelp == "-help") {
			ShowHelp();
			return 0;
		}
		else {
			return ErrorExitSeq(true, 1, "Arg incomplete");
		}
	}
	// Size And Var Setup
	unsigned long long SizePreset = 0;
	const unsigned short bindex = 1;
	const unsigned short kbindex = 1024;
	const unsigned int mbindex = 1048576;
	const unsigned int gbindex = 1073741824;
	const unsigned long long tbindex = 1099511627776;
	string ArgContent = argv[2];
	const char* IfAppendEnabled = argv[3];
	// Append arg.check
	const char* FilePath;
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
	if (TargetSize > 1024) {
		if (ArgContent == "B" || ArgContent == "b") {}
		else {
			return ErrorExitSeq(true, 1, "If you want size larger than 1024, you better off choosing a larger size unit. (The max possible value is 1024 TB.)");
		}
	}
	HANDLE hFile = CreateFileA(
		FilePath,           // lpFileName
		GENERIC_WRITE,      // dwDesiredAccess
		0,                  // dwShareMode
		NULL,               // lpSecurityAttributes
		CREATE_ALWAYS,      // dwCreationDisposition
		FILE_ATTRIBUTE_NORMAL, // dwFlagsAndAttributes
		NULL                // hTemplateFile
	);
	
	if (IfAppendEnabled == "Append" || IfAppendEnabled == "append") {
		CloseHandle(hFile);
		HANDLE hFile = CreateFileA(
			FilePath,           // lpFileName
			GENERIC_WRITE | FILE_APPEND_DATA,   // dwDesiredAccess
			0,                  // dwShareMode
			NULL,               // lpSecurityAttributes
			OPEN_ALWAYS,        // dwCreationDisposition
			FILE_ATTRIBUTE_NORMAL, // dwFlagsAndAttributes
			NULL                // hTemplateFile
		);
		cout << "Apparently append does not work.";
	}
	if (hFile == INVALID_HANDLE_VALUE) {
		ErrorExitSeq(true, 1, "File can't be opened. Either disk full or file in use");
	}
	// Map size to preset size
	if (ArgContent == "B" || ArgContent == "b") { SizePreset = bindex; }
	else if (ArgContent == "KB" || ArgContent == "Kb" || ArgContent == "kB" || ArgContent == "kb") { SizePreset = kbindex; }
	else if (ArgContent == "MB" || ArgContent == "Mb" || ArgContent == "mB" || ArgContent == "mb") { SizePreset = mbindex; }
	else if (ArgContent == "GB" || ArgContent == "Gb" || ArgContent == "gB" || ArgContent == "gb") { SizePreset = gbindex; }
	else if (ArgContent == "TB" || ArgContent == "Tb" || ArgContent == "tB" || ArgContent == "tb") { SizePreset = tbindex; }
	else { return ErrorExitSeq(true, 1, "Invalid size unit."); };
	LARGE_INTEGER size;
	size.QuadPart = SizePreset * TargetSize;
	// Debug output
	if (IsDebug) {
		cout << "Current SizePreset: " << SizePreset << endl;
		cout << "TargetSize: " << TargetSize << endl;
		cout << "Size: " << size.QuadPart << endl;
		cout << "FilePath: " << FilePath << endl;
		cout << "IfAppendEnabled: " << IfAppendEnabled << endl;
	}
	// Main filling loop
	SetFilePointer(hFile, size.LowPart, &size.HighPart, FILE_BEGIN);
	SetEndOfFile(hFile);
	if (hFile == INVALID_HANDLE_VALUE) {
		return ErrorExitSeq(true, 1, "^Ignore the upper text. No offense.^ Disk is full halfway");
	}
	CloseHandle(hFile);
	return 0;
}