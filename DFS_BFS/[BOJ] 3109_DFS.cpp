#include <string>
#include <iostream>

int R,C,ans = 0;
bool Map[50001][501] = {0,};
int dy[3] = {-1,0,1};
int dx[3] = {1,1,1};

inline int MAX(int a,int b) { return (a > b ? a : b); }

inline bool range(int y,int x) { return ((0 <= y && y < R) && (0 <= x && x < C)); }

int dfs(int row,int col)
{
    if(col >= C-1)
        return 1;
    
    for(int i = 0; i < 3; i++)
    {
        int nrow = row+dy[i];
        int ncol = col+dx[i];
        
        if(!range(nrow,ncol))
            continue;
        
        if(!Map[nrow][ncol])
        {
            Map[nrow][ncol] = 1;
            if(dfs(nrow,ncol))
                return 1;
        }
    }
    
    return 0;
}

int main(int argc,char* argv[])
{
    std::cin >> R >> C;
    for(int i = 0; i < R; i++)
    {
        std::string tmp = ""; std::cin >> tmp;
        for(int j = 0; j < C; j++)
        {
            if(tmp[j] != 'x')
                Map[i][j] = 0;
            else
                Map[i][j] = 1;
        }
    }
    
    for(int row = 0; row < R; row++)
        ans += dfs(row,0);
    
    std::cout << ans << '\n';
    return 0;
}
