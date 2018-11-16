#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <valarray>
#include <cstdio>
using namespace std;

pair<int, vector<int>> get_data();
void count_(pair<int, vector<int>> &&data);
void show(valarray<int> &vi);

int main()
{
    count_(get_data());

    return 0;
}

pair<int, vector<int>> get_data()
{
    ifstream fin;
    fin.open("road.in");
    if (!fin.is_open())
    {
        cout << "Can't open file.\n";
        exit(EXIT_FAILURE);
    }

    string tmp;
    vector<string> lines;
    while (fin.good())
    {
        getline(fin, tmp);
        lines.push_back(tmp);
    }

    int Size = stoi(lines[0]);
    vector<int> num;
    tmp.clear();
    for (unsigned i = 0; i < lines[1].size(); ++i)
    {
        if (lines[1][i] != ' ')
            tmp += lines[1][i];
        else if (lines[1][i] == ' ' && !tmp.empty())
        {
            num.push_back(stoi(tmp));
            tmp.clear();
        }
    }
    if (!tmp.empty())
        num.push_back(stoi(tmp));
        
    return make_pair(Size, num);
};

void count_(pair<int, vector<int>> &&data)
{
    int Size = data.first;
    auto num = data.second;

    valarray<int> roads(Size);
    for (int i = 0; i < Size; i++)
        roads[i] = num[i];

    int days = 0;
    while (roads.min() != 0)
    {
        roads -= 1;
        show(roads);
        days++;
    }

    bool flag = false;
    while (true)
    {
        if (!roads.sum())
            break;
        for (int i = 0; i < Size; ++i)
        {
            if (roads[i] != 0)
            {
                roads[i] -= 1;
                flag = true;
            }
            else if (roads[i] == 0 && flag)
                break;
        }
        flag = false;
        days++;
        show(roads);
    }
    cout << days << endl;
}

void show(valarray<int> &vi)
{
    for (auto x: vi)
        cout << x << ' ';
    cout << endl;
}
