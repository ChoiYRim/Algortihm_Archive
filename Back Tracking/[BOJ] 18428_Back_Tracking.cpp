#include <vector>
#include <cstdlib>
#include <iostream>

int N;
int arr[8][8] = {0,}; // student : 1 , teacher : 2 , block : 3
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
std::vector<bool> visit;
std::vector<std::pair<int,int>> student,empty;

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < N)); }

void dfs(int depth)
{
    if(depth >= 3)
    {
        for(int i = 0; i < (int)student.size(); i++)
        {
            int y = student[i].first;
            int x = student[i].second;
            
            for(int j = 0; j < 4; j++)
            {
                for(int dist = 1; ; dist++)
                {
                    int ny = y+dist*dy[j];
                    int nx = x+dist*dx[j];
                    
                    if(!range(ny,nx))
                        break;
                    if(arr[ny][nx] == 3)
                        break;
                    if(arr[ny][nx] == 2)
                        return;
                }
            }
        }
        
        std::cout << "YES" << '\n';
        exit(0);
    }
    
    for(int i = 0; i < (int)empty.size(); i++)
    {
        if(!visit[i])
        {
            visit[i] = true;
            arr[empty[i].first][empty[i].second] = 3;
            dfs(depth+1);
            arr[empty[i].first][empty[i].second] = 0;
            visit[i] = false;
        }
    }
}

int main(int argc,char* argv[])
{
    std::cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            char ch; std::cin >> ch;
            
            if(ch == 'S')
            {
                arr[i][j] = 1;
                student.push_back({i,j});
            }
            else if(ch == 'T')
                arr[i][j] = 2;
            else
                empty.push_back({i,j});
        }
    }
    
    visit = std::vector<bool>(empty.size(),false);
    
    dfs(0);
    
    std::cout << "NO" << '\n';
    return 0;
}
