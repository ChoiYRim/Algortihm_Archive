#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int W,H;
vector<char*> map;

class Map
{
private:
    int W;
    int H;
    vector<pair<int,int>> mirrors;
    vector<char*> map;
    vector<vector<int>> visit;
    const int dy[4] = {-1,0,1,0};
    const int dx[4] = {0,1,0,-1};
    
public:
    Map() : W(0), H(0) { }
    
    void input()
    {
        cin >> W >> H;
        
        map = vector<char*>(H,nullptr);
        visit = vector<vector<int>>(H,vector<int>(W,0x7fffffff));
        for(int i = 0; i < H; i++)
            map[i] = new char[W];
        for(int i = 0; i < H; i++)
        {
            cin >> map[i];
            for(int j = 0; j < W; j++)
            {
                if(map[i][j] == 'C')
                    mirrors.push_back({i,j});
            }
        }
    }
    
    void print_map()
    {
        cout << "\n------------------\n";
        for(int i = 0; i < H; i++)
            cout << map[i] << endl;
    }
    
    inline bool range(int y,int x) { return ((y >= 0 && y < H) && (x >= 0 && x < W)); }
    
    int solve()
    {
        int result = 0;
        int sy = mirrors[0].first;
        int sx = mirrors[0].second;
        
        int ey = mirrors[1].first;
        int ex = mirrors[1].second;
        queue<pair<pair<int,int>,pair<int,int>>> q;
        
        q.push({{sy,sx},{0,-1}});
        visit[sy][sx] = 0;
        while(!q.empty())
        {
            int y = q.front().first.first;
            int x = q.front().first.second;
            int turn = q.front().second.first;
            int dir = q.front().second.second;
            q.pop();
            
            if(y == ey && x == ex)
            {
                result = turn;
                continue;
            }
            
            for(int i = 0; i < 4; i++)
            {
                int ny = y+dy[i];
                int nx = x+dx[i];
                
                if(!range(ny,nx))
                    continue;
                if(map[ny][nx] == '*')
                    continue;
                if(visit[ny][nx] <= turn)
                    continue;
                
                if(dir == -1)
                {
                    visit[ny][nx] = turn;
                    q.push({{ny,nx},{turn,i}});
                }
                else
                {
                    visit[ny][nx] = turn;
                    if(dir == 0 || dir == 2)
                    {
                        if(i == 1 || i == 3)
                        {
                            visit[ny][nx]++;
                            q.push({{ny,nx},{turn+1,i}});
                        }
                        else
                            q.push({{ny,nx},{turn,i}});
                    }
                    else
                    {
                        if(i == 0 || i == 2)
                        {
                            visit[ny][nx]++;
                            q.push({{ny,nx},{turn+1,i}});
                        }
                        else
                            q.push({{ny,nx},{turn,i}});
                    }
                }
            }
        }
        
        return result;
    }
    
    virtual ~Map()
    {
        for(int i = 0; i < H; i++)
        {
            if(map[i] != nullptr)
                delete[] map[i];
        }
    }
};

int main(int argc,char* argv[])
{
    Map map;
    
    map.input();
    //map.print_map();
    cout << map.solve() << endl;
    return 0;
}
