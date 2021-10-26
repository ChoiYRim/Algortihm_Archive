#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N,cur = 2;
vector<string> v;
vector<int> result;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < N)); }

int DFS(int y,int x)
{
    int cnt = 1;
    
    v[y][x] = cur+'0';
    for(int i = 0; i < 4; i++)
    {
        int ny = y+dy[i];
        int nx = x+dx[i];
        
        if(range(ny,nx) && v[ny][nx] == '1')
            cnt += DFS(ny,nx);
    }
    
    return cnt;
}

int main(void)
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        v.push_back(tmp);
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(v[i][j] == '1')
            {
                int ret = DFS(i,j);
                result.push_back(ret);
                cur++;
            }
        }
    }
    
    sort(result.begin(),result.end());
    cout << result.size() << '\n';
    for(int i = 0; i < (int)result.size(); i++)
        cout << result[i] << '\n';
    
    return 0;
}
