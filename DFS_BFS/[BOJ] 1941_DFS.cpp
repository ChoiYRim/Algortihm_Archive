#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int result = 0;
vector<int> check(25);
vector<string> map(5);
vector<pair<int,int>> pos(7);

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

bool range(int y, int x) { return ((y >= 0 && y < 5) && (x >= 0 && x < 5)); }

void input()
{
    for(int i = 0; i < 5; i++)
    {
        string tmp; cin >> tmp;
        map[i] = tmp;
    }
}

void dfs(int depth, int cur)
{
    if(depth == 7)
    {
        int S = 0, Y = 0, cnt = 0;
        queue<pair<int, int>> q;
        vector<bool> pick(depth, 0);
        
        pick[0] = 1;
        q.push({pos[0].first, pos[0].second});
        while(!q.empty())
        {
            cnt++;
            int y = q.front().first;
            int x = q.front().second;
            q.pop();
            
            if(map[y][x] == 'S') S++;
            else Y++;
            
            for(int i = 0; i < 4; i++)
            {
                int ny = y+dy[i];
                int nx = x+dx[i];
                
                if(!range(ny, nx)) continue;
                
                for(int j = 0; j < depth; j++)
                {
                    if(pick[j])
                        continue;
                    if(pos[j].first == ny && pos[j].second == nx)
                    {
                        q.push({ny, nx});
                        pick[j] = 1;
                    }
                }
            }
        }
        if(cnt == 7 && S > Y)
        {
//            for(int i = 0; i < depth; i++)
//            {
//                printf("[%d,%d] ", pos[i].first, pos[i].second);
//            }
//            printf("\n");
            result++;
        }
        return;
    }
    
    for(int i = cur; i < 25; i++)
    {
        if(check[i]) continue;
        
        int y = i/5;
        int x = i%5;
        
        check[i] = 1;
        pos[depth] = {y, x};
        dfs(depth+1, i+1);
        check[i] = 0;
    }
}

int main(int argc, char* argv[])
{
    input();
    dfs(0, 0);
    cout << result << endl;
    return 0;
}
