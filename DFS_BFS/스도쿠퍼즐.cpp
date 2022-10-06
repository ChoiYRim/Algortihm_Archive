#include <iostream>
#include <algorithm>

using namespace std;

int map[10][10];
int row[10][10];
int col[10][10];
int box[10][10];

inline int get_index(int r, int c)
{
    return r/3*3+c/3;
}

void input()
{
    for(int r = 0; r < 9; r++)
    {
        for(int c = 0; c < 9; c++)
        {
            int b = get_index(r, c);
                        
            cin >> map[r][c];
            
            row[r][map[r][c]] = 1;
            col[c][map[r][c]] = 1;
            box[b][map[r][c]] = 1;
        }
    }
}

void output()
{
    printf("-------------------\n");
    for(int r = 0; r < 9; r++)
    {
        for(int c = 0; c < 9; c++)
        {
            cout << map[r][c] << " ";
        }
        cout << endl;
    }
}

void solve(int idx)
{
    if(idx >= 81)
    {
        output();
        exit(0);
    }
    
    int r = idx/9;
    int c = idx%9;
    
    if(map[r][c] != 0)
    {
        solve(idx+1);
        return;
    }
    
    for(int i = 1; i < 10; i++)
    {
        int b = get_index(r, c);
        
        if(!row[r][i] && !col[c][i] && !box[b][i])
        {
            row[r][i] = col[c][i] = box[b][i] = 1;
            map[r][c] = i;
            solve(idx+1);
            map[r][c] = 0;
            row[r][i] = col[c][i] = box[b][i] = 0;
        }
    }
}

int main(int argc, char* argv[])
{
    input();
    solve(0);
    return 0;
}
