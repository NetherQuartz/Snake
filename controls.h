#ifndef CONTROLS_H
#define CONTROLS_H

#include "types.h"

#include <termios.h>

class Controls
{
    public:

    Controls();

    ~Controls();

    directions Input();

    void EchoOn();
    void EchoOff();
    void BufferOff();

    menu todo;

    private:

    bool kbhit();
    
    termios old_tio, new_tio;
    unsigned char c;
};

#endif