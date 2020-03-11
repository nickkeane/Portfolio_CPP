#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#if defined(__MINGW__) || defined(_WIN64)
#include <conio.h>
#elif defined(__LINUX__)
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Set STD.IN settings to nonblocking and to not echo typed chars, 
    // and store old values
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
#endif

#include "ToDo.h"

using namespace std;

int main() {
    ToDo tc;

    bool bNum = false;
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code!"};
    for (const string& word : msg) {
        cout << word << " ";
    }
    cout << endl;

    cout << this_thread::get_id() << endl;
    cout << "Press any key to continue..." << endl;
    while(!kbhit()) this_thread::sleep_for(chrono::milliseconds(200));

    return 0;
}