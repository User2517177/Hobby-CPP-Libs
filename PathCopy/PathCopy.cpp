#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

//Nah ChatGPT Based Stuff
int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "No data to be copied." << endl;
        return 1;
    }
    string contentWithQuotes = "\"" + string(argv[1]) + "\"";
    const char* clipboardData = contentWithQuotes.c_str();
    if (!OpenClipboard(nullptr)) {
        cerr << "Failed to open clipboard" << endl;
        return 1;
    }
    if (!EmptyClipboard()) {
        cerr << "Failed to empty clipboard" << endl;
        CloseClipboard();
        return 1;
    }
    size_t textLength = strlen(clipboardData) + 1;
    HGLOBAL clipboardDataHandle = GlobalAlloc(GMEM_MOVEABLE, textLength);
    if (!clipboardDataHandle) {
        cerr << "Failed to allocate global memory" << endl;
        CloseClipboard();
        return 1;
    }
   char* pGlobal = static_cast<char*>(GlobalLock(clipboardDataHandle));
    if (!pGlobal) {
        cerr << "Failed to lock global memory" << endl;
        GlobalFree(clipboardDataHandle);
        CloseClipboard();
        return 1;
    }
    memcpy(pGlobal, clipboardData, textLength);
    GlobalUnlock(clipboardDataHandle);
    if (!SetClipboardData(CF_TEXT, clipboardDataHandle)) {
        cerr << "Failed to set clipboard data" << endl;
        GlobalFree(clipboardDataHandle);
        CloseClipboard();
        return 1;
    }
    CloseClipboard();
    cout << "Text copied to clipboard: " << clipboardData << endl;
    return 0;
}