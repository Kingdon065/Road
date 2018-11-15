#include "Test.h"
#include <fstream>
#include <valarray>
#include <cstdio>

pair<int, vector<int>> get_data();
void count(pair<int, vector<int>> &&data);
void show(valarray<int> &vi);

int main()
{
    count(get_data());

    return 0;
}

pair<int, vector<int>> get_data()
{
    ifstream fin;
    fin.open("../road.in");
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

    int Size;
    sscanf(lines[0].c_str(), "%d", &Size);
    vector<int> num;
    int n;
    tmp.clear();
    for (int i = 0; i < lines[1].size(); ++i)
    {
        if (lines[1][i] != ' ')
            tmp += lines[1][i];
        else if (lines[1][i] == ' ' && !tmp.empty())
        {
            sscanf(tmp.c_str(), "%d", &n);
            num.push_back(n);
            tmp.clear();
        }
    }
    if (!tmp.empty())
    {
        sscanf(tmp.c_str(), "%d", &n);
        num.push_back(n);
    }
    return make_pair(Size, num);
};

void count(pair<int, vector<int>> &&data)
{
    int Size = data.first;
    auto num = data.second;

    valarray<int> roads(Size);
    for (int i = 0; i < Size; i++)
        roads[i] = num[i];

    int days = 0;
    vector<int> index;
    while (roads.min() != 0)
    {
        roads -= 1;
        days++;
    }
    while (true)
    {
        if (!roads.sum())
            break;
        for (int i = 0; i < Size; ++i)
        {
            if (roads[i] != 0)
                index.push_back(i);
            else if (roads[i] == 0 && !index.empty())
                break;
        }
        for (auto x: index)
            roads[x] -= 1;
        index.clear();
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
