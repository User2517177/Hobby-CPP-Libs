#include <windows.h>

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    MessageBox(nullptr, L"WSB Is Not Installed", L"Information", MB_OK | MB_ICONINFORMATION);
    return 0;
}
