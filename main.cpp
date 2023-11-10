// Highest Score:
//           99.336

#pragma GCC optimize("O2")
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <chrono>

double getHighestScore()
{
    std::fstream file("./main.cpp");
    file.seekp(22, std::ios_base::beg);
    double ans;
    file >> ans;
    file.close();
    return ans;
}

void setHighestScore(double value)
{
    std::fstream file("./main.cpp");
    file.seekp(22, std::ios_base::beg);
    file << std::setprecision(9) << std::setw(16) << value;
}

const double penalty = 1;
const int oneGameCount = 5;
const int stringLen = 20;
const char *alphabets = "qwertyuiopasdfghjklzxcvbnm ";
int len;

char actual[5005];

int oneGame()
{
    char expected[stringLen];
    for (int i = 0; i < stringLen; i++)
    {
        int idx = std::rand() % len;
        expected[i] = alphabets[idx];
        putchar(alphabets[idx]);
    }
    putchar('\n');
    std::cin.getline(actual, 5000);
    if (actual[0] == 0)
        return -1;
    int correct = 0;
    for (int i = 0; i < stringLen; i++)
    {
        if (actual[i] == 0)
            break;
        correct += expected[i] == actual[i];
    }
    return correct;
}

int main()
{
    srand((unsigned)time(NULL));
    while (alphabets[len] != 0)
        len++;

    std::chrono::steady_clock clock;
    while (true)
    {
        double highestScore = getHighestScore();
        std::cout << "Highest Score: " << highestScore << "s\n";
        int cnt = 1;
        int correct = 0;
        auto start = clock.now();
        for (; cnt <= oneGameCount; cnt++)
        {
            std::cout << cnt << '/' << oneGameCount << '\n';
            int c = oneGame();
            if (c == -1)
                break;
            correct += c;
        }
        auto end = clock.now();
        if (cnt <= oneGameCount)
        {
            std::cout << "Restarting\n";
            continue;
        }
        double time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000;
        double score = time + (oneGameCount * stringLen - correct) * penalty;

        std::cout << "Elapsed Time: " << time << "s ";
        std::cout << "Correctness: " << correct << '/' << oneGameCount * stringLen << '\n';
        std::cout << "Previous Highest Score: " << highestScore << '\n';
        std::cout << "Score: " << score << '\n';
        if (score < highestScore)
            setHighestScore(score);
    }
}