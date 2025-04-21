#pragma once
#include <string>
#include <vector>
namespace ApplesGames
{
    struct Record
    {
        std::string name;
        int score;
    };

    // ������ ���������� ����������� ������
    extern std::vector<Record> leaderboard;
    void SortLeaderboard(std::vector<Record>& records);
}
