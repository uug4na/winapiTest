#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <fstream>
#include <string>
#include "dirent.h"
#include <sys/types.h>
#define FILE_MENU_NEW 1
#define ENC_BUTTON 123
#define DEC_BUTTON 69
using namespace std;


void encrypt(string fileName) {
    char fileName[30], ch;
    fstream fin, fout;
    cout << "Encrypting:)";
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
    cout << "donekk: " << fileName << endl;
}

void getFile() {
    DIR* dr;
    struct dirent* en;
    dr = opendir("."); //open all directory
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            encrypt(en->d_name);
            cout << " \n" << en->d_name; //print all directory name
        }
        closedir(dr); //close all directory
    }
}

void decrypt() {
    cout << "decrypting kk:)" << endl;
}

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void Menus(HWND hWnd);
void button(HWND);
HMENU hMenu;


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
        case ENC_BUTTON:
            getFile();
            break;
        case DEC_BUTTON:
            getFile();
        }
        break;
    case WM_CREATE:
        Menus(hWnd);
        button(hWnd);
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

void Menus(HWND hWnd)
{
    hMenu = CreateMenu();

    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, L"Connect");
    AppendMenu(hSubMenu, MF_STRING, NULL, L"Host");

    AppendMenu(hFileMenu, MF_STRING, 1, L"Encrypt");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Room");
    AppendMenu(hFileMenu, MF_STRING, 4, L"Exit");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"Menu");
    AppendMenu(hMenu, MF_STRING, 2, L"Help");
    SetMenu(hWnd, hMenu);
}

void button(HWND hWnd)
{
    CreateWindowW(
        L"BUTTON", L"Encrypt", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10,40,130,100,hWnd,(HMENU)ENC_BUTTON,       
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),NULL);    
    CreateWindowW(
        L"BUTTON", L"Decrypt", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150,40, 130, 100, hWnd, (HMENU)DEC_BUTTON,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
}

