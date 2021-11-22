#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

bool row[9][10] = {0,};
bool col[9][10] = {0,};
bool box[9][10] = {0,};
int board[16][16] = {0,};
vector<pair<int,int>> pos;

void print_board()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
            cout << board[i][j] << ' ';
        cout << '\n';
    }
}

void DFS(int idx)
{
    if(idx >= (int)pos.size())
    {
        print_board();
        exit(0);
    }
    
    int y = pos[idx].first;
    int x = pos[idx].second;
    int b = (y/3)*3+x/3;
    
    for(int i = 1; i <= 9; i++)
    {
        if(!row[y][i] && !col[x][i] && !box[b][i])
        {
            row[y][i] = col[x][i] = box[b][i] = true;
            board[y][x] = i;
            DFS(idx+1);
            board[y][x] = 0;
            row[y][i] = col[x][i] = box[b][i] = false;
        }
    }
}

int main()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            int b = (i/3)*3+j/3;
            
            cin >> board[i][j];
            if(!board[i][j])
                pos.push_back({i,j});
            
            row[i][board[i][j]] = true;
            col[j][board[i][j]] = true;
            box[b][board[i][j]] = true;
        }
    }
    
    DFS(0);
    return 0;
}
