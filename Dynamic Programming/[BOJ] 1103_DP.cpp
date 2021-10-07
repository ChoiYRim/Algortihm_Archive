#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

#define IN(y,x,Y,X) ((0 <= y && y < Y) && (0 <= x && x < X))

int N,M;
int dp[51][51] = {0,};
int Map[51][51] = {0,};
bool visit[51][51] = {0,};

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

int DFS(int y,int x)
{
    if(!IN(y,x,N,M) || !Map[y][x])
        return 0;
    if(visit[y][x])
    {
        std::cout << -1 << '\n';
        exit(0);
    }
    if(dp[y][x])
        return dp[y][x];
    
    visit[y][x] = true;
    int value = Map[y][x];
    
    for(int i = 0; i < 4; i++)
    {
        int ny = y+value*dy[i];
        int nx = x+value*dx[i];
        
        dp[y][x] = std::max(dp[y][x],DFS(ny,nx)+1);
    }
    
    visit[y][x] = false;
    return dp[y][x];
}

int main(int argc,char* argv[])
{
    std::cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        std::string str = ""; std::cin >> str;
        for(int j = 0; j < (int)str.length(); j++)
        {
            if(str[j] == 'H')
                Map[i][j] = 0;
            else
                Map[i][j] = str[j]-'0';
        }
    }
    
    std::cout << DFS(0,0) << '\n';
    return 0;
}
