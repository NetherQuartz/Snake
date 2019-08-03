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
    record *readHighScore();
    std::vector<record> listScores();
    bool comp(const Save::record &lhs, const Save::record &rhs);
};

#endif
