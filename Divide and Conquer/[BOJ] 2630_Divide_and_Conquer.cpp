#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<vector<int>> map;

pair<int, int> check(int ly, int lx, int ry, int rx)
{
    int color = map[ly][lx], cnt = 0;
    int flag = color+1;
    
    for(int y = ly; y < ry && flag; y++)
    {
        for(int x = lx; x < rx; x++)
        {
            if(map[y][x] != color)
            {
                flag = 0;
                break;
            }
            else cnt++;
        }
    }
    
    return {flag, cnt};
}

pair<int, int> count(int ly, int lx, int ry, int rx)
{
    if(ly == ry && lx == rx)
    {
        return (map[ly][lx] == 0 ? make_pair(1, 0) : make_pair(0, 1));
    }
    
    pair<int, int> result = {0, 0};
    pair<int, int> ret = check(ly, lx, ry, rx);
    
    if(ret.first != 0)
        return (ret.first == 1 ? make_pair(1, 0) : make_pair(0, 1));
    
    ret = count(ly, lx, (ly+ry)/2, (lx+rx)/2);
    result.first += ret.first; result.second += ret.second;
    
    ret = count(ly, (lx+rx)/2, (ly+ry)/2, rx);
    result.first += ret.first; result.second += ret.second;
    
    ret = count((ly+ry)/2, lx, ry, (lx+rx)/2);
    result.first += ret.first; result.second += ret.second;
    
    ret = count((ly+ry)/2, (lx+rx)/2, ry, rx);
    result.first += ret.first; result.second += ret.second;
    
    return result;
}

void input()
{
    cin >> N;
    map = vector<vector<int>>(N, vector<int>(N, 0));
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
            cin >> map[y][x];
    }
}

int main(int argc, char* argv[])
{
    input();
    auto result = count(0, 0, N, N);
    cout << result.first << endl;
    cout << result.second << endl;
    return 0;
}
