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

    private:

    bool kbhit();
    
    termios old_tio, new_tio;
    unsigned char c;
};

#endif