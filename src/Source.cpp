#define _WIN32_WINNT 0x0500
#include <iostream>
#include <string>
#include <Windows.h>
#include "Header.h"
int main() {

    // Console Window Config.
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 36;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 1000, 750, TRUE);
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);
    COORD new_screen_buffer_size;
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right -
        screenBufferInfo.srWindow.Left + 1;
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom -
        screenBufferInfo.srWindow.Top + 1;
    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
    system("title Chess");

    // Game Begins.
    init.play();
    return 0;
}