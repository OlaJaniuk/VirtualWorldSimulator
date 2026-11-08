#ifndef POBIERZZNAK_H
#define POBIERZZNAK_H

#include <termios.h>
#include <unistd.h>
#include <iostream>

class PobierzZnak {
public:
    // Metoda statyczna - nie potrzebuje obiektu, by działać
    // potrzebna na MacOS bo nie ma tu _getch() jak na Windows
    static int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
};

#endif