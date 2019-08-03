#include "save.h"

#include <fstream>
#include <algorithm>
#include <unistd.h>

int Save::readHighScore(std::string username)
{
    for (record rec : listScores())
    {
        if (rec.username == username)
        {
            return rec.score;
        } 
    }
    return 0;
}

Save::record *Save::readHighScore()
{
    std::ifstream in;
    in.open("snake.save", std::ios::binary);

    int score, size;
    std::string username;
    record *rec = new record;
    if (in.read((char *)&score, sizeof(score)))
    {
        in.read((char *)&size, sizeof(size));
        username.resize(size);
        in.read((char *)&username[0], size);
        *rec = {username, score};
    }
    else
    {
        *rec = {"", 0};
    }
    in.close();

    return rec;
}

void Save::writeHighScore(std::string username, int score)
{
    std::vector<record> records = listScores();
    bool found = false;
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].username == username)
        {
            found = true;
            if (score > records[i].score)
            {
                records[i].score = score;
            }
            else
            {
                return;
            }
            break;
        }
    }
    if (!found)
    {
        records.push_back({username, score});
    }
    std::sort(records.begin(), records.end(), comp);

    std::ofstream out;
    out.open("snake.save", std::ios::binary);
    for (int i = 0; i < records.size(); i++)
    {
        out.write((char *)&records[i].score, sizeof(int));
        int size = records[i].username.size();
        out.write((char *)&size, sizeof(size));
        out.write((char *)&records[i].username[0], size);
    }
    out.close();
}

std::vector<Save::record> Save::listScores()
{
    std::ifstream in;
    in.open("snake.save", std::ios::binary);
    std::vector<record> records(0);

    int score, size;
    while (in.read((char *)&score, sizeof(score)))
    {
        in.read((char *)&size, sizeof(size));
        std::string username;
        username.resize(size);
        in.read((char *)&username[0], size);
        records.push_back({username, score});
    }
    in.close();

    return records;
}

bool Save::record::operator<(const record other)
{
    return this->score > other.score;
}

bool Save::comp(const Save::record &lhs, const Save::record &rhs)
{
    return lhs.score > rhs.score;
}
