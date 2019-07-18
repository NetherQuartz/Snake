#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <vector>

namespace Save
{
    struct record
    {
        std::string username;
        int score;

        bool operator<(const record);
    };

    int readHighScore(std::string);
    void writeHighScore(std::string, int);
    std::vector<record> listScores();
};

#endif