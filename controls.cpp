#include "controls.h"

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

Controls::Controls()
{
    tcgetattr(STDIN_FILENO,&old_tio);
    new_tio=old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
}

Controls::~Controls()
{
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    tcflush(0, TCIFLUSH);
}

directions Controls::Input()
{
    if (!kbhit()) return NONE;

    int c = getchar();
    directions ans = NONE;

    switch (c) {
        case 'w':
        case 'W':
        ans = UP;
        break;

        case 'a':
        case 'A':
        ans = LEFT;
        break;

        case 's':
        case 'S':
        ans = DOWN;
        break;

        case 'd':
        case 'D':
        ans = RIGHT;
        break;

        case '\033':
        getchar();
        c = getchar();
        switch (c)
        {
            case 'A':
            ans = UP;
            break;

            case 'B':
            ans = DOWN;
            break;

            case 'C':
            ans = RIGHT;
            break;

            case 'D':
            ans = LEFT;
            break;
        }
        break;
    }
    tcflush(0, TCIFLUSH);
    return ans;
}

bool Controls::kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}