#include <queue>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

struct Pos
{
    int y;
    int x;
};

enum Direction
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};

int R,C;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
vector<string> Map;
vector<Pos> sheep,wolf;

inline bool range(int y,int x) { return ((0 <= y && y < R) && (0 <= x && x < C)); }

void print(bool possible)
{
    cout << possible << '\n';

    if(possible)
    {
        for(int y = 0; y < R; y++)
            cout << Map[y] << '\n';
    }
}

int main()
{
    cin >> R >> C;
    for(int i = 0; i < R; i++)
    {
        string tmp; cin >> tmp;
        for(int j = 0; j < (int)tmp.length(); j++)
        {
            if(tmp[j] == 'S')
                sheep.push_back({i,j});
            if(tmp[j] == 'W')
                wolf.push_back({i,j});
        }
        Map.push_back(tmp);
    }
    
    for(int i = 0; i < (int)sheep.size(); i++)
    {
        int y = sheep[i].y;
        int x = sheep[i].x;
        
        for(int dir = NORTH; dir <= WEST; dir++)
        {
            int ny = y+dy[dir];
            int nx = x+dx[dir];
            
            if(range(ny,nx) && Map[ny][nx] != 'S')
            {
                if(Map[ny][nx] == 'W')
                {
                    print(false);
                    exit(0);
                }
            }
        }
    }
    
    for(int i = 0; i < (int)sheep.size(); i++)
    {
        int y = sheep[i].y;
        int x = sheep[i].x;
        
        for(int dir = NORTH; dir <= WEST; dir++)
        {
            int ny = y+dy[dir];
            int nx = x+dx[dir];
            
            if(range(ny,nx) && Map[ny][nx] == '.')
                Map[ny][nx] = 'D';
        }
    }
    
    print(true);
    return 0;
}
