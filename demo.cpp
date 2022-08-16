#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#define FILE_MENU_NEW 1
using namespace std;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void Menus(HWND hWnd);
void AddText(HWND);

HMENU hMenu; // global scope

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {
        case 1:
            MessageBeep(MB_OK);
            break;
        case 2:
            MessageBeep(MB_HELP);
            break;
        case 4:
            DestroyWindow(hWnd);
            break;
        }

        break;
    case WM_CREATE:
        Menus(hWnd);
        AddText(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

int WINAPI main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = { 0 };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"workPlease";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"workPlease", L"Windowontsor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
        NULL, NULL, NULL, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// menus
void Menus(HWND hWnd)
{
    hMenu = CreateMenu();

    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, L"Connect");
    AppendMenu(hSubMenu, MF_STRING, NULL, L"Host");

    AppendMenu(hFileMenu, MF_STRING, 1, L"Name");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Room");
    AppendMenu(hFileMenu, MF_STRING, 4, L"Exit");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"Menu");
    AppendMenu(hMenu, MF_STRING, 2, L"Help");
    SetMenu(hWnd, hMenu);
}

void AddText(HWND hWnd)
{
    CreateWindowW(L"workPlease", L"lma0", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 100, 100, 50,
        hWnd, NULL, NULL, NULL);
}

void encrypt() {
    char fileName[30], ch;
    fstream fin, fout;
    cout << "Enter File NAme:)";
    cin >> fileName;
    fin.open(fileName, fstream::in);
    if (!fin)
        cout << "errorrRR:RL:)";
    fout.open("enc.txt", fstream::out);
    while (fin >> noskipws >> ch) {
        ch += 100;
        fout << ch;
    }
    fin.close();
    fout.close();
    fin.open(fileName, fstream::out);
    fout.open("enc.txt", fstream::in);
    while (fout >> noskipws >> ch) {
        fin << ch;
    }
    fin.close();
    fout.close();
    cout << "donekk:" << fileName << endl;
}

